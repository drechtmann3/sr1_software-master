/*
 * DS2484_Coms.h
 *
 *  Created on: Apr 4, 2014
 *      Author: Alex
 */
#ifndef DS2484_COMS_H_
#define DS2484_COMS_H_

//DEFINES
#define DS2484_ADDRESS 0x18 // 7-bit I2C slave address of the DS2484
#define READ_TRIES_BEFORE_FAIL 1e3L // How many times we try to read bytes from I2C before declaring an error.

#define _10_BIT_RESOLUTION_START 50.0f // Start 10-bit (+/- 2C) resolution (from default 9-bit) at 50deg C
#define _12_BIT_RESOLUTION_START 55.0f // Start 12-bit (+/- 0.5C) resolution at 55deg C

//PROTOTYPES
char sendReadCommandOfDS18B20(char tempSenseID); //Send read temp command
float32 readTemperatureOfDS18B20(char tempSenseID, int* error_code); //Get the temperature of the temperature sensor
char getROMNumberOfOnlyDevice(Uint16 ROMNumber[]); //Read the ROM number of the only 1-wire device
char setTempResolutionForTempSensorID(char tempSenseID, char resolutionBits); //Set temperature conversion resolution

char send1WireResetPulse(void); //Tell DS2484 to transmit reset pulse on 1-wire bus
char resetDS2484(void); //Resets the DS2484
Uint16 calculateDS2484CRC(Uint16 dataBytes[], int num_bytes); //Returns the Cyclic Redundancy Check for the received bytes from the DS2484
char oneWireWriteByte(Uint16 byte); //Writes a single byte to the 1-wire line
Uint16 oneWireReadByte(void); //Reads a single byte from the 1-wire line
Uint16 writeDS2484Configuration(Uint16 register_value); //Write the configuration register byte on the DS2484



#endif /* DS2484_COMS_H_ */
