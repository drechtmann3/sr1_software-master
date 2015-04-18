/*
 * WiFiFormat.c
 *
 *  Created on: Jul 5, 2014
 *      Author: andrey
 */

#include "WiFi.h"
#include "string.h"
void sendSoC(float SoC){
	sendFloat(SoC,"SoC",3);
}

void sendCurrent(float current){
	sendFloat(current,"current",7);
}

void sendVoltages(float* voltages){
	sendFloats(voltages,32,"voltage",7);
}

