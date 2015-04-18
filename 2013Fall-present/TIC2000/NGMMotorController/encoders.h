/*
 * encoders.h
 *
 *  Created on: Jun 7, 2014
 *      Author: Alex
 */
#include "PeripheralHeaderIncludes.h"
#include <stdio.h>
#include "math.h"

#ifndef ENCODERS_H_
#define ENCODERS_H_

// The Bourns EAW encoder reads values from 0 to 127. Here you can set the deadband and usable range of these values.
#define EAW_ACCEL_ENCODER_MAX_VAL (64) // This is the maximum value read from the encoder
                                       // MUST BE >= 0
#define EAW_ACCEL_ENCODER_MIN_VAL (56)  // This is the minimum value read from the encoder, to go to motor torque.
                                       // MUST BE <= 127
#define EAW_REGEN_ENCODER_MAX_VAL (31)
#define EAW_REGEN_ENCODER_MIN_VAL (21)

extern const Uint16 NGMSCMTorqueTransFunc[32];



unsigned char getAccelEncoderValue();
unsigned char getRegenEncoderValue();
float32 getAccelEncoderNormval();
float32 getRegenEncoderNormval();

float32 getNormalizedTorqueFromNormalizedVal(float32 input_val);


#endif /* ENCODERS_H_ */
