#include "BMS.h"

/*
 * This file has the functions for determining the battery state of charge.
 */

volatile float32 SoC; //Battery SoC
// Save SOC:
// http://www.ti.com/lit/an/sprab69/sprab69.pdf

//Calculate SoC
//Max battery capacity = 3.2 Ah / cell, 3.2 * 16 = 51.2 Ah total

void calcSOC(float32 avg_current){
	//TODO Need a way of keeping track of battery charge when car turns off!
	float32 delta_SoC; //Store change of SoC

	//If batteries' voltages are too high, then SoC is 100% (51.2 Ah)
	if(averageVoltage >= MAX_BATTERY_VOLTAGE)
	{
		delta_SoC = 51.2 - SoC;
		SoC = 51.2;
	}
	////If batteries' voltages are too low, then SoC is 0% (0 Ah)
	else if(averageVoltage <= MIN_BATTERY_VOLTAGE)
	{
		delta_SoC = 0 - SoC;
		SoC = 0;
	}
	else
	{
		//Coulomb counting method of calculating SoC
		//Just integrating current over time
		//1/36000 comes from (.1 seconds)*(3600 seconds/hour) = SoC calculation frequency
		delta_SoC = avg_current / 36000;
		SoC -= delta_SoC;
	}
		// Save SoC every time we decrease/increase a percent in SoC
	if (fabs(delta_SoC) > 0.01*52.1) {
		/*
		i2c_send_start_and_slave_address(FRAM_I2C_SLAVE_ADDRESS, 0);
		i2c_send_data_byte((Uint16) FRAM_SOC_ADDRESS);
		i2c_send_data_byte((Uint16) SoC*100);
		I2caRegs.I2CMDR.bit.STP = 1; // Stop transaction.
				//puts("SOC in flash updated!");
				//writeSOCIntoFlash();
				 */
	}
}
