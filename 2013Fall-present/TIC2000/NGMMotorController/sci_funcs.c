#include "sci_funcs.h"

#define TX_WAIT_CYCLES 100e3L
#define RX_WAIT_CYCLES 150e3L

char scia_receive_buffer[17];
Uint32 txrxWaitCycles;


/**
 * \brief Transmit a string from the SCI-A pins. DOES NOT SEND End-Of-Line or Carriage-Return!
 *        Wait for the other end to repeat the characters back to us, verifying the transmission!
 * \warning Only ASCII characters with ASCII values 0<v<255 can be transmitted!
 * \return +1 OK
 * \return -1 Error sending, or echo error.
 */
signed char scia_transmit_string_echo(char *transmit_string)
{
	//char string[32];
	//sprintf(string, "TXe '%s'", transmit_string);
	//puts(string);

	Uint16 i;
	for (i = 0; i < strlen(transmit_string); i++) {
		int status = scia_send_char_wait_for_echo(transmit_string[i]);
		if (status != 1) {

			char str[32];
			sprintf(str, "Transmit status: %i", status);
			puts(str);
			return -1;
		}
	}
	return 1; // Success!
}

/**
 * \brief Transmit end-of-line and carriage-return via SCI-A.
 * \return +1 OK
 * \return -1 Error sending, or echo error.
 */
signed char scia_send_eol_cr_echo() {
	if (scia_send_char_wait_for_echo(10) != 1) return -1; // Send EOL
	if (scia_send_char_wait_for_echo(13) != 1) return -1; // Send carriage return character (\r)
	return 1;
}

/**
 * \brief Transmit a character from SCI-A. **Wait for an echo'd character from the other end!**
 *        This function must be very thorough in error-checking, because of E/M interference near
 *        the motor!
 * \warning If the other end doesn't echo back, error will be triggered!
 * \return +1 : OK; echo received correctly.
 * \return -1 : Sending timeout
 * \return -2 : Receive timeout
 * \return -3 : SCI Receive error: Break detect, framing error, or overrun detected! Recommended: reset SCI.
 * \return -4 : SCI FIFO overflow! Recommend: reset FIFO.
 * \return -5 : SCI FIFO frame error!
 * \return -6 : Received character =//= sent character (probably due to noise/interference on RS-232 line)
 */
signed char scia_send_char_wait_for_echo(char sendChar) {
	char receivedChar;
	if (scia_send_char(sendChar) != 1) return -1;

	// Wait for echo...
	txrxWaitCycles = 0;
	while (SciaRegs.SCIFFRX.bit.RXFFST == 0) {
		// Wait while receive FIFO is empty or no byte has been received.
		if (txrxWaitCycles >= RX_WAIT_CYCLES)
			return -2;
		txrxWaitCycles++;
	}

	receivedChar = SciaRegs.SCIRXBUF.all; // MUST BE READ *IMMEDIATELY* AFTER READY!
	// Check for receive errors:
	if (SciaRegs.SCIRXST.bit.RXERROR == 1) return -3;
	if (SciaRegs.SCIFFRX.bit.RXFFOVF == 1) return -4;
	if (SciaRegs.SCIRXBUF.bit.SCIFFFE == 1) return -5;

	//char str[32];
	//sprintf(str, "Sent %c, Received %c", sendChar, receivedChar);
	//puts(str);

	if (sendChar == receivedChar) return 1; // Verify echo.
	return -6;
}

/**
 * \brief Transmit a string from the SCI-A pins. DOES NOT SEND End-Of-Line or Carriage-Return!
 * \warning Doesn't wait for echo back!
 * \return +1 OK
 * \return -1 Error sending, or echo error.
 */
signed char scia_transmit_string(char *transmit_string)
{
	Uint16 i;
	for (i = 0; i < strlen(transmit_string); i++) {
		if (scia_send_char(transmit_string[i]) != 1)
			return -1; // Error sending this character.
	}
	//char string[32];
	//      sprintf(string, "TX '%s'", transmit_string);
	//      puts(string);
	return 1; // Success!
}

/**
 * \brief Transmit a character from SCI-A. Don't wait for an echo!
 * \warning This is unreliable, since there is no echo!
 * \return +1 OK
 * \return -1 Couldn't send or no/wrong echo received.
 */
signed char scia_send_char(char sendChar) {
	txrxWaitCycles = 0;
	while (SciaRegs.SCIFFTX.bit.TXFFST != 0 || SciaRegs.SCICTL2.bit.TXEMPTY != 1) {
		// Wait till transmit FIFO is empty, transmit buffer is empty.
		if (txrxWaitCycles >= TX_WAIT_CYCLES)
			return -1;
		txrxWaitCycles++;
	}
	SciaRegs.SCITXBUF = (Uint16)sendChar; // Transmit character.

	// Wait for character to be sent...
	txrxWaitCycles = 0;
	while (SciaRegs.SCIFFTX.bit.TXFFST != 0 || SciaRegs.SCICTL2.bit.TXEMPTY != 1) {
		// Wait till transmit FIFO is empty, transmit buffer is empty.
		if (txrxWaitCycles >= TX_WAIT_CYCLES)
			return -1;
		txrxWaitCycles++;
	}
	return 1;
}

/**
 * \brief Receive a string from the SCI-A module. Assumes the received string ends with
 *        the carriage-return (CR) character. The result is stored in global variable scia_receive_buffer.
 * \return the status of the receive operation:
 * \return +1 : OK
 * \return -1 : Receive timeout (waited too long w/ no response.)
 * \return -2 : Received string was >16 bytes; unexpected behavior.
 * \return -3 : SCI Receive error: Break detect, framing error, or overrun detected! Recommended: reset SCI.
 * \return -4 : SCI FIFO overflow! Recommend: reset FIFO.
 * \return -5 : SCI FIFO frame error!
 */
signed char scia_receive_string() {
	int c = 0;
	char receivedChar;
	while (c < 16) { // Limit received characters to 16 to prevent infinite loop.
		txrxWaitCycles = 0;
		while (SciaRegs.SCIFFRX.bit.RXFFST == 0 /*|| SciaRegs.SCIRXST.bit.RXRDY != 1*/) {
			// Wait while receive FIFO is empty or no byte has been received.
			if (txrxWaitCycles >= RX_WAIT_CYCLES)
				return -1;
			txrxWaitCycles++;
		}
		receivedChar = SciaRegs.SCIRXBUF.all; // Store read character.

		if (receivedChar == '\n' && c >= 2) { // \n has to be at least the 3rd char
			scia_receive_buffer[c] = '\0'; // Terminate string properly.
			return 1; // String terminated as expected
		}
		scia_receive_buffer[c] = receivedChar;
		c++; // Haha, we are using only C.
	}
	// Check for receive errors:
	if (SciaRegs.SCIRXST.bit.RXERROR == 1) return -3;
	if (SciaRegs.SCIFFRX.bit.RXFFOVF == 1) return -4;
	if (SciaRegs.SCIRXBUF.bit.SCIFFFE == 1) return -5;
	return -2; // The string was longer than 16 bytes, unexpected!
}

/**
 * \brief Initalize the SCI FIFO.
 */
void scia_fifo_init()
{
	SciaRegs.SCIFFTX.all=0xE040;
	SciaRegs.SCIFFRX.all=0x2044;
	SciaRegs.SCIFFCT.all=0x0;
}

/**
 * \brief Initialize SCI-A pins on microcontroller.
 */
void scia_init()
{
	// Note: Clocks were turned on to the SCIA peripheral
	// in the InitSysCtrl() function


	SciaRegs.SCICCR.all =0x7;   // 1 stop bit,  No loopback
	// No parity, 8 char bits,
	// async mode, idle-line protocol
	SciaRegs.SCICTL1.all =0x0003;  // enable TX, RX, internal SCICLK,
	// Disable RX ERR, SLEEP, TXWAKE
	SciaRegs.SCICTL2.all =0x0;

	// BAUD RATE REGISTERS:
	// SPI BAUD RATE = LSPCLK / (SCIHBAUD<<8 + SCILBAUD + 1) / 8. For SYSCLKOUT=90MHz, LOSPCLK=about 22.5MHz = 90MHz/4
	//SciaRegs.SCIHBAUD    =0x0000;
	//SciaRegs.SCILBAUD    =0x0017; // Uncomment for 115200 baud
	SciaRegs.SCIHBAUD    =0;
	SciaRegs.SCILBAUD    =146; // 19200 baud @ 90MHz clk (fastest motor will go)
	//SciaRegs.SCILBAUD = 114; // 19200 @ 70 MHz clk

	SciaRegs.SCICTL1.all =0x0023;     // Relinquish SCI from Reset
}
