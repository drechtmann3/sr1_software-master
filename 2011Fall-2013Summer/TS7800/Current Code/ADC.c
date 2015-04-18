/**
 @file ADC.c
 @author Reid Kersey <reidkersey@gmail.com> 678-736-0899
 @brief This file contains the C code to properly implent
 and control the ADC.
 @details This file contiains functions called by external
 sources. These functions interact directly with the ADC
 through the DIO pins.
 @note The ADC contains 32 channels (1-32)
 @note On channel 32 the board has a built in temperature
 sensor. There should be no other inputs on this channel
 @note On channels 1-4 there is an op-amp, to deal with
 high impediance loads. This op-amp may impact reading
 accuracy, due to the typical offset of 2-5 bits.
 @todo Implement averaging function.
*/

#include "DIO.h"
#include <stdio.h>
#include "ADC.h"
#include "pins.h"
#include "datastore.h"
#include <pthread.h>
#include "motor.h"

static int mT = 0;
static int rawT[AVG_SIZE] = {0};
static int averageT = 0;
// static int mR = 0;
static int resetT = 0;
// static int rawR[AVG_SIZE] = {0};
// static int averageR = 0;
pthread_mutex_t ADC_mutex;

/**
@author Reid Kersey <reidkersey@gmail.com> 678-736-0899

@brief This function initializes the ADC

@details This function initialzes the ADC pin directions, 
and sets outputs to the correct starting values.

@warning This function must be called before any calls to
the ADC

@todo make static, and implement initialization call in each ADC
function that communicates with the ADC. This can be done with a
set value in the data store, indicating if the ADC has been initialized
yet or not.
*/
void InitADC()
{
	// initialize pin directions 
	InitDIO_direction(ADC_CS0, ADC_CS0_ROW, GPIO_OUTPUT);
	InitDIO_direction(ADC_CLK, ADC_CLK_ROW, GPIO_OUTPUT);
	InitDIO_direction(ADC_MOSI, ADC_MOSI_ROW, GPIO_OUTPUT);
	InitDIO_direction(ADC_MISO, ADC_MISO_ROW, GPIO_INPUT );

	// initialize outputs
	SetPin(ADC_MOSI, ADC_MOSI_ROW, ADC_MOSI_INIT);
	SetPin(ADC_CS0, ADC_CS0_ROW, ADC_SS_INIT); //Same thing here, not sure if the other ADC SetPins matter.
	SetPin(ADC_CLK, ADC_CLK_ROW, ADC_CLK_INIT);
}

/**
@author Reid Kersey <reidkersey@gmail.com> 678-736-0899

@brief This function reads the value of one channel on the ADC, multiple times and returns the average

@details 

@warning 

@param 
@return *
*/
int ADCAverage(int channel, int numForAverage){
	
	int min = 1024;
	int max = 0;
	int values[numForAverage];
	int retval = 0;
	int i;
	for(i = 0; i < numForAverage; i++){
		values[i] = ADCReadRaw(channel);
	}
	for(i = 0; i < numForAverage; i++){
		if(values[i] < min){
			min = values[i];
		}
		if(values[i] > max){
			max = values[i];
		}
	}
	for(i = 0; i < numForAverage; i++){
		retval += values[i];
	}
	retval -= min;
	retval -= max;
 	printf("ADC RETVAL = %d\n", (retval/(numForAverage-2)));
	
	return (retval/(numForAverage-2));
}
 


double sum(int num_array1[], int start, int end){
	int total=0;
	int a;
	for(a = start; a<=end; a++) {
		total = total + num_array1[a];
	}
	return total;
}

//TODO: get rid of magic numbers (define them)
//TODO: use min and max pedal settings instead of 0. Keep in mind that min and max pedal settings include a deadband. 
//The number received from the ADC can be less tahn the min pedal setting. Negative throttle numbers cause problems.
void averagePedal(int channel){
	int min;

	rawT[mT] = ADCReadRaw(channel);
	averageT = (sum(rawT, 0, AVG_SIZE-1)/(double)AVG_SIZE); 
	min = getThrottleMin();
	
	if(rawT[mT] <= min){
		resetT++;
		if(resetT >= MAX_RESET){
			int i;
			for(i = 0; i < AVG_SIZE; i++){
				rawT[i] = min;
			}
		}
	}
	
	resetT = 0;
	
	mT = mT + 1;
	if(mT > AVG_SIZE-1){
		mT = 0;
	}
	
	setThrottle(averageT);
}

/**
@author Reid Kersey <reidkersey@gmail.com> 678-736-0899

@brief This function reads the value of one channel on the ADC

@details This function reads the current 10 bit value (0-1023) on the
specified channel (1-32) on the ADC. The ADC has a 3V refrence, so each
bit represents aproximatly .003V. On inputs 1-4 there is an op-amp, so that
the ADC can read high impediance loads. On these inputs there is a typical
offset of about 2-5 bits. On channel 32, the board has a built in temperature
sensor.

@warning This function reads RAW data from the ADC, so any temporary
voltage spikes may cause inacurate readings. For best accuracy, a rolling
average should be taken.

@param channel This function takes in the channel being read (1-32)
@return This function will return a 10 bit value of the ADC channel.
This function will return a negative number if there is an error.
*/
int ADCReadRaw(int channel)
{       
	pthread_mutex_lock(&ADC_mutex);
	int i;
	unsigned int ret = 0;
	/*Return raw output of one ADC sample.
	 *See MCP3008 datasheet (section on serial communication)
	 *for more info. */
	 
	if (channel > 8 || channel < 1) {
		perror("Invalid ADC channel selection.\n"
		"Please go find someone who knows what they are doing\n"
		"Error #ID30T\n");
		return -1;
	}
	
	//channel and ADC CS calculations
	channel = channel-1;
	
	// start bit
	SetPin(ADC_CS0, ADC_CS0_ROW, 1);
	SetPin(ADC_CS0, ADC_CS0_ROW, 0);
	SetPin(ADC_MOSI, ADC_MOSI_ROW, 1);
	ADC_SPIclockCycle(ADC_CLK, ADC_CLK_ROW);
	// select single-ended input
	SetPin(ADC_MOSI, ADC_MOSI_ROW, 1);
	ADC_SPIclockCycle(ADC_CLK, ADC_CLK_ROW);
	// channel request (three clock cycles)
	for ( i = 0; i < 3; i++ ) {
			SetPin(ADC_MOSI, ADC_MOSI_ROW, channel & (1<<(2-i)));
			ADC_SPIclockCycle(ADC_CLK, ADC_CLK_ROW);
	}
	// ignore null bits (there are 2)
	ADC_SPIclockCycle(ADC_CLK, ADC_CLK_ROW);
	ADC_SPIclockCycle(ADC_CLK, ADC_CLK_ROW);
	// recieve response
	for(i=0; i < 10; i++) {
			ADC_SPIclockCycle(ADC_CLK, ADC_CLK_ROW);
			ret <<= 1;      
			ret |= CheckPin(ADC_MISO, ADC_MISO_ROW);    
	}
	SetPin(ADC_CS0, ADC_CS0_ROW, PIN_HIGH);
	
	//printf("ADC Channel: %d = %d\n", channel, ret);
	pthread_mutex_unlock(&ADC_mutex);
	return ret;
}

/**
@author Reid Kersey <reidkersey@gmail.com> 678-736-0899

@brief This function converts the temperature from the onboard temperature
sensor into deg farenheight.

@todo This function needs to be moved somewhere else. It does not belong with
the other ADC functions.

@param channel This function takes in the channel of the temperature sensor
being read (1-32)
@return This function will return the amount in deg ferenheight of the temperature
sensor.
*/
int TempSensor(int channel){
	float temp; //make a variable for the temperature
	temp = ADCReadRaw(channel); //get the temperature
	temp = temp/1024; //divide by the number of bits, and multiply by the refrence voltage to get the voltage of the source
	temp = temp*3.3;
	temp = temp*180;//sensor gives 10mV for every deg C, so conversion from C to F is C*1.8+32, but since the original is in mV we multiply by 180 instead of 1.8
	temp = temp + 32;
	return (int)temp; //Truncate the value, and return an int
}


/**
@author Reid Kersey <reidkersey@gmail.com> 678-736-0899

@brief This function pulses the clock, and signals the start of a new bit.

@todo This function needs to be moved somewhere else. It does not belong with
the other ADC functions.

@param clk this is the pin number of the clock pin being cycled.
@param clk_row This is the row of the pin number being cycled.
*/
void ADC_SPIclockCycle(int clk, int clk_row)
{       /* Single clock cycle. */
        SetPin(clk, clk_row, 0);
 SetPin(clk, clk_row, 0);
 SetPin(clk, clk_row, 0);
 SetPin(clk, clk_row, 0);
        SetPin(clk, clk_row, 1);

        SetPin(clk, clk_row, 1);
        SetPin(clk, clk_row, 1);
        SetPin(clk, clk_row, 1);
        SetPin(clk, clk_row, 1);
        SetPin(clk, clk_row, 1);

}
