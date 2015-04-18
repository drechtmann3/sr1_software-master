#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <string.h>

#include "Motor.h"
#include "MotorController.h"
#include "mc_fault_codes.h"
#include "wrapper.h"
#include "shared_data.h"
#include "MC_commands.h"
#include "DIO.h"

#define FORWARD ("forwardTest")
#define FAST 	 ("fastTest")
#define DURATION ("dur")
#define MAX_TESTS (10)

typedef void (*testFunc)(long);

void print_motor_status();
void print_MC_faults();
void testMotorForward(long dur);
void testMotorFast(long dur);
void genericThrottleTest(char* name,long dur,int speed, int throttle);
#define ENABLE_MOTOR_KILLSWITCH 1
/**
@author Andrey Kurenkov <akurenkov3@gatech.edu> 678-900-4326

@brief An unmanned motor test meant to be run from command line and given a series of tests to run

@detail command line arguments are those defined above - currently FORWARD and FAST to check motor going forward properly and going at high speed.
example usage: ./UnmannedMotorTest forwardTest

@return returns the hex value of the ascii
*/
int main(int argc, char *argv[])
{	
	MC_Setup();
	long dur=5000;
	testFunc funcArray[MAX_TESTS];
	int funcNum=0;
	int i=0;

	// initialize mutexes
	pthread_mutex_init(&Motor_info_mutex, NULL);
	pthread_mutex_init(&MC_faults_mutex, NULL);
	// set up IO
	InitDIO(TOTAL_GPIO);

	if(argc==0){
		testMotorForward(dur);
	}
	else{
		for(i=0;i<argc;i++){
			char* locate=strstr(argv[i],DURATION);
			if(locate){
				char* at=strchr(argv[i],':')+1;
				dur=atol(at);
				continue;
			}

			locate=strstr(argv[i],FORWARD);
			if(locate){
				funcArray[funcNum++]=&testMotorForward;
				continue;
			}

			locate=strstr(argv[i],FAST);
			if(locate){
				funcArray[funcNum++]=&testMotorFast;
				continue;
			}
		}
	}

	for(i=0;i<funcNum;i++){
		funcArray[i](dur);
	}

	print_MC_faults();

	return 0;
}


void testMotorForward(long dur){
	 genericThrottleTest("MotorForward",dur, 50,5);
}

void testMotorFast(long dur){
	 genericThrottleTest("MotorFast",dur, 100,10);
}

/**
@author Andrey Kurenkov <akurenkov3@gatech.edu> 678-900-4326

@brief A generic usage of the motor to be reused elsewhere as needed

@param name the name of the test
@param dur the duration for which to run the motor
@param speed the speed to run the motor at
@param throttle the value of the throttle
*/
void genericThrottleTest(char* name,long dur, int speed, int throttle){
	long elapsed=0;
	struct timeval init, curr;
	struct timezone zone;
	struct tm* time;
	gettimeofday(&init, &zone);
	time=localtime(&init.tv_sec);
	printf("Starting %s test at %d:%02d:%02d %d \nSet to last for %ld microsec\n",name, (int)time->tm_hour, (int)time->tm_min,
		    (int)time->tm_sec, (int)init.tv_usec, dur);

	MC_Setup();
	MC_Command(SET_TORQUE_CONTROL);

	MC_SetRegister(MC_THROTTLE_REGISTER, throttle);
	MC_SetRegister(MC_SPEED_REGISTER, speed);

	while(elapsed<dur) {
		#ifdef ENABLE_MOTOR_KILLSWITCH
			//Check for emergency software killswitch.
			if (CheckKillswitch()) {
				MC_SetRegister(MC_THROTTLE_REGISTER, 0);	//phase current 0dA.
				MC_SetRegister(MC_SPEED_REGISTER, 0); //speed 0dHz.
				printf("Software killswitch pressed. Motor stopped.\n");
			}
		#endif
		gettimeofday(&curr, &zone);
		time=localtime(&curr.tv_sec);
		elapsed=curr.tv_usec-init.tv_usec;

		report_motor_status();
		report_fault_status();
	
	}

	//end run
	MC_SetRegister(MC_THROTTLE_REGISTER, 0); //phase current 0dA.
	MC_SetRegister(MC_SPEED_REGISTER, 0);  //speed 0dHz.
	

	printf("Ending %s test at %d:%02d:%02d %d\n",name, (int)time->tm_hour, (int)time->tm_min,
		    (int)time->tm_sec, (int)init.tv_usec);
	MC_CloseConnection();
}

void print_motor_status()
{
	printf("*********************\n");
	printf("print_motor_status():\n");
	printf("*********************\n");

	pthread_mutex_lock(&Motor_info_mutex);
	printf("speed_rpm:            %d\n", Motor_info.speed_rpm);
	printf("airgap_pos:           %d\n", Motor_info.airgap_pos);
	printf("direction:            %d\n", Motor_info.direction);
	printf("target_speed:         %d\n", Motor_info.target_speed);
	printf("target_phase_current: %d\n", Motor_info.target_phase_current);
	printf("throttle:             %d\n", Motor_info.throttle);
	printf("brake_indicator:      %d\n", Motor_info.brake_indicator);
	pthread_mutex_unlock(&Motor_info_mutex);

	printf("*********************\n");
}

void print_MC_faults()
{
	printf("********************");
	printf("print_MC_faults():\n");
	printf("********************");

	pthread_mutex_lock(&MC_faults_mutex);
	printf("type 1: %d\n", MC_faults.fault_1);
	printf("type 2: %d\n", MC_faults.fault_2);
	printf("type 3: %d\n", MC_faults.fault_3);
	printf("type 4: %d\n", MC_faults.fault_4);
	pthread_mutex_unlock(&MC_faults_mutex);

	printf("*********************\n");

}

