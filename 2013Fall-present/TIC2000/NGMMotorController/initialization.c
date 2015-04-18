/*
 * initialization.c
 *
 *  Created on: Jun 14, 2014
 *      Author: Alex
 */

#include "initialization.h"

void sciGPIOSetup(){
	EALLOW;
	   // Enable SCI-A on GPIO28 - GPIO29
	   GpioCtrlRegs.GPAPUD.bit.GPIO28 = 0;   // Enable pullup on GPIO28
	   GpioCtrlRegs.GPAQSEL2.bit.GPIO28 = 3; // Asynch input
	   GpioCtrlRegs.GPAMUX2.bit.GPIO28 = 1;  // GPIO28 = SCIRXDA
	   GpioCtrlRegs.GPAPUD.bit.GPIO29 = 0;   // Enable pullup on GPIO29
	   GpioCtrlRegs.GPAMUX2.bit.GPIO29 = 1;  // GPIO29 = SCITXDA
	EDIS;
}

void buttonsGPIOSetup(){
	EALLOW;
	GpioCtrlRegs.GPAPUD.bit.GPIO21 = 0;   // Enable pullup on GPIO21
	GpioDataRegs.GPASET.bit.GPIO21 = 1;   // Load output latch
	GpioCtrlRegs.GPAMUX2.bit.GPIO21 = 0;  // GPIO21 = GPIO21
	GpioCtrlRegs.GPADIR.bit.GPIO21 = 0;   // GPIO21 = input

	GpioCtrlRegs.GPAPUD.bit.GPIO20 = 0;   // Enable pullup on GPIO22
	GpioDataRegs.GPASET.bit.GPIO20 = 1;   // Load output latch
	GpioCtrlRegs.GPAMUX2.bit.GPIO20 = 0;  // GPIO21 = GPIO22
	GpioCtrlRegs.GPADIR.bit.GPIO20 = 0;   // GPIO21 = input
	EDIS;
}

void encoderGPIOSetup(){
	EALLOW;
	GpioCtrlRegs.GPAPUD.bit.GPIO0 = 0;   // Enable pullup on GPIO0
	GpioCtrlRegs.GPAPUD.bit.GPIO1 = 0;   // Enable pullup on GPIO1
	GpioCtrlRegs.GPAPUD.bit.GPIO2 = 0;   // Enable pullup on GPIO2
	GpioCtrlRegs.GPAPUD.bit.GPIO3 = 0;   // Enable pullup on GPIO3
	GpioCtrlRegs.GPAPUD.bit.GPIO4 = 0;   // Enable pullup on GPIO4
	GpioCtrlRegs.GPAPUD.bit.GPIO5 = 0;   // Enable pullup on GPIO5
	GpioDataRegs.GPASET.bit.GPIO0 = 1;   // Load output latch
	GpioDataRegs.GPASET.bit.GPIO1 = 1;   // Load output latch
	GpioDataRegs.GPASET.bit.GPIO2 = 1;   // Load output latch
	GpioDataRegs.GPASET.bit.GPIO3 = 1;   // Load output latch
	GpioDataRegs.GPASET.bit.GPIO4 = 1;   // Load output latch
	GpioDataRegs.GPASET.bit.GPIO5 = 1;   // Load output latch
	GpioCtrlRegs.GPAMUX1.bit.GPIO0 = 0;  // GPIO0 = GPIO0 //
	GpioCtrlRegs.GPAMUX1.bit.GPIO1 = 0;  // GPIO1 = GPIO1 //
	GpioCtrlRegs.GPAMUX1.bit.GPIO2 = 0;  // GPIO2 = GPIO2 //
	GpioCtrlRegs.GPAMUX1.bit.GPIO3 = 0;  // GPIO3 = GPIO3 //
	GpioCtrlRegs.GPAMUX1.bit.GPIO4 = 0;  // GPIO4 = GPIO4 //
	GpioCtrlRegs.GPAMUX1.bit.GPIO5 = 0;  // GPIO5 = GPIO5 //
	GpioCtrlRegs.GPADIR.bit.GPIO0 = 0;   // GPIO0 = input
	GpioCtrlRegs.GPADIR.bit.GPIO1 = 0;   // GPIO1 = input
	GpioCtrlRegs.GPADIR.bit.GPIO2 = 0;   // GPIO2 = input
	GpioCtrlRegs.GPADIR.bit.GPIO3 = 0;   // GPIO3 = input
	GpioCtrlRegs.GPADIR.bit.GPIO4 = 0;   // GPIO4 = input
	GpioCtrlRegs.GPADIR.bit.GPIO5 = 0;   // GPIO5 = input
	GpioCtrlRegs.GPAPUD.bit.GPIO6 = 0;   // Enable pullup on GPIO6
	GpioDataRegs.GPASET.bit.GPIO6 = 1;   // Load output latch
	GpioCtrlRegs.GPAMUX1.bit.GPIO6 = 0;  // GPIO6 = GPIO6
	GpioCtrlRegs.GPADIR.bit.GPIO6 = 0;   // GPIO6 = input
	GpioCtrlRegs.GPAPUD.bit.GPIO7 = 0;   // Enable pullup on GPIO7
	GpioDataRegs.GPASET.bit.GPIO7 = 1;   // Load output latch
	GpioCtrlRegs.GPAMUX1.bit.GPIO7 = 0;  // GPIO7 = GPIO7
	GpioCtrlRegs.GPADIR.bit.GPIO7 = 0;   // GPIO7 = input


	GpioCtrlRegs.GPAPUD.bit.GPIO8 = 0;   // Enable pullup on GPIO0
	GpioCtrlRegs.GPAPUD.bit.GPIO9 = 0;   // Enable pullup on GPIO1
	GpioCtrlRegs.GPAPUD.bit.GPIO10 = 0;   // Enable pullup on GPIO2
	GpioCtrlRegs.GPAPUD.bit.GPIO11 = 0;   // Enable pullup on GPIO3
	GpioCtrlRegs.GPAPUD.bit.GPIO12 = 0;   // Enable pullup on GPIO4
	GpioCtrlRegs.GPAPUD.bit.GPIO13 = 0;   // Enable pullup on GPIO5
	GpioDataRegs.GPASET.bit.GPIO8 = 1;   // Load output latch
	GpioDataRegs.GPASET.bit.GPIO9 = 1;   // Load output latch
	GpioDataRegs.GPASET.bit.GPIO10 = 1;   // Load output latch
	GpioDataRegs.GPASET.bit.GPIO11 = 1;   // Load output latch
	GpioDataRegs.GPASET.bit.GPIO12 = 1;   // Load output latch
	GpioDataRegs.GPASET.bit.GPIO13 = 1;   // Load output latch
	GpioCtrlRegs.GPAMUX1.bit.GPIO8 = 0;  // GPIO0 = GPIO0 //
	GpioCtrlRegs.GPAMUX1.bit.GPIO9 = 0;  // GPIO1 = GPIO1 //
	GpioCtrlRegs.GPAMUX1.bit.GPIO10 = 0;  // GPIO2 = GPIO2 //
	GpioCtrlRegs.GPAMUX1.bit.GPIO11 = 0;  // GPIO3 = GPIO3 //
	GpioCtrlRegs.GPAMUX1.bit.GPIO12 = 0;  // GPIO4 = GPIO4 //
	GpioCtrlRegs.GPAMUX1.bit.GPIO13 = 0;  // GPIO5 = GPIO5 //
	GpioCtrlRegs.GPADIR.bit.GPIO8 = 0;   // GPIO0 = input
	GpioCtrlRegs.GPADIR.bit.GPIO9 = 0;   // GPIO1 = input
	GpioCtrlRegs.GPADIR.bit.GPIO10 = 0;   // GPIO2 = input
	GpioCtrlRegs.GPADIR.bit.GPIO11 = 0;   // GPIO3 = input
	GpioCtrlRegs.GPADIR.bit.GPIO12 = 0;   // GPIO4 = input
	GpioCtrlRegs.GPADIR.bit.GPIO13 = 0;   // GPIO5 = input

	// Enable an GPIO input on GPIO6, set it high
	GpioCtrlRegs.GPAPUD.bit.GPIO14 = 0;   // Enable pullup on GPIO6
	GpioDataRegs.GPASET.bit.GPIO14 = 1;   // Load output latch
	GpioCtrlRegs.GPAMUX1.bit.GPIO14 = 0;  // GPIO6 = GPIO6
	GpioCtrlRegs.GPADIR.bit.GPIO14 = 0;   // GPIO6 = input

	// Enable eCAP2 on GPIO7
	GpioCtrlRegs.GPAPUD.bit.GPIO15 = 0;   // Enable pullup on GPIO7
	GpioDataRegs.GPASET.bit.GPIO15 = 1;   // Load output latch
	GpioCtrlRegs.GPAMUX1.bit.GPIO15 = 0;  // GPIO7 = GPIO7
	GpioCtrlRegs.GPADIR.bit.GPIO15 = 0;   // GPIO7 = input
	EDIS;
}


/**
 * \brief Initializes the F28069 C2000 Microcontroller GPIO serial communications for motor, as well as CAN.
 * \return  1: Initialization went OK.
 * \return -1: Initialization failed.
 */
signed char initializeuCANndSerialComs() {
	stdiologstr("Initializing uC");
	InitSysCtrl();  // Initialize System Control registers, PLL, WatchDog, Clocks to default state

	DINT;           // Disable interrupts
	InitPieCtrl();  // Initialize and clear PIE control registers. Clear all interrupt flags.
	IER = 0x0000;   // Disable CPU interrupts and clear all CPU interrupt flags:
	IFR = 0x0000;
	InitPieVectTable(); //Initialize the PIE vector table with pointers to the shell Interrupt Service Routines (ISR).

	// Map interrupt to ISR function:
	EALLOW;  // This is needed to write to EALLOW protected registers
	PieVectTable.TINT0 = &cpu_timer0_isr_torque_control_loop_iteration;
	EDIS;    // This is needed to disable write to EALLOW protected registers

	// Initialize clock timer peripheral
	InitCpuTimers();
	ConfigCpuTimer(&CpuTimer0, 90, 250000); // Configure CPU-Timer 0 to interrupt every 250 milliseconds:

	// 90MHz CPU Freq, 50 millisecond Period (in uSeconds)
	CpuTimer0Regs.TCR.all = 0x4001; // Use write-only instruction to set TSS bit = 0
	IER |= M_INT1;  // Enable CPU INT1 which is connected to CPU-Timer 0:
	PieCtrlRegs.PIEIER1.bit.INTx7 = 0; // Disable TINT0 in the PIE: Group 1 interrupt 7, until we are ready to start the control loop.

	// Enable global Interrupts and higher priority real-time debug events:
	EINT;   // Enable Global interrupt INTM
	ERTM;   // Enable Global realtime interrupt DBGM
	InitGpio(); //This function is found in the F2806x_Gpio.c file and illustrates how to set the GPIO to its default state.
	InitSciGpio(); // Select GPIO for the device or for the specific application.
	encoderGPIOSetup();
	buttonsGPIOSetup();
	sciGPIOSetup();

	// CAN RS does not have to be grounded for the motor controller board, since I cut that trace.

	//initialize_CAN(); // Initialize CAN

	// Initialize Serial (SCI) communications
	scia_fifo_init();	   // Initialize the SCI FIFO
	scia_init();           // Initalize SCI

	stdiologstr("Done");

	return 1;
}


