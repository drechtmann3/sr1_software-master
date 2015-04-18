
#include "buttons.h"



/**
 * \brief Returns true if cruise control was toggled, 0 otherwise. Must be called in a high-frequency loop. Debounces the toggle switch.
 * \note Cruise control is a toggle switch.
 */
Uint32 cruiseControl0Counts = 0;
Uint32 cruiseControl1Counts = 0;
char cruiseControlWasToggled() {
	char cc = GpioDataRegs.GPADAT.bit.GPIO22; // Replace with whichever GPIO CC toggle is
	if (cc == 0) {
		cruiseControl0Counts++; if (cruiseControl0Counts == 0) cruiseControl0Counts--;
		if (cruiseControl1Counts >= 10e3L && cruiseControl0Counts >= 10e3L) {
			cruiseControl1Counts = 0; // Reset when we have returned to 0.
			return 1;
		}
	} else { // We have recieved a 1
		cruiseControl1Counts++; if (cruiseControl1Counts == 0) cruiseControl1Counts--;
		cruiseControl0Counts = 0;
	}

	return 0;
}

/**
 * \brief Returns true if brake pedal is pressed. Must be called in a high-frequency loop. Debounces.
 */
Uint32 brakePedalPressedCounts = 0;
char brakePedalIsPressed() {
	char pp = GpioDataRegs.GPADAT.bit.GPIO21; // Replace with whichever GPIO mech brake button is hooked up to.
	if (pp) {
		brakePedalPressedCounts++;
		if (brakePedalPressedCounts == 0) brakePedalPressedCounts--; // If overflow, keep at max.
	} else {
		brakePedalPressedCounts = 0;
	}
	if (brakePedalPressedCounts >= 10) return 1; // Don't take chances with the brake pedal, only a LITTLE debounce!
	return 0;
}

/**
 * \brief Returns true if reverse switch is on. Must be called in a high-frequency loop. Debounces.
 */
Uint32 reverseSwitchOnCounts = 0;
char reverseSwitchIsOn() {
	char pp = GpioDataRegs.GPADAT.bit.GPIO20; // Replace with whichever GPIO reverse switch button is hooked up to.
	if (pp) {
		reverseSwitchOnCounts++;
		if (reverseSwitchOnCounts == 0) reverseSwitchOnCounts--; // If overflow, keep at max.
	} else {
		reverseSwitchOnCounts = 0;
	}
	if (reverseSwitchOnCounts >= 10) return 1;
	return 0;
}

/**
 * \brief Returns true if right blinker is on. Must be called in a high-frequency loop. Debounces.
 */
Uint32 rightBlinkerOnCounts = 0;
char isRightBlinkerOn() {
	char pp = GpioDataRegs.GPADAT.bit.GPIO22; // Replace with whichever GPIO right blinker button is hooked up to. CHECK THIS
	if (pp) {
		rightBlinkerOnCounts++;
		if (rightBlinkerOnCounts == 0) rightBlinkerOnCounts--; // If overflow, keep at max.
	} else {
		rightBlinkerOnCounts = 0;
	}
	if (rightBlinkerOnCounts >= 10e3L) return 1;
	return 0;
}

/**
 * \brief Returns true if left blinker is on. Must be called in a high-frequency loop. Debounces.
 */
Uint32 leftBlinkerOnCounts = 0;
char isLeftBlinkerOn() {
	char pp = GpioDataRegs.GPADAT.bit.GPIO23; // Replace with whichever GPIO left brake button is hooked up to. CHECK THIS
	if (pp) {
		leftBlinkerOnCounts++;
		if (leftBlinkerOnCounts == 0) leftBlinkerOnCounts--; // If overflow, keep at max.
	} else {
		leftBlinkerOnCounts = 0;
	}
	if (leftBlinkerOnCounts >= 10e3L) return 1;
	return 0;
}

/**
 * \brief Returns true if hazard lights are on. Must be called in a high-frequency loop. Debounces.
 */
Uint32 hazardOnCounts = 0;
char isHazardOn() {
	char pp = GpioDataRegs.GPADAT.bit.GPIO24; // Replace with whichever GPIO right brake button is hooked up to. CHECK THIS
	if (pp) {
		hazardOnCounts++;
		if (hazardOnCounts == 0) hazardOnCounts--; // If overflow, keep at max.
	} else {
		hazardOnCounts = 0;
	}
	if (hazardOnCounts >= 10e3L) return 1;
	return 0;
}

