/*
 * WiFIMU_CAN.c
 *
 *  Created on: Jul 5, 2014
 *      Author: andrey
 */


#include "CAN.h"
#include "WiFiFuncs.h"
float vArray[32];
char vArrayIndex;
Uint32 requestMessage[1] = {0};

void IMUSendInterrupt(CAN_ID ID, Uint32 dataH, Uint32 dataL, Uint16 length, int mbox_num);
void IMUReceiveInterrupt(CAN_ID ID, Uint32 dataH, Uint32 dataL, Uint16 length, int mbox_num);
void WIFISendInterrupt(CAN_ID ID, Uint32 dataH, Uint32 dataL, Uint16 length, int mbox_num);
void WIFIReceiveInterrupt(CAN_ID ID, Uint32 dataH, Uint32 dataL, Uint16 length, int mbox_num);
void BMSSendInterrupt(CAN_ID ID, Uint32 dataH, Uint32 dataL, Uint16 length, int mbox_num);
void BMSReceiveInterrupt(CAN_ID ID, Uint32 dataH, Uint32 dataL, Uint16 length, int mbox_num);

CAN_INFO INFO_ARRAY[] = {
		{
				IMU,
				&IMUSendInterrupt,
				&IMUReceiveInterrupt
		},{
				WIFI,
				&WIFISendInterrupt,
				&WIFIReceiveInterrupt
		},{
				BMS_TEMP,
				&BMSSendInterrupt,
				&BMSReceiveInterrupt
		},{
				BMS_VOLTS,
				&BMSSendInterrupt,
				&BMSReceiveInterrupt
		},{
				BMS_CURRENT,
				&BMSSendInterrupt,
				&BMSReceiveInterrupt
		},{
				BMS_CHARGE,
				&BMSSendInterrupt,
				&BMSReceiveInterrupt
		}
};

void requestBMSData(){
	CAN_send(requestMessage,4,BMS_TEMP,0,0);
	//rest are requested upon reception of previous request in interrupt
}


void WiFIMU_CAN_init(){
	CAN_init(INFO_ARRAY, 6, 1);
}


void IMUSendInterrupt(CAN_ID ID, Uint32 dataH, Uint32 dataL, Uint16 length, int mbox_num){

}

void IMUReceiveInterrupt(CAN_ID ID, Uint32 dataH, Uint32 dataL, Uint16 length, int mbox_num){

}


void WIFISendInterrupt(CAN_ID ID, Uint32 dataH, Uint32 dataL, Uint16 length, int mbox_num){

}

void WIFIReceiveInterrupt(CAN_ID ID, Uint32 dataH, Uint32 dataL, Uint16 length, int mbox_num){

}

void BMSSendInterrupt(CAN_ID ID, Uint32 dataH, Uint32 dataL, Uint16 length, int mbox_num){

}

void BMSReceiveInterrupt(CAN_ID ID, Uint32 dataH, Uint32 dataL, Uint16 length, int mbox_num){
	if(ID == BMS_TEMP){
		//TODO send temps over wifi (dont know how to parse)
		CAN_send(requestMessage,4,BMS_CURRENT,0,0);
	}else if(ID == BMS_CURRENT){
		float current = {convertInt(dataL)};
		sendCurrent(current);
		CAN_send(requestMessage,4,BMS_CHARGE,0,0);
	}else if(ID == BMS_CHARGE){
		float SoC = {convertInt(dataL)};
		sendSoC(SoC);
		vArrayIndex = 0;
		CAN_send(requestMessage,4,BMS_VOLTS,0,0);
	}else if(ID == BMS_VOLTS){
		if(vArrayIndex<32){
			vArray[vArrayIndex++] = convertInt(dataL);
			vArray[vArrayIndex++] = convertInt(dataH);
		}
		else
			sendVoltages(vArray);
}
}
