// /**
	// @file GPIO.c
	// @author Reid Kersey <reidkersey@gmail.com> 678-736-0899
	// @brief
	// @details
	// @warning
	// @note
	// @todo Make this call functions that change the values, or use data store, do not execute code
	// directly in the function.
	// @ingroup
	// @addtogroup
	// @brief
	// @{
// */

// #include "GPIO.h"
// #include "lights.h"
// #include "DIO.h"
// #include "pins.h"
// #include "datastore.h"
// #include "threads.h"
// #include "motor.h"
// #include <pthread.h>
// #include <unistd.h>
// #include <stdio.h>

// /**
	// @author Reid Kersey <reidkersey@gmail.com> 678-736-0899
	// @brief This function initialzes the button inputs.
	// @warning This function must be run in order to use the GPIO functions.
// */
// void initGPIO(){  // initialize pin directions 
	
	// // InitDIO_direction(AIRGAP_DOWN, 	AIRGAP_DOWN_ROW, 	GPIO_INPUT);
	// // InitDIO_direction(AIRGAP_UP, 	AIRGAP_UP_ROW, 		GPIO_INPUT);
	// // InitDIO_direction(CRUISE_DOWN, 	CRUISE_UP_ROW, 		GPIO_INPUT);
	// // InitDIO_direction(CRUISE_UP, 	CRUISE_UP_ROW, 		GPIO_INPUT);
	// // InitDIO_direction(MECH_BRAKE, 	MECH_BRAKE_ROW, 	GPIO_INPUT);

	
	
	
	// //This is initializing the pins for the blinkers, I think? -Brian Kuo
	// InitDIO_direction(BLINK_L, 		BLINK_L_ROW, 		GPIO_INPUT);
	// InitDIO_direction(BLINK_R, 		BLINK_R_ROW, 		GPIO_INPUT);
	// InitDIO_direction(HAZARDS, 		HAZARDS_ROW, 		GPIO_INPUT);
	
	// setInt("BLINKER_R_ON", 0);
	// setInt("BLINKER_L_ON", 0);
	// setInt("HAZARDS_ON", 0);
	
	// setInt(DS_DIR_BUTTON, 0);
// }

// /**
	// @author Reid Kersey <reidkersey@gmail.com> 678-736-0899
	// @brief This function checks each button input, and then runs the nessassary code.
	// @warning The GPIO must be initialized.
	// @todo Software debounce buttons (dont use checkpin)
// */
// void detectGPIO(){

	// //GENERATES ERRORS in compiling!!!! fix it!!
	
	// //AIRGAP
	// //TODO stop airgap if it is not progressing
	// //if(CheckPin(AIRGAP_DOWN, AIRGAP_DOWN_ROW)){
		// // start down
	// //}
	// //else if(CheckPin(AIRGAP_UP, AIRGAP_UP_ROW)){
		// //start up
	// //}
	// //else{
		// //stop airgap
	// //}
	
	// //Cruise Control
	// //TODO define rate, stop timer
	// //TODO dont set cruise speed if motor is in torque mode
	// // if(CheckPin(CRUISE_DOWN, CRUISE_DOWN_ROW)){
		// // setCruiseSpeed(getInt(DS_CRUISE_SPEED) - 1);
	// // }
	// // else if(CheckPin(CRUISE_UP, CRUISE_UP_ROW)){
		// // setCruiseSpeed(getInt(DS_CRUISE_SPEED) + 1);
	// // }
	
	
	// // Blinkers
	
	
	// // -Brian Kuo 703-606-9686
	
	// // ==========================Left Blinker==========================
	// // Checks to see if the left blinker mode is currently active.
	// if (getInt("BLINKER_L_ON")==1){
		// //printf("BLINKER L STOP\n");
		// // Checks to see there is a connection through any of the blinker button pins (including the left blinker button) in the TS-7800.
		// if (CheckPin(BLINK_L, BLINK_L_ROW) || CheckPin(BLINK_R, BLINK_R_ROW) || CheckPin(HAZARDS, HAZARDS_ROW)){
			// // Basically, pressing any blinker button (including the left blinker button) while the left blinker mode is active will disable left blinker mode.
			// printf("BLINKER L STOP\n");
			// stopBlinker(BLINK_L);
			// while(CheckPin(BLINK_L, BLINK_L_ROW)){
				// //usleep(100);
			// }
		// }
	// }else{
		
	// }
	
	// // "If the left blinker mode is inactive and there is currently a connection through the left blinker button pin, activate left blinker mode."
	// // Essentially, this is for when the left blinker mode is currently inactive and is waiting for a connection through the left blinker button pin.
	// if (getInt("BLINKER_L_ON")==0 && CheckPin(BLINK_L, BLINK_L_ROW)){
		// printf("BLINKER L\n");
		// startBlinker(BLINK_L);
		// while(CheckPin(BLINK_L, BLINK_L_ROW) == 1){
			// //printf("BLINKER L Loop\n");
			// //usleep(100);
		// }
	// }
	
	// // ==========================Right Blinker==========================
	// if (getInt("BLINKER_R_ON")==1){
		// if (CheckPin(BLINK_R, BLINK_R_ROW) || CheckPin(BLINK_L, BLINK_L_ROW) || CheckPin(HAZARDS, HAZARDS_ROW)){
			// stopBlinker(BLINK_R);
			// while(CheckPin(BLINK_R, BLINK_R_ROW)){
				// //usleep(100);
			// }
		// }
	// }
	// if (getInt("BLINKER_R_ON")==0 && CheckPin(BLINK_R, BLINK_R_ROW)){
		// printf("BLINKER R\n");
		// startBlinker(BLINK_R);
		// while(CheckPin(BLINK_R, BLINK_R_ROW) == 1){
			// //usleep(100);
		// }
	// }
	
	// // ==========================Hazard Blinker==========================
	// if (getInt("HAZARDS_ON")==1){
		// if (CheckPin(BLINK_R, BLINK_R_ROW) || CheckPin(BLINK_L, BLINK_L_ROW) || CheckPin(HAZARDS, HAZARDS_ROW)){
			// stopBlinker(HAZARDS);
			// while(CheckPin(HAZARDS, HAZARDS_ROW)){
				// //usleep(100);
			// }
		// }
	// }
	// if (getInt("HAZARDS_ON")==0 && CheckPin(HAZARDS, HAZARDS_ROW)){
		// printf("BLINKER H\n");
		// startBlinker(HAZARDS);
		// while(CheckPin(HAZARDS, HAZARDS_ROW) == 1){
			// //usleep(100);
		// }
	// }
	

	// // if(CheckPin(MECH_BRAKE, MECH_BRAKE_ROW)){
		// // brakeOn(LIGHT_BRAKE, LIGHT_BRAKE_ROW);
	// // }
	// // else{
		// // brakeOff(LIGHT_BRAKE, LIGHT_BRAKE_ROW);
	// // }
	
	// // if (CheckPin(DIRECTION, DIRECTION_ROW) && getInt(DS_DIR_BUTTON)==0){
		
		// // if (getInt(DS_DIRECTION) == DIRECTION_FORWARD) {
			// // setInt(DS_DIRECTION, DIRECTION_REVERSE);
		// // }	
		// // else{
			// // setInt(DS_DIRECTION, DIRECTION_FORWARD);
		// // }
		
		// // setInt(DS_DIR_BUTTON, 1);
	// // }    
	// // else{
		// // if(!CheckPin(DIRECTION, DIRECTION_ROW) && getInt(DS_DIR_BUTTON==1){
			// // setInt(DS_DIR_BUTTON, 0);
		// // }
	// // }
// }

