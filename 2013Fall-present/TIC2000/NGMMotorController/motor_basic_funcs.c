/*
 * motor_basic_funcs.c
 *
 *  Created on: Jun 1, 2014
 *      Author: Alex
 */

#include "motor_basic_funcs.h"

#define MOTOR_BASIC_FNS_DBG 0

char NGMSCM_error_buffer[17]; // Stores error string from motor controller.
unsigned char NGMEV_fault_code_buffer[4]; // Stores fault codes received from motor controller.


/**
 * \brief Assign a value to a RAM or EEPROM register on the NGM-EVM 200 motor controller. Specify
 *        the memory location of the register, and what value to set it to.
 * \var memLoc the location to be read from memory
 * \var inRAM  =1 iff the the variable desired resides in RAM. =0 iff in EEPROM.
 * \var value the value to be stored at the memory location.
 * \return +1 : Memory register was set to value OK.
 * \return -1 : Error setting this register, look in NGMSCM_error_buffer for the error.
 */
signed char NGMEVAssignment(unsigned char memLoc, char inRAM, int32 value) {
	char transmit_string[16]; // Transmit string can be a maximum of 15 bytes.
	if (inRAM) {
		sprintf(transmit_string, "%02X=%ld\r", (unsigned int)(memLoc & 0xFF), value); // RAM: =
	} else {
		sprintf(transmit_string, "%02X<%ld\r", (unsigned int)(memLoc & 0xFF), value); // EEPROM: <
	}

	if (MOTOR_BASIC_FNS_DBG) puts(transmit_string);

	switch (scia_transmit_string_echo(transmit_string)) {
	case -1:
		return -1;
	}

	scia_receive_string(); // Receive string.
	if (MOTOR_BASIC_FNS_DBG) {
		stdiologstr(transmit_string);
		stdiologstr(scia_receive_buffer);
	}

	if (strcmp(scia_receive_buffer, "\nOk\r") == 0)
		return 1;

	strcpy(NGMSCM_error_buffer, scia_receive_buffer); // Copy error into error buffer.
	return -1;
}

/**
 * \brief Send a command to the NGM-EVM 200 motor controller. The command is sent in the
 *        format "XX!\r", where XX is the command_code. For example, to enable the motor
 *        use command code "00".
 * \return +1 : The motor controller replied "OK", meaning command was accepted.
 * \return -1 : The motor controller did not reply with OK, something is amiss! Recommend: check for faults.
 *              The NGMSCM_error_buffer will be populated with the error received.
 */
signed char sendNGMEVCommand(char *command_code) {
	char transmit_string[16]; // Transmit string can be a maximum of 15 bytes.
	sprintf(transmit_string, "%s!\r", command_code); // Send command code: XX!\r
	if (MOTOR_BASIC_FNS_DBG) puts(transmit_string);

	switch (scia_transmit_string_echo(transmit_string)) {
	case -1:
		return -1;
	}

	// Check for OK:
	scia_receive_string(); // Receive.
	if (strcmp(scia_receive_buffer, "\nOk\r") == 0)
		return 1;

	// If we have reached this point, the motor controller has an error.
	strcpy(NGMSCM_error_buffer, scia_receive_buffer); // Copy error into error buffer.
	return -1;
}

/**
 * \brief Send a query to the NGM-EVM 200 motor controller's RAM or EEPROM values. (Read value)
 * \detail RAM query:    XX?(CR)
 *         EEPROM query: XX>(CR)    <---- Note: No limit on EEPROM *reading*
 * \var memLoc the location to be read from memory
 * \var inRAM  =1 iff the the variable desired resides in RAM. =0 iff in EEPROM.
 * \var status a pointer to a char in which the status of the command is stored, as follows:
 *      +1: Result OK
 *      -1: Failed to send query: timeout or failed to receive echo.
 * \return The result of the operation (the value in the motor controller's memory).
 * \warning There is no way to detect an erroneous command was sent; the value returned will just be 0.
 * \warning Make sure you are accessing a valid register!
 */
int32 NGMEVQuery(unsigned char memLoc, char inRAM, signed char* status) {
	char transmit_string[16]; // Transmit string can be a maximum of 15 bytes.
	int32 received_val;
	if (inRAM) {
		sprintf(transmit_string, "%02X?\r", (unsigned int)(memLoc & 0xFF)); // RAM: ?
	} else {
		sprintf(transmit_string, "%02X>\r", (unsigned int)(memLoc & 0xFF)); // EEPROM: >
	}
	switch (scia_transmit_string_echo(transmit_string)) {
	case -1:
		*status = -1;
		return 0;
	}
	scia_receive_string(); // Receive string.

	if (MOTOR_BASIC_FNS_DBG) {
		stdiologstr("Received:");
		stdiologstr(scia_receive_buffer);
	}
	received_val = atol(scia_receive_buffer); // Convert received value string to long int, uses less memory than scanf.

	*status = 1;
	return received_val;
}

/**
 * \brief Tests the communications and operation of the NGM EVM 200 motor controller (not the motor).
 *
 * Tests SCI echo is enabled, accesses a few registers.
 * \return +1 : The motor controller seems to be communicating fine.
 * \return -1 : Failed echo test; you need to enable echo (register 0x90 EEPROM)
 * \return -2 : Failed register checking test, there might be a timing issue in the code, interference on the SCI line, bad configs...
 *
 */
signed char testNGMEVComsAndOperation() {
	signed char echotest, status; // Variables must be defined before they are used!
	int32 buffer;

	clearSCIFIFOAndNGMEVReceiveQueue();
	// Now, the motor controller should communicate normally.

	echotest = scia_transmit_string_echo("echotest\r");
	scia_receive_string(); // Wait for response, should be error string.
	if (echotest != 1) {
		puts("Echo failed!");
		return -1; // Echo test failed.
	}

	// Check echo is enabled...
	status = 0;
	buffer = NGMEVQuery(CG_ECHO, NGMEV_VALUE_IN_EEPROM, &status);
	if (status != 1 || buffer != 1) {
		puts("No echo!");
		return -2; // Could not check echo register.
	}

	// Check baud rate...
	buffer = NGMEVQuery(CG_BAUDRATE, NGMEV_VALUE_IN_EEPROM, &status);
	if (status != 1 || buffer != NGMEV_BAUDRATE) {
		puts("Baud wrong!");
		return -2; // Baud rate is wrong
	}

	// Check discrete inputs are DISABLED!
	buffer = NGMEVQuery(CG_ENDISCRETE_THR, NGMEV_VALUE_IN_EEPROM, &status);
	if (status != 1 || buffer != 0) {
		puts("DIS_THR enabled!");
		return -2; // NO discrete throttle
	}
	buffer = NGMEVQuery(CG_ENDISCRETE_DIR, NGMEV_VALUE_IN_EEPROM, &status);
	if (status != 1 || buffer != 0) {
		puts("DIS_DIR enabled!");
		return -2; // NO discrete direction input
	}
	buffer = NGMEVQuery(CG_ENDISCRETE_THRENABLE, NGMEV_VALUE_IN_EEPROM, &status);
	if (status != 1 || buffer != 0) {
		puts("DIS_THREN enabled!");
		return -2; // NO discrete throttle enable input
	}
	buffer = NGMEVQuery(CG_ENDISCRETE_DISABLE, NGMEV_VALUE_IN_EEPROM, &status);
	if (status != 1 || buffer != 0) {
		puts("DIS_DIS enabled!");
		return -2; // NO discrete throttle disable input
	}
	buffer = NGMEVQuery(CG_MAXSCIIDLE, NGMEV_VALUE_IN_EEPROM, &status);
	if (status == 1) {
		stdiolog1int("Serial idle wdg: %d s*10", (int)buffer);
	}

	puts("NGM SCM150 passed all tests!");
	return 1; // Passed all tests
}

/**
 * \brief Sets the motor to timeout and stop if it does not get a command for this length of time.
 */
signed char setMotorWatchogTime(int32 tenthsOfSeconds){
	return NGMEVAssignment(CG_MAXSCIIDLE,NGMEV_VALUE_IN_EEPROM,tenthsOfSeconds);
}

/**
 * \brief Get fundemental motor statistics, and print them over stdio currently. This should
 *        be replaced with sending CAN messages.
 *        TODO
 */
void getNGMEVMotorStats() {
	signed char status = 0;
	int32 buffer;
	buffer = NGMEVQuery(SV_DRIVESTATE, NGMEV_VALUE_IN_RAM, &status);
	stdiolog1int("Drive state: %d", (int)buffer);
	buffer = NGMEVQuery(AM_SUPPLYV, NGMEV_VALUE_IN_RAM, &status);
	stdiolog1int("Current V: %d dV", (int)buffer);
	buffer = NGMEVQuery(IN_DESIREDPHASEI, NGMEV_VALUE_IN_RAM, &status);
	stdiolog1int("Current A: %d dA", (int)buffer);
	buffer = NGMEVQuery(AM_MOTORT, NGMEV_VALUE_IN_RAM, &status);
	stdiolog1int("Temp: %d C*10", (int)buffer);
	buffer = NGMEVQuery(AM_HTSINKT, NGMEV_VALUE_IN_RAM, &status);
	stdiolog1int("Heatsink Temp: %d C*10", (int)buffer);
	buffer = NGMEVQuery(AM_SPEED, NGMEV_VALUE_IN_RAM, &status);
	stdiolog1int("Speed: %d dHz", (int)buffer);
	if (status != 1) stdiologstr("Error getting stats!");
}

/**
 * \brief Get set values from EEPROM, and print them over stdio currently. This should
 *        be replaced with sending CAN messages.
 */
void getNGMEVMotorEEPROMVals() {
	signed char status = 0;
	int32 buffer;
	buffer = NGMEVQuery(CG_MAXMOTORI, NGMEV_VALUE_IN_EEPROM, &status);
	stdiolog1int("Max motor I: %d", (int)buffer);
	buffer = NGMEVQuery(CG_SPEEDTHRESHOLD, NGMEV_VALUE_IN_EEPROM, &status);
	stdiolog1int("Reverse Threshold: %d dV", (int)buffer);
	buffer = NGMEVQuery(CG_MAXTHRI0, NGMEV_VALUE_IN_EEPROM, &status);
	stdiolog1int("Maximum threshold I: %d dI", (int)buffer);
	buffer = NGMEVQuery(CG_MAXRGNI0, NGMEV_VALUE_IN_EEPROM, &status);
	stdiolog1int("Maximum Regen I: %d dI", (int)buffer);

	if (status != 1) stdiologstr("Error getting stats!");
}

/**
 * \brief Sends motor status messages on CAN bus. Lets the other controllers know the motor is still alive.
 */
void send_CAN_heartbeat_messages() {
	int32 buffer, buffer2, buffer3;
	signed char status;
	buffer = NGMEVQuery(SV_DRIVESTATE, NGMEV_VALUE_IN_RAM, &status);                 // Get motor drivestate
	if (status == 1) CAN_send_drivestate_msg(buffer); else CAN_send_error_msg(0x05);
	buffer = NGMEVQuery(AM_SPEED, NGMEV_VALUE_IN_RAM, &status);                      // Get motor speed
	if (status == 1) CAN_send_speed_msg(buffer); else CAN_send_error_msg(0x05);
	buffer = NGMEVQuery(IN_DESIREDPHASEI, NGMEV_VALUE_IN_RAM, &status);              // Get throttle-regen current
	if (status == 1) CAN_send_throttle_regen_msg(buffer); else CAN_send_error_msg(0x05);
	NGMEV_fault_code_buffer[0] = (unsigned char)NGMEVQuery(SV_FAULT1LATCH, NGMEV_VALUE_IN_RAM, &status); // Get faults
	NGMEV_fault_code_buffer[1] = (unsigned char)NGMEVQuery(SV_FAULT2, NGMEV_VALUE_IN_RAM, &status);
	NGMEV_fault_code_buffer[2] = (unsigned char)NGMEVQuery(SV_FAULT3, NGMEV_VALUE_IN_RAM, &status);
	NGMEV_fault_code_buffer[3] = (unsigned char)NGMEVQuery(SV_FAULT4, NGMEV_VALUE_IN_RAM, &status);
	if (status == 1) CAN_send_faults_msg(NGMEV_fault_code_buffer); else CAN_send_error_msg(0x05);
	buffer = NGMEVQuery(AM_MOTORT, NGMEV_VALUE_IN_RAM, &status);                     // Get temperature of motor
	buffer2 = NGMEVQuery(AM_HTSINKT, NGMEV_VALUE_IN_RAM, &status);                   // Get temperature of motor controller heatsink
	buffer3 = NGMEVQuery(AM_SUPPLYV, NGMEV_VALUE_IN_RAM, &status);                   // Get motor controller supply voltage
	if (status == 1) CAN_send_temperature_voltage_msg(buffer, buffer2, buffer3); else CAN_send_error_msg(0x05);
	CAN_send_blinker_status_msg(GpioDataRegs.GPADAT.bit.GPIO17, GpioDataRegs.GPADAT.bit.GPIO18); // Left blinker on = GPIO17, Right blinker on = GPIO18
}


/**
 * \brief Check for faults in the NGM EV-200 motor controller.
 *        Look in NGMEV_fault_code_buffer and NGMEV_fault_type_buffer for the fault code and type.
 *        This data is currently printed, should be sent via CAN!
 * \return +1 If faults were downloaded successfully.
 * \return -1 If faults were not downloaded successfully!
 */
signed char NGMEVGetFaults() {
	signed char status;
	// Check for type 1 faults that have disabled the motor controller.
	NGMEV_fault_code_buffer[0] = (unsigned char)NGMEVQuery(SV_FAULT1LATCH, NGMEV_VALUE_IN_RAM, &status);
	if (status != 1) return -1; // Error talking to motor controller.
	stdiolog1int("Fault1: 0x%x", NGMEV_fault_code_buffer[0]);

	// Check for type 2 faults.
	NGMEV_fault_code_buffer[1] = (unsigned char)NGMEVQuery(SV_FAULT2, NGMEV_VALUE_IN_RAM, &status);
	if (status != 1) return -1; // Error talking to motor controller.
	stdiolog1int("Fault2: 0x%x", NGMEV_fault_code_buffer[1]);

	// Check for type 3 faults.
	NGMEV_fault_code_buffer[2] = (unsigned char)NGMEVQuery(SV_FAULT3, NGMEV_VALUE_IN_RAM, &status);
	if (status != 1) return -1; // Error talking to motor controller.
	stdiolog1int("Fault3: 0x%x", NGMEV_fault_code_buffer[2]);

	// Check for type 4 faults.
	NGMEV_fault_code_buffer[3] = (unsigned char)NGMEVQuery(SV_FAULT4, NGMEV_VALUE_IN_RAM, &status);
	if (status != 1) return -1; // Error talking to motor controller.
	stdiolog1int("Fault4: 0x%x", NGMEV_fault_code_buffer[3]);

	return 1;
}

/**
 * \brief Clears the TX, RX FIFOs on the uC and sends an erroneous command to the motor, to clear
 *        the receive queue.
 */
void clearSCIFIFOAndNGMEVReceiveQueue() {
	scia_send_char('b'); // Send "b\r", do not wait for an echo. This clears the command-receive buffer of the motor.
	scia_send_char('\r');
	scia_receive_string(); // Wait to receive the result, but we don't care what it is (an error).
	scia_receive_string(); // Wait in case there is another new line (sometimes happens inexplicably).

	SciaRegs.SCIFFRX.bit.RXFIFORESET = 0; // Clear TX and RX SCI FIFO buffers on the uC to flush old chars.
	SciaRegs.SCIFFRX.bit.RXFIFORESET = 1;
	SciaRegs.SCIFFTX.bit.TXFIFOXRESET = 0;
	SciaRegs.SCIFFTX.bit.TXFIFOXRESET = 1;
}
