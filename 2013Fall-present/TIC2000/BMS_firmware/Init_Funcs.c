#include "BMS.h"

/*
 * This file contains the functions to initialize the microcontroller.
 */

//Initialize system clock frequency to 90 MHz using PLL
//Set low-speed peripheral clock = 90 MHz for SPI module
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
		while(SysCtrlRegs.PLLSTS.bit.PLLLOCKS != 1);

		// Disable oscillator fail detect logic
		SysCtrlRegs.PLLSTS.bit.MCLKOFF = 0;

		// Set the value of DIVSEL that gives 90 MHz
		SysCtrlRegs.PLLSTS.bit.DIVSEL = 3;
	}

	SysCtrlRegs.LOSPCP.bit.LSPCLK = 2;  //Sets Low-Speed Peripheral Clock = 90MHz/4 for SPI Module.
}

//Initializes system interrupts
//Timer0
void InterruptInit(void){
	//Uint16 IERShadow;

	// Step 3. Clear all interrupts and initialize PIE vector table:
	// Disable CPU interrupts
	DINT;

	// Disable the PIE Vector Table
	PieCtrlRegs.PIECTRL.bit.ENPIE = 0;

	// Disable CPU interrupts and clear all CPU interrupt flags
	// Save interrupts that were previously enabled
	//IERShadow = IER;
	IER = 0x0000;
	IFR = 0x0000;

	// Enable the PIE Vector Table
	PieCtrlRegs.PIECTRL.bit.ENPIE = 1;

	//Direct ADC interrupts to the proper isr
	PieVectTable.ADCINT1 = &getCurrent;

	//ADC interrupts are part of IER 1
	IER = IER | M_INT1;

	//Enable ADC1 interrupt in PIE
	PieCtrlRegs.PIEIER1.bit.INTx1 = 1;

	// Enable global Interrupts and higher priority real-time debug events:
	EINT;   // Enable Global interrupt INTM
	ERTM;   // Enable Global realtime interrupt DBGM
}

//Initialize timer
//Frequency is based on ftmr variable
void TmrInit(void)
{
	Uint32 fsys = 90000000; //CPU System Frequency is 90MHz
	Uint32 ftmr = 1000; //Timer reset Frequency is 1000Hz

	//Set the appropriate 32 bit main counter
	CpuTimer0Regs.PRD.all = (fsys/ftmr)-1;

	//TODO research timer
	CpuTimer0Regs.TCR.bit.TSS = 1;
	CpuTimer0Regs.TCR.bit.TRB = 1;
	CpuTimer0Regs.TCR.bit.TIE = 1;

	CpuTimer0Regs.TCR.bit.TSS = 0; //Start CPU Timer
}

//Configure GPIOs
//TODO investigate GPIOs
void GpioInit(){
	GpioCtrlRegs.GPAMUX2.bit.GPIO20 = 0; // Configure pin as GPIO
	GpioCtrlRegs.GPAPUD.bit.GPIO20 = 0; // Enable internal pullup on the specified pin
	GpioCtrlRegs.GPADIR.bit.GPIO20 = 1; // Configure as Output
	// Pack Cutoff GPIO2
	GpioCtrlRegs.GPAMUX1.bit.GPIO2 = 0;
	GpioCtrlRegs.GPAPUD.bit.GPIO2 = 1; // Disable internal pullup on the specified pin
	GpioCtrlRegs.GPADIR.bit.GPIO2 = 1;
	// Array Relay GPIO1
	GpioCtrlRegs.GPAMUX1.bit.GPIO1 = 0;
	GpioCtrlRegs.GPAPUD.bit.GPIO1 = 1;
	GpioCtrlRegs.GPADIR.bit.GPIO1 = 1;
	// LED 1
	GpioCtrlRegs.GPAMUX2.bit.GPIO20 = 0;
	GpioCtrlRegs.GPAPUD.bit.GPIO20 = 1;
	GpioCtrlRegs.GPADIR.bit.GPIO20 = 1;
}

//Initialize SPI module to use GPIOs 16,17,18,19
//GPIO 16 = SIMO
//GPIO 17 = SOMI
//GPIO 18 = CLK
//GPIO 19 = STE
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

//Initializes ADC
//Analog in 2 is used for hall effect sensor
void AdcInit(void)
{
	int32 delay = 0; //int32 so that we can count to 90000
	int ms = 5;

	// Configure AIO2 for A2 (analog input) operation
	GpioCtrlRegs.AIOMUX1.bit.AIO2 = 2;

	// Initialize ADC Clocking
	SysCtrlRegs.PCLKCR0.bit.ADCENCLK = 1; //enables ADC clock

	// Wait one millisecond
	for(delay = 0; delay <= 89999; delay++);
	//asm(" NOP");     asm(" NOP");     // Wait 2 clock cycles

	// Enable Power to the ADC
	AdcRegs.ADCCTL1.bit.ADCBGPWD  = 1;      // Power ADC BG
	AdcRegs.ADCCTL1.bit.ADCREFPWD = 1;      // Power reference
	AdcRegs.ADCCTL1.bit.ADCPWDN   = 1;      // Power ADC
	AdcRegs.ADCCTL1.bit.ADCENABLE = 1;      // Enable ADC
	AdcRegs.ADCCTL1.bit.ADCREFSEL = 0;      // Select interal BG

	// Wait one millisecond
	for(delay = 0; delay <= 89999; delay++);

	// Scale the ADC Clock = SYSCLK/2
	AdcRegs.ADCCTL2.bit.CLKDIV2EN = 1;
	//AdcRegs.ADCCTL2.bit.CLKDIV4EN = 1;

	// Wait one millisecond
	for(delay = 0; delay <= 89999; delay++);

	//AdcRegs.ADCOFFTRIM.bit.OFFTRIM = -150;

	// Overlap of sample is not allowed
	AdcRegs.ADCCTL2.bit.ADCNONOVERLAP = 1;

	// Conversion Configuration
	/* Set A0, A1, A2 as Current Sensor input */
	/*AdcRegs.ADCSOC0CTL.bit.CHSEL = 0x0;	//ADCINA0
	AdcRegs.ADCSOC0CTL.bit.ACQPS = 0x10;
	AdcRegs.ADCSOC0CTL.bit.TRIGSEL = 0x1; //Triggered by timer 0 interrupt (CPU Timer0n)

	AdcRegs.ADCSOC1CTL.bit.CHSEL = 0x1; //ADCINA1
	AdcRegs.ADCSOC1CTL.bit.ACQPS = 0x6;
	AdcRegs.ADCSOC1CTL.bit.TRIGSEL = 0x1;*/

	AdcRegs.ADCSOC1CTL.bit.CHSEL = 0x2; //ADCINA2
	AdcRegs.ADCSOC1CTL.bit.ACQPS = 0x6; //Sample window is 23+1 cycles long
	AdcRegs.ADCSOC1CTL.bit.TRIGSEL = 0x1; //Triggered by timer0

	/* Set B2, B3, B4, B5, B6 as Temperature Sensor Input */
	/*AdcRegs.ADCSOC2CTL.bit.CHSEL = 0xA; //ADCINB2
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
	AdcRegs.ADCSOC6CTL.bit.TRIGSEL = 0x1;*/

	// Enable ADC Interrupts
	AdcRegs.INTSEL1N2.bit.INT1SEL = 1; //Setup EOC1 to trigger ADCINT1 to fire
	AdcRegs.INTSEL1N2.bit.INT1E = 1;
	AdcRegs.ADCCTL1.bit.INTPULSEPOS = 1; //ADCINT1 trips after AdcResults latch
	AdcRegs.INTSEL1N2.bit.INT1CONT  = 0;	//Disable ADCINT1 Continuous mode



	// Wait for 5ms
	//The max count value is found by: (1 ms / (1/90 MHz))-1
	for(ms = 0; ms < 5; ms++){
		for(delay = 0; delay <= 89999; delay++){

		}
	}
}
