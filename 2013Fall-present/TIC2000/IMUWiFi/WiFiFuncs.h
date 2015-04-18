/*
 * WiFiFormat.h
 *
 *  Created on: Jul 5, 2014
 *      Author: andrey
 */

#ifndef WIFIFUNCS_H_
#define WIFIFUNCS_H_

void sendSoC(float SoC);
void sendCurrent(float current);
void sendVoltages(float* voltages);
void sendTemps(float temp);

#endif /* WIFIFORMAT_H_ */
