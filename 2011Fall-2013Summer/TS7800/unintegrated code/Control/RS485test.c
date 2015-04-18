/* testing of RS485 functionality */
/*For Andrey only: scp andrey@192.168.0.1:/home/andrey/School/SJ/pp/SBC/src/Control/RS485test ./RS485test*/
#include "stdio.h"
#include "RS485ControlCom.h"
#include "shared_data.h"

#include <pthread.h>


/**
@author Andrey Kurenkov <akurenkov3@gatech.edu> 678-900-4326

@brief Simple test of RS485 functionality that inits the needed thread

@return char that is an error code as defined by SUCCESS and FAILURE
*/
int main()
{	

	//set up thread
	pthread_t RS485_thread;
	pthread_attr_t attr; 
	void *thread_join_status;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

	// initialize mutexes
	pthread_mutex_init(&Motor_info_mutex, NULL);
	pthread_mutex_init(&MC_faults_mutex, NULL);

	//start thread
	if(pthread_create(&RS485_thread, &attr, RS485_Control, NULL)) {
		printf("Error creating RS485 thread !\n");
		return -1;
	}

	// cleanup
	pthread_attr_destroy(&attr);

	//join thread
	if (pthread_join(RS485_thread, &thread_join_status))
		printf("RS485 thread join failed !\n");


	//cleanup
	pthread_mutex_destroy(&Motor_info_mutex);
	pthread_mutex_destroy(&MC_faults_mutex);

	pthread_exit(NULL);

	return 0;
}
