#include "threads.h"
#include "ADC.h"
#include <stdio.h>
#include "DIO.h"
#include "GPIO.h"
#include "LCD.h"
#include "wireless.h"
#include "gps.h"
#include "motor.h"
#include "lights.h"
#include "airgap.h"
#include "pins.h"
#include "log.h"
#include <unistd.h>
#include "datastore.h"
 


/**
@author Reid Kersey <reidkersey@gmail.com> 678-736-0899

@brief This function controlls the motor controll thread

@details This function calls repeatedly the motor controll thread 
function, so that the tread can preform its specified task. This allows 
the code inside of the thread to be run independantly from other code 
running on the same processor. This threads task is to keep in constant
communication with the motor controller, and to continualy read and deal
with value from the pedals. This function also logs information received
from the motor controller, such as speed, and torque.

@warning You must keep the calling variable in order to stop execution, 
or otherwise control this thread

@note There should only be one function call inside the while loop, 
and one initialization outside of the while loop. No advanced coding 
should be done in the thread function.

@todo create and implement function code and initialization

@param x This function takes in an arguement. Due to C standards, 
we must include this arguemnet even though we do not use or implement it.
*/
void *motor_thread(int *x){
	MC_Setup();
	SetupPedals();

	while(1){
		printf("running motor \n\n");
		runMotor();
	}
}

/**
@author Reid Kersey <reidkersey@gmail.com> 678-736-0899

@brief This function controlls the airgap thread

@details This function calls repeatedly the airgap thread function, 
so that the tread can preform its specified task. This allows the 
code inside of the thread to be run independantly from other code 
running on the same processor. This functions task is when called
to move the airgap motor a specified amount (found in data store).
This needs its own thread, so that the thread can continually check
the ADC for wether the value of the airgap is at the correct setting
or not.

@warning You must keep the calling variable in order to stop execution, 
or otherwise control this thread

@note There should only be one function call inside the while loop, 
and one initialization outside of the while loop. No advanced coding 
should be done in the thread function.

@note This function is "temporary". Meaning that this thread should be
created to preform its task for a specified time, and then stopped after
execution. This thread is desiged to run for only a short specified amount
of time.

@todo create and implement function code and initialization

@param x This function takes in an arguement. Due to C standards, 
we must include this arguemnet even though we do not use or implent it.
*/
// void *airgap_thread(int *x){
	// InitAirgap();
	// GEARS_ARRAY(getInt("airgapMin"), getInt("airgapMax"));

	// while(1){
		// runAirgap();
		// usleep(100);
	// }
// }



/**
@author John, Travis, and Brian <reidkersey@gmail.com> 678-736-0899

@brief This function controlls the 

@details

@warning 

@warning

@note 

@note 

@todo define zeros as throttlemin in data store function. Define orange vaalues. 

@param 
*/
void *pedalAvg_thread(int *x){
	while(getStep() != STEP4){
		usleep(100);
	}
	
	while(1){
		averagePedal(THROTTLE_CHANNEL);
		//usleep(100);
	}
}
