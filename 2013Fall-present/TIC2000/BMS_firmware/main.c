/*
 * Georgia Tech Solar Racing
 * Battery Management System Firmware version 2.0
 * Contributors: Drew Harris
 */


/*
 * Adding CAN into the code gives out of memory errors. Removing stuff.
 * de-include CAN library
 * exclude BMS_CAN.c from build
 * comment out temp.c's can.h include and sendreadingsoverCAN
 */

#include "BMS.h"
#include "BMS_CAN.h"

Uint16 car_ready=0;
Uint16 temps_delay=0;
Uint16 temps_started=0;
Uint16 voltages_started=0;
float32 TempSensorSlope=0;
Uint16 TempSensorOffset=0;
Uint16 current_int=0;
Uint16 dietemp_int=0;
float32 current=0;
float32 dietemp=0;
Uint32 error_V=0;
Uint32 error_T=0;
Uint32 error_I=0;
Uint32 v_low_count=0;
Uint32 v_high_count=0;
Uint32 v_high_count_clear=0;
Uint16 UV_flag=0;
Uint16 OV_flag=0;
Uint32 timerloopcount=0;
float32 maxbatcurrent=0;
volatile float32 batCurrent = 0; //Instantaneous battery current
float32 time_ms=0; //delay time in msec
static const Uint16 sysclk_mult = 9; //Set integer multiplier of 10MHz oscillator between 1 [10MHz] < sysclk_mult < 9 [90MHz]
static const Uint16 timer_freq = 1000; //Set CPU Timer 0 frequency (Hz)

#pragma CODE_SECTION(InitFlash, "secureRamFuncs")
void InitFlash(void) {
EALLOW;
FlashRegs.FPWR.bit.PWR = 3; //Change flash wait states
FlashRegs.FBANKWAIT.bit.RANDWAIT = 2;
FlashRegs.FBANKWAIT.bit.PAGEWAIT = 2;
FlashRegs.FOPT.bit.ENPIPE = 1;
EDIS;
asm(" RPT #6 || NOP");
}

#include "string.h"
extern unsigned int secureRamFuncs_loadstart;
extern unsigned int secureRamFuncs_loadsize;
extern unsigned int secureRamFuncs_runstart;

//extern Uint16 RamfuncsLoadStart;
//extern Uint16 RamfuncsLoadEnd;
//extern Uint16 RamfuncsRunStart;

void main(void) {
	memcpy(&secureRamFuncs_runstart, &secureRamFuncs_loadstart, (Uint32)&secureRamFuncs_loadsize);

//	memcpy(&RamfuncsRunStart, &RamfuncsLoadStart, (Uint32) &RamfuncsLoadEnd);
	InitFlash();

	EALLOW;
	SysCtrlRegs.WDCR=0x68; //disable watchdog

	// Initialize clock, timer, interrupts, GPIO, ADC, and SPI
	SysClkInit();
	TimerInit();
	InterruptInit();
	GpioInit();
	AdcInit();
	SpiInit();
//	BMS_CAN_init();
	WaitLoop(3); //changed from 5msec to 3msec

	initializeTempSensors(); //set up I2C for digital temp sensors
	writeConfig(); //write LTC6803 config to all chips
//	importSOCfromFRAM();

	EINT; //enable CPU interrupts
	CpuTimer0Regs.TCR.bit.TSS = 0; //start CPU timer O

	SysCtrlRegs.WDCR=0x28; //enable watchdog
	EDIS;

	TempSensorSlope = getTempSlope()/((float32)((int32)0x2 << 15)); //load stored temp slope for dietemp
	TempSensorOffset = getTempOffset(); //load stored temp offset for dietemp

//	CanReceive();

	while(1)
	{
		EALLOW;
		SysCtrlRegs.WDKEY = 0x55; // service watchdog sequence
		SysCtrlRegs.WDKEY = 0xAA;
		EDIS;
	}
}

void SysClkInit(void)
{
	SysCtrlRegs.CLKCTL.bit.INTOSC1OFF = 0; //Use internal osc 1
	while (SysCtrlRegs.PLLSTS.bit.MCLKSTS); //Check whether clock exists
	SysCtrlRegs.PLLSTS.bit.DIVSEL = 0; //Reset DIVSEL to 0 before PLL locks
	SysCtrlRegs.PLLSTS.bit.MCLKOFF = 1; //Turn off clock check
	SysCtrlRegs.PLLCR.bit.DIV = sysclk_mult; //Set 1<DIV<18 for clock multiplication; 0 to bypass PLL
	while (!SysCtrlRegs.PLLSTS.bit.PLLLOCKS); //Wait until PLL locks
	SysCtrlRegs.PLLSTS.bit.MCLKOFF = 0; //Turn on clock check
	SysCtrlRegs.PLLSTS.bit.DIVSEL = 3; //Set 0<DIVSEL<3 to divide clock (CLKIN/4,CLKIN/2,CLKIN/1)

	SysCtrlRegs.LOSPCP.bit.LSPCLK = 2;  //Sets Low-Speed Peripheral Clock = 90MHz/4 for SPI module
}

void TimerInit(void)
{

	CpuTimer0Regs.PRD.all = (Uint32)(sysclk_mult*10000000/timer_freq-1); // PRD.ALL = (fsys/ftmr)-1
	CpuTimer0Regs.TPR.bit.TDDR = 0x0;
	CpuTimer0Regs.TPRH.bit.TDDRH = 0x0;

	CpuTimer0Regs.TCR.bit.TSS = 1; //stop CPU timer 0
	CpuTimer0Regs.TCR.bit.TRB = 1; //reload CPU Timer 0 counter
	CpuTimer0Regs.TCR.bit.TIE = 1; // Enable CPU Timer 0 as an interrupt source

}

void GpioInit(void)
{
	// Configure GPIOs to act as GPIOs (0)
	GpioCtrlRegs.GPAMUX2.bit.GPIO20=0; //LED1
	GpioCtrlRegs.GPAMUX2.bit.GPIO23=0; //LED2
	GpioCtrlRegs.GPAMUX1.bit.GPIO11=0; //LED3
	GpioCtrlRegs.GPAMUX1.bit.GPIO10=0; //LED4
	GpioCtrlRegs.GPAMUX2.bit.GPIO26=0; //Fan1
	GpioCtrlRegs.GPAMUX2.bit.GPIO27=0; //Fan2
	GpioCtrlRegs.GPAMUX1.bit.GPIO1=0; //Array Cutoff
	GpioCtrlRegs.GPAMUX1.bit.GPIO2=0; //Pack Cutoff
	GpioCtrlRegs.GPAMUX1.bit.GPIO4=0; //CAN_RS

	// Configure GPIO as input (0) or output (1)
	GpioCtrlRegs.GPADIR.bit.GPIO20=1; //LED1
	GpioCtrlRegs.GPADIR.bit.GPIO23=1; //LED2
	GpioCtrlRegs.GPADIR.bit.GPIO11=1; //LED3
	GpioCtrlRegs.GPADIR.bit.GPIO10=1; //LED4
	GpioCtrlRegs.GPADIR.bit.GPIO26=1; //Fan1
	GpioCtrlRegs.GPADIR.bit.GPIO27=1; //Fan2
	GpioCtrlRegs.GPADIR.bit.GPIO1=1; //Array Cutoff
	GpioCtrlRegs.GPADIR.bit.GPIO2=1; //Pack Cutoff
	GpioCtrlRegs.GPADIR.bit.GPIO4=1; //CAN_RS

	// Configure startup behavior of GPIOs
	GpioDataRegs.GPASET.bit.GPIO20=1; //LED1 off
	GpioDataRegs.GPASET.bit.GPIO23=1; //LED2 off
	GpioDataRegs.GPASET.bit.GPIO11=1; //LED3 off
	GpioDataRegs.GPASET.bit.GPIO10=1; //LED4 off
	GpioDataRegs.GPACLEAR.bit.GPIO26=1; //Fan1 off
	GpioDataRegs.GPACLEAR.bit.GPIO27=1; //Fan2 off
	GpioDataRegs.GPACLEAR.bit.GPIO1=1; //Array off
	GpioDataRegs.GPACLEAR.bit.GPIO2=1; //Pack off
	GpioDataRegs.GPACLEAR.bit.GPIO4=1; //CAN_RS low
}

void InterruptInit(void)
{
	PieCtrlRegs.PIECTRL.bit.ENPIE = 1; //Enable PIE vector table
	PieVectTable.TINT0 = &TimerISR; //Set interrupt subroutine pointing to TimerISR
	PieVectTable.ADCINT1 = &AdcISR; //Set interrupt subroutine pointing to AdcISR
	PieCtrlRegs.PIEIER1.bit.INTx7 = 1; //Enable PIE for CPU Timer 0
	PieCtrlRegs.PIEIER1.bit.INTx1 = 1; //Enablie PIE for ADCINT1
	IER = 1; //Enable CPU INT1
}

void SpiInit(void)
{
	// Initialize SPI Clocking
	SysCtrlRegs.PCLKCR0.bit.SPIAENCLK = 1;
	NOP;	NOP;     // Wait 2 clock cycles

	/* Enable internal pull-up for the selected pins */
	//   GpioCtrlRegs.GPAPUD.bit.GPIO3 = 0;    // Enable pull-up on GPIO3 (SPISOMIA)
	//   GpioCtrlRegs.GPAPUD.bit.GPIO5 = 0;    // Enable pull-up on GPIO5 (SPISIMOA)
	GpioCtrlRegs.GPAPUD.bit.GPIO16 = 0;   // Enable pull-up on GPIO16 (SPISIMOA)
	GpioCtrlRegs.GPAPUD.bit.GPIO17 = 0;   // Enable pull-up on GPIO17 (SPISOMIA)
	GpioCtrlRegs.GPAPUD.bit.GPIO18 = 0;   // Enable pull-up on GPIO18 (SPICLKA)
	GpioCtrlRegs.GPAPUD.bit.GPIO19 = 0;   // Enable pull-up on GPIO19 (SPISTEA)

	/* Set qualification for selected pins to ASYNC only */
	// This will select asynch (no qualification) for the selected pins.
	//   GpioCtrlRegs.GPAQSEL1.bit.GPIO3 = 3;  // Asynch input GPIO3 (SPISOMIA)
	//   GpioCtrlRegs.GPAQSEL1.bit.GPIO5 = 3;  // Asynch input GPIO5 (SPISIMOA)
	GpioCtrlRegs.GPAQSEL2.bit.GPIO16 = 3; // Asynch input GPIO16 (SPISIMOA)
	GpioCtrlRegs.GPAQSEL2.bit.GPIO17 = 3; // Asynch input GPIO17 (SPISOMIA)
	GpioCtrlRegs.GPAQSEL2.bit.GPIO18 = 3; // Asynch input GPIO18 (SPICLKA)
	GpioCtrlRegs.GPAQSEL2.bit.GPIO19 = 3; // Asynch input GPIO19 (SPISTEA)

	/* Configure SPI-A pins using GPIO regs*/
	// This specifies which of the possible GPIO pins will be SPI functional pins.
	//   GpioCtrlRegs.GPAMUX1.bit.GPIO3 = 2;  // Configure GPIO3 as SPISOMIA
	//   GpioCtrlRegs.GPAMUX1.bit.GPIO5 = 2;  // Configure GPIO5 as SPISIMOA
	GpioCtrlRegs.GPAMUX2.bit.GPIO16 = 1; 	// Configure GPIO16 as SPISIMOA
	GpioCtrlRegs.GPAMUX2.bit.GPIO17 = 1; 	// Configure GPIO17 as SPISOMIA
	GpioCtrlRegs.GPAMUX2.bit.GPIO18 = 1; 	// Configure GPIO18 as SPICLKA
	GpioCtrlRegs.GPAMUX2.bit.GPIO19 = 1; 	// Configure GPIO19 as SPISTEA, or ChipSelect

	/* Configuring SIMO, CLK, CS as Output pins, SOMI as Input pin */
	GpioCtrlRegs.GPADIR.bit.GPIO16 = 1;
	GpioCtrlRegs.GPADIR.bit.GPIO17 = 0;
	GpioCtrlRegs.GPADIR.bit.GPIO18 = 1;
	GpioCtrlRegs.GPADIR.bit.GPIO19 = 1;

	/* Our SPI configuration does not utilize FIFO mode. Instead, use regular SPI interrupts and communication mode.
	 * The following configuration was based upon page 839 and 849 of Technical Reference Manual.
	 */
	SpiaRegs.SPICCR.bit.SPISWRESET = 0;	//Enabling Sequence Step 1
	SpiaRegs.SPIBRR = 24;					//Step 2, Set Baud Rate to 900kHz
	SpiaRegs.SPICCR.bit.SPILBK = 0;		//Disable Loopback Mode;
	SpiaRegs.SPICTL.bit.MASTER_SLAVE = 1;	//Enabling Master Mode on microcontroller
	SpiaRegs.SPICTL.bit.TALK = 1;
	SpiaRegs.SPICCR.bit.SPICHAR = 7;		//Transmit 8 bits per clock cycle.
	SpiaRegs.SPIFFTX.bit.SPIFFENA = 0;		//As Described on page 849 of Manual, in order to trigger SPIINT w/o FIFO, this bit needs to be set to 0.
	SpiaRegs.SPICCR.bit.CLKPOLARITY = 1;	//Demanded by LTC6803-3 datasheet, page 17, under "Clock Phase And Polarity". Both Phase and Polarity need to be set to 1 in order to initiate communication.
	SpiaRegs.SPICTL.bit.CLK_PHASE = 0;
	SpiaRegs.SPICCR.bit.SPISWRESET = 1;  	//Step 3, Enable SPI
	SpiaRegs.SPIPRI.bit.FREE = 1;
}

void AdcInit(void)
{
	SysCtrlRegs.PCLKCR0.bit.ADCENCLK=1; //Enable ADC clock
	NOP;	NOP; //Wait 2 cycles after setting PCLKCR0

	AdcRegs.ADCCTL2.bit.CLKDIV2EN=1; // Divide SYSCLK/2 total
	AdcRegs.ADCCTL2.bit.CLKDIV4EN=0; //Divide SYSCLK/4 total (when CLKDIV2EN=1 and CLKDIV4EN=1)
	AdcRegs.ADCCTL2.bit.ADCNONOVERLAP=1; //Enable nonoverlap sampling

	AdcRegs.ADCCTL1.bit.ADCPWDN=1; //Power-up sequence of ADC
	AdcRegs.ADCCTL1.bit.ADCBGPWD=1;
	AdcRegs.ADCCTL1.bit.ADCREFPWD=1;
	AdcRegs.ADCCTL1.bit.ADCENABLE=1;

	AdcRegs.ADCSOC0CTL.bit.CHSEL=2; //use ADCINA2
	AdcRegs.ADCSOC0CTL.bit.ACQPS=0x3F; //sampling window is 63+1 samples
	AdcRegs.ADCSOC0CTL.bit.TRIGSEL=0; //software triggered

	AdcRegs.ADCCTL1.bit.TEMPCONV = 1;//use ADCINA5 for die_temp sensor
	AdcRegs.ADCSOC1CTL.bit.CHSEL=5; //use die_temp sensor
	AdcRegs.ADCSOC1CTL.bit.ACQPS=0x3F; //sampling window is 63+1 samples
	AdcRegs.ADCSOC1CTL.bit.TRIGSEL=0; //software triggered

	AdcRegs.INTSEL1N2.bit.INT1SEL=1; //EOC1
	AdcRegs.INTSEL1N2.bit.INT1E=1; //enable
	AdcRegs.ADCCTL1.bit.INTPULSEPOS=1; //late pulse
}

void WaitLoop(float time_ms)
{
	Uint32 j;
	for(j=0;j<(int)(8*time_ms*10000);j++)
	{
		NOP; //Each loop takes 8 CPU cycles to complete; waiting 1ms at 90MHz SYSCLK is 80k loops
	}
}

interrupt void TimerISR(void)
{
	int i;

	if(!voltages_started)
	{
		startCellConversions(); //send STCVAD to all LTC chips
		voltages_started=1;
		GpioDataRegs.GPACLEAR.bit.GPIO20 = 1; //Turn on LED1 when voltage conversions started
	}
	if(voltages_started)
	{
		if(pollVoltages()) {
			readVoltages(); //read all voltages from all chips and compute min/max/sum/avg voltages
			voltages_started=0; //reset voltages_started for next measurement
			GpioDataRegs.GPASET.bit.GPIO20 = 1; //Turn off LED1 when voltages read from LTC chips
		}
	}

	if(!temps_started)
	{
		for(i=1;i<=30;i++)
		{
			if(!sendReadCommandOfDS18B20(i))
			{
				puts("ERROR-main.c:275");
			}
		}
		temps_started=1;
		GpioDataRegs.GPACLEAR.bit.GPIO23 = 1; //Turn on LED2 to indicate temp conversions started
	}
	temps_delay++; //each timerISR is 1ms delay
	if(temps_started && temps_delay==750) //delay for 12bit resolution is 750ms
	{
		for(i=1;i<=30;i++)
		{
			if (!readTempSensor(i))
			{
				puts("ERROR-main.c:288");
			}
		}
		temps_started=0; //reset temps_started for next measurement
		temps_delay=0; //reset temps_delay for next measurement
		GpioDataRegs.GPASET.bit.GPIO23 = 1; //Turn off LED2 to indicate temp conversions have been read successfully
	}

	//	checkEverything(); //verify all voltages, temps, and current are within acceptable ranges

	AdcRegs.ADCSOCFRC1.bit.SOC0=1; //start ADC current measurement
	AdcRegs.ADCSOCFRC1.bit.SOC1=1; //start ADC dietemp measurement



	GpioDataRegs.GPATOGGLE.bit.GPIO10 = 1; //Toggle LED4

	if(minVoltage < MIN_MODULE_VOLTAGE_CRITICAL || maxVoltage > MAX_MODULE_VOLTAGE_CRITICAL)
	{
		error_V++;
	}
	else
	{
//		error_V= error_V>0?error_V--:0;
		error_V=0;
	}
	if(batCurrent < MAX_CHARGE_CUR || batCurrent > MAX_DISCHARGE_CUR) //values/inequalities flipped due to backward current sensor
	{
		error_I++;
	}
	else
	{
//		error_I= error_I>0?error_I--:0;
		error_I=0;
	}
	if(getHighestTempSensorReading() > BAT_TEMP_LIMIT_C)
	{
		error_T++;
	}
	else
	{
//		error_T= error_T>0?error_T--:0;
		error_T=0;
	}

	if(error_V>10 || error_I>5 || error_T>4)
	{
		turnOffCar();
	}
//				** working check of all values**
//	if(minVoltage > MIN_MODULE_VOLTAGE && maxVoltage < MAX_MODULE_VOLTAGE
//			&& batCurrent > MAX_CHARGE_CUR && batCurrent < MAX_DISCHARGE_CUR
//			&& getHighestTempSensorReading() < BAT_TEMP_LIMIT_C)
//	{
//		GpioDataRegs.GPASET.bit.GPIO1 = 1; //Enable Pack
//		GpioDataRegs.GPASET.bit.GPIO2 = 1; //Enable Array
//		car_ready=1;
//	}

//			**experimental check of values**
	if(minVoltage > MIN_MODULE_VOLTAGE_CRITICAL && maxVoltage < MAX_MODULE_VOLTAGE_CRITICAL
			&& batCurrent > MAX_CHARGE_CUR && batCurrent < MAX_DISCHARGE_CUR
			&& getHighestTempSensorReading() < BAT_TEMP_LIMIT_C)											//check to first make sure everything is not out of absolute max/min ratings
	{
		car_ready = 1; 																						//set to show car has initially started
		if(minVoltage >= MIN_MODULE_VOLTAGE && maxVoltage <= MAX_MODULE_VOLTAGE && !UV_flag && !OV_flag)	//make sure voltages between recommended voltage range
		{
			GpioDataRegs.GPASET.bit.GPIO1 = 1; //Enable Pack
			GpioDataRegs.GPASET.bit.GPIO2 = 1; //Enable Array
		}
		else if(minVoltage < MIN_MODULE_VOLTAGE && !UV_flag)										//if below the min recommended, turn off pack
		{
			v_low_count++;
			if(v_low_count>10)
			{
				GpioDataRegs.GPACLEAR.bit.GPIO1 = 1; //Disable Pack
				GpioDataRegs.GPASET.bit.GPIO2 = 1; //Enable Array
				UV_flag = 1;
				v_low_count=0;
			}
		}
		else if(maxVoltage > MAX_MODULE_VOLTAGE && !OV_flag)										//if above max recommended, turn off array
		{
			v_high_count++;
			if(v_high_count>10)
			{
				GpioDataRegs.GPASET.bit.GPIO1 = 1; //Enable Pack
				GpioDataRegs.GPACLEAR.bit.GPIO2 = 1; //Disable Array
				OV_flag = 1;
				v_high_count=0;
			}
		}
//		else if(minVoltage > MIN_MODULE_VOLTAGE_CAUTION && UV_flag)								//if min was prev. below min recommended but is now above the min caution level, re-engage pack
//		{
//			v_low_count_clear++;																//DO NOT USE because this would bypass precharge
//			if(v_low_count_clear>10)
//			{
//				GpioDataRegs.GPASET.bit.GPIO1 = 1; //Enable Pack
//				GpioDataRegs.GPASET.bit.GPIO2 = 1; //Enable Array
//				UV_flag = 0;
//				v_low_count_clear=0;
//			}
//		}
		else if(maxVoltage < MAX_MODULE_VOLTAGE_CAUTION && OV_flag)								//if max was prev. above max recommended but is now below the max caution level, re-engage array
		{
			v_high_count_clear++;
			if(v_high_count_clear>10)
			{
				GpioDataRegs.GPASET.bit.GPIO1 = 1; //Enable Pack
				GpioDataRegs.GPASET.bit.GPIO2 = 1; //Enable Array
				OV_flag = 0;
				v_high_count_clear=0;
			}
		}
	}

//			** Balancing decision making**
//	if (maxVoltage>MAX_MODULE_VOLTAGE_CAUTION && maxVoltage-minVoltage>.02 && batCurrent<3 && batCurrent>-3)
//	{
//		//commence balancing
//		// write config bytes once determined which cells need balancing
//		balance_flag=1;
//	}


//	timerloopcount++;

	PieCtrlRegs.PIEACK.bit.ACK1 = 1; //Clear the ACK to allow for new interrupts to be serviced in the future
}

interrupt void AdcISR(void)
{
	current_int = AdcResult.ADCRESULT0; //read result
	dietemp_int = AdcResult.ADCRESULT1; //read result
	// for current, just changed -274.978 to -275.978; when charging at 10A, it was reading about 11A
	batCurrent = -1*(((float32)current_int * 0.14139f) - 274.978f); //Determined from experimental data //added -1* since sensor is flipped
	dietemp = (dietemp_int - TempSensorOffset) * TempSensorSlope;
	if(batCurrent>maxbatcurrent)
	{
		maxbatcurrent=batCurrent;
	}
	//calcSOC(batCurrent);

	GpioDataRegs.GPATOGGLE.bit.GPIO11 = 1; //Toggle LED3

	//	logData();

	AdcRegs.ADCINTFLGCLR.bit.ADCINT1=1; //clear ADC interrupt
	PieCtrlRegs.PIEACK.all=1; //clear PIE interrupt
}

void turnOffCar(void)
{
	GpioDataRegs.GPACLEAR.bit.GPIO1 = 1; //Disable Pack
	GpioDataRegs.GPACLEAR.bit.GPIO2 = 1; //Disable Array
	if(car_ready==1)
	{
		while(1);
		// eventually fill with CAN message sending to driver and logging
	}
}

void startCellConversions(void)
{
	int wait = 0;
	//Necessary wait time
	while(wait < 100)
	{
		wait++;
	}
	SpiSend(STCVAD); //start all chips converting all voltages
	SpiSend(calcPEC(STCVAD));
}

int pollVoltages(void)
{
	SpiSend(PLADC); //poll whether conversions finished
	SpiSend(calcPEC(PLADC));
	SpiReceive(); //dmmy receive
	return SpiReceive(); //should be 1 when chips are finished converting
}
