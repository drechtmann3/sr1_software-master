/*
 * DS2484_Coms.c
 *
 * This file has functions that are used to control & communicate (I2C) with the DS2484 temperature sensor controller
 * for the 2014 SJ-1 BMS system, designed by Drew and his senior design team.
 *
 *  Created on: Apr 4, 2014
 *      Author: Alex Popescu
 *
 * This TI webpage has lots of helpful information about I2C:
 * http://processors.wiki.ti.com/index.php/I2C_Tips
 */
#include "BMS.h"

unsigned char tempSensorDataArr[] = { // 8 bytes TOT for each temp sensor.
	//  [        64-bit Temp Sensor ROM Code        ]
		0x28, 0x29, 0x37, 0x9c, 0x05, 0x0, 0x0, 0x2d,       // ID 0 : Test sensor
		// Other pack sensors:
		0x28, 0x6a, 0x73, 0xc, 0x6, 0x0, 0x0, 0xf2, // ID 1   Pack 1
		0x28, 0x24, 0x7f, 0x9c, 0x5, 0x0, 0x0, 0xb0, // ID 2  Pack 1
		0x28, 0xbe, 0x8f, 0x9c, 0x5, 0x0, 0x0, 0x68, // ID 3  Pack 2
		0x28, 0x9b, 0x1a, 0xd0, 0x5, 0x0, 0x0, 0xa2, // 4     Pack 2
		0x28, 0x51, 0xd0, 0x9b, 0x5, 0x0, 0x0, 0x19, // 5   Pack 3
		0x28, 0x46, 0x48, 0x9c, 0x5, 0x0, 0x0, 0xc8, // 6   Pack 3
		0x28, 0xfb, 0xa9, 0x9c, 0x5, 0x0, 0x0, 0x92, // 7   Pack 4
		0x28, 0x3a, 0x60, 0x9c, 0x5, 0x0, 0x0, 0xeb, // 8   Pack 4
		0x28, 0xaf, 0xf5, 0xb, 0x6, 0x0, 0x0, 0x57, // 9    Pack 5
		0x28, 0x6d, 0x84, 0xb, 0x6, 0x0, 0x0, 0x6, // 10     Pack 5
		0x28, 0x92, 0x6b, 0xc, 0x6, 0x0, 0x0, 0x63, // 11   Pack 6
		0x28, 0xc1, 0xee, 0xb, 0x6, 0x0, 0x0, 0x8b, // 12   Pack 6
		0x28, 0x26, 0xef, 0xb, 0x6, 0x0, 0x0, 0xea, // 13   Pack 7
		0x28, 0xb3, 0x49, 0xc, 0x6, 0x0, 0x0, 0x99, // 14   Pack 7
		0x28, 0x13, 0x7e, 0xcf, 0x5, 0x0, 0x0, 0x45, // 15    Pack 8
		0x28, 0xf4, 0x58, 0xc, 0x6, 0x0, 0x0, 0xd8, // 16    Pack 8
		0x28, 0xa7, 0xf8, 0xcf, 0x5, 0x0, 0x0, 0xc9, // 17   Pack 9
		0x28, 0xc6, 0x73, 0xc, 0x6, 0x0, 0x0, 0xd3, // 18    Pack 9
		0x28, 0xd1, 0xa7, 0xb, 0x6, 0x0, 0x0, 0xca, // 19    Pack 10
		0x28, 0xcf, 0x31, 0xc, 0x6, 0x0, 0x0, 0x2f, // 20    Pack 10
		0x28, 0xe5, 0x6b, 0xc, 0x6, 0x0, 0x0, 0x7e, // 21    Pack 11
		0x28, 0xcb, 0xe, 0x9d, 0x5, 0x0, 0x0, 0x92, // 22    Pack 11
		0x28, 0xd7, 0x63, 0xc, 0x6, 0x0, 0x0, 0xc3, // 23     Pack 12
		0x28, 0xe, 0xab, 0xb, 0x6, 0x0, 0x0, 0xb, // 24    Pack 12
		0x28, 0xaa, 0x15, 0xc, 0x6, 0x0, 0x0, 0xe0, // 25    Pack 13
		0x28, 0xc7, 0x60, 0xc, 0x6, 0x0, 0x0, 0xd6, // 26      Pack 13
		0x28, 0x97, 0xc7, 0x9c, 0x5, 0x0, 0x0, 0x9f, // 27    Pack 14
		0x28, 0xfc, 0x63, 0x9c, 0x5, 0x0, 0x0, 0x88, // 28    Pack 14
		0x28, 0x1f, 0x63, 0xc, 0x6, 0x0, 0x0, 0xfd, // 29    Pack 15
		0x28, 0xb8, 0x72, 0xc, 0x6, 0x0, 0x0, 0x95 // 30     Pack 15



};

/**
 * \brief send read temp. command. Temp must be read >= a certain amount of time, depending on resolution.
 */
char sendReadCommandOfDS18B20(char tempSenseID) {
	int i, idx0 = ((int)tempSenseID)*8;
	if (!send1WireResetPulse()) { // Send 1-wire reset pulse to begin 1-wire communication
		return 0;
	}
	//puts("Matching ROM...");
	if (!oneWireWriteByte((Uint16)0x55)) { // Send MATCH ROM command over 1-wire line
		return 0;
	}
	// Transmit the 64-bit ROM code LSB first.
	for (i = 0; i < 8; i++) {
		if (!oneWireWriteByte(tempSensorDataArr[idx0 + i])) { // Send the ROM number over the 1-wire line
			return 0;
		}
	}
	//puts("Sent convert T command");
	if (!oneWireWriteByte((Uint16)0x44)) { // Send the "Convert T" command over 1-wire
		puts("Error sending Convert Temperature command!");
	}
	return 1;
}

// Get the temperature of the temperature sensor with the passed ROM number,
// in DEGREES CELSIUS. Accurate to +/- 0.5 C.
// Check the value of error_code to determine if the returned value is valid!
// Error code:
// 0 : Data OK; temperature reading is valid
// 1 : I2C communication error
// 2 : Temperature sensor data error (CRC wrong)
float32 readTemperatureOfDS18B20(char tempSenseID, int* error_code) {
	int i, idx0 = ((int)tempSenseID)*8;
	// Now, temperature is converted. Begin 1-wire communication again...
	if (!send1WireResetPulse()) { // Send 1-wire reset pulse to begin 1-wire communication
		*error_code = 1;
		return 0;
	}
	//puts("Matching ROM again...");
	if (!oneWireWriteByte((Uint16)0x55)) { // Send MATCH ROM command over 1-wire line
		*error_code = 1;
		return 0;
	}
	//puts("Reading scratchpad...");
	// Transmit the 64-bit ROM code LSB first.
	for (i = 0; i < 8; i++) {
		if(!oneWireWriteByte(tempSensorDataArr[idx0 + i])) { // Send the ROM number over the 1-wire line
			*error_code = 1;
			return 0;
		}
	}
	// Read the scratchpad of the DS18B20 to get temperature:
	if (!oneWireWriteByte((Uint16)0xBE)) { // Send READ SCRATCHPAD command
		*error_code = 1;
		return 0;
	}
	// Read 9 data bytes (the scratchpad):
	Uint16 scratchpad[9];
	for (i = 0; i < 9; i++) {
		scratchpad[i] = oneWireReadByte();
		if (scratchpad[i] > 0xFF) {
			*error_code = 1;
			return 0; // We should always get only a byte of information.
		}
		//char str[25];
		//sprintf(str, "Read scratchpad byte: 0x%x", scratchpad[i]);
		//puts(str);
	}

	//char str[25];
	//sprintf(str, "CRC: 0x%x", calculateDS2484CRC(scratchpad, 8));
	//puts(str);

	// Confirm the validity of the response by performing a CRC:
	if (calculateDS2484CRC(scratchpad, 8) == scratchpad[8]) {
		//puts("Scratchpad data validated!");
		// Now that the response has been CRC'd, we can read the temperature:
		Uint16 raw_temp_reading = scratchpad[0] + (Uint16)(scratchpad[1]<<8);
		int signed_reading = (int)raw_temp_reading;
		float32 temp_reading = (float)signed_reading / 16.0f; // Divide by 16 since 4 LSB are decimal.
		*error_code = 0;
		return temp_reading;
	}

	*error_code = 2;
	//puts("Error validating CRC on scratchpad! Data transmission error occurred!");
	return 0;
}

/**
 * \brief Set temperature conversion resolution
 * tempSenseID: the ID of the temp sensor to be changed.
 * resolutionBits: 9-12 bits, resolution of temp sensor reading
 */
char setTempResolutionForTempSensorID(char tempSenseID, char resolutionBits) {
	int i, idx0 = ((int)tempSenseID)*8;
	unsigned char configRegister = 0x1F | ((resolutionBits-9)<<5);
	unsigned char scratchpad[9];
	if (!send1WireResetPulse()) { // Send 1-wire reset pulse to begin 1-wire communication
		return 0;
	}
	if (!oneWireWriteByte((Uint16)0x55)) { // Send MATCH ROM command over 1-wire line
		return 0;
	}
	// Transmit the 64-bit ROM code LSB first, for this temp sensor.
	for (i = 0; i < 8; i++) {
		if (!oneWireWriteByte(tempSensorDataArr[idx0 + i])) { // Send the ROM number over the 1-wire line
			return 0;
		}
	}
	if (!oneWireWriteByte((Uint16)0x4E)) { // Send the "Write scratchpad" command over 1-wire
		puts("Error sending Convert Temperature command!");
		return 0;
	}
	if (!oneWireWriteByte(0xFF)) { // Send T_H, high alarm temperature
		return 0;
	}
	if (!oneWireWriteByte(0x00)) { // Send T_L, low alarm temperature
		return 0;
	}
	if (!oneWireWriteByte(configRegister)) { // Send config register byte: 0XX11111
		return 0;
	}
	if (!send1WireResetPulse()) { // Send 1-wire reset pulse to begin 1-wire communication
		return 0;
	}
	if (!oneWireWriteByte((Uint16)0x55)) { // Send MATCH ROM command over 1-wire line
		return 0;
	}
	// Transmit the 64-bit ROM code LSB first, for this temp sensor.
	for (i = 0; i < 8; i++) {
		if (!oneWireWriteByte(tempSensorDataArr[idx0 + i])) { // Send the ROM number over the 1-wire line
			return 0;
		}
	}
	if (!oneWireWriteByte((Uint16)0xBE)) { // Send READ SCRATCHPAD command
		return 0;
	}
	// Read 9 data bytes (the scratchpad):
	for (i = 0; i < 9; i++) {
		scratchpad[i] = oneWireReadByte();
		if (scratchpad[i] > 0xFF) {
			return 0; // We should always get only a byte of information.
		}
	}
	// Check temp value was set:
	if (scratchpad[4] != configRegister) {
		puts("Config invalid!");
		return 0; // We should always get only a byte of information.
	}
	puts("Config register validated!");
	//tempSensorDataArr[idx0 + 8] = resolutionBits; // Store resolution bits locally.
	return 1;
}

// !ONLY APPLICABLE WHEN *ONE* 1-WIRE DEVICE IS HOOKED UP!
// Read the ROM number of the only 1-wire device hooked up to the 1-wire bus.
// Used for testing purposes to determine the ROM number of this device.
// Pass an unsigned char array of 8 cells, to store the 64-bit ROM number (each cell stores 1 byte).
char getROMNumberOfOnlyDevice(Uint16 ROMNumber[]) {
	puts("Getting ROM number of only connected device...");
	// Send 1-wire reset pulse to initiate 1-wire communication to 1-wire slaves:
	if (send1WireResetPulse() == 0) {
		puts("No 1-wire devices connected!");
		return 0;
	}

	// Tell the 1-wire device to "READ ROM" by writing to the 1-wire line:
	if (!oneWireWriteByte((Uint16)0x33)) return 0;

	int i;
	for (i = 0; i < 8; i++) {
		ROMNumber[i] = oneWireReadByte(); // Retrieve the ROM data byte.
		if (ROMNumber[i] > 0xFF) return 0;
	}

	// Perform a CRC check on the ROM number, to verify no transmission errors:
	if (calculateDS2484CRC(ROMNumber, 7) == ROMNumber[7]) {
		puts("ROM number CRC verified!");
		return 1;
	}

	puts("ROM number CRC verification failed! Error must have occurred in transmission!");
	return 0;
}

// Tell DS2484 to transmit reset pulse on 1-wire bus.
// This must occur before every transaction sequence with the 1-wire slaves.
char send1WireResetPulse(void) {
	//puts("Transmitting reset pulse to 1-wire bus...");
	if (!i2c_send_start_and_slave_address(DS2484_ADDRESS, 0)) return 0; // Send start condition with write option
	if (!i2c_send_data_byte((Uint16)0xB4)) return 0; // Send 1-wire reset command
	while (I2caRegs.I2CSTR.bit.ARDY != 1); // Wait for bus to be ready for repeated start
	if (!i2c_send_start_and_slave_address(DS2484_ADDRESS, 1)) return 0; // Send repeated start with read

	// Wait for reset pulse command to complete...
	Uint16 status_reg = 0;
	Uint32 read_tries = 0;
	while (read_tries < READ_TRIES_BEFORE_FAIL) {
		status_reg = i2c_read_data_byte(0); // Read status register, generate ACK after each byte received.
		char WB_bit = getBitFromByte(status_reg, 0); // Read the 1WB bit.
		if (WB_bit == 0) break; // Wait till we read a 0 on 1WB. This means the 1-wire command is completed.
		read_tries++;
	}
	if (read_tries >= READ_TRIES_BEFORE_FAIL) return 0;
	i2c_read_data_byte(2); // Ask for one more "dummy" byte, and send NACK+STOP after it is received.

	// Check if 1-wire devices were detected by sampling PPD bit:
	char PPD = getBitFromByte(status_reg, 1); // 1 if presence pulse detected
	char SD = getBitFromByte(status_reg, 2); // 1 if short detected

	if (PPD==1 && SD==0) // Return success if presence pulse detected and no short detected.
		return 1;

	if (PPD == 0) puts("No presence pulse detected from 1-wire devices!");
	if (SD == 1) puts("Short circuit detected on 1-wire bus!");
	return 0;
}

// Resets the DS2484 and returns 1 if the device read what was expected, 0 if failed.
char resetDS2484(void) {
	//puts("Resetting...");
	char a1 = i2c_send_start_and_slave_address(DS2484_ADDRESS, 0); // Send start condition with write option.
	char a2 = i2c_send_data_byte((Uint16)0xF0); // Send master reset command.
	while (I2caRegs.I2CSTR.bit.ARDY != 1); // Wait for bus to be ready for repeated start
	char a3 = i2c_send_start_and_slave_address(DS2484_ADDRESS, 1); // Send repeated start condition with read option
	if (a1 + a2 + a3 != 3) return 0; // Some acknowledge bits were not sent! Abort.

	Uint16 status_reg = i2c_read_data_byte(2); // Read status register, send NACK+STOP after this byte is received.
	char RST = getBitFromByte(status_reg, 4); // Get reset bit (RST)

	//char string[32];
	//sprintf(string, "Read from reset: 0x%x", status_reg);
	//puts(string);

	return RST; // RST bit is 1 after successful reset.
}

// Returns the Cyclic Redundancy Check for the received bytes from the DS2484,
// using the DS2484 CRC generator polynomial x^8 + x^5 + x^4 + 1.
// The DS2484 uses an LSB format for the CRC, which is also little-endian (LSByte first).
Uint16 calculateDS2484CRC(Uint16 dataBytes[], int num_bytes) {
	Uint16 remainderPolynomial = 0; // 8 bits, the degree of the generator polynomial, are needed.
	Uint16 generatorPolynomial = 0x8C; // 8 bits, MSB of generator removed, in LSB form.
	int i;
	int j;
	for (i = 0; i < num_bytes; i++) {
		remainderPolynomial = remainderPolynomial ^ dataBytes[i]; // ^=bitwise XOR
		for (j = 0; j < 8; j++) {
			if (getBitFromByte(remainderPolynomial, 0) == 1) { // If coefficient of x^7 == 1
				remainderPolynomial = (remainderPolynomial>>1) ^ generatorPolynomial;
			} else {
				remainderPolynomial = remainderPolynomial>>1;
			}
		}
	}
	return remainderPolynomial;
}

// Writes a single byte to the 1-wire line, and waits until the 1-wire command is completed and 1-wire is
// no longer busy.
char oneWireWriteByte(Uint16 byte) {
	if (!i2c_send_start_and_slave_address(DS2484_ADDRESS, 0)) return 0; // Send start condition with write option
	if (!i2c_send_data_byte((Uint16)0xA5)) return 0; // Send "1-wire write byte" to DS2484
	if (!i2c_send_data_byte(byte)) return 0; // Put a 1-wire command/byte on 1-wire line
	while (I2caRegs.I2CSTR.bit.ARDY != 1); // Wait for bus to be ready for repeated start

	if (!i2c_send_start_and_slave_address(DS2484_ADDRESS, 1)) return 0; // Send repeated start condition with read option

	Uint16 status_reg = 0;
	Uint32 read_tries = 0;
	while (read_tries < READ_TRIES_BEFORE_FAIL) {
		status_reg = i2c_read_data_byte(0); // Read status register, generate ACK after each byte received.
		char WB_bit = getBitFromByte(status_reg, 0); // Read the 1WB bit.
		if (WB_bit == 0) break; // Wait till we see a 0 on 1WB. This means the 1-wire command is completed.
		read_tries++;
	}
	if (read_tries >= READ_TRIES_BEFORE_FAIL) return 0;
	i2c_read_data_byte(2); // Ask for one more dummy byte, and send NACK + STOP after it is received.
	return 1;
}

// Reads a single byte from the 1-wire line (sets up 8 read-bit slots). Returns the read data byte.
// If a return with value GREATER than the max possible for 1 byte is given, consider it an error!
Uint16 oneWireReadByte(void) {
	if (!i2c_send_start_and_slave_address(DS2484_ADDRESS, 0)) return 0x8000; // Send start condition with write option
	if (!i2c_send_data_byte((Uint16)0x96)) return 0x8000; // Send "1-wire read byte" to DS2484
	while (I2caRegs.I2CSTR.bit.ARDY != 1); // Wait for bus to be ready for repeated start
	if (!i2c_send_start_and_slave_address(DS2484_ADDRESS, 1)) return 0x8000; // Send repeated start condition with read option

	Uint16 status_reg = 0;
	Uint32 read_tries = 0;
	while (read_tries < READ_TRIES_BEFORE_FAIL) {
		status_reg = i2c_read_data_byte(0); // Read status register, generate ACK after each byte received.
		char WB_bit = getBitFromByte(status_reg, 0); // Read the 1WB bit.
		if (WB_bit == 0) break; // Wait till we see a 0 on 1WB. This means the 1-wire command is completed.
		read_tries++;
	}
	if (read_tries >= READ_TRIES_BEFORE_FAIL) return 0x8000;
	i2c_read_data_byte(1); // Ask for one more dummy byte, and send NACK after it is received.

	if (!i2c_send_start_and_slave_address(DS2484_ADDRESS, 0)) return 0x8000; // Send start condition with write option
	if (!i2c_send_data_byte((Uint16)0xE1)) return 0x8000; // Send "set read pointer" command
	if (!i2c_send_data_byte((Uint16)0xE1)) return 0x8000; // Send "Read 1-wire data register" code

	while (I2caRegs.I2CSTR.bit.ARDY != 1); // Wait for bus to be ready for repeated start
	if (!i2c_send_start_and_slave_address(DS2484_ADDRESS, 1)) return 0x8000; // Send repeated start condition with read option
	Uint16 readByte = i2c_read_data_byte(2); // Retrieve the ROM data byte, send NACK+STOP.
	return readByte;
}

// Write the configuration register byte on the DS2484.
// Returns the value it reads from the register, or 0x8000 which means error.
Uint16 writeDS2484Configuration(Uint16 register_value) {
	if (!i2c_send_start_and_slave_address(DS2484_ADDRESS, 0)) return 0x8000; // Send start condition with write option
	if (!i2c_send_data_byte((Uint16)0xD2)) return 0x8000; // Send "Write device configuration"  to DS2484
	if (!i2c_send_data_byte(register_value)) return 0x8000; // Write the value of the register
	while (I2caRegs.I2CSTR.bit.ARDY != 1); // Wait for bus to be ready for repeated start

	if (!i2c_send_start_and_slave_address(DS2484_ADDRESS, 1)) return 0x8000; // Send repeated start condition with read option
	return i2c_read_data_byte(2); // Read status register, generate NACK+STOP after each byte received.
}
