#include "F2806x_Device.h"
#include "DSP28x_Project.h"     //define default things
#include "WiFi.h"
#include "CAN.h"
#include "WiFIMU_CAN.h"
#include "28069Common.h"
// Prototype statements for functions found within this file.
interrupt void FourHertzInterrupt(void);
interrupt void TwoHertzInterrupt(void);
interrupt void OneHertsInterrupt(void);

void main(void) {

	GpioCtrlRegs.GPADIR.bit.GPIO0 = 1;	  //<--makes gpio0 an output

	deviceInit();
	InitSysCtrl(); //PLL, WatchDog, enable Peripheral Clocks. This function is found in the F2806x_SysCtrl.c file.
	InitGpio(); //This function is found in the F2806x_Gpio.c file and illustrates how to set the GPIO to its default state.
	InitSciaGpio(); //Init the pins for the SCI-A port. This function is found in the F2806x_Sci.c file.
	scia_fifo_init();
	scia_init();
	//GpioDataRegs.GPADAT.bit.GPIO0 = 1;//make gpio0 and output

	//Note: below code from  3326.Example_2833xCpuTimer.c
	//see http://e2e.ti.com/support/microcontrollers/c2000/f/171/t/265605.aspx

	// Step 3. Clear all interrupts and initialize PIE vector table:
	// Disable CPU interrupts
	DINT;

	// Initialize the PIE control registers to their default state.
	// The default state is all PIE interrupts disabled and flags
	// are cleared.
	// This function is found in the DSP2833x_PieCtrl.c file.
	InitPieCtrl();

	// Disable CPU interrupts and clear all CPU interrupt flags:
	IER = 0x0000;
	IFR = 0x0000;

	// Initialize the PIE vector table with pointers to the shell Interrupt
	// Service Routines (ISR).
	// This will populate the entire table, even if the interrupt
	// is not used in this example.  This is useful for debug purposes.
	// The shell ISR routines are found in DSP2833x_DefaultIsr.c.
	// This function is found in DSP2833x_PieVect.c.
	InitPieVectTable();

	// Interrupts that are used in this example are re-mapped to
	// ISR functions found within this file.
	EALLOW;  // This is needed to write to EALLOW protected registers
	PieVectTable.TINT0 = &FourHertzInterrupt;
	PieVectTable.TINT1 = &TwoHertzInterrupt;
	PieVectTable.TINT2 = &OneHertsInterrupt;
	EDIS;    // This is needed to disable write to EALLOW protected registers

	// Step 4. Initialize the Device Peripheral. This function can be
	//         found in DSP2833x_CpuTimers.c
	InitCpuTimers();   // For this example, only initialize the Cpu Timers

	// Configure CPU-Timer 0, 1, and 2 to interrupt every second:
	// 100MHz CPU Freq, different periods (in uSeconds)

	ConfigCpuTimer(&CpuTimer0, 100, 2500000);//o.25 second period
	ConfigCpuTimer(&CpuTimer1, 100, 500000);//0.5 second period
	ConfigCpuTimer(&CpuTimer2, 100, 1000000);//1 second period
	// To ensure precise timing, use write-only instructions to write to the entire register. Therefore, if any
	// of the configuration bits are changed in ConfigCpuTimer and InitCpuTimers (in DSP2833x_CpuTimers.h), the
	// below settings must also be updated.

	CpuTimer0Regs.TCR.all = 0x4001; // Use write-only instruction to set TSS bit = 0
	CpuTimer1Regs.TCR.all = 0x4001; // Use write-only instruction to set TSS bit = 0
	CpuTimer2Regs.TCR.all = 0x4001; // Use write-only instruction to set TSS bit = 0

	// Step 5. User specific code, enable interrupts:


	// Enable CPU int1 which is connected to CPU-Timer 0, CPU int13
	// which is connected to CPU-Timer 1, and CPU int 14, which is connected
	// to CPU-Timer 2:
	IER |= M_INT1;
	IER |= M_INT13;
	IER |= M_INT14;

	// Enable TINT0 in the PIE: Group 1 interrupt 7
	PieCtrlRegs.PIEIER1.bit.INTx7 = 1;

	// Enable global Interrupts and higher priority real-time debug events:
	EINT;   // Enable Global interrupt INTM
	ERTM;   // Enable Global realtime interrupt DBGM

	WiFIMU_CAN_init();
	// Step 6. IDLE loop. Just sit and loop forever (optional):
	while(1);
}

interrupt void FourHertzInterrupt(void){
	CpuTimer0.InterruptCount++;

	//TODO:
	// Acknowledge this interrupt to receive more interrupts from group 1
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}

interrupt void TwoHertzInterrupt(void){
	CpuTimer1.InterruptCount++;
	// The CPU acknowledges the interrupt.
	EDIS;
	requestBMSData();
}

interrupt void OneHertsInterrupt(void){
	EALLOW;
	CpuTimer2.InterruptCount++;
	// The CPU acknowledges the interrupt.
	EDIS;
}
