/* Solar Jackets Battery Management System (BMS) Source Code
 * Author: Fred Chen (tm602502@gmail.com)
 * Current Author: Leonardo Bernal (leo.esteban.bernal@gmail.com)
 * Last Updated: 4/16/14
 * Microcontroller: TMS320F28069
 */

#include "F2806x_Device.h"
#include <math.h>
#include "BMS.h"
#include "F2806x_PieVect.h"
#include <stdlib.h>
#include "28069Common.h"
#include "CAN.h"

/****Global Variables****/
/* Beware of Memory limit of any combination of float32 arrays that add up to 4000 elements.*/
Uint32 fsys = 90000000; // CPU System Frequency is 90MHz
Uint32 ftmr = 100; // Timer reset Frequency is 100Hz
int32 k = 0;
int32 i = 0;
int32 a = 0;
int32 shift = 0;
int32 vtgcnt = 0;
int32 ctr = 0;

// ADC Variables
float32 Temp_1[100];  // Will not be converted from F28069 ADC, but received from the I2C data
float32 Temp_11;
float32 Temp_2[100];
float32 Temp_22;
float32 Temp_3[100];
float32 Temp_33;
float32 Temp_4[100];
float32 Temp_44;
float32 Temp_5[100];
float32 Temp_55;
float32 Temp_6[100];
float32 Temp_66;
float32 TempAverage = 0.00;

float32 i_Hall_1[100];
float32 i_Hall_11;
float32 i_Hall_2[100];
float32 i_Hall_22;

// SPI Variables
float32 V_Result_1[100];
float32 V_Result_2[100];
float32 V_Result_3[100];
float32 V_Result_4[100];
float32 V_Result_5[100];
float32 V_Result_6[100];
float32 V_Result_7[100];
float32 V_Result_8[100];
float32 vAverage = 0.00;

float32 VVV;
char spiTestBuf;
Uint16 CFGR_PEC = 0;
Uint16 CFGR1 = 0;
Uint16 CFGR2 = 0;
Uint16 CFGR3 = 0x20;
Uint16 CFGR4 = 0;
Uint16 CFGR5 = 0;
Uint16 ConfigBytes[7];
int32 testPurposes = 0;
int32 testCFG[6];
int32 numCells = 9;
int32 numCVR = 15;
Uint16 FLG[3];
Uint32 dummy = 0;
int32 ListenConfig = 0;

// Battery Stack Monitor Variables
int32 OVvalue = 0;
int32 OVthresh = 4200;
int32 UVvalue = 0;
int32 UVthresh = 3200;

// Test Variables
float32 iii = 0;
float32 packSoc;
float32 Temp_Actual[4];
float32 currentact = 0.5; // current in Amps
float32 i_Test = 0;

// Balancing Algorithm Variables
float32 minVolt; //stores the minimum cell voltage at any given time
float32 v_Arr[27];
float32 preBal_Arr[27];
int32 sizeArr;
float32 CellVoltages[9];
int32 CellVolts[10];
Uint16 CVR[15];
float32 Vavg=0.00;
int32 VoltageBad = 0;

// SoC Variables
float32 dischar = 0.00;
float32 capacity = 1.3; // in Ah
float32 p1 = 3.095;
float32 p2 = 40.09;
float32 p3 = 191.00;
float32 p4 = 398.30;
float32 p5 = 310.90;
float32 x = 0.00;
float32 socPct;
float32 i_11_Actual = 0.00;
/***Global Variables End***/

bool sent = true;
bool data_init = false;
	//Number of CAN nodes must be less than 2^29! Not going to be a problem...ever
void BMSSendInterrupt(CAN_ID ID, Uint32 dataH, Uint32 dataL, Uint16 length, int mbox_num){
	sent = true;
}

void BMSReceiveInterrupt(CAN_ID ID, Uint32 dataH, Uint32 dataL, Uint16 length, int mbox_num){
	if(data_init && sent){
		sent = false;
		if(ID == BMS_TEMP){
			float32 temps[7];
			temps[0] = Temp_11;
			temps[1] = Temp_22;
			temps[2] = Temp_33;
			temps[3] = Temp_44;
			temps[4] = Temp_55;
			temps[5] = Temp_66;
			temps[6] = TempAverage;
			CAN_send(convertFloats(temps,7),7*4,ID,0,0);
		}else if(ID == BMS_VOLTS){
			int i;
			Uint32 voltages[11];
			Uint32* vIntArr = convertFloats(CellVoltages,9);
			for(i=0;i<9;i++)
				voltages[i] = vIntArr[i];
			voltages[9] = convertFloat(minVolt);
			voltages[10] = convertInt(Vavg);
			CAN_send(voltages,11*4,ID,0,0);
		}else if(ID == BMS_CURRENT){
			Uint32 currents[2];
			currents[0] = convertFloat(i_Hall_11);
			currents[1] = convertFloat(i_Hall_22);
			CAN_send(currents,2*4,ID,0,0);
		}else if(ID == BMS_CHARGE){
			//TODO
		}
	}
}

CAN_INFO CAN_ARRAY[] = {
		{
				BMS_TEMP,
				&BMSSendInterrupt,
				&BMSReceiveInterrupt
		},{
				BMS_VOLTS,
				&BMSSendInterrupt,
				&BMSReceiveInterrupt
		},{
				BMS_CURRENT,
				&BMSSendInterrupt,
				&BMSReceiveInterrupt
		},{
				BMS_CHARGE,
				&BMSSendInterrupt,
				&BMSReceiveInterrupt
		}
};

void canInit(){
	deviceInit();
	CAN_init(CAN_ARRAY,4);
}


void main(void)
{
	EALLOW;
	// Disable watchdog timer
	SysCtrlRegs.WDCR = 0x68;

	// Initialize System Clock
	SysClkInit();

	// Initialize Timer Reset
    TmrInit();

	// Initialize Program
	GpioInit();

	// ADC Module Initialization
	AdcInit();

	// SPI Module Initialization
	SpiInit();

	// SPI Functions Initialization
	writeConfig();
	readConfig();

	// Start CPU Timer
	CpuTimer0Regs.TCR.bit.TSS = 0;

	// Re-enable watchdog timer
	SysCtrlRegs.WDCR = 0x28;
	EDIS;

	while(1)
	{
		EALLOW;
		// Service watchdog timer
		SysCtrlRegs.WDKEY = 0x55;
		SysCtrlRegs.WDKEY = 0xAA;
		EDIS;

		// Main Functions
		startCellRead();
		AdcRead();
		DataRecord();
		waitforCells();
		readVoltages();

		// Blinking LED
		if (ctr == 10) { GpioDataRegs.GPATOGGLE.bit.GPIO20 = 1; ctr=0; }
		ctr++;

		// Check State of Charge of the Battery
		checkSOC();

		// Relay Open and Close Conditions
		if (VoltageBad == 0 && TempAverage <= 32.00)
		{
			GpioDataRegs.GPASET.bit.GPIO9 = 1;
			GpioDataRegs.GPASET.bit.GPIO28 = 1;
		}
		else if (TempAverage >= 36.00)
		{
			GpioDataRegs.GPACLEAR.bit.GPIO9 = 1;
			GpioDataRegs.GPACLEAR.bit.GPIO28 = 1;
		}
	}
}

/* This function sets the system clock frequency */
void SysClkInit(void){
	if(SysCtrlRegs.PLLSTS.bit.MCLKSTS == 0)
	{
		// Check if DIVSEL is 2 or 3 and if yes, set it to 0
	    if(SysCtrlRegs.PLLSTS.bit.DIVSEL == 2 || SysCtrlRegs.PLLSTS.bit.DIVSEL == 3 )
		{
		  SysCtrlRegs.PLLSTS.bit.DIVSEL = 0;
		}

	    // Enable oscillator fail detect logic
		SysCtrlRegs.PLLSTS.bit.MCLKOFF = 1;

		// Set System clock frequency (90 MHz)
		SysCtrlRegs.PLLCR.bit.DIV = 9;

		// Wait until phase locked loop has locked
	while(SysCtrlRegs.PLLSTS.bit.PLLLOCKS != 1)
		{

		}

	    // Disable oscillator fail detect logic
		SysCtrlRegs.PLLSTS.bit.MCLKOFF = 0;

		// Set the value of DIVSEL that gives 90 MHz
		SysCtrlRegs.PLLSTS.bit.DIVSEL = 3;
	}
	SysCtrlRegs.LOSPCP.bit.LSPCLK = 0;  //Sets Low-Speed Peripheral Clock = 90MHz for SPI Module.
}

/* This function sets the timer reset frequency */
void TmrInit(void)
{
    // Set the appropriate 32 bit main counter
	CpuTimer0Regs.PRD.all = (fsys/ftmr)-1;

	// Prepare CPU Timer 0 for action
	CpuTimer0Regs.TCR.bit.TSS = 1;
	CpuTimer0Regs.TCR.bit.TRB = 1;
	CpuTimer0Regs.TCR.bit.TIE = 1;
}
/* This function configures the GPIOs */
void GpioInit(){
	GpioCtrlRegs.GPAMUX2.bit.GPIO20 = 0; // Configure pin as GPIO
	GpioCtrlRegs.GPAPUD.bit.GPIO20 = 0; // Enable internal pullup on the specified pin
	GpioCtrlRegs.GPADIR.bit.GPIO20 = 1; // Configure as Output
	// Pack Cutoff GPIO28
	GpioCtrlRegs.GPAMUX2.bit.GPIO28 = 0;
	GpioCtrlRegs.GPAPUD.bit.GPIO28 = 1; // Disable internal pullup on the specified pin
	GpioCtrlRegs.GPADIR.bit.GPIO28 = 1;
	// Array Relay GPIO09
	GpioCtrlRegs.GPAMUX1.bit.GPIO9 = 0;
	GpioCtrlRegs.GPAPUD.bit.GPIO9 = 1;
	GpioCtrlRegs.GPADIR.bit.GPIO9 = 1;
	// SDA (I2C) GPIO32
	GpioCtrlRegs.GPBMUX1.bit.GPIO32 = 1; // Configure pin as SDAA for I2C
	// SCLK (I2C) GPIO33
	GpioCtrlRegs.GPBMUX1.bit.GPIO33 = 1; // Configure pin as SCLA for I2C
	GpioCtrlRegs.GPBDIR.bit.GPIO33 = 1;
}

/* This function initializes the ADC module*/
void AdcInit(void)
{
	// Initialize ADC Clocking
	SysCtrlRegs.PCLKCR0.bit.ADCENCLK = 1; //enables ADC clock
		asm(" NOP");     asm(" NOP");     // Wait 2 clock cycles

	// Scale the ADC Clock = SYSCLK/4
	AdcRegs.ADCCTL2.bit.CLKDIV2EN = 1;
	AdcRegs.ADCCTL2.bit.CLKDIV4EN = 1;

	// Overlap of sample is not allowed
	AdcRegs.ADCCTL2.bit.ADCNONOVERLAP = 1;

	// Conversion Configuration
	/* Set A0 and A1 as Current Sensor input */
	AdcRegs.ADCSOC0CTL.bit.CHSEL = 0x0;	//ADCINA1
	AdcRegs.ADCSOC0CTL.bit.ACQPS = 0x10;
	AdcRegs.ADCSOC0CTL.bit.TRIGSEL = 0x1; //Triggered by TimerISR (CPU Timer0n)

	AdcRegs.ADCSOC1CTL.bit.CHSEL = 0x1; //ADCINA0
	AdcRegs.ADCSOC1CTL.bit.ACQPS = 0x6;
	AdcRegs.ADCSOC1CTL.bit.TRIGSEL = 0x1;
	/* Set B2, B3, B4, B5, B6 as Temperature Sensor Input */
	AdcRegs.ADCSOC2CTL.bit.CHSEL = 0xA; //ADCINB2
	AdcRegs.ADCSOC2CTL.bit.ACQPS = 0x3F;
	AdcRegs.ADCSOC2CTL.bit.TRIGSEL = 0x1;

//	AdcRegs.ADCSOC3CTL.bit.CHSEL = 0xB; //ADCINB3
//	AdcRegs.ADCSOC3CTL.bit.ACQPS = 0x6;
//	AdcRegs.ADCSOC3CTL.bit.TRIGSEL = 0x1;

	AdcRegs.ADCSOC4CTL.bit.CHSEL = 0xC; //ADCINB4
	AdcRegs.ADCSOC4CTL.bit.ACQPS = 0x3F;
	AdcRegs.ADCSOC4CTL.bit.TRIGSEL = 0x1;

	AdcRegs.ADCSOC5CTL.bit.CHSEL = 0xD; //ADCINB5
	AdcRegs.ADCSOC5CTL.bit.ACQPS = 0x3F;
	AdcRegs.ADCSOC5CTL.bit.TRIGSEL = 0x1;

	AdcRegs.ADCSOC6CTL.bit.CHSEL = 0xE; //ADCINB6
	AdcRegs.ADCSOC6CTL.bit.ACQPS = 0x3F;
	AdcRegs.ADCSOC6CTL.bit.TRIGSEL = 0x1;

	// Enable ADC Interrupts
	AdcRegs.INTSEL1N2.bit.INT1SEL = 6;
	AdcRegs.INTSEL1N2.bit.INT1E = 1;
	AdcRegs.ADCCTL1.bit.INTPULSEPOS = 1;

	// Enable Power to the ADC
	AdcRegs.ADCCTL1.bit.ADCPWDN = 1;
	AdcRegs.ADCCTL1.bit.ADCBGPWD = 1;
	AdcRegs.ADCCTL1.bit.ADCREFPWD = 1;
	AdcRegs.ADCCTL1.bit.ADCENABLE = 1;

	// Wait for 1ms
	Delay();
}

void SpiInit()
{
	// Initialize SPI Clocking
	 SysCtrlRegs.PCLKCR0.bit.SPIAENCLK = 1;
		 asm(" NOP");     asm(" NOP");     // Wait 2 clock cycles

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
	 SpiaRegs.SPIBRR = 99;					//Step 2, Set Baud Rate = LSPCLK/90 = 1MHz
	 SpiaRegs.SPICCR.bit.SPILBK = 0;		//Enable Loopback Mode;
	 SpiaRegs.SPICTL.bit.MASTER_SLAVE = 1;	//Enabling Master Mode on microcontroller
	 SpiaRegs.SPICTL.bit.TALK = 1;
	 SpiaRegs.SPICCR.bit.SPICHAR = 7;		//Transmit 8 bits per clock cycle.
	 SpiaRegs.SPIFFTX.bit.SPIFFENA = 0;		//As Described on page 849 of Manual, in order to trigger SPIINT w/o FIFO, this bit needs to be set to 0.
	 SpiaRegs.SPICCR.bit.CLKPOLARITY = 1;	//Demanded by LTC6803-3 datasheet, page 17, under "Clock Phase And Polarity". Both Phase and Polarity need to be set to 1 in order to initiate communication.
	 SpiaRegs.SPICTL.bit.CLK_PHASE = 0;
	 SpiaRegs.SPICCR.bit.SPISWRESET = 1;  	//Step 3, Enable SPI
	 SpiaRegs.SPIPRI.bit.FREE = 1;

	//testSPI();
	/* Above is SPI Enabling Sequence:
	1. Clear the SPI SW RESET bit (SPICCR.7) to 0 to force the SPI to the reset state.
	2. Initialize the SPI configuration, format, baud rate, and pin functions as desired.
	3. Set the SPI SW RESET bit to 1 to release the SPI from the reset state.
	4. Write to SPIDAT or SPITXBUF (this initiates the communication process in the master).
	5. Read SPIRXBUF after the data transmission has completed (SPISTS.6 = 1) to determine what data was received.
	*/
}

/* Record the last samples of Temperature, Voltage and Current Data */
void DataRecord()
{
	float32 Threshold = 0.3;
	// Record Data
	if (shift > 99)
	{
		for (i = 1; i <= 100; i++)
		{
			i_Hall_1[i-1] = i_Hall_1[i];
			i_Hall_2[i-1] = i_Hall_2[i-1];
			Temp_1[i-1] = Temp_1[i];
			Temp_2[i-1] = Temp_2[i];
			Temp_3[i-1] = Temp_3[i];
			Temp_4[i-1] = Temp_4[i];
			//Temp_5[i-1] = Temp_5[i];
			V_Result_1[i-1] = V_Result_1[i];
			V_Result_2[i-1] = V_Result_2[i];
			V_Result_3[i-1] = V_Result_3[i];
			V_Result_4[i-1] = V_Result_4[i];
			V_Result_5[i-1] = V_Result_5[i];
			V_Result_6[i-1] = V_Result_6[i];
			V_Result_7[i-1] = V_Result_2[i];
			V_Result_8[i-1] = V_Result_8[i];
		}

		i_Hall_1[99] = i_Hall_11;
		i_Hall_2[99] = i_Hall_22;
		Temp_1[99] = Temp_Actual[0];
		Temp_2[99] = Temp_Actual[1];
		Temp_3[99] = Temp_Actual[2];
		Temp_4[99] = Temp_Actual[3];
		//Temp_5[99] = Temp_Actual[4];

		V_Result_1[99] = CellVoltages[0];
		V_Result_2[99] = CellVoltages[1];
		V_Result_3[99] = CellVoltages[2];
		V_Result_4[99] = CellVoltages[3];
		V_Result_5[99] = CellVoltages[4];
		V_Result_6[99] = CellVoltages[5];
		V_Result_7[99] = CellVoltages[6];
		V_Result_8[99] = CellVoltages[7];
	}

	if (shift < 99)
	{
		i_Hall_1[a] = i_Hall_11;
		i_Hall_2[a] = i_Hall_22;
		Temp_1[a] = Temp_Actual[0];
		Temp_2[a] = Temp_Actual[1];
		Temp_3[a] = Temp_Actual[2];
		Temp_4[a] = Temp_Actual[3];
		//Temp_5[a] = Temp_Actual[4];

		V_Result_1[a] = CellVoltages[0];
		V_Result_2[a] = CellVoltages[1];
		V_Result_3[a] = CellVoltages[2];
		V_Result_4[a] = CellVoltages[3];
		V_Result_5[a] = CellVoltages[4];
		V_Result_6[a] = CellVoltages[5];
		V_Result_7[a] = CellVoltages[6];
		V_Result_8[a] = CellVoltages[7];
	}
	a++;
	shift++;

	for (i = 0; i < sizeof(v_Arr) / sizeof(v_Arr[0]); i++) {
		v_Arr[i] = randRange(3.4, 4.3);//fills array with random values
	}
	sizeArr = sizeof(preBal_Arr) / 2;
	minVolt = getMin(preBal_Arr, sizeArr);	//store the minimum value
	for (k = 0; k < sizeof(v_Arr) / sizeof(v_Arr[0]); k++) {
		if (preBal_Arr[k] > minVolt + Threshold)
			preBal_Arr[k] = minVolt;
	}

	if(!data_init)
		data_init = true;
}


/* Read the reading from the ADC Module */
void AdcRead()
{
	int cntTemp = 0;
	// Hall Effect Sensor
	i_Hall_11 = (float32)(3.3/4096.0*(AdcResult.ADCRESULT0));
	i_11_Actual = (float32)((1000.00*i_Hall_11-1250.00)/15.00);
	i_Hall_22 = (float32)(3.3/4096.0*(AdcResult.ADCRESULT1));

	// Temperature Sensors
	Temp_11 = (float32)(3.3/4096.0*(AdcResult.ADCRESULT2));
	//Temp_22 = (float32)(3.3/4096.0*(AdcResult.ADCRESULT3));
	Temp_33 = (float32)(3.3/4096.0*(AdcResult.ADCRESULT4));
	Temp_44 = (float32)(3.3/4096.0*(AdcResult.ADCRESULT5));
	Temp_55 = (float32)(3.3/4096.0*(AdcResult.ADCRESULT6));
	//Temp_66 = (float32)(3.3/4096.0*(AdcResult.ADCRESULT7));

	Temp_Actual[0] = (1000.00*Temp_11-500.00)/10.00;
	//Temp_Actual[1] = (1000.00*Temp_22-500.00)/10.00;
	Temp_Actual[1] = (1000.00*Temp_33-500.00)/10.00;
	Temp_Actual[2] = (1000.00*Temp_44-500.00)/10.00;
	Temp_Actual[3] = (1000.00*Temp_55-500.00)/10.00;

	for (cntTemp = 0; cntTemp < 4; cntTemp++)
	{
		TempAverage = (ArraySumInt(Temp_Actual, 4)/4);
	}
}

/* This function inserts a 1 ms delay for use with ADC*/
void Delay(void)
{
   int32 cnt;
    /* The max count value is found by: (1 ms / (1/90 MHz))-1*/
   for(cnt = 0; cnt <= 89999; cnt++){ }
}

/***** Fred Please comment!!! *****/
void translateVoltage()
{
	int vtgcnt = 0;
    CellVolts[0] = (CVR[0] & 0xFF) | (CVR[1] & 0x0F) << 8;
    CellVolts[1] = (CVR[1] & 0xF0) >> 4 | (CVR[2] & 0xFF) << 4;
    CellVolts[2] = (CVR[3] & 0xFF) | (CVR[4] & 0x0F) << 8;
    CellVolts[3] = (CVR[4] & 0xF0) >> 4 | (CVR[5] & 0xFF) << 4;
    CellVolts[4] = (CVR[6] & 0xFF) | (CVR[7] & 0x0F) << 8;
    CellVolts[5] = (CVR[7] & 0xF0) >> 4 | (CVR[8] & 0xFF) << 4;
    CellVolts[6] = (CVR[9] & 0xFF) | (CVR[10] & 0x0F) << 8;
    CellVolts[7] = (CVR[10] & 0xF0) >> 4 | (CVR[11] & 0xFF) << 4;
    CellVolts[8] = (CVR[12] & 0xFF) | (CVR[13] & 0x0F) << 8;
    //CellVolts[9] = (CVR[13] & 0xF0) >> 4 | (CVR[14] & 0xFF) << 4;
    for (vtgcnt = 0; vtgcnt < 9; vtgcnt++)
    {
    	CellVoltages[vtgcnt] = (CellVolts[vtgcnt]-512)*1.500/1000.000;
    }
    vtgcnt = 0;
    for (vtgcnt = 0; vtgcnt < 9; vtgcnt++)
    {
    	vAverage = vAverage + CellVoltages[vtgcnt]/9;
    }
}

/***** Fred Please comment!!! *****/
void writeConfig()
{
	OVvalue = (int)OVthresh/24+31;
	UVvalue = (int)UVthresh/24+32;
	CFGR4 = (Uint16)UVvalue;
	CFGR5 = (Uint16)OVvalue;
	CFGR_PEC = calcPEC(CFGR0);
	CFGR_PEC = calcPECMult(CFGR1,CFGR_PEC);
	CFGR_PEC = calcPECMult(CFGR2,CFGR_PEC);
	CFGR_PEC = calcPECMult(CFGR3,CFGR_PEC);
	CFGR_PEC = calcPECMult(CFGR4,CFGR_PEC);
	CFGR_PEC = calcPECMult(CFGR5,CFGR_PEC);
	SpiSend(WRCFG);
	SpiSend(calcPEC(WRCFG));
	SpiSend(CFGR0); //Config register 0 (GPIO settings, LVL poll setting, 10 cell setting, Comparator duty cycle setting)
	SpiSend(CFGR1);
	SpiSend(CFGR2);
	SpiSend(CFGR3);
	SpiSend(CFGR4);
	SpiSend(CFGR5);
    SpiSend(CFGR_PEC);
}

/***** Fred Please comment!!! *****/
void readConfig()
{
	while(dummy < 100)
	{
		dummy++;
	}dummy = 0;
	SpiSend(RDCFG);
	SpiSend(RDCFG_PEC);
	ListenConfig = receiveSPI();

	for (testPurposes=0; testPurposes<7; testPurposes++)
	{
		ConfigBytes[testPurposes] = receiveSPI();
	}
}

/***** Fred Please comment!!! *****/
void startCellRead()
{
	while(dummy < 100)
	{
		dummy++;
	}dummy = 0;
	SpiSend(STCVAD);
	SpiSend(calcPEC(STCVAD));
}

/***** Fred Please comment!!! *****/
void waitforCells()
{
	int ready = 0;
	while(!ready) {
		SpiSend(PLADC);
		SpiSend(calcPEC(PLADC));
		receiveSPI();
		int result = receiveSPI();
		if (result!=0) {
			ready = 1;
		}
	}
}

/***** Fred Please comment!!! *****/
void readVoltages() {
	while(dummy < 100)
	{
		dummy++;
	}dummy = 0;
	SpiSend(RDFLG);
	SpiSend(calcPEC(RDFLG));
	FLG[0]=receiveSPI();
	FLG[1]=receiveSPI();
	FLG[2]=receiveSPI();
	if (FLG[0] == 1 || FLG[1] == 1 || FLG[2] == 1)
	{
		//send error to CAN
		GpioDataRegs.GPACLEAR.bit.GPIO9 = 1;//packCutoffRelay = 0;
		GpioDataRegs.GPACLEAR.bit.GPIO28 = 1;
		VoltageBad = 1;
		//break;
	}
	//VoltageBad = 0;
	while(dummy < 100)
	{
		dummy++;
	}dummy = 0;
	SpiSend(RDCV);
	SpiSend(calcPEC(RDCV));
	receiveSPI();
	for (i=0;i<15;i++)
	{
		CVR[i]=receiveSPI();
	}
	//lightUpLED(1000);
	translateVoltage();
}

/* State of Charge Curve Fitting Algorithm */
float checkSOC()
{
	Vavg = ArraySumFloat(CellVoltages, 8)/8;
	x = Vavg + 0.23*(currentact-0.650)/capacity; // Voltage is adjusted by the current.
	if (x >= 4.2)
	{// When voltage is at 4.2V or more, battery is at full capacity regardless of the current.
		dischar = 0.00;
	}
	else {
		dischar = p5 + p1*(x*x*x*x) - p2*(x*x*x) + p3*(x*x) - p4*x; // Finds the capacity of the batteries that has been used up.
	}
	return socPct = 100*(capacity - dischar)/capacity;
}

void lightUpLED(Uint32 Interval)
{
	int lightUpLED = 0;
	int Pause = 0;
	lightUpLED++;

	if (lightUpLED % Interval == 0)
	{
		GpioDataRegs.GPACLEAR.bit.GPIO20 = 1;
		while(Pause < 100){
			Pause++;
		}Pause = 0;
		GpioDataRegs.GPASET.bit.GPIO20 = 1;
	}
	lightUpLED = 0;
}

/***** Fred Please comment!!! *****/
float32 randRange(double min, double max) {
	return rand() * (max - min) / RAND_MAX + min;
}

/* Basic Functions */
float32 getMin(float32 arr[], int arr_size) {
	int16 c;
	float32 minimum = 0;
	for (c = 0; c < arr_size; ++c) {
		if (c == 0)
			minimum = arr[c];
		else if (arr[c] < minimum)
			minimum = arr[c];
	}
	return minimum;
}
float32 ArraySumInt(float a[], int num_elements)
{
   int16 i;
   float32 sum = 0.00;
   for (i=0; i<num_elements; i++)
   {
	   sum = sum + a[i];
   }
   return(sum);
}
float32 ArraySumFloat(float array[], int num_elements)
{
   int16 i;
   float32 sum = 0.00;
   for (i=0; i<num_elements; i++)
   {
	   sum = sum + array[i];
   }
   return(sum);
}
