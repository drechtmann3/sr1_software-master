/**
	@file datastore.c
	@author Michelle Van Enige <mave3@gatech.edu> 727-433-2927
	@brief This file facilitates data storage across multiple threads.
	@details This file uses linked lists in order to store data values of type node with an identifier
	@warning
	@note
	@todo finish get functions
	@todo test data storage
	@ingroup Common
	@addtogroup dataStore Data Store
	@brief Data storage, in a linked list.
	@{
*/
#include "datastore.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>


static int throttle;
void setThrottle(int in){
	throttle = in;
}
int getThrottle(){
	return throttle;
}

static int regenMin;
void setRegenMin(int in){
	regenMin = in;
}
int getRegenMin(){
	return regenMin;
}

static int regenMax;
void setRegenMax(int in){
	regenMax = in;
}
int getRegenMax(){
	return regenMax;
}

static int throttleMin;
void setThrottleMin(int in){
	throttleMin = in;
}
int getThrottleMin(){
	return throttleMin;
}

static int throttleMax;
void setThrottleMax(int in){
	throttleMax = in;
}
int getThrottleMax(){
	return throttleMax;
}

static int step;
void setStep(int in){
	step = in;
}
int getStep(){
	return step;
}
