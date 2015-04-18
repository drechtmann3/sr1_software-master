// #include "airgap.h"
// #include "GPIO.h"
// #include "DIO.h"
// #include "threads.h"
// #include "ADC.h"
// #include "pins.h"
// #include "datastore.h"
// #include <stdio.h>
// #include <math.h>

// //Brian Kuo: (703)-606-9686
// //This starts our airgap function and will run at the same time as the driver is doing the Pedal stuff
// void InitAirgap(){

	// SetPin(MOVE_AIRGAP, AIRGAP_UP_ROW, OUTWARD);
	// int count = 0;
	// int max = 0;
	// int min = 1023;
	// while (count < 30){

		// if(ADCReadRaw(0) > max){
			// max = ADCReadRaw(0);
			// count = 0;
		// }
		// count++;
	// }

	// int staticMax = max - 10;

	// SetPin(MOVE_AIRGAP, AIRGAP_UP_ROW, INWARD);
	// int count2 = 0;
	// while (count2 < 30){

		// if(ADCReadRaw(0) < min){
			// min = ADCReadRaw(0);
			// count2 = 0;
		// }
		// count2++;
	// }

	// int staticMin = min + 10;

	// setInt("airgapMax", staticMax);
	// setInt("airgapMin", staticMin);

// }

// //this is where I define what the increments shall be between each airgap level
// //numOfGears defines number of levels and can be changed based on preference
// //x1 is staticMin, and y1 is staticMax
// ///name variables better?
// void GEARS_ARRAY(int x1, int y1)
// { 	
	// int gearArray1[10];
	// int m;
	// int gearIncrement = (y1 - x1) / numOfGears;
	// for (m = 0; m < numOfGears; m++){
	// //**POSSIBLE SOURCE OF ERROR** DONT KNOW IF "C" WILL DO MATH LIKE THIS WITHOUT THE "MATH LIBRARY"**
	// ///cmath added
	
	// gearArray1[m] = x1 + (m * gearIncrement);
	// }
	// //**POSSIBLE SOURCE OF ERROR** DONT KNOW IF "C" CAN RETURN AN ARRAY WITHOUT USING POINTERS
	// //return gearArray1;
	
	// int i;
	// for(i = 0; i < numOfGears; i++){
	
	// setInt(sprintf("gear%d",(i+1)) , gearArray1[i]);
	
	// }
	
// }
	
	
	
	

// //This function will start moving the airgap in either the forward or backward direction.
// // void moveAirgap(int direction){
	// //pin 1 is direction, pin 3 is on/off
	// ///use pins.h to not hard code
	// ///use defines
	// // SetPin(AIRGAP_DIR, AIRGAP_UP_ROW, direction)
	// // SetPin(MOVE_AIRGAP, AIRGAP_UP_ROW, 1 );
// // }



// //run airgap, this is the real deal
// ///put the runairgap function in your thread in threads.c so that it is in a while one loop
// ///functions should not have while 1 loops in them



// void runAirgap(){
	// //continuously runs this runAirgap function
	
	// // while (1)  //
	// // { 
		// //checks to see if Airgap_up button is being pressed.
		// //If it is, moves airgap to desired level
		// TargetAirgap();
		// CurrentAirgap(numOfGears);
		// int Target = getInt("Target_Gear");
		// int Current = getInt("currentGear");
		// if (Current < Target)
		// {
			// SetPin(MOVE_AIRGAP, AIRGAP_UP_ROW, 1);
			// //set direction to outward
			// SetPin(AIRGAP_DIR, AIRGAP_UP_ROW, OUTWARD);
			
			
			
		// }
		// else if (Current > Target)
		// {
			// SetPin(MOVE_AIRGAP, AIRGAP_UP_ROW, 1);
			// // set direction to inward	]
			// SetPin(AIRGAP_DIR, AIRGAP_UP_ROW, INWARD);
		// }
		// else{
		// SetPin(MOVE_AIRGAP, AIRGAP_UP_ROW, 0);		
			
		// }

		
	// //}
// }
// //actions to take if airgap up is pressed
// void TargetAirgap()
// {
	// int Target_Gear;
	// int gear = getInt("currentGear");
	// if((checkPinDebounce(AIRGAP_UP, AIRGAP_UP_ROW) == 1) && (gear != 10)){
		// while (checkPinDebounce(AIRGAP_UP, AIRGAP_UP_ROW) != 0);
		// Target_Gear = gear + 1;
	// }
	// else if(checkPinDebounce(AIRGAP_DOWN, AIRGAP_DOWN_ROW) == 1 && gear != 1){
		// while (checkPinDebounce(AIRGAP_DOWN, AIRGAP_DOWN_ROW) != 0);
		// Target_Gear= gear - 1;
	// }
	// setInt("Target_Gear", Target_Gear);
	// //HEY~!!!!!!!!!!!!! MAKE THE LCD READ OUT TARGET GEAR!!!!!!!!!!
// }


// void CurrentAirgap(int numGear)
// {
	// int currentGear = 0;	
	// int maxVal = 1023;	
	// int j;
		// for(j = 0; j < (numOfGears); j++)
		// {
			// //if sprintf doesn't work, we can just make an array with all of the gear variable names
			// int val = abs(ADCReadRaw(0) - getInt(sprintf("gear%i", j + 1)));	
			// if(val < maxVal)
			// {
				// maxVal = val;
				// currentGear++;
			// }	
			
		// }
		// setInt("currentGear", currentGear);
// //HEY!!!!!!!!! MAKE THE LCD READ OUT YOUR CURRENT GEAR!!!!!!		
// }








