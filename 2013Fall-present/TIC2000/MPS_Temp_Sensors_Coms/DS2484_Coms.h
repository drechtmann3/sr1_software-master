/*
 * DS2484_Coms.h
 *
 *  Created on: Apr 4, 2014
 *      Author: Alex
 */

#include "28069Common.h"
#include "I2CForDS2484.h"
#include "stdio.h"
#include "F2806x_Examples.h"
#include "PeripheralHeaderIncludes.h"

#ifndef DS2484_COMS_H_
#define DS2484_COMS_H_

char sendReadCommandOfDS18B20(char tempSenseID);
float32 readTemperatureOfDS18B20(char tempSenseID, int* error_code);
char getROMNumberOfOnlyDevice(Uint16 ROMNumber[]);
char setTempResolutionForTempSensorID(char tempSenseID, char resolutionBits);

char send1WireResetPulse(void);
char resetDS2484(void);
Uint16 calculateDS2484CRC(Uint16 dataBytes[], int num_bytes);
char oneWireWriteByte(Uint16 byte);
Uint16 oneWireReadByte(void);
Uint16 writeDS2484Configuration(Uint16 register_value);

#endif /* DS2484_COMS_H_ */
