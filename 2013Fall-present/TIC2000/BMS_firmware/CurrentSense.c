#include "BMS.h"

/*
 * This file contains the functions for sensing the battery current using a hall effect sensor.
 */

volatile float32 batCurrent = 0; //Instantaneous battery current
volatile char batCurrentRead = 0;
volatile int BMSCurrentTrips = 0;
volatile Uint32 BMSCurrentCycles = 0;

//Fetch value from ADC and calculate current from battery pack
//Shuts off car if current is out of bounds
/* Recommended continuous discharge rate per battery is <= 3.2 A
 * Recommended pulse discharge rate is <= 13 A
 * Recommended charge current is <= 1.6 A
 * 16 batteries in parallel
 * Looks like we gotta use 4 current sensors now.
 */
__interrupt void getCurrent(void){
	//puts("Current interrupt");
	static int counter = 0;
	static float32 batCurrent_sum = 0; //Running sum of measured currents
	Uint16 ADC_res;

	/* Update temp sensor timers */
	int i = 0;
	for (i = 1; i <= 30; i++)
		tempSensorTimers[i]++;

	ADC_res = AdcResult.ADCRESULT1;
	//Convert ADC result into battery current
	batCurrent =  ((float32) ADC_res * 0.14139f) - 283.978f; //Determined from experimental data
	batCurrent = -batCurrent; // Flip b/c current sensor is flipped.
	batCurrent_sum  += batCurrent; //Keep a running sum of measured currents
	BMSCurrentCycles++;

	if (batCurrent >= MAX_DISCHARGE_CUR || batCurrent <= MAX_CHARGE_CUR) {
		//char str[32];
		//sprintf(str, "Tripped at I:%dA", (int)(batCurrent));
		//puts(str);
		BMSCurrentTrips++;
	}
	if (BMSCurrentTrips >= 50 /*&& BMSCurrentCycles > 15000L*/) {
		puts("Final current trip!");
		batCurrentRead = 1;

		GpioDataRegs.GPACLEAR.bit.GPIO1 = 1; // Turn off Array Relay
		GpioDataRegs.GPACLEAR.bit.GPIO2 = 1;// Turn off Battery Relay
		AdcRegs.ADCINTFLGCLR.bit.ADCINT1 = 1; //Clear ADCINT1 flag reinitialize for next SOC
		PieCtrlRegs.PIEACK.all = PIEACK_GROUP1; // Acknowledge interrupt to PIE
	}

	// Send warning messages if we are 5A within either charging or discharging limit:
	if(batCurrent > MAX_DISCHARGE_CUR - 5){
		// Send overdischarge warning
	}
	else if(batCurrent < MAX_CHARGE_CUR + 5){
		// Send overcharge warning
	}

	//Calculate SOC every 100 ms (1 interrupt = 1 ms)
	if(++counter > 99){
		calcSOC(batCurrent_sum / 100.0f + 0.35); //Calculate SOC based on the average of the last 100 current samples, added small offset to offset negative voltage
		counter = 0; //Reset counter
		batCurrent_sum = 0; //Reset running sum
	}

	batCurrentRead = 1;
	AdcRegs.ADCINTFLGCLR.bit.ADCINT1 = 1; //Clear ADCINT1 flag reinitialize for next SOC
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP1; // Acknowledge interrupt to PIE
	return;
}
