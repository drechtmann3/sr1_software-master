#include <stdio.h>
#include <pthread.h>
#include "threads.h"
#include "motor.h"
#include "DIO.h"
#include "ADC.h"
#include "datastore.h"
#include "lights.h"
#include "LCD.h"
#include <unistd.h>
#include "pins.h"

int main() {

	int i1=1;
	

	//initialize the pins	
	InitDIO();
	InitADC();
	
	pthread_t pthread_motor;
	pthread_t pthread_pedalAvg;
	//pthread_t pthread_airgap;
	
	pthread_create(&pthread_motor,	 	NULL, (void *) &motor_thread, 		&i1);
	pthread_create(&pthread_pedalAvg,	NULL, (void *) &pedalAvg_thread, 	&i1);
	//pthread_create(&pthread_airgap,		NULL, (void *) &airgap_thread, 		&i1);
	
	pthread_join(pthread_motor, 		NULL);
	pthread_join(pthread_pedalAvg, 		NULL);
	//pthread_join(pthread_airgap, 		NULL);

	return 1;


}
