#include "BMS.h"
//#include "CAN.h"

/*
 * This file has the functions for determining the temperatures of the batteries.
 */


volatile float32 tempSensorReadings[NUM_TEMP_SENSORS]; //Readings, in degrees C
volatile unsigned char tempSensorStatuses[NUM_TEMP_SENSORS]; //Status of temp sensors
volatile unsigned int tempSensorTimers[NUM_TEMP_SENSORS];
volatile unsigned char tempSensorReadCommandSent[NUM_TEMP_SENSORS];
volatile char tempSensorsRead = -1; // Only use temp sensor readings if this is ==+1!
//TODO List of temp sensors and IDs is in DS2484_Coms.c??

/**
 * \brief Read temperature sensors, and store in tempSensorReadings, statuses in tempSensorStatuses.
 * \brief Provide min and max temp sensor indices to read, inclusive
 * \return -1 : Reading temp sensors failed
 * \return  0 : Reading temp sensors succeeded
 */
signed char readTempSensor(char indx) {
	int error;
/*
	for (i = minIndx; i <= maxIndx; i++) {
		if (!sendReadCommandOfDS18B20(i)) { // Send read command to each temp sensor
			return 0;
		}
	}
	*/
	// Wait for all temperatures to be converted...
	//DELAY_US(700e3L); // The read commands take ~500ms, and 750ms are needed to convert temp total.
	//DELAY_US(750e3L); // Should be 300e3L in production code! (all 30 temp sensors in)
	//Uint32 delayi = 0;
	//for (delayi = 0; delayi < 4e5; delayi++) { }

		error = 0;
		tempSensorReadings[indx] = readTemperatureOfDS18B20(indx, &error); // Save temperature of each sensor

		if (error == 0) {
			tempSensorStatuses[indx] = 1;
/*
			if (tempSensorReadings[i] >= 0.0f) {
				char str[64];
				sprintf(str, "Temp %i: %iC", i, (int)(tempSensorReadings[i]));
				puts(str);
			}
			*/

		}
		else tempSensorStatuses[indx] = 0; // Set error! This temp sensor did not respond correctly!
		if (error == 1) {
			puts("I2C Error triggered!");
			// Try to reset I2C:
			i2c_init();
			return 0;
		}
		if (error == 2) {
			puts("Data integrity error triggered!");
			return 0;
		}
	tempSensorsRead = 1;
	return 1;
}

/**
 * \brief Initialize temp sensors, must be called before temp sensors are read!
 * \return -1 : Initializing temp sensors failed
 * \return  0 : Initializing temp sensors succeeded
 */
signed char initializeTempSensors() {
	i2c_init(); // Initialize I2C on microcontroller, including pins.
	puts("Set up I2C successfully.");
	tempSensorReadings[0]=25; //ignore the first entry in the temp reading array since it is indexed from 1 rather than 0
	// Reset DS2484, to clear any ongoing 1-wire transfers:
	if (resetDS2484() == 0) {
		puts("Resetting DS2484 temp sense master failed! There could be an I2C bus/DS2484 hardware problem!");
		return 0;
	}
	return 1;
}

/**
 * \brief Get the highest temp sensor reading. If no readings are taken yet, returns 0.
 */
float32 getHighestTempSensorReading() {
	float32 highest = 0;
	int i;
	if (tempSensorsRead != 1) return highest;
	for (i = 1; i < NUM_TEMP_SENSORS; i++) {
		if (tempSensorStatuses[i] == 1 && tempSensorReadings[i] > highest) highest = tempSensorReadings[i];
	}
	return highest;
}

/**
 * \brief Send readings on CAN, with format:
 * Temperature is stored in deci-degrees-Celcius (C*10), as an Uint16.
 * [temp sense status][temperature_H][temperature_L][Temp sense number] [temp sense status][temperature_H][temperature_L][Temp sense number], for as many CAN messages as neccessary.
 */
//void sendTempSensorReadingsViaCAN() {
//	Uint32 CANbuffer[2];
//	unsigned char i, tid0;
//	Uint16 reading;
//	if (tempSensorsRead != 1) return; // Nothing read yet.
//
//	for (i = 0; i < NUM_TEMP_SENSORS/2 + 1; i++) {
//		tid0 = i * 2;
//		reading = (Uint16)tempSensorReadings[tid0];
//		CANbuffer[0] = (Uint32)tid0 | ((Uint32)reading<<8) | ((Uint32)tempSensorStatuses[tid0]<<24);
//		CANbuffer[1] = 0;
//		if (tid0 + 1 < NUM_TEMP_SENSORS) {
//			reading = (Uint16)tempSensorReadings[tid0 + 1];
//			CANbuffer[1] = (Uint32)(tid0+1) | ((Uint32)reading<<8) | ((Uint32)tempSensorStatuses[tid0 + 1]<<24);
//		}
//		CAN_send(CANbuffer, 8, BMS_TEMP, 15, 1); // Put 8 bytes of data in Mailbox 15. Wait to send
//	}
//
//	CANbuffer[0] = (Uint32)0x98 | ((Uint32)((Uint16)getHighestTempSensorReading()) << 8); // Send highest temp sensor reading.
//	CANbuffer[1] = 0;
//	CAN_send(CANbuffer, 8, BMS_TEMP, 16, 1); // Put 8 bytes of data in Mailbox 16. Wait to send.
//}
