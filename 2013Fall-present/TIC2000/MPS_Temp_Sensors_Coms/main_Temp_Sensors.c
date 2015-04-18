#include "DS2484_Coms.h"

// Function prototype for Piccolo initialization routine:
void DeviceInit(void);

void main(void) {
	InitSysCtrl();
	i2c_init(); // Initialize I2C on microcontroller, including pins.
	puts("Set up I2C successfully.");

	// Reset DS2484, to clear any ongoing 1-wire transfers:
	if (resetDS2484() == 0) puts("Resetting DS2484 failed! There could be an I2C bus/DS2484 hardware problem!");

	/*
	  // Use to find ROM number of 1 temp sensor:
	Uint16 ROM_num1[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	if ( getROMNumberOfOnlyDevice(ROM_num1) == 1 ) {
		char string[50];
		sprintf(string, "Read ROM number: %x %x %x %x %x %x %x %x", ROM_num1[7], ROM_num1[6], ROM_num1[5], ROM_num1[4], ROM_num1[3], ROM_num1[2], ROM_num1[1], ROM_num1[0]);
		puts(string);
	} else
		puts("Error finding ROM number");
*/


	//Uint16 ROM_num[8] = {0x28, 0x29, 0x37, 0x9c, 0x05, 0x0, 0x0, 0x2d};
	//Uint16 ROM_num[8] = {0x28, 0x51, 0xd0, 0x9b, 0x05, 0x0, 0x0, 0x19};
	int error = 0;

	while (1) {
		if (!sendReadCommandOfDS18B20(0)) puts("Error sending read command!");
		int i; for (i = 0; i < 30; i++) sendReadCommandOfDS18B20(1); // Read dummy sensor 30 times for now.

		// Wait for all temperatures to be converted...
		DELAY_US(300e3L); // The read commands take ~500ms, and 750ms are needed to convert temp total.
		float32 temp;
		for (i = 0; i < 30; i++) temp = readTemperatureOfDS18B20(0, &error);
		if (error == 1) {
			puts("I2C Error triggered!");
			// Try to reset I2C:
			i2c_init();
			continue;
		}
		if (error == 2) {
			puts("Data integrity error triggered!");
			continue;
		}
		if (error == 0) { // Data is OK:
			float32 faren = 9.0f / 5.0f * temp + 32.0f;
			char string[70];
			sprintf(string, "Temperature read (Degrees C): %d.%d (Degrees F):%d.%d", (int)temp, ((int)(temp*10))%10, (int)faren, ((int)(faren*10))%10);
			puts(string);
		}
	}
}

