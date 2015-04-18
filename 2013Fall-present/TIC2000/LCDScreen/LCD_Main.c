/**
 * \brief This is the code for the LDC screen in the driver's cockpit for SJ-1.
 *
 * The screen this is designed to work with is 128x160 pixels.
 */

#include "LDC_Main.h"

void main(void)
{
	// When clock=70MHz, CAN bit rate = 1758000
	initializeuCANndSerialComs(); // Initialize serial coms, CAN. Start receiving CAN messages.

	DELAY_US(1.2e6); // Wait 1s for splashscreen to exit, only in production code.

	LCD_resetXY();
	LCD_clearScreen();

	DELAY_US(0.1e6);

	refreshAllElementsToDefaultState(); // Draw UI in default state.

	//int i = 0;

	while(1) {
		// Refresh all UI elements with minimal pixel updates.
		draw_blinkers();
		if (ECanaRegs.CANGIF0.bit.BOIF0) CANErrorActive = 1; // Trigger CAN error if bus-off error is found.
		draw_CAN_error();
		draw_motor_error();
		draw_SOC(0);
		draw_throttle_regen(0);
		draw_signal_strength(0);
		draw_bat_temp(0);
		draw_motor_temp(0);
		draw_speed_mph(0);
		draw_mppt_value(0);
		draw_currentI_value(0);
		draw_cruise_control();
		draw_motor_faults();
		draw_motor_reverse_enabled();

		/*  // Uncomment for test program
		speedMph = 15 + i; // Set mph.
		motorFaultRegisters = 2324 + i;
		motorErrorActive = 1;
		motorTempVal = (float32)i/10;
		throttleVal = -0.5;
		i++;
		*/
	}
}

void refreshAllElementsToDefaultState() {
	blinkerState = 3;
	draw_blinkers();

	CANErrorActive = 1;
	draw_CAN_error();

	motorErrorActive = 1;
	draw_motor_error();

	SOCVal = 0.7;
	draw_SOC(1);

	throttleVal = 0;
	draw_throttle_regen(1);

	signalStrengthVal = 0.25;
	draw_signal_strength(1);

	batTempVal = 0.75;
	draw_bat_temp(1);

	motorTempVal = 0;
	draw_motor_temp(1);

	speedMph = 12;
	draw_speed_mph(1);

	mpptVal = 0.5;
	draw_mppt_value(1);

	currentIVal = 0.25;
	draw_currentI_value(1);

	cruiseControlEnabled = 0;
	draw_cruise_control();

	motorFaultRegisters=(Uint32)0x01<<(2*8+3);
	draw_motor_faults();

	reverseModeEnabled = 0;
}

signed char initializeuCANndSerialComs() {
	puts("Initializing uC");
	// UNCOMMENT 2 LINES IF USING FLASH:
	memcpy((Uint16 *)&RamfuncsRunStart,(Uint16 *)&RamfuncsLoadStart, (Uint32)&RamfuncsLoadSize); // Copy some RAM functions from flash into RAM.
	InitFlash();
	InitSysCtrl();  // Initialize System Control registers, PLL, WatchDog, Clocks to default state

	DINT;           // Disable interrupts
	InitPieCtrl();  // Initialize and clear PIE control registers. Clear all interrupt flags.
	IER = 0x0000;   // Disable CPU interrupts and clear all CPU interrupt flags:
	IFR = 0x0000;
	//InitPieVectTable(); //Initialize the PIE vector table with pointers to the shell Interrupt Service Routines (ISR).

	/*
	// Map interrupt to ISR function:
	EALLOW;  // This is needed to write to EALLOW protected registers
	PieVectTable.TINT0 = &cpu_timer0_isr_torque_control_loop_iteration;
	EDIS;    // This is needed to disable write to EALLOW protected registers

	// Initialize clock timer peripheral
	InitCpuTimers();
	ConfigCpuTimer(&CpuTimer0, 90, 500000); // Configure CPU-Timer 0 to interrupt every 500 milliseconds:
	// 90MHz CPU Freq, 50 millisecond Period (in uSeconds)
	CpuTimer0Regs.TCR.all = 0x4001; // Use write-only instruction to set TSS bit = 0
	IER |= M_INT1;  // Enable CPU INT1 which is connected to CPU-Timer 0:
	PieCtrlRegs.PIEIER1.bit.INTx7 = 0; // Disable TINT0 in the PIE: Group 1 interrupt 7, until we are ready to start the control loop.
	 */
	// Enable global Interrupts and higher priority real-time debug events:

	EINT;   // Enable Global interrupt INTM
	ERTM;   // Enable Global realtime interrupt DBGM

	InitGpio(); //This function is found in the F2806x_Gpio.c file and illustrates how to set the GPIO to its default state.
	InitSciGpio(); // Select GPIO for the device or for the specific application.
	EALLOW;
	GpioCtrlRegs.GPAMUX1.bit.GPIO4 = 0; // Ground GPIO4, connected to CAN RS, to enable proper CAN operation.
	GpioCtrlRegs.GPADIR.bit.GPIO4 = 1;
	EDIS;
	GpioDataRegs.GPACLEAR.bit.GPIO4 = 1;
	LCD_Initialize_CAN(); // Initialize CAN
	CAN_receive(MOTOR_CONTROLLER, 8, 0, 0); // Start receiving from motor controller.

	// Initialize Serial (SCI) communications
	scia_fifo_init();	   // Initialize the SCI FIFO
	scia_init();           // Initalize SCI

	return 1;
}

