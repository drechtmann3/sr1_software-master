/*
 * LCD_CAN.c
 *
 *  Created on: Jun 24, 2014
 *      Author: Alex
 */

#include "LCD_CAN.h"

void LCD_CAN_send_isr(CAN_ID ID, Uint32 dataH, Uint32 dataL, Uint16 length, int mbox_num) {
}
/**
 * \brief Called when CAN receives something. We set up receive in the initialization function.
 */
void LCD_CAN_receive_isr(CAN_ID ID, Uint32 dataH, Uint32 dataL, Uint16 length, int mbox_num) {
	char msg_id;
	Uint16 buffer;
	msg_id = dataL & 0xFF; // Get CAN message ID. For motor controller, this is the first byte of the message.
	switch (msg_id) {
	case CAN_SPEED_MSG: // CAN Speed (mph) message.
		buffer = dataL >> 8;
		speedMph = buffer; // Set mph.
		//stdiolog1int("Speed %d", speedMph);
		break;
	case CAN_MOTOR_FAULT_MSG: // Motor fault message
		motorFaultRegisters = (dataL>>8) | dataH<<24;
		//stdiolog1int("Motorfault %d", (Uint16)motorFaultRegisters);
		break;
	case CAN_MOTOR_STATUS_MSG: // Motor drivestate message
		buffer = (dataL >> 8) & 0xFF; // First byte after ID
		if (buffer < 74 || buffer > 79 )
			motorErrorActive = 1; // We are in a bad drivestate!
		else
			motorErrorActive = 0; // If we are in a good drivestate, release from motor error.
		//stdiolog1int("drivestate %d", buffer);
		break;
	case CAN_TEMPERATURE_VOLTAGE_MSG: // Temperature and voltage message
		buffer = ((dataL >> 24) | (dataH<<8)) & (Uint32)0xFFFF; // Only get heatsink temperature
		motorTempVal = (float32)buffer / MOTOR_MAX_HEATSINK_TEMP / 10.0f;
		buffer = dataL & 0x00FFFF00;

		//stdiolog1int("heatsink temp: %d", buffer);
		break;
	case CAN_MOTOR_ERROR_MSG: // Motor controller had an SCI/RS-232 error communicating w/ motor!
		motorErrorActive = 1; // As of now, doesn't check for actual error code.
		break;
	case CAN_THROTTLE_REGEN_VALUE_MSG: // Throttle value, in dA
		buffer = dataL >> 8;
		throttleVal = ((float32)((int)buffer)) / MOTOR_MAX_THROTTLE_CURRENT_AMPS / 10.0f;
		//stdiolog1int("throttle/regen: %d", (int)buffer);
		break;
	case CAN_MOTOR_CC_EN_MSG: // Cruise control is toggled
		buffer = dataL >> 8;
		cruiseControlEnabled = buffer;
		break;
	case CAN_MOTOR_REV_EN_MSG: // Reversed/Forwarded motor direction
		buffer = dataL >> 8;
		reverseModeEnabled = buffer;
		break;
	case CAN_BLINKER_EN_MSG: // Blinker on/off status message
		if (dataL>>8 && dataL>>16) blinkerState = 3; // Both blinkers
		else if (dataL>>8 && dataL>>16==0) blinkerState = 2; // Right blinker only
		else if (dataL>>8==0 && dataL>>16) blinkerState = 1; // Left blinker only
		else blinkerState = 0; // No blinkers.
		break;
	default:
		puts("Unrecognized message ID!");
		CANErrorActive = 1;
		return;
	}
	CANErrorActive = 0; // Release CAN error if we have successfully parsed a CAN motor message.
}

// This array describes what ID CAN sends, and send and receive callbacks
CAN_INFO LCD_CAN_info_array[] = {
	{
		MOTOR_CONTROLLER,
		&LCD_CAN_send_isr,
		&LCD_CAN_receive_isr
	}
};


void LCD_Initialize_CAN() {
	CAN_init(LCD_CAN_info_array, 1, 1); // Initialize CAN with the number of CAN ID's we intend to be sending/receiving from, in this case, 1. USE interrupts.
}
