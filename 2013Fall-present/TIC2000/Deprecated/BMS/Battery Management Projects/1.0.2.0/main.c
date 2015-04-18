/*
 * Georgia Tech Solar Racing
 * Battery Management System Source Code
 * Microcontroller: Texas Instruments Piccolo Series - TMS320F28069
 * Originator: Fred Chen (tm602502@gmail.com)
 * Contributor: Leonardo Bernal (leo.esteban.bernal@gmail.com)
 * Date: 06/08/2014
 * Version: 1.0.2.0
 */

#include "F2806x_Device.h"
#include <math.h>
#include "main.h"
#include "F2806x_PieVect.h"
#include <stdlib.h>

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



// Battery Stack Monitor Variables
int32 OVvalue = 0;
int32 OVthresh = 4200;
int32 UVvalue = 0;
int32 UVthresh = 3200;

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
int32 numCells = 10;
int32 numCVR = 15;
Uint32 dummy = 0;
int32 ListenConfig = 0;
int32 VoltageBad = 0;


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
	// SPI Module Initialization
	SpiInit();

	// Start CPU Timer
	CpuTimer0Regs.TCR.bit.TSS = 0;

	// SPI Functions Initialization
	writeConfig();
	readConfig();

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
		waitforCells();
		fetchVoltage();
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
void fetchVoltage();

