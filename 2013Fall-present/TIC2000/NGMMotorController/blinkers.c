/*
 * blinkers.c
 *
 *  Created on: Sept 27, 2014
 *      Author: Victoria
 */
#include "buttons.h"
#include "blinkers.h"
#include "F2806x_Cla_typedefs.h"
#include "F2806x_Gpio.h"

char rightBlinker;
char leftBlinker;
char hazardLights;
char brakeLights;

/**
 * \brief Sets all lights on car depending on which button is pressed.
 */
void updateBlinkers() {
	rightBlinker = isRightBlinkerOn();
	leftBlinker = isLeftBlinkerOn();
	hazardLights = isHazardOn();
	brakeLights = brakePedalIsPressed();
	if (brakeLights) {
		GpioDataRegs.GPBSET.bit.GPIO32 = 1; // set output for brakes
	} else if (rightBlinker || hazardLights) {
		GpioDataRegs.GPBSET.bit.GPIO33 = 1; // set output for rightBlinker
	} else if (leftBlinker || hazardLights) {
		GpioDataRegs.GPBSET.bit.GPIO34 = 1; // set output for leftBlinker
	}
}
