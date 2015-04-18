/*
 * motor_control_loop.h
 *
 *  Created on: Jun 14, 2014
 *      Author: Alex
 */

#ifndef MOTOR_CONTROL_LOOP_H_
#define MOTOR_CONTROL_LOOP_H_

#include "PeripheralHeaderIncludes.h"
#include "F2806x_Examples.h"   // Examples Include File
#include <stdio.h>
#include "motor_basic_funcs.h"
#include "buttons.h"
#include "main_motor_controller.h"
#include "blinkers.h"

/* *************** ENCODER/MOTOR CONTROL LOOP CONSTANTS *************** */
#define ACCELERATION_ENCODER_SMOOTHING_FRAC 0.1f // The affect the current value of the encoder has on past values.
                                                 // [0 to 1] 0 means no effect (too much smoothing), and 1 means immediate effect on motor speed (no smoothing).

#define NGMSCM_MAX_THROTTLE_PERCENT_INCREASE_PER_LOOP_CYCLE 0.05f // The amount the throttle can increase, PER CONTROL LOOP CYCLE when we want to go faster.
                                                                  // WARNING: IF YOU INCREASE THE FREQUENCY OF THE CONTROL LOOP, YOU WILL BE ABLE TO TURN UP THROTTLE FASTER!

#define NGMSCM_MAX_PHASE_CURRENT_DAMPS 1500.0f // The maximum current that can be delivered to the motor in torque control mode (deci-Amps), by encoder

#define NGMSCM_MAX_REGEN_CURRENT_DAMPS 800.0f // Maximum regen phase current selectable by encoder

/* ************* END ENCODER/MOTOR CONTROL LOOP CONSTANTS ************* */


extern volatile char NGMSCM_torquecontrolloop_isrunning;
extern volatile float32 functional_accel_encoder_normval;

__interrupt void cpu_timer0_isr_torque_control_loop_iteration(void);
int main_callable_torque_control_loop_iteration(void);
#endif /* MOTOR_CONTROL_LOOP_H_ */
