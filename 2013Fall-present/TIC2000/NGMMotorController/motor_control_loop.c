/*
 * motor_control_loop.c
 *
 *  Created on: Jun 14, 2014
 *      Author: Alex
 */

#include "motor_control_loop.h"

#define MOTOR_CONTROL_LOOP_DBG 0

volatile char NGMSCM_torquecontrolloop_isrunning = 0;

Uint16 NGMSCM_Desired_Phase_Current = 0; // For torque-control mode, desired phase current.
Uint16 NGMSCM_CC_Desired_Speed = 0;      // For cruise control mode, desired speed in deci-Hz.

float32 accel_encoder_normval = 0; // Magnitude of accel encoder (0 - 1). Both initially 0.
volatile float32 regen_encoder_normval = 0; // Magnitude of regen encoder (0 - 1).

volatile float32 functional_accel_encoder_normval = 0; // The REAL accel encoder normalized value used for throttle phase current calculation to motor.


/**
 * \brief This ISR is called from the CPU timer, and runs one iteration of the current control loop of the motor.
 *        A timer is used to ensure the control loop does not run too fast or slow.
 *        This control loop should run every 10ms.
 */
__interrupt void cpu_timer0_isr_torque_control_loop_iteration(void)
{
	int32 motor_speed, desired_phase_current, desired_regen_current;
	signed char status;
	char drivestate;
	puts("Hey Interrupt");

	motor_speed = NGMEVQuery(AM_SPEED, NGMEV_VALUE_IN_RAM, &status);           // Get motor speed
	if (status != 1) {
		puts("Error retreiving speed!");
		//CAN_send_error_msg(0x05);
		return;
	}
	drivestate = (char)NGMEVQuery(SV_DRIVESTATE, NGMEV_VALUE_IN_RAM, &status); // Get motor drivestate
	if (status == 1)
		stdiolog1int("DS: %d", drivestate);

	// Handle direction changes:
	if (reverseModeRequested && !inReverseMode && motor_speed == 0) {        // Reverse direction, if we are not reversed already.
		if (sendNGMEVCommand("04") != 1) {                                                                   // Set direction to reverse
			puts("Could not reverse!");
		} else {
			inReverseMode = 1;
			puts("REVERSED DIRECTION!");
			//CAN_send_reverse_direction_enabled_msg(1);
		}
	}
	if (!reverseModeRequested && inReverseMode && motor_speed == 0) {         // If we are in reverse mode and switch is turned off, go forward.                                                                                     // If current speed == 0
		if (sendNGMEVCommand("05") != 1) {                                                                   // Set direction to forward
			puts("Could not go forward!");
		} else {
			inReverseMode = 0;                                                                               // Turn off reverse mode.
			puts("FORWARDED DIRECTION");
			//CAN_send_reverse_direction_enabled_msg(0);
		}
	}

	accel_encoder_normval = getAccelEncoderNormval(); // Get acceleration encoder normalized value:
	regen_encoder_normval = getRegenEncoderNormval(); // Get regen encoder normalized value:

	stdiolog1int("ACCEL: %d/100", (int)(accel_encoder_normval*100.0f));
	stdiolog1int("REGEN: %d/100", (int)(regen_encoder_normval*100.0f));

	if (accel_encoder_normval > functional_accel_encoder_normval) {
		// Increase torque.
		functional_accel_encoder_normval += NGMSCM_MAX_THROTTLE_PERCENT_INCREASE_PER_LOOP_CYCLE;
	} else {
		// Decrease torque.
		functional_accel_encoder_normval = accel_encoder_normval; // Allow immediate change, since we are slowing down.
	}
	// Update motor phase current
	desired_phase_current = getNormalizedTorqueFromNormalizedVal( functional_accel_encoder_normval ) * (float32)NGMSCM_MAX_PHASE_CURRENT_DAMPS;
	desired_regen_current = regen_encoder_normval * (float32)NGMSCM_MAX_REGEN_CURRENT_DAMPS;

	// Derate current if regen pedal is pressed:
	if (desired_regen_current > 10 && functional_accel_encoder_normval > 0) functional_accel_encoder_normval -= 3*NGMSCM_MAX_THROTTLE_PERCENT_INCREASE_PER_LOOP_CYCLE; // Derate accleration current if we are pressing on regen.
	if (functional_accel_encoder_normval < 0) functional_accel_encoder_normval = 0;

	if (MOTOR_CONTROL_LOOP_DBG) {
		stdiolog1int("%% Throttle: %d", (int)(getNormalizedTorqueFromNormalizedVal( functional_accel_encoder_normval ) * 100.0f));
		char str[32];
		sprintf(str, "NET MOTOR CURRENT: %ld", desired_phase_current - desired_regen_current);
		puts(str);
	}

	//stdiolog1int("Phase current: %d", (int)desired_phase_current);
	//stdiolog1int("Regen current: %d", (int)desired_regen_current);
	if (NGMEVAssignment(SI_DESIREDPHASEI, NGMEV_VALUE_IN_RAM, desired_phase_current - desired_regen_current) == 1) {
		// Only turn on throttle AFTER desired current is sent to motor.
		if (sendNGMEVCommand("02") != 1) puts("Couldn't throttle enable!"); // Enable throttle.
	} else {
		puts("Couldn't assign throttle!");
	}

	CpuTimer0.InterruptCount++; // Register that this interrupt has occurred.
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP1; // Acknowledge this interrupt to receive more interrupts from group 1
}

int32 motor_speed, desired_phase_current,desired_regen_current;
int main_callable_torque_control_loop_iteration(void)
{
	signed char status;
	char drivestate;
	//puts("Hey Main Interrupt");

	motor_speed = NGMEVQuery(AM_SPEED, NGMEV_VALUE_IN_RAM, &status);           // Get motor speed
	if (status != 1) {
		puts("Error retreiving speed!");
		//CAN_send_error_msg(0x05);
		return -1;
	}
	drivestate = (char)NGMEVQuery(SV_DRIVESTATE, NGMEV_VALUE_IN_RAM, &status); // Get motor drivestate
	//if (status == 1)
		//stdiolog1int("DS: %d", drivestate);

	// Handle direction changes:
	if (reverseModeRequested && !inReverseMode && motor_speed == 0) {        // Reverse direction, if we are not reversed already.
		if (sendNGMEVCommand("04") != 1) {                                                                   // Set direction to reverse
			puts("Could not reverse!");
		} else {
			inReverseMode = 1;
			puts("REVERSED DIRECTION!");
		//	CAN_send_reverse_direction_enabled_msg(1);
		}
	}
	if (!reverseModeRequested && inReverseMode && motor_speed == 0) {         // If we are in reverse mode and switch is turned off, go forward.                                                                                     // If current speed == 0
		if (sendNGMEVCommand("05") != 1) {                                                                   // Set direction to forward
			puts("Could not go forward!");
		} else {
			inReverseMode = 0;                                                                               // Turn off reverse mode.
			puts("FORWARDED DIRECTION");
			//CAN_send_reverse_direction_enabled_msg(0);
		}
	}

	accel_encoder_normval = getAccelEncoderNormval(); // Get acceleration encoder normalized value:
	regen_encoder_normval = getRegenEncoderNormval(); // Get regen encoder normalized value:

	//stdiolog1int("ACCEL: %d/100", (int)(accel_encoder_normval*100.0f));
	//stdiolog1int("REGEN: %d/100", (int)(regen_encoder_normval*100.0f));

	if (accel_encoder_normval > functional_accel_encoder_normval) {
		// Increase torque.
		functional_accel_encoder_normval += NGMSCM_MAX_THROTTLE_PERCENT_INCREASE_PER_LOOP_CYCLE;
	} else {
		// Decrease torque.
		functional_accel_encoder_normval = accel_encoder_normval; // Allow immediate change, since we are slowing down.
	}
	// Update motor phase current
	desired_phase_current = getNormalizedTorqueFromNormalizedVal( functional_accel_encoder_normval ) * (float32)NGMSCM_MAX_PHASE_CURRENT_DAMPS;
	desired_regen_current = regen_encoder_normval * (float32)NGMSCM_MAX_REGEN_CURRENT_DAMPS;

	// Derate current if regen pedal is pressed:
	if (desired_regen_current > 10 && functional_accel_encoder_normval > 0) functional_accel_encoder_normval -= 3*NGMSCM_MAX_THROTTLE_PERCENT_INCREASE_PER_LOOP_CYCLE; // Derate accleration current if we are pressing on regen.
	if (functional_accel_encoder_normval < 0) functional_accel_encoder_normval = 0;

	if (MOTOR_CONTROL_LOOP_DBG) {
		stdiolog1int("%% Throttle: %d", (int)(getNormalizedTorqueFromNormalizedVal( functional_accel_encoder_normval ) * 100.0f));
		char str[32];
		sprintf(str, "NET MOTOR CURRENT: %ld", desired_phase_current - desired_regen_current);
		puts(str);
	}

	//stdiolog1int("Phase current: %d", (int)desired_phase_current);
	//stdiolog1int("Regen current: %d", (int)desired_regen_current);
	if (NGMEVAssignment(SI_DESIREDPHASEI, NGMEV_VALUE_IN_RAM, desired_phase_current - desired_regen_current) == 1) {
		// Only turn on throttle AFTER desired current is sent to motor.
		if (sendNGMEVCommand("02") != 1) puts("Couldn't throttle enable!"); // Enable throttle.
	} else {
		puts("Couldn't assign throttle!");
		return -1;
	}

	CpuTimer0.InterruptCount++; // Register that this interrupt has occurred.
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP1; // Acknowledge this interrupt to receive more interrupts from group 1
	return 1;
}



