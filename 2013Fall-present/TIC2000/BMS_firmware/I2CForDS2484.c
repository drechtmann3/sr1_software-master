/*
 * I2CForDS2484.c
 *
 *  Created on: Apr 5, 2014
 *      Author: Alex Popescu
 */
#include "BMS.h"

// Read a data byte from the I2C line. Assumes you already sent a start condition with read mode enabled!
// NACKSTOPTreatment specification:
// 0 -> After read, send ACK bit
// 1 -> After read, send NACK bit
// 2 -> After read, send NACK bit and STOP condition
Uint16 i2c_read_data_byte(char NACKSTOPTreatment) {
	if (NACKSTOPTreatment == 1)
		I2caRegs.I2CMDR.bit.NACKMOD = 1; // Send NACK after this byte is received.
	else if (NACKSTOPTreatment == 2)
		I2caRegs.I2CMDR.bit.STP = 1; // Send NACK + STOP signals after this byte is received.

	if (I2caRegs.I2CSTR.bit.RSFULL == 1) {
		puts("FOUND OVERFLOW WHEN READING");
		Uint16 byte = I2caRegs.I2CDRR;
		char string[32];
		sprintf(string, "UNCLAIMED BYTE: 0x%x", byte);
		puts(string);
	}

	Uint32 read_tries = 0;
	Uint32 MAX_READ_TRIES = 50000;
	while(I2caRegs.I2CSTR.bit.RRDY != 1 && read_tries < MAX_READ_TRIES) // Wait for receive buffer to be filled, a hardware error occurred if we don't receive anything!
		read_tries++;

	if (I2caRegs.I2CSTR.bit.ARBL == 1) {
		puts("Arbitration lost in transmission!");
		I2caRegs.I2CMDR.bit.STP = 1; // Attempt to stop transaction.
		return 0;
	}

	Uint16 readData = I2caRegs.I2CDRR;

	Uint16 dummyRead = 0;
	if (NACKSTOPTreatment != 0) {
		dummyRead = I2caRegs.I2CDRR; // We have to do another "dummy" read to get the NACK generated, though no data actually is sent via I2C lines here.
	}

	if (NACKSTOPTreatment == 1) {
		//puts("NACK sent.");
	} else if (NACKSTOPTreatment == 2) {
		while (I2caRegs.I2CMDR.bit.STP != 0); // Wait for stop condition to be generated.
		while (I2caRegs.I2CMDR.bit.MST != 0); // The MST bit goes to 0 after STOP generated.
		while (I2caRegs.I2CSTR.bit.BB != 0); // Wait for bus to NOT be busy.
		//puts("Stop condition sent.");
	}

	return readData + 0*dummyRead; // Return the read data.
}

// Send a command/data byte over the I2C Line. A START condition must have been sent first!
// Returns 1 if successful, 0 otherwise.
char i2c_send_data_byte(Uint16 data) {
	//if (I2caRegs.I2CSTR.bit.XSMT == 0)
	//	puts("Transmit register underflow!");

	// Wait to be ready to transmit data byte:
	while (I2caRegs.I2CSTR.bit.XRDY != 1 && I2caRegs.I2CSTR.bit.ARDY != 1); // ARDY will be set instead of XRDY if a NACK is received.
	// Check if data was received/acknowledged:
	if (I2caRegs.I2CSTR.bit.NACK == 1) {
		puts("NACK bit received in transmit! Aborting transmit...");
		I2caRegs.I2CMDR.bit.STP = 1; // Send STOP condition.
		I2caRegs.I2CSTR.bit.NACK = 1; // Reset NACK bit.
		return 0;
	}

	I2caRegs.I2CDXR = data; // Transmit data.

	Uint32 SEND_TIMEOUT = 1e5;
	Uint32 send_tries = 0;
	while (I2caRegs.I2CSTR.bit.ARDY != 1 && send_tries < SEND_TIMEOUT) send_tries++; // ARDY is set after the byte is actually sent, in repeat mode.
	if (send_tries >= SEND_TIMEOUT) return 0; // We waited, but the data was not sent! Error!

	return 1;
}

// Send start condition over I2C Line. Then, send device address to read/write from.
// rwbit: Write = 0, Read = 1 (to/from slave device(s))
// Returns 1 if successful, 0 otherwise.
char i2c_send_start_and_slave_address(Uint16 slave_address, int rwbit) {
	//puts("Starting transmission...");
	// Wait to be ready...
	Uint32 wait_counts = 0;
	Uint32 MAX_WAIT_COUNTS = 1e6;
	while(I2caRegs.I2CMDR.bit.STP != 0 && wait_counts < MAX_WAIT_COUNTS) // Wait for stop to clear.
		wait_counts++;
	if (wait_counts >= MAX_WAIT_COUNTS) return 0; // We were not able to generate a start condition; the bus wasn't clear!

	I2caRegs.I2CSAR = slave_address; // Save slave address to transmit.

	I2caRegs.I2CMDR.bit.NACKMOD = 0; // The I2C module sends an ACK bit during each acknowledge cycle until the internal data counter counts down to 0. At that point, the I2C module sends a NACK bit to the transmitter. To have a NACK bit sent earlier, you must set the NACKMOD bit.
	I2caRegs.I2CMDR.bit.FREE = 0; // When there is a breakpoint, stop I2C.
	I2caRegs.I2CMDR.bit.MST = 1; // The I2C module is a master and generates the serial clock on the SCL pin.
	if (rwbit == 0)
		I2caRegs.I2CMDR.bit.TRX = 1; // When r/w bit is 0, we are transmitting to slave
	else
		I2caRegs.I2CMDR.bit.TRX = 0; // When r/w bit is 1, we are receiving from slave.
	I2caRegs.I2CMDR.bit.XA = 0; // Use standard 7-bit slave address.
	I2caRegs.I2CMDR.bit.RM = 1; // Keep sending every time a byte is written to I2CDXR, when transmitting. Send a ACK bit every time a byte is received.
	I2caRegs.I2CMDR.bit.DLB = 0; // Disable loopback mode.
	I2caRegs.I2CMDR.bit.STB = 0; // No special start mode.
	I2caRegs.I2CMDR.bit.FDF = 0; // No free data format
	I2caRegs.I2CMDR.bit.BC = 0; // Set to 8-bit bytes.

	I2caRegs.I2CMDR.bit.STT = 1; // Generate a start condition on the I2C bus, and send the slave address with r/w.

	// Check if ACK was received:
	if (I2caRegs.I2CSTR.bit.NACK == 1) {
		puts("Sent address was not acknowledged! NACK (no acknowledgment bit received)!");
		I2caRegs.I2CMDR.bit.STP = 1; // Send STOP condition.
		I2caRegs.I2CSTR.bit.NACK = 1; // Reset NACK bit.
		return 0;
	}
	if (I2caRegs.I2CSTR.bit.ARBL == 1) {
		puts("Arbitration lost in transmission!");
		I2caRegs.I2CMDR.bit.STP = 1; // Stop transaction.
		return 0;
	}

	if (I2caRegs.I2CSTR.bit.RRDY == 1) {
		puts("That's funny: in start func, data received!? You coded something wrong!"); // This shouldn't happen.
		Uint16 byte = I2caRegs.I2CDRR;
		char string[32];
		sprintf(string, "READ BYTE: 0x%x", byte);
		puts(string);
		return 0;
	}

	if (I2caRegs.I2CSTR.bit.RSFULL == 1) { // This happens when a byte was received, but not read by CPU.
		while (I2caRegs.I2CSTR.bit.RRDY != 1);
		puts("I2C READ BUFFER OVERFLOW ON START");
		Uint16 byte = I2caRegs.I2CDRR;
		char string[32];
		sprintf(string, "UNCLAIMED BYTE: 0x%x", byte);
		puts(string);
	}

	//puts("Finished starting transmission");
	return 1;
}

// Initialize I2C on microcontroller.
// This should be called in the initialization stages as the microcontroller is starting up, after InitSysCtrl().
void i2c_init(void) {
	EALLOW;
	 SysCtrlRegs.PCLKCR0.bit.I2CAENCLK = 1;     // I2C-A CLK
	/* Enable internal pull-up for the selected pins */
	GpioCtrlRegs.GPAPUD.bit.GPIO28 = 0;    // Enable pull-up for GPIO28 (SDAA)
	GpioCtrlRegs.GPAPUD.bit.GPIO29 = 0;    // Enable pull-up for GPIO29 (SCLA)
	/* Set qualification for selected pins to asynch only */
	// This will select asynch (no qualification) for the selected pins.
	// Comment out other unwanted lines.
	GpioCtrlRegs.GPAQSEL2.bit.GPIO28 = 3;  // Asynch input GPIO28 (SDAA)
	GpioCtrlRegs.GPAQSEL2.bit.GPIO29 = 3;  // Asynch input GPIO29 (SCLA)

	/* Configure I2C pins using GPIO regs*/
	// This specifies which of the possible GPIO pins will be I2C functional pins.
	// Comment out other unwanted lines.
	GpioCtrlRegs.GPAMUX2.bit.GPIO28 = 2;   // Configure GPIO28 for SDAA operation
	GpioCtrlRegs.GPAMUX2.bit.GPIO29 = 2;   // Configure GPIO29 for SCLA operation
	EDIS;

	// Initialize I2C
	I2caRegs.I2CMDR.bit.IRS = 0; // Put I2C into reset.
	I2caRegs.I2CPSC.all = (Uint16)59;		    // The I2C Clock speed is CLOCK/(I2CPSC+1). Set to 400 KHz
	// The current peripheral clock speed is 90MHz/4
	I2caRegs.I2CCLKL = 10;			// NOTE: must be non zero, the amount of time the SCL clock pin is low
	I2caRegs.I2CCLKH = 5;			// NOTE: must be non zero, the amount of time the SCL is high

	// Sets I2C module to master, receiver mode.
	I2caRegs.I2CMDR.all = 0x0420; // 0000 0100 0010 0000
	//I2caRegs.I2CFFTX.bit.I2CFFEN = 0; // DISABLE FIFO

	I2caRegs.I2CMDR.bit.IRS = 1; // Takes I2C out of reset, ENABLE I2C!
}

// Prints out useful information about I2C state.
void i2c_status(void) {
	char string[32];
	sprintf(string, "BB: %d, SCD:%d, NACKSNT:%d", I2caRegs.I2CSTR.bit.BB, I2caRegs.I2CSTR.bit.SCD, I2caRegs.I2CSTR.bit.NACKSNT);
	puts(string);
}

// Get the ith bit from the passed byte (MSB is leftmost bit)
// bitnum index: [7 6 5 4 3 2 1 0] = 1 Byte
char getBitFromByte(Uint16 byte, char bitnum) {
	return (char)( ((Uint16)1) & (byte>>bitnum) );
}
