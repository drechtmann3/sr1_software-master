/*
 * encoders.c
 *
 *  Created on: Jun 7, 2014
 *      Author: Alex
 */
#include "encoders.h"

// This transfer function maps encoder values to a torque value (proportional).
const Uint16 NGMSCMTorqueTransFunc[32] = {
		0,
		32,
		175,
		468,
		930,
		1573,
		2403,
		3421,
		4625,
		6011,
		7574,
		9307,
		11202,
		13249,
		15439,
		17763,
		20211,
		22772,
		25436,
		28193,
		31033,
		33946,
		36922,
		39952,
		43027,
		46137,
		49275,
		52432,
		55599,
		58770,
		61938,
		65535
};

const char conversionArray[256] = {
		-1, 56, 40, 55, 24, -1, 39, 52, 8, 57, -1, -1, 23, -1, 36, 13, 120, -1, 41,
		54, -1, -1, -1, 53, 7, -1, -1, -1, 20, 19, 125, 18, 104, 105, -1, -1, 25, 106, 38,
		-1, -1, 58, -1, -1, -1, -1, 37, 14, 119, 118, -1, -1, -1, 107, -1, -1, 4, -1, 3,
		-1, 109, 108, 2, 1, 88, -1, 89, -1, -1, -1, -1, 51, 9, 10, 90, -1, 22, 11, -1,
		12, -1, -1, 42, 43, -1, -1, -1, -1, -1, -1, -1, -1, 21, -1, 126, 127, 103, -1, 102,
		-1, -1, -1, -1, -1, -1, -1, 91, -1, -1, -1, -1, -1, 116, 117, -1, -1, 115, -1, -1,
		-1, 93, 94, 92, -1, 114, 95, 113, 0, 72, 71, -1, 68, 73, -1, -1, 29, -1, 70, -1,
		69, -1, -1, 35, 34, 121, -1, 122, -1, 74, -1, -1, 30, 6, -1, 123, -1, -1, -1, 124,
		17, -1, -1, -1, 67, 26, -1, 27, 28, -1, 59, -1, -1, -1, -1, -1, 15, -1, -1, -1,
		-1, -1, -1, -1, -1, 5, -1, -1, -1, 110, -1, 111, 16, 87, 84, -1, 45, 86, 85, -1,
		50, -1, -1, -1, 46, -1, -1, -1, 33, -1, 83, -1, 44, 75, -1, -1, 31, -1, -1, -1,
		-1, -1, -1, -1, 32, 100, 61, 101, 66, -1, 62, -1, 65/*49*/, 99, 60, -1, 47, -1, -1, -1,
		48, 77, 82, 78, 65, 76, 63, -1, 64, 98, 81, 79, 80, 97, 96, 112};



/**
 * \brief This function reads the acceleration encoder value (GPIO 00-07). (Bourns EAW ACE Absolute-Value encoders)
 * \return The encoder value, from 0 to 127.
 */
unsigned char getAccelEncoderValue() {
	char bits[8]; // Read bits from encoder
	int i = 0;
	int index = 0;
	int mult = 1;
	int result;

	while (1){
		bits[0] = GpioDataRegs.GPADAT.bit.GPIO0;
		bits[1] = GpioDataRegs.GPADAT.bit.GPIO1;
		bits[2] = GpioDataRegs.GPADAT.bit.GPIO2;
		bits[3] = GpioDataRegs.GPADAT.bit.GPIO3;
		bits[4] = GpioDataRegs.GPADAT.bit.GPIO4;
		bits[5] = GpioDataRegs.GPADAT.bit.GPIO5;
		bits[6] = GpioDataRegs.GPADAT.bit.GPIO6;
		bits[7] = GpioDataRegs.GPADAT.bit.GPIO7;

		index = 0;
		mult = 1;
		for(i=0;i<8;i++){
			index+=mult*bits[i];
			mult*=2;
		}
		//stdiolog1int("acc val %d",index);

		result = conversionArray[index];
		if (result == -1) puts("Acceleration encoder error! Check connections!");

		if(result==66 || result==65){
			result-=2;
		}
		return result;
	}
}

/**
 * \brief This function reads the regenerative braking encoder value (GPIO 08-15). (Bourns EAW ACE Absolute-Value encoders)
 * \return The encoder value, from 0 to 127.
 */
unsigned char getRegenEncoderValue() {
	char bits[8]; // Read bits from encoder
	int i = 0;
	int index = 0;
	int mult = 1;
	int result;

	while (1){
		bits[0] = GpioDataRegs.GPADAT.bit.GPIO8;
		bits[1] = GpioDataRegs.GPADAT.bit.GPIO9;
		bits[2] = GpioDataRegs.GPADAT.bit.GPIO10;
		bits[3] = GpioDataRegs.GPADAT.bit.GPIO11;
		bits[4] = GpioDataRegs.GPADAT.bit.GPIO12;
		bits[5] = GpioDataRegs.GPADAT.bit.GPIO13;
		bits[6] = GpioDataRegs.GPADAT.bit.GPIO14;
		bits[7] = GpioDataRegs.GPADAT.bit.GPIO15;

		index = 0;
		mult = 1;
		for(i=0;i<8;i++){
			index+=mult*bits[i];
			mult*=2;
		}
		//stdiolog1int("regen val %d",index);

		result = conversionArray[index];
		if (result == -1) puts("Regenerative encoder error! Check connections!");

		return result;
	}
}

/**
 * \brief This function converts a linear value (encoder press value, normalized), and converts it to a normalized
 *        torque value.
 *        This function linearly interpolates between the above lookup torque table.
 * \return A normalized torque value, from 0 to 1.
 */
float32 getNormalizedTorqueFromNormalizedVal(float32 input_val) {
	char indx, indx2;
	float32 val1, val2, rem, ret;
	indx = floor(input_val*32.0f) - 1;
	if (indx < 0) indx = 0;
	if (indx > 31) indx = 31;
	indx2 = indx + 1;
	if (indx2 < 0) indx2 = 0;
	if (indx2 > 31) indx2 = 31;
	val1 = (float32)NGMSCMTorqueTransFunc[indx] / 65535.0f;
	val2 = (float32)NGMSCMTorqueTransFunc[indx2] / 65535.0f;
	rem = input_val*32.0f - indx;

	ret = val1 + (val2 - val1) * rem;
	if (ret > 1.0f) return 1.0f;
	if (ret < 0.0f) return 0.0f;
	return ret;
}

float32 smoothed_accel_encoder_normval = 0;
/**
 * Gets the desired acceleration value in the range [0-1].
 * Note: Encoder is mounted in reverse, so max throttle is min value in terms of readings.
 *
 * @author Andrey Kurenkov, Alex Popescu, Reid Kersey
 */
float32 getAccelEncoderNormval() {
	//TODO
	char accel_val;
	float32 accel_encoder_normval;
	accel_val = getAccelEncoderValue();
	if (accel_val < EAW_ACCEL_ENCODER_MIN_VAL) {// We are already at full throttle
		stdiologstr("Accel encoder below minimum value.");
		accel_encoder_normval = 1.0;
	} else if (accel_val > EAW_ACCEL_ENCODER_MAX_VAL) {// Check if acceleration encoder is in zero deadzone
		stdiologstr("Accel encoder above maximum value.");
		accel_encoder_normval = 0.0;
	} else { // Normal operating range
		accel_encoder_normval = 1.0f- (float)(accel_val - EAW_ACCEL_ENCODER_MIN_VAL) / (float)(EAW_ACCEL_ENCODER_MAX_VAL - EAW_ACCEL_ENCODER_MIN_VAL);
	}
	smoothed_accel_encoder_normval = smoothed_accel_encoder_normval*0.5f + accel_encoder_normval*0.5f;
	return smoothed_accel_encoder_normval;
}

float32 smoothed_regen_encoder_normval = 0;
float32 getRegenEncoderNormval() {
	char regen_val;
	float32 regen_encoder_normval;
	regen_val = getRegenEncoderValue();
	if (regen_val < EAW_REGEN_ENCODER_MIN_VAL) {
		stdiologstr("Regen encoder below minimum value.");
		regen_encoder_normval = 0.0; // Check if regen encoder is in zero deadzone
	} else if (regen_val > EAW_REGEN_ENCODER_MAX_VAL) {
		stdiologstr("Regen encoder above maximum value.");
		regen_encoder_normval = 1.0; // We are already at full regen
	} else { // Normal operating range
		regen_encoder_normval = (float)(regen_val - EAW_REGEN_ENCODER_MIN_VAL) / (float)(EAW_REGEN_ENCODER_MAX_VAL - EAW_REGEN_ENCODER_MIN_VAL);
	}
	smoothed_regen_encoder_normval = smoothed_regen_encoder_normval*0.5f + regen_encoder_normval*0.5f;
	return smoothed_regen_encoder_normval;
}
