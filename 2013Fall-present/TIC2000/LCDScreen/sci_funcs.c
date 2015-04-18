#include "sci_funcs.h"

#define TX_WAIT_CYCLES 100e3L

Uint32 txrxWaitCycles;

/**
 * \brief Transmit a string from the SCI-A pins.
 * \return +1 OK
 * \return -1 Error sending, or echo error.
 */
signed char scia_transmit_string(char *transmit_string)
{
	Uint16 i;
	for (i = 0; i < strlen(transmit_string); i++) {
		if (scia_xmit(transmit_string[i]) != 1)
			return -1; // Error sending this character.
	}
	//char string[32];
	//      sprintf(string, "TX '%s'", transmit_string);
	//      puts(string);
	return 1; // Success!
}

/**
 * \brief Transmit a character from SCI-A. Don't wait for an echo!
 * \return +1 OK
 * \return -1 Couldn't send or no/wrong echo received.
 */
signed char scia_xmit(char sendChar) {
	txrxWaitCycles = 0;
	while (SciaRegs.SCIFFTX.bit.TXFFST != 0) {
		// Wait till transmit FIFO is empty, transmit buffer is empty.
		if (txrxWaitCycles >= TX_WAIT_CYCLES)
			return -1;
		txrxWaitCycles++;
	}
	SciaRegs.SCITXBUF = sendChar; // Transmit character.

	// Wait for character to be sent...
	txrxWaitCycles = 0;
	while (SciaRegs.SCIFFTX.bit.TXFFST != 0) {
		// Wait till transmit FIFO is empty, transmit buffer is empty.
		if (txrxWaitCycles >= TX_WAIT_CYCLES)
			return -1;
		txrxWaitCycles++;
	}
	return 1;
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

	SciaRegs.SCICCR.all =0x0007;   // 1 stop bit,  No loopback
	// No parity, 8 char bits,
	// async mode, idle-line protocol
	SciaRegs.SCICTL1.all =0x0003;  // enable TX, RX, internal SCICLK,
	// Disable RX ERR, SLEEP, TXWAKE
	SciaRegs.SCICTL2.all =0x0003;
	SciaRegs.SCICTL2.bit.TXINTENA =0; // Disable TX interrupt
	SciaRegs.SCICTL2.bit.RXBKINTENA =0; // Disable RX interrupt

	// BAUD RATE REGISTERS:
	// SPI BAUD RATE = LSPCLK / (SCIHBAUD<<8 + SCILBAUD + 1) / 8. For SYSCLKOUT=90MHz, LOSPCLK=about 22.5MHz = 90MHz/4
	SciaRegs.SCIHBAUD    =0x0000;
	SciaRegs.SCILBAUD    =0x0017; // 115200 baud

	SciaRegs.SCICCR.bit.LOOPBKENA =0; // Disable loop back (internal connection TX-RX)
	SciaRegs.SCICTL1.all =0x0023;     // Relinquish SCI from Reset
}
