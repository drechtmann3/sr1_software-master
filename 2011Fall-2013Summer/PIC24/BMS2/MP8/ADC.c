#include "ADC.h"
#include "relay.h"
#include "main.h"
#include "LED.h"
#include "datastore.h"
#include <stdio.h>
#include <p24HJ128GP202.h>

//TODO:
//set ranges for current sensors

int checkTemperature(int channel){
    //TODO: comment code
//	char buffer [7];
    double temp = readTempSensor(channel);
//	sprintf(buffer, "temp%d", channel+1);
//	setInt(buffer, (int)temp*100);
    if(temp < TEMP_MIN || temp > TEMP_MAX){
        setRelay(RELAY_OFF);
		setCritical(LED_ON);
		setWarn2(LED_ON);
        return 0;
    }
    if(temp <= TEMP_YELLOW_MIN || temp >= TEMP_YELLOW_MAX){
        setWarn2(LED_ON);
		return 1;
    }
    else{
        return 2;
    }
}

int checkCurrentSensor(int channel){
    double current = readCurrentSensor(channel);
	//setInt("current", (int)current*100);
    if (current < CURRENT_MIN || current > CURRENT_MAX){
        setRelay(RELAY_OFF);
		setCritical(LED_ON);
		setWarn2(LED_ON);
        return 0;
    }
    if(current <= CURR_YELLOW_MIN || current >= CURR_YELLOW_MAX){
		setWarn2(LED_ON);
		return 1;
    }
    else{
		return 2;
    }
}

double readCurrentSensor(int channel){
    double vpb = (5.0/1024.0); //volts per bit = refrence voltage (5V) over the number of available ADC resolution (10 bits = 2^10 = 1024)
    double ret = ADCReadAvg(channel); //read the channel
    ret = ret * vpb; //get voltage of input
    ret=(ret/0.1) - 25; //since the ratio of voltage to amperage is .1. when we have 0 A we have 2.5 V or when we have 0 V we have 25 A.
    return ret;
}

double readTempSensor(int channel){
    double vpb = (5.0/1024.0); //volts per bit = refrence voltage (5V) over the number of available ADC resolution (10 bits = 2^10 = 1024)
    double ret = (double)ADCReadAvg(channel); //read the channel
    ret = ret * vpb; //get voltage of input
    ret = ret / .01; //temp sensors (LM35) have a scale of 10mv per deg C
    return ret;
}

int ADCReadAvg(int channel){
    long ret = 0; //defined as long, so it can hold all of the required amounts
    int read = 0; //initialize read
    int min = 1023; //set minimum to the highest possible value
    int max = 0; //set maximum to the lowest possible value
    int i;
    for(i = 0; i < ADC_AVG_CYCLE; i++){
        read = ADCReadRaw(channel); //read in the channel
        ret += read; //add read into all of the previous reads
        if(read > max){ //determine if the current value is the new "dynamic maximum"
            max = read;
        }
        if(read < min){ //determine if the current value is the new "dynamic minimum"
            min = read;
        }
    }
    ret = ret - min - max; //subtract the min and max from the total
    ret = ret/(ADC_AVG_CYCLE - 2); //average out over the number of cycles taken (-2 due to min and max being taken out)
    return (int) ret; //convert ret into an integer to be returned
}

int initADC(){
	if(checkTemperature(TEMP1_CHANNEL) == 0){
		return 0;
	}else if(checkTemperature(TEMP2_CHANNEL) == 0){
		return 0;
	}else if(checkTemperature(TEMP3_CHANNEL) == 0){
		return 0;
	}else if(checkTemperature(TEMP4_CHANNEL) == 0){
		return 0;
	}else if(checkCurrentSensor(CURR_CHANNEL) == 0){
		return 0;
	}else {
		return 1;
	}
}

int checkADC(){
	if(checkTemperature(TEMP1_CHANNEL) == 0){
		return 0;
	}else if(checkTemperature(TEMP2_CHANNEL) == 0){
		return 0;
	}else if(checkTemperature(TEMP3_CHANNEL) == 0){
		return 0;
	}else if(checkTemperature(TEMP4_CHANNEL) == 0){
		return 0;
	}else if(checkCurrentSensor(CURR_CHANNEL) == 0){
		return 0;
	}else {
		return 1;
	}
}

int ADCReadRaw(int channel)
{
	ADC_clock();
	int i;
	int ret = 0;

	//CYCLE CS TO WAKE CHIP
        ADC_setCS(1); //cs
        ADC_setCS(0);
        ADC_setCS(1); //cs
        ADC_setCS(0);
        //send start bit
        ADC_setMOSI(1); //din
        ADC_clock();

	// select single-ended input
        ADC_setMOSI(1); //Din
        ADC_clock();

	// channel request (three clock cycles)
	for ( i = 0; i < 3; i++ ) {
         ADC_setMOSI((channel & (1<<(2-i)))>>(2-i)); //Din
         ADC_clock();
	}

	// ignore null bits (there are 2)
        ADC_clock();

	// recieve response
	for(i=0; i < 10; i++) {
		ADC_clock();
		ret <<= 1;
		ret |= ADC_getMISO();	 //Dout
	}

        //set CS back to original state
        ADC_setCS(1); // CS

	return ret;

}

int ADC_getMISO(){
	//GET THE INPUT
	return PORTBbits.RB8;	
}

void ADC_clock(){
    //cycle the clock
	LATBbits.LATB3 = 1; //CLK
	LATBbits.LATB3 = 0; //CLK

}

void ADC_setCS(int val){
	//set CS pin
	LATBbits.LATB15 = val;
}

void ADC_setMOSI(int val){
	//set MOSI 
	LATBbits.LATB2 = val;
}


