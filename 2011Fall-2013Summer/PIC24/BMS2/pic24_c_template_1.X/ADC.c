#include "ADC.h"
#include "relay.h"
#include "main.h"
#include <p24HJ128GP202.h>

//TODO:
//set ranges for current sensors

int checkTemperature(int channel){
    //TODO: comment code
    double temp = readTempSensor(channel);
    if(temp < TEMP_MIN || temp > TEMP_MAX){
        setRelay(RELAY_OFF);
        return RED_STATUS;
    }
    if(temp <= TEMP_YELLOW_MIN || temp >= TEMP_YELLOW_MAX){
        return OVERTEMP_STATUS;
    }
    else{
        return GREEN_STATUS;
    }
}

int checkCurrentSensor(int channel){
    double current = readCurrentSensor(channel);
    if (current < CURRENT_MIN || current > CURRENT_MAX){
      setRelay(RELAY_OFF);
      return RED_STATUS;
    }
    if(current <= CURR_YELLOW_MIN || current >= CURR_YELLOW_MAX){
        return OVERCURRENT_STATUS;
    }
    else{
        return GREEN_STATUS;
    }
}

double readCurrentSensor(int channel){
    double vpb = (5/1024); //volts per bit = refrence voltage (5V) over the number of available ADC resolution (10 bits = 2^10 = 1024)
    double ret = ADCReadAvg(channel); //read the channel
    ret = ret * vpb; //get voltage of input
    ret=(ret/0.1) + 25; //since the ratio of voltage to amperage is .1. when we have 0 A we have 2.5 V or when we have 0 V we have 25 A.
    return ret;
}

double readTempSensor(int channel){
    double vpb = (5/1024); //volts per bit = refrence voltage (5V) over the number of available ADC resolution (10 bits = 2^10 = 1024)
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

int ADCReadRaw(int channel)
{

	int i;
	int ret = 0;

	//CYCLE CS TO WAKE CHIP
        LATBbits.LATB15 = 1; //cs
        LATBbits.LATB15 = 0;

        //send start bit
        LATBbits.LATB14 = 1; //din
        clock();

	// select single-ended input
        LATBbits.LATB14 = 1; //Din
        clock();

	// channel request (three clock cycles)
	for ( i = 0; i < 3; i++ ) {
            LATBbits.LATB14 = ((channel & (1<<(2-i)))>>(2-i)); //Din
            clock();
	}

	// ignore null bits (there are 2)
        clock();
        clock();

	// recieve response
	for(i=0; i < 10; i++) {
            clock();
            ret <<= 1;
            ret |= PORTBbits.RB13; //Dout
	}

        //set CS back to original state
        LATBbits.LATB15 = 1; // CS

	return ret;

}
void clock(){
    //cycle the clock
    LATBbits.LATB12 = 0; //CLK
    LATBbits.LATB12 = 1;
}