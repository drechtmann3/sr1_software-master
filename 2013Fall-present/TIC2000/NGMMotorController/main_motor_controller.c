/**
 * \brief This is the motor controller code for the NGM SCM 150 motor, used on SJ-1 2014.
 *
 * \details RS-232 serial communications are used to communicate with and monitor the state
 *          of the NGM motor.
 *
 * \details This code is meant to work with the following components:
 *   		1.) (1) NGM-SCM150 Motor [Connected to Motor Controller]
 *   		2.) (1) NGM-EV-C200 Motor Controller [Connected to microcontroller by serial]
 *   		3.) (2) Bourns EAW0J-B24-AE0128L Mechanical Encoders (Accl. & Regen Pedals)
 *   		    [Connected via GPIO to microcontroller] Datasheet: http://www.mouser.com/ds/2/54/ACE-73551.pdf
 *  		4.) (2) Switches (Forward/Reverse, Brake-Pedal-Pressed) [Connected via GPIO to microcontroller]
 *   		5.) (1) TI F28069 C2000 Piccolo microcontroller
 *   		DASH-BOARD in 1 : BRAKE SWITCH (1 = MECH. BRAKE ON, 0 = BRAKE OFF)
 *   		DASH-BOARD in 2 : FORWARD/REV SWITCH (1 = REVERSE, 0 = FORWARD)
 *   		DASH-BOARD in 3 : CRUISE-CONTROL EN. TOGGLE (TRANSIENT 1->0 = CRUISE CONTROL TOGGLE)
 *   			NOTE: For DASH-BOARD, closed connection = 1, open connection = 0
 *
 * \pre Steps for running this code:
 *      1.) Make sure to define the encoders' limits in encoders.h, as well as torque, timing, speed constants in motor_control_loop.h, main_motor_controller.h!
 *      2.) Ready the motor (precharge, then power it.) [IMPORTANT!]
 *      3.) Run this code.
 *
 * \warning If the aforementioned components are not connected and functioning, do not run this code!
 *          Undefined behavior will result!
 *
 * \author Alex Popescu <pop850@gmail.com>
 * \author Reid Kersey <reidkersey@gmail.com> 678-736-0899
 * \author Andrey Kurenkov <akurenkov3@gatech.edu> 678-900-4326
 *
 * Thanks to Brian Kuo for help.
 *
 * \version 0.1
 * \date 6/1/2014
 * \ingroup motor
 */

#include "main_motor_controller.h"

volatile NGMSCM_ControlStateType NGMSCM_ControlState;

float32 CCinitialAccelNormVal = 0; // Initial acceleration value when cruise control is started
int32 CCinitialSpeed = 0;          // Initial speed (dHz) in cruise control
volatile char inReverseMode = 0;   // Initially, we are in forward mode.
volatile char reverseModeRequested = 0;
char mechBrake, cruiseControlToggled;
// When SYSclock=70MHz, CAN bit rate = 1758000
float32 accel_normval, regen_normval;

void main(void)
{
	volatile Uint32 timeI;
	Uint32 CAN_heartbeat_counter = 0;

	/******************* STARTUP SEQUENCE *******************/
	initializeuCANndSerialComs();              // Initialize serial communications, GPIO, and CAN

	/* CAN TEST MESSAGES
	while(1) {
		CAN_send_speed_msg((Uint16)getAccelEncoderValue() * 10);
		for (i = 0; i < .1e6; i++);
		unsigned char faults[4] = {0x20, 0x08, 0x04, 0x02};
		CAN_send_faults_msg(faults);
		for (i = 0; i < .1e6; i++);
		CAN_send_drivestate_msg(74);
		for (i = 0; i < .1e6; i++);
		CAN_send_throttle_regen_msg(-80);
		for (i = 0; i < .1e6; i++);
	}
	 */

	clearSCIFIFOAndNGMEVReceiveQueue();       // Clear comms buffer with motor

	/*while(1){//Test encoders
		stdiolog1int("Acc : %d", getAccelEncoderValue());
		stdiolog1int("Encoder 2: %d", getRegenEncoderValue());
		accel_normval = getAccelEncoderNormval();
		regen_normval = getRegenEncoderNormval();
	}*/
	// Test Motor RS-232
	//clearSCIFIFOAndNGMEVReceiveQueue();
	/*while(1) {
		mechBrake = scia_send_char('b'); // Send "b\r", do not wait for an echo. This clears the command-receive buffer of the motor.
		while (SciaRegs.SCIFFRX.bit.RXFFST == 0) {}

		char receivedChar = SciaRegs.SCIRXBUF.all; // Store read character.
		stdiolog1int("Received: %c", receivedChar);
	}*/


	/*while(1){check buttons
		cruiseControlToggled = cruiseControlWasToggled();
		reverseModeRequested = reverseSwitchIsOn();
	}*/

	// Test to make sure the motor is connected and functioning. If not, wait until it is.
	// If cannot communicate: user must intervene to fix settings, etc. An error message describing the situation should have been printed.


	while (testNGMEVComsAndOperation() != 1) {
		stdiologstr("MOTOR ERROR 01; ABORTING!");

		//CAN_send_error_msg(0x05);
		for (CAN_heartbeat_counter = 0; CAN_heartbeat_counter < .1e6; CAN_heartbeat_counter++); // Idle a little
		//CAN_send_speed_msg(0);

	}
	getNGMEVMotorStats(); // Printout current state of the motor.
	getNGMEVMotorEEPROMVals();//Printout EEPROM values
	NGMEVGetFaults(); // Print/send any faults found.
	stdiologstr("NGM-SCM150 READY");
	/***************** END STARTUP SEQUENCE ******************/


	NGMSCM_ControlState = NGMSCM_CONTROLSTATE_TORQUE_CONTROL; // Set startup state to torque control.
	if (sendNGMEVCommand("05") != 1) puts("Couldn't set forward!"); // Set direction to forward
	//CAN_send_reverse_direction_enabled_msg(0);

	if (beginNGMSCMTorqueControlLoop() != 1) puts("Could not exit Cruise Control!");

	setMotorWatchogTime(MOTOR_WATCHDOG_TIME);
	// Enter the main motor control loop
	while (1) {
		mechBrake = brakePedalIsPressed();               // Must be called every loop cycle, for debouncing algorithm.
		cruiseControlToggled = cruiseControlWasToggled();
		reverseModeRequested = reverseSwitchIsOn();
		accel_normval = getAccelEncoderNormval();
		regen_normval = getRegenEncoderNormval();

		main_callable_torque_control_loop_iteration();
		while(timeI<1000){
			timeI++;
		}
		timeI=0;
		//if (mechBrake) puts("Mechbrake!");
		//if (reverseModeRequested) puts ("Reverse mode!");
		//if (cruiseControlToggled) puts("CC Toggled!");

		/*switch (NGMSCM_ControlState) {
		case NGMSCM_CONTROLSTATE_TORQUE_CONTROL:
			// Go to cruise control
			if (regen_normval<0.005 && !mechBrake && cruiseControlToggled) { // ONLY go to cruise if NO BRAKES are pressed, AND NO pedals.
				endNGMSCMTorqueControlLoop();                                                                      // End torque control loop

				buffer = NGMEVQuery(AM_SPEED, NGMEV_VALUE_IN_RAM, &status);                                        // Get current speed
				if (status != 1) {
					puts("Could not enter cruise control!");
					break;
				}
				CCinitialSpeed = buffer;                                                                           // Store initial speed
				CCinitialAccelNormVal = accel_normval;                                                             // Store initial accel pedal value
				if (NGMEVAssignment(SI_DESIREDSPEED, NGMEV_VALUE_IN_RAM, buffer) != 1) {                           // Set desired speed
					puts("Couldn't assign CC speed!");
					CAN_send_error_msg(0x07);
					break;
				}
				if (sendNGMEVCommand("07") != 1) {                                                                 // Go to speed mode
					puts("Couldn't enable CC!");
					CAN_send_error_msg(0x07);
					break;
				}
				if (sendNGMEVCommand("02") != 1) {                                                                 // Turn on throttle
					puts("Couldn't start CC!");
					CAN_send_error_msg(0x07);
					break;
				}
				NGMSCM_ControlState = NGMSCM_CONTROLSTATE_CRUISE_CONTROL;
				stdiologstr("Going to cruise control!");
				CAN_send_cruise_control_enabled_msg(1); // Send we are in CC on CAN
				break;
			}
			break;

		case NGMSCM_CONTROLSTATE_CRUISE_CONTROL:
			// Go to torque control
			if (regen_normval > 0 || mechBrake || cruiseControlToggled) {  // Only go to torque control loop if regen is pressed OR mechanical brake is pressed OR cruise control is turned off
				functional_accel_encoder_normval = 0;
				if (beginNGMSCMTorqueControlLoop() == 1) {
					NGMSCM_ControlState = NGMSCM_CONTROLSTATE_TORQUE_CONTROL;
					CAN_send_cruise_control_enabled_msg(0); // Send we are out of CC on CAN
					puts("Going to torque mode!");
				} else {
					puts("Could not exit Cruise Control!");
					CAN_send_error_msg(0x07);
				}
				break;
			}

			if (CAN_heartbeat_counter == 0) { // Only after CAN heartbeat sent.
				if (accel_normval >= CCinitialAccelNormVal) {                  // Check if we should change speed in cruise control:  NOTE: This slows down loop execution, so only do this AFTER CAN messages have been sent.
					if (NGMEVAssignment(SI_DESIREDSPEED, NGMEV_VALUE_IN_RAM, CCinitialSpeed + (int32)(CRUISE_CONTROL_ACCEL_PEDAL_INCREASE*(accel_normval-CCinitialAccelNormVal))) != 1) {                           // Set desired speed
						puts("ERR: Couldn't assign CC speed!");
						CAN_send_error_msg(0x07);
					}
				} else {
					if (NGMEVAssignment(SI_DESIREDSPEED, NGMEV_VALUE_IN_RAM, CCinitialSpeed) != 1) {                           // Set desired speed
						puts("ERR: Couldn't assign CC0 speed!");
						CAN_send_error_msg(0x07);
					}
				}
			}
			break;

		default:
			puts("Not in a valid motor state!");
			CAN_send_error_msg(0x02);
			return;
		}

		// Send CAN heartbeat:
		CAN_heartbeat_counter++;
		if (CAN_heartbeat_counter >= 80e3L) {
			//puts("Sending CAN heartbeat!");
			if (NGMSCM_ControlState==NGMSCM_CONTROLSTATE_TORQUE_CONTROL) PieCtrlRegs.PIEIER1.bit.INTx7 = 0; // Disable control loop interrupt, so it does not run while we send heartbeat
			send_CAN_heartbeat_messages(); // Send heartbeat messages to indicate the motor is still alive
			if (NGMSCM_ControlState==NGMSCM_CONTROLSTATE_TORQUE_CONTROL) PieCtrlRegs.PIEIER1.bit.INTx7 = 1; // Re-enable interrupt
			CAN_heartbeat_counter = 0;
		}*/

	} // End of main motor control loop

}

/**
 * \brief Enables the NGM SCM 150 motor using the NGM EVM-200 motor controller for throttle, by changing torque.
 * \detail Attempt to enable the motor for throttle control, in the forward direction (by default). The input torque
 *         is read from an encoder value, then transformed by a transfer function, and finally sent to the motor
 *         to be set as the phase current (proportional to torque).
 * \return  1: Control loop started OK.
 * \return -1: Error starting the control loop (error should be printed or sent via CAN).
 */
signed char beginNGMSCMTorqueControlLoop() {
	signed char status = 0;
	int32 buffer;

	if (NGMSCM_torquecontrolloop_isrunning) {
		stdiologstr("Control loop is already running!");
		return -1;
	}

	// Read current drivestate to see if we are already running.
	buffer = NGMEVQuery(SV_DRIVESTATE, NGMEV_VALUE_IN_RAM, &status);
	if (status != 1) return -1;
	if (buffer < DS_POWERUPEND || buffer == DS_INTERLOCK || buffer == DS_INTERLOCKCOAST) {
		stdiologstr("Motor is not in valid drivestate to begin throttling.");
		return -1;
	}

	if (sendNGMEVCommand("00") != 1) return -1; // Enable motor.
	// Let control loop Throttle enable!
	if (sendNGMEVCommand("06") != 1) return -1; // Enable Torque control
	// Set control loop to torque control.
	NGMSCM_torquecontrolloop_isrunning = 1;
	functional_accel_encoder_normval = 0; // Reset acceleration to 0 when starting.
	//PieCtrlRegs.PIEIER1.bit.INTx7 = 1; // Enable control loop interrupt, to start running control loop.
	//CAN_send_cruise_control_enabled_msg(0); // Send we are out of CC on CAN, since we are torque mode.
	return 1;
}

void endNGMSCMTorqueControlLoop() {
	NGMSCM_torquecontrolloop_isrunning = 0;
	PieCtrlRegs.PIEIER1.bit.INTx7 = 0; // Disable control loop interrupt, to stop running control loop.
}
