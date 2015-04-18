/*
 * main_motor_controller.h
 *
 *  Created on: Jun 1, 2014
 *      Author: Alex
 */

#ifndef MAIN_MOTOR_CONTROLLER_H_
#define MAIN_MOTOR_CONTROLLER_H_

#include "sci_funcs.h"
#include "math.h"
#include "motor_basic_funcs.h"
#include <stdio.h>
#include "motor_control_loop.h"
#include "initialization.h"

#include "F2806x_Examples.h"   // Examples Include File

typedef enum {NGMSCM_CONTROLSTATE_TORQUE_CONTROL, // Torque control (includes regen braking)
			  NGMSCM_CONTROLSTATE_CRUISE_CONTROL  // Cruise control
} NGMSCM_ControlStateType;



#define CRUISE_CONTROL_ACCEL_PEDAL_INCREASE 500.0f // How much to increase speed in dHz in cruise control, MAX.
#define MOTOR_WATCHDOG_TIME (10) //Tenths of seconds the motor is allowed not to receive a command before shutting down.

extern volatile NGMSCM_ControlStateType NGMSCM_ControlState;
extern volatile char inReverseMode;
extern volatile char reverseModeRequested;

signed char beginNGMSCMTorqueControlLoop();
void endNGMSCMTorqueControlLoop();


#endif /* MAIN_MOTOR_CONTROLLER_H_ */
