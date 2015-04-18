// /**
	// @file lights.c
	// @author Reid Kersey <reidkersey@gmail.com> 678-736-0899
	// @brief This file contains functions, that controll the brake and blinker lights.
	// @warning The lights must be initialized using initLights, before they can be turned on or off
	// @warning When calling blink, you must be careful, to put it in a thread by itself, becuase execution
	// of blink, make take some time
	// @ingroup Common
	// @addtogroup lights Lights
	// @brief Functions that control the brake and blinker lights.
	// @{
// */
// #include "lights.h"
// #include "DIO.h"
// #include "pins.h"
// #include "motor.h"
// #include "datastore.h"
// #include "threads.h"
// #include <unistd.h>
// #include <stdio.h>
// #include <pthread.h>

// static pthread_t pthread_blinkersL;
// static pthread_t pthread_blinkersR;
// static pthread_t pthread_blinkersH;

// /**
	// @author Reid Kersey <reidkersey@gmail.com> 678-736-0899
	// @brief This function intitializes the pins for the blinkers, and brakes
	// @warning This function must be called before calling any of the brake, or blinker control functions.
// */
// void initLights(){
	// // initialize pin directions 
	// InitDIO_direction(LIGHT_BRAKE, LIGHT_BRAKE_ROW, GPIO_OUTPUT);
	// InitDIO_direction(LIGHT_BLINK_L, LIGHT_BLINK_L_ROW, GPIO_OUTPUT);
	// InitDIO_direction(LIGHT_BLINK_R, LIGHT_BLINK_R_ROW, GPIO_OUTPUT);

	// // initialize outputs
	// SetPin(LIGHT_BRAKE, LIGHT_BRAKE_ROW, LIGHT_OFF);
	// SetPin(LIGHT_BLINK_L, LIGHT_BLINK_L_ROW, LIGHT_OFF);
	// SetPin(LIGHT_BLINK_R, LIGHT_BLINK_R_ROW, LIGHT_OFF);
// }

// /**
	// @author Reid Kersey <reidkersey@gmail.com> 678-736-0899
	// @brief  This function turns the brake lights off.
	// @param brake This is the pin number of the brake pin (defined in pins.h)
	// @param brakeRow This is the row number of the brake pin (defined in pins.h)
// */
// void brakeOff(int brake, int brakeRow){
	// SetPin(brake, brakeRow, LIGHT_OFF);
	// if(brake == LIGHT_BRAKE){
		// setInt(DS_MECH_BRAKE, BRAKE_OFF);
	// }
	// else{
		// setInt(DS_REGEN_BRAKE, BRAKE_OFF);
	// }
// }

// /**
	// @author Reid Kersey <reidkersey@gmail.com> 678-736-0899
	// @brief  This function turns the brake lights on.
	// @param brake This is the pin number of the brake pin (defined in pins.h)
	// @param brakeRow This is the row number of the brake pin (defined in pins.h)
// */
// void brakeOn(int brake, int brakeRow){
	// SetPin(brake, brakeRow, LIGHT_ON);
	// if(brake == LIGHT_BRAKE){
		// setInt(DS_MECH_BRAKE, BRAKE_ON);
	// }
	// else{
		// setInt(DS_REGEN_BRAKE, BRAKE_ON);
	// }
// }

// /**
	// @author Reid Kersey <reidkersey@gmail.com> 678-736-0899
	// @brief  This function blinks the blinker specifed on and off one time.
	// @details This Function takes in the blinker pin, and turns the blinker on
	// for a specified amount of time (defined in lights.h), and then it turns the
	// blinker off, for the same amount of time.
	// @warning This function may take >1 second to complete. It should only be started
	// from a seprate thread.
	// @param blinker This is the pin number of the blinker pin (defined in pins.h)
	// @param blinkRow This is the row number of the blinker pin (defined in pins.h)
// */
// void blink(int blinker, int blinkRow){
	// if(blinker != LIGHT_BLINK_L && blinker != LIGHT_BLINK_R){ //if the blinker is not either side, then turn on the hazzards.
		// blinkerOn(LIGHT_BLINK_L, LIGHT_BLINK_L_ROW);
		// blinkerOn(LIGHT_BLINK_R, LIGHT_BLINK_R_ROW);
		// setInt("BLINKER_BLINK", BLINKER_HAZARD);
		// usleep(BLINK_FREQ);
		// blinkerOff(LIGHT_BLINK_L, LIGHT_BLINK_L_ROW);
		// blinkerOff(LIGHT_BLINK_R, LIGHT_BLINK_R_ROW);
		// setInt("BLINKER_BLINK", BLINKER_OFF);
		// usleep(BLINK_FREQ);
		// return;
	// }else if(blinker == LIGHT_BLINK_L){
		// blinkerOn(blinker, blinkRow);
		// setInt("BLINKER_BLINK", BLINKER_LEFT);
		// usleep(BLINK_FREQ);
		// blinkerOff(blinker, blinkRow);
		// setInt("BLINKER_BLINK", BLINKER_OFF);
		// usleep(BLINK_FREQ);
	// }else{
		// blinkerOn(blinker, blinkRow);
		// setInt("BLINKER_BLINK", BLINKER_RIGHT);
		// usleep(BLINK_FREQ);
		// blinkerOff(blinker, blinkRow);
		// setInt("BLINKER_BLINK", BLINKER_OFF);
		// usleep(BLINK_FREQ);
	// }
// }

// void startBlinker(int blink){
	// if(getInt("BLINKER_L_ON") == 0 && blink == BLINK_L){
		// static int blinker = LIGHT_BLINK_L;
		// setInt("BLINKER_L_ON", 1);
		// pthread_create(&pthread_blinkersL, NULL, (void *)&blinkers_thread, &blinker);
		// printf("blinker L create\n");
		// //pthread_join(pthread_blinkersL, NULL);
		// printf("blinker  joined\n");
	// }
	
	// if(!getInt("BLINKER_R_ON") && blink == BLINK_R){
		// static int blinker = LIGHT_BLINK_R;
		// setInt("BLINKER_R_ON", 1);
		// pthread_create(&pthread_blinkersR, NULL, (void *)&blinkers_thread, &blinker);
		// printf("blinker create\n");
		// //pthread_join(pthread_blinkersR, NULL);
		
	// }
	
	// if(!getInt("HAZARDS_ON")&& blink == HAZARDS){
		// static int blinker = HAZARDS;
		// setInt("HAZARDS_ON", 1);
		// pthread_create(&pthread_blinkersH, NULL, (void *)&blinkers_thread, &blinker);
		// pthread_join(pthread_blinkersH, NULL);
		// printf("hazards on\n");
	// }
// } 

// void stopBlinker(int blink){
	// if(getInt("BLINKER_L_ON") && blink == BLINK_L){
		// pthread_cancel(pthread_blinkersL);
		// setInt("BLINKER_L_ON", 0);
		// blinkerOff(LIGHT_BLINK_L, LIGHT_BLINK_L_ROW);
		// printf("stoped l\n");
	// }else if(getInt("BLINKER_R_ON") && blink == BLINK_R){
		// pthread_cancel(pthread_blinkersR);
		// setInt("BLINKER_R_ON", 0);
		// blinkerOff(LIGHT_BLINK_R, LIGHT_BLINK_R_ROW);
		// printf("stoped R\n");
	// }else if(getInt("HAZARDS_ON") && blink == HAZARDS){
		// pthread_cancel(pthread_blinkersH);
		// setInt("HAZARDS_ON", 0);
		// blinkerOff(LIGHT_BLINK_R, LIGHT_BLINK_R_ROW);
		// blinkerOff(LIGHT_BLINK_L, LIGHT_BLINK_L_ROW);
	// }
// }

// /**
	// @author Reid Kersey <reidkersey@gmail.com> 678-736-0899
	// @brief  This function turns the specified blinker on
	// @warning This lights must be initialized for this function to work.
	// @param blinker This is the pin number of the blinker pin (defined in pins.h)
	// @param blinkRow This is the row number of the blinker pin (defined in pins.h)
// */
// void blinkerOn(int blinker, int blinkRow){
	// SetPin(blinker, blinkRow, LIGHT_ON);
// }

// /**
	// @author Reid Kersey <reidkersey@gmail.com> 678-736-0899
	// @brief  This function turns the specified blinker off
	// @warning This lights must be initialized for this function to work.
	// @param blinker This is the pin number of the blinker pin (defined in pins.h)
	// @param blinkRow This is the row number of the blinker pin (defined in pins.h)
// */
// void blinkerOff(int blinker, int blinkRow){
	// SetPin(blinker, blinkRow, LIGHT_OFF);
// }
// /**
	// @}
// */
