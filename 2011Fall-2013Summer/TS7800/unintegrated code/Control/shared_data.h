#ifndef SHARED_DATA_H
#define SHARED_DATA_H
#include <pthread.h>

// Mutexes and shared data


//shared data 
struct Motor_info_struct {
	// 	put whatever needs to be reported
	// 	over the RS485 network here and use the
	//	Motor_info_mutex mutex to access it.
	int speed_rpm; //rpm
	int airgap_pos; //voltage across potentiometer
	int direction; //motor direction: 1 == forward

	int target_speed; //dHz
	int target_phase_current; //dA
	// throttle := (throttle - regen). If throttle is
	//	negative, we are regeneratively braking.
	int throttle; 

	int brake_indicator; //TODO:  brake indicator sensor

	//int target_dir; // 1 == forward TODO: figure out how to go in reverse
} Motor_info ; 


struct MC_faults_struct {
	int fault_1;
	int fault_2;
	int fault_3;
	int fault_4;
} MC_faults;


//mutexes
pthread_mutex_t Motor_info_mutex; //for access to Motor_info
pthread_mutex_t MC_faults_mutex; //for access to MC_faults

#endif
