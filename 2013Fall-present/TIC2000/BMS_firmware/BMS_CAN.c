#include "BMS.h"
#include "CAN.h"
#include "BMS_CAN.h"
/*
 * This file has the functions for CAN.
 */


void BMSSendInterrupt(CAN_ID ID, Uint32 dataH, Uint32 dataL, Uint16 length, int mbox_num){
}

/**
 * \brief This function is called whenever BMS receives a CAN message that it hasn't sent.
 */
void BMSReceiveInterrupt(CAN_ID ID, Uint32 dataH, Uint32 dataL, Uint16 length, int mbox_num){
	puts("BMS Received CAN!");
	switch (ID) {
	case BMS_TEMP: // BMS temp sensor CAN message
		sendTempSensorReadingsViaCAN();
		puts("Sending temp");
		break;
	case BMS_VOLTS: // BMS send voltages CAN message
		BMSCAN_sendVoltages();
		puts("Sending voltage");
		break;
	case BMS_CURRENT: // If BMS_CURRENT or BMS_CHARGE is received, send out SOC and Charge
		BMSCAN_sendSOCAndCurrent();
		puts("Sending current and soc");
		break;
	case BMS_CHARGE:
		BMSCAN_sendSOCAndCurrent();
		puts("Sending current and soc");
		break;
	default:
		break;
	}
}

CAN_INFO BMS_CAN_INFO_ARRAY[4] = {
		{
				BMS_TEMP,
				&BMSSendInterrupt,
				&BMSReceiveInterrupt
		},
		{
				BMS_VOLTS,
				&BMSSendInterrupt,
				&BMSReceiveInterrupt
		},
		{
				BMS_CURRENT,
				&BMSSendInterrupt,
				&BMSReceiveInterrupt
		},
		{
				BMS_CHARGE,
				&BMSSendInterrupt,
				&BMSReceiveInterrupt
		}
};

void BMS_CAN_init(){
	CAN_init(BMS_CAN_INFO_ARRAY,4,1);
}

/**
 * \brief Send battery voltage data on the CAN bus, with CAN ID BMS_VOLTS
 * Sends CAN message:
 * [empty byte][High Byte V][Low Byte V][Module number][empty byte][High Byte V][Low Byte V][Module Number]
 * Where V = Measured voltage * 1000;
 */
void BMSCAN_sendVoltages() {
	Uint32 CANbuffer[2];
	Uint16 voltage;
	unsigned char i;

	for (i = 0; i < 5; i++) { // Send bottom-10 voltages:
		voltage = (Uint16)(bVoltages[i*2] * 1000.0f);
		CANbuffer[0] = (Uint32)(i*2) | ((Uint32)voltage<<8);
		voltage = (Uint16)(bVoltages[i*2 + 1] * 1000.0f);
		CANbuffer[1] = (Uint32)(i*2 + 1) | ((Uint32)voltage<<8);
		CAN_send(CANbuffer, 8, BMS_VOLTS, 12, 1); // Put 8 bytes of data in Mailbox 12. Wait to send.
	}
	for (i = 0; i < 5; i++) { // Send middle-10 voltages:
		voltage = (Uint16)(mVoltages[i*2] * 1000.0f);
		CANbuffer[0] = (Uint32)(i*2) | ((Uint32)voltage<<8);
		voltage = (Uint16)(mVoltages[i*2 + 1] * 1000.0f);
		CANbuffer[1] = (Uint32)(i*2 + 1) | ((Uint32)voltage<<8);
		CAN_send(CANbuffer, 8, BMS_VOLTS, 13, 1); // Put 8 bytes of data in Mailbox 13
	}
	for (i = 0; i < 5; i++) { // Send top-10 voltages:
		voltage = (Uint16)(tVoltages[i*2] * 1000.0f);
		CANbuffer[0] = (Uint32)(i*2) | ((Uint32)voltage<<8);
		voltage = (Uint16)(tVoltages[i*2 + 1] * 1000.0f);
		CANbuffer[1] = (Uint32)(i*2 + 1) | ((Uint32)voltage<<8);
		CAN_send(CANbuffer, 8, BMS_VOLTS, 14, 1); // Put 8 bytes of data in Mailbox 14
	}
}

/**
 * \brief Send battery SoC (State of Charge) and current (AMPS) measurement on CAN.
 * Send CAN: [SOC H][SOC L] with BMS_CHARGE, where SOC is from 0 to 2^16
 * Send CAN: [Current H][Current L], with current amperes used, where Current = I * 100 (hundreths of an ampere), current can be + or -
 */
void BMSCAN_sendSOCAndCurrent() {
	Uint32 CAN_buffer[2];
	CAN_buffer[0] = (Uint32)0x98 | ((Uint32)((int16)(batCurrent*100.0f))<<8); // Signed I * 100.0;
	CAN_buffer[1] = 0;
	CAN_send(CAN_buffer, 8, BMS_CURRENT, 11, 0); // Put 8 bytes of data in Mailbox 11
	CAN_buffer[0] = (Uint32)0x98 | (((Uint32)(SoC*65535.0f)) <<8);
	CAN_buffer[1] = 0;
	CAN_send(CAN_buffer, 8, BMS_CHARGE, 10, 0); // Put 8 bytes of data in Mailbox 10
}