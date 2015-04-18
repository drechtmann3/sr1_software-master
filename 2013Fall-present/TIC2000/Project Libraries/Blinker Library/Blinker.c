/*
 * Set up blinkers to flash based on external interrupt
 */
#include "DSP28x_Project.h"
#include "Blinker.h"


void InitBlinker(void){
	Uint16 IERShadow;

	//Save and disable CPU interrupts
	DINT;
	IERShadow = IER;
	IER = 0x0000;
	IFR = 0x0000;

	//Redirect timer 0 interrupts to cpu_timer0_isr
	//Redirect external interrupt 1 to xint1_isr
	EALLOW;
	PieVectTable.TINT0 = &cpu_timer0_isr;
	PieVectTable.XINT1 = &xint1_isr;
	EDIS;

	//Initialize CPU timers to a known state
	InitCpuTimers();

	//Configure CPU timer 0 to interrupt every 500 ms
	//80 = 80 MHz CPU freq
	ConfigCpuTimer(&CpuTimer0, 80, 500000);

	//To ensure precise timing, use write-only instructions to write to the entire register. If any configuration bits
	//were changed, the below settings must also be updated
	//CpuTimer0Regs.TCR.all = 0x4001; //Set TSS bit = 0
	//Or screw precise timing
	//CpuTimer0Regs.TCR.bit.TSS = 0;

	//Configure GPIOx as a GPIO output pin
	EALLOW;
	GpioCtrlRegs.GPAMUX2.bit.GPIO16 = 0;
	GpioCtrlRegs.GPADIR.bit.GPIO16 = 1;
	GpioCtrlRegs.GPBMUX1.bit.GPIO34 = 0;
	GpioCtrlRegs.GPBDIR.bit.GPIO34 = 1;

	//Configure GPIOy as GPIO input pin with pullup
	GpioCtrlRegs.GPAMUX1.bit.GPIO0 = 0;         // GPIO
	GpioCtrlRegs.GPADIR.bit.GPIO0 = 0;          // input
	GpioCtrlRegs.GPAPUD.bit.GPIO0 = 0;			// enable pullup
	GpioCtrlRegs.GPAQSEL1.bit.GPIO0 = 0;        // XINT1 Synch to SYSCLKOUT only

	// GPIO0 is XINT1
	GpioIntRegs.GPIOXINT1SEL.bit.GPIOSEL = 0;   // XINT1 is GPIO0
	EDIS;

	// Configure XINT1
	XIntruptRegs.XINT1CR.bit.POLARITY = 3;      // Both falling and rising edge interrupts

	// Enable XINT1
	XIntruptRegs.XINT1CR.bit.ENABLE = 1;

	//Enable CPU INT1 which is connected to CPU timer 0 and XINT1
	IER = IERShadow | M_INT1;

	//Enable TINT0 in the PIE: Group 1 interrupt 7
	//Enable XINT1 in the PIE: Group 1 interrupt 4
	PieCtrlRegs.PIEIER1.bit.INTx7 = 1;
	PieCtrlRegs.PIEIER1.bit.INTx4 = 1;

	//Enable global interrupts and higher priority real-time debug events
	EINT;
	ERTM;

	//Initialize starting state of blinkers
	//GPIO0 high - timer 0 off
	//GPIO0 low - timer 0 on
	if(GpioDataRegs.GPADAT.bit.GPIO0){
		CpuTimer0Regs.TCR.bit.TSS = 1; //Stop timer
		GpioDataRegs.GPACLEAR.bit.GPIO16 = 1; //Turn off LED
		GpioDataRegs.GPBCLEAR.bit.GPIO34 = 1; //Turn off LED
	}
	else{
		CpuTimer0Regs.TCR.bit.TSS = 0; //Start timer
	}
}

__interrupt void cpu_timer0_isr(void){
	//Toggle GPIOx
	GpioDataRegs.GPATOGGLE.bit.GPIO16 = 1;
	GpioDataRegs.GPBTOGGLE.bit.GPIO34 = 1;

	//Acknowledge interrupt
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}

__interrupt void xint1_isr(void)
{
	//GPIO0 high - timer 0 off
	//GPIO0 low - timer 0 on
	if(GpioDataRegs.GPADAT.bit.GPIO0){
		CpuTimer0Regs.TCR.bit.TSS = 1; //Stop timer
		GpioDataRegs.GPACLEAR.bit.GPIO16 = 1; //Turn off LED
		GpioDataRegs.GPBCLEAR.bit.GPIO34 = 1; //Turn off LED
	}
	else{
		CpuTimer0Regs.TCR.bit.TSS = 0; //Start timer
	}


	// Acknowledge this interrupt to get more from group 1
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}


