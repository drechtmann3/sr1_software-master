/*
 * Georgia Tech Solar Racing
 * Battery Management System Source Code
 * Microcontroller: Texas Instruments Piccolo Series - TMS320F28069
 * Contributors: Fred Chen (tm602502@gmail.com), Leonardo Bernal (leo.esteban.bernal@gmail.com),
 * Reid Kersey (reidkersey@gmail.com), Ricky Liou (rliou92@gmail.com), Alex Popescu (apopescu@gatech.edu)
 * Date: 06/21/2014
 * Version: 2.0
 */

#include "BMS.h"

//Beware of Memory limit of any combination of float32 arrays that add up to 4000 elements.

int tempSensorSegment = 0; // Can be 0, 1, 2, or 3 for 1-10, 11-20, and 21-30 temp sensors.
char allTempSensorsRead = 0;
char voltageTrips = 0;

Uint32 loopCount = 0;

void main(void) {
	/*
	// Copy PIE vect table from Flash into RAM
	PieCtrlRegs.PIECTRL.bit.ENPIE = 0; // Disable the PIE
	EALLOW;
	memcpy((void *)0x000D06, (Uint16 *)&PieVectTableInit+6, 256-6);
	EDIS;*/
	InitPieVectTable();

	//memcpy((Uint16 *)&RamfuncsRunStart,(Uint16 *)&RamfuncsLoadStart, (Uint32)&RamfuncsLoadSize); // Copy RAM functions from Flash into RAM.
	//InitFlash();


	//InitSysCtrl();

	/*
			//Initialize other GPIO
			GpioInit();

		//GpioDataRegs.GPASET.bit.GPIO1 = 1;  // Turn on Array Relay
					//GpioDataRegs.GPASET.bit.GPIO2 = 1; // Turn on Battery Relay
			DELAY_US(1e6);
			while(1) {
				EALLOW;

			GpioDataRegs.GPACLEAR.bit.GPIO20 = 1;
			EDIS;
			}

					while(1);
	 */
	EALLOW;

	//Disable watchdog timer
	SysCtrlRegs.WDCR = 0x68;



	//Initialize System Clock
	SysClkInit();


	//if (!writeSOCIntoFlash()) puts("Could not write flash!");

	// Initialize interrupts.
	InterruptInit();
	/* If interrupts don't work, try this:
	 DINT;           // Disable interrupts
	InitPieCtrl();  // Initialize and clear PIE control registers. Clear all interrupt flags.
	IER = 0x0000;   // Disable CPU interrupts and clear all CPU interrupt flags:
	IFR = 0x0000;
	InitPieVectTable(); //Initialize the PIE vector table with pointers to the shell Interrupt Service Routines (ISR).
	 */
	//Initialize timer
	TmrInit();

	//Intialize ADC
	AdcInit();
	//Initialize other GPIO
	GpioInit();
	//Initialize SPI Module
	SpiInit();

	//Initialize CAN, with interrupts
	//CAN_init(BMS_CAN_INFO_ARRAY, 4, 1);


	//Initialize temp sensors
	intializeTempSensors();

	// SPI Functions Initialization
	writeConfig();
	//readConfig();

	// Re-enable watchdog timer
	//SysCtrlRegs.WDCR = 0x28;
	EDIS;

	// Make sure contactors are off initially.
	GpioDataRegs.GPACLEAR.bit.GPIO1 = 1; // Turn off Array Relay
	GpioDataRegs.GPACLEAR.bit.GPIO2 = 1;// Turn off Battery Relay

	//GpioDataRegs.GPACLEAR.bit.GPIO20 = 1; // LED 1 turn on
	//DELAY_US(1e6L); // 100ms delay before we turn on any contactors.
	//GpioDataRegs.GPASET.bit.GPIO20 = 1; // Turn LED 1 turn off, to let us know the code is actually running.

	//Fetch SoC value
	/*
	i2c_send_start_and_slave_address(FRAM_I2C_SLAVE_ADDRESS, 0);
	i2c_send_data_byte((Uint16) FRAM_SOC_ADDRESS);
	i2c_send_start_and_slave_address(FRAM_I2C_SLAVE_ADDRESS, 1);
	SoC = (float32) i2c_read_data_byte(2) / 100.0f; //Send no acknowledge and then STOP bit
*/
	int i;
	for (i = 1; i <= 30; i++) {
		voltagesTripped[i] = 0;
		tempSensorReadCommandSent[i] = 0;
		tempSensorTimers[i] = 1700;
		tempSensorStatuses[i] = 0;
	}
	while(1) {
		//puts("ml");
		//EALLOW;
		//Service watchdog timer
		//SysCtrlRegs.WDKEY = 0x55;
		//SysCtrlRegs.WDKEY = 0xAA;
		//EDIS;
		loopCount++;

		// Read voltages of batteries...
		readSPIVoltages();

		for (i = 0; i < 10; i++) { // Bottom voltages
			if (bVoltages[i] <= MIN_MODULE_VOLTAGE || bVoltages[i] > MAX_MODULE_VOLTAGE) voltagesTripped[i]++;
			else voltagesTripped[i] = 0;
		}
		for (i = 0; i < 10; i++) { // Middle voltages
			if (mVoltages[i] <= MIN_MODULE_VOLTAGE || mVoltages[i] > MAX_MODULE_VOLTAGE) voltagesTripped[10 + i]++;
			else voltagesTripped[10 + i] = 0;
		}
		for (i = 0; i < 10; i++) { // Top voltages
			if (tVoltages[i] <= MIN_MODULE_VOLTAGE || tVoltages[i] > MAX_MODULE_VOLTAGE) voltagesTripped[20 + i]++;
			else voltagesTripped[20 + i] = 0;
		}
		for (i = 0; i < 30; i++) {
			if (voltagesTripped[i] >= 30) {
				// Trip for real.
				char str[32];
				if (i < 10) sprintf(str, "Cell %d at %d (V*100)", i, (int)(bVoltages[i]*100.0f));
				else if (i < 20) sprintf(str, "Cell %d at %d (V*100)", i, (int)(mVoltages[i-10]*100.0f));
				else if (i < 30) sprintf(str, "Cell %d at %d (V*100)", i, (int)(tVoltages[i-20]*100.0f));
				puts(str);
				turnOffCar();
			}
			if (voltagesTripped[i] >= 1) {
				char str[32];
								if (i < 10) sprintf(str, "Cell %d at %d (V*100)", i, (int)(bVoltages[i]*100.0f));
								else if (i < 20) sprintf(str, "Cell %d at %d (V*100)", i, (int)(mVoltages[i-10]*100.0f));
								else if (i < 30) sprintf(str, "Cell %d at %d (V*100)", i, (int)(tVoltages[i-20]*100.0f));
								puts(str);
			}
		}

/*
		// Check overvoltage and undervoltage conditions:
		if (minVoltage <= MIN_MODULE_VOLTAGE) {
			puts("Min voltage");
			char str[32];
			sprintf(str, "Tripped at V:%dV", (int)(minVoltage*30.0f));
			puts(str);
			voltageTrips++;
		}
		if (maxVoltage >= MAX_MODULE_VOLTAGE) {
			puts("Max voltage");
			char str[32];
				sprintf(str, "Tripped at V:%dV", (int)(maxVoltage*30.0f));
				puts(str);
			voltageTrips++;
		}
		if (voltageTrips > 30) {
			puts("Bad voltage");
			turnOffCar();
		}
*/

		for (i = 1; i <= 30; i++) {
			if (tempSensorTimers[i] > 1600) { // Wait 750ms
				if (tempSensorReadCommandSent[i]) {
					if (!readTempSensor(i)) {
						puts("Temp sensor read error");
						turnOffCar();
					}
					if (tempSensorReadings[i] >= BAT_TEMP_LIMIT_C) {
						puts("Battery temp limit reached! Turning off car!");
						turnOffCar();
					}
				}
				tempSensorTimers[i] = 0;
				if (!sendReadCommandOfDS18B20(i)) {
					puts("Temp sensor send read command error");
					turnOffCar();
				}
				tempSensorReadCommandSent[i] = 1;
				break;
			}
		}


/*
		// Read temperature sensors...
		if (tempSensorSegment == 0) {
			if (!readTempSensors(1, 6)) { // Takes ~1.8s for 30 temp sensors.
				puts("t1");
				turnOffCar();
			}
		} else if (tempSensorSegment == 1) {
			if (!readTempSensors(7, 13)) { // Takes ~1.8s for 30 temp sensors.
				puts("t2");
				turnOffCar();
				return;
			}
		} else if (tempSensorSegment == 2) {
			if (!readTempSensors(14, 23)) { // Takes ~1.8s for 30 temp sensors.
				puts("t3");
				turnOffCar();
			}
		} else if (tempSensorSegment == 3) {
			allTempSensorsRead = 1;
			if (!readTempSensors(24, 30)) { // Takes ~1.8s for 30 temp sensors.
				puts("t4");
				turnOffCar();
				allTempSensorsRead = 0;
			}

		}
		tempSensorSegment++;
		if (tempSensorSegment > 3) tempSensorSegment = 0;

		if (allTempSensorsRead && getHighestTempSensorReading() >= BAT_TEMP_LIMIT_C) {
			puts("Battery temp limit reached! Turning off car!");B
			turnOffCar();
		}*/

		//char str[32];
		//sprintf(str, "Highest temp sensor: %d", (int)getHighestTempSensorReading());
		//puts(str);

		if (minVoltage > MIN_MODULE_VOLTAGE && maxVoltage < MAX_MODULE_VOLTAGE_WARNING             // Voltage OK
				&& batCurrent > MAX_CHARGE_CUR && batCurrent < MAX_DISCHARGE_CUR && batCurrentRead // Current OK
				&& getHighestTempSensorReading() < BAT_TEMP_LIMIT_C) {       // Temperature OK
			// We are OK to operate.
			//puts("Everything is OK, turning on.");

			GpioDataRegs.GPASET.bit.GPIO1 = 1; // Turn on Array Relay
			GpioDataRegs.GPASET.bit.GPIO2 = 1; // Turn on Battery Relay

			//char str[32];
			//sprintf(str, "Amps: %dA", (int)(batCurrent));
			//puts(str);
		}

	}
}

void turnOffCar() {
	GpioDataRegs.GPACLEAR.bit.GPIO1 = 1; // Turn off Array Relay
	GpioDataRegs.GPACLEAR.bit.GPIO2 = 1;// Turn off Battery Relay
	while(1); // Stop running code.
}

#pragma CODE_SECTION(readSPIVoltages,"ramfuncs");
void readSPIVoltages() {
	startCellRead();
	waitforCells();
	readVoltages(); // Must call this before doing voltage logic below
}

