/**************************************************************
 * Motor control program for the Georgia Tech Solar Jackets
 * Endeavour solar car.
 *
 *************************************************************
 */

#include "Motor.h"
#include "MotorController.h"
#include "RS485ControlCom.h"
#include "wrapper.h"
#include "shared_data.h"
#include "DIO.h"

#include <pthread.h>
#include <stdio.h>


/**
@author Matt Olson <matt.a.olson@gmail.com> 404-680-0566

@brief  Basically inits all the threads

@return -1 on error
*/
int main()
{
	void *thread_join_status;
	pthread_attr_t attr; 

	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);


//set up threads
#ifdef USE_MOTOR_THREAD
	pthread_t Motor_thread;
#endif
#ifdef USE_AIRGAP_THREAD
	pthread_t Airgap_thread;
#endif
#ifdef USE_RS485_THREAD
	pthread_t RS485_thread;
#endif

// initialize mutexes
	pthread_mutex_init(&Motor_info_mutex, NULL);
	pthread_mutex_init(&MC_faults_mutex, NULL);


// initialize shared structs
	pthread_mutex_lock(&Motor_info_mutex);
	Motor_info.speed_rpm = 0;
	Motor_info.airgap_pos = 0;
	Motor_info.direction = 0;
	Motor_info.target_speed = 0;
	Motor_info.target_phase_current = 0;
	Motor_info.throttle = 0;
	Motor_info.brake_indicator = 0;
	pthread_mutex_unlock(&Motor_info_mutex);

	pthread_mutex_lock(&MC_faults_mutex);
	MC_faults.fault_1 = 0;
	MC_faults.fault_2 = 0;
	MC_faults.fault_3 = 0;
	MC_faults.fault_4 = 0;
	pthread_mutex_unlock(&MC_faults_mutex);


// set up IO
	InitDIO(TOTAL_GPIO);


// start threads
#ifdef DEBUG
	printf("Main: starting threads...\n");
#endif

#ifdef USE_MOTOR_THREAD
	if(pthread_create(&Motor_thread, &attr, MotorControl, NULL)) { // start motor thread
		printf("Error creating Motor thread !\n");
		return -1;
	}
#endif
#ifdef USE_AIRGAP_THREAD
	if(pthread_create(&Airgap_thread, &attr, AirgapControl, NULL)) { // start airgap thread
		printf("Error creating Airgap thread !\n");
		return -1;
	}
#endif
#ifdef USE_RS485_THREAD
	if(pthread_create(&RS485_thread, &attr, RS485_Control, NULL)) {
		printf("Error creating RS485 thread !\n");
		return -1;
	}
#endif


// cleanup
	pthread_attr_destroy(&attr);


// join threads:
#ifdef USE_MOTOR_THREAD
	if (pthread_join(Motor_thread, &thread_join_status))
		printf("Motor thread join failed !\n");
#endif
#ifdef USE_AIRGAP_THREAD
	if (pthread_join(Airgap_thread, &thread_join_status))
		printf("Airgap thread join failed !\n");
#endif
#ifdef USE_RS485_THREAD
	if (pthread_join(RS485_thread, &thread_join_status))
		printf("RS485 thread join failed !\n");
#endif


//cleanup
	pthread_mutex_destroy(&Motor_info_mutex);
	pthread_mutex_destroy(&MC_faults_mutex);

#ifdef USE_MOTOR_THREAD
	MC_CloseConnection();
#endif /* #ifdef USE_MOTOR_THREAD */

	pthread_exit(NULL);
}
