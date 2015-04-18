/*
 * main.c
 */

// These interrupt functions are not actually called ever, since I have disabled interrupts for the motor controller.
#include "CAN.h"
#include "stdio.h"
#include "F2806x_Cla_typedefs.h"
#include "F2806x_GlobalPrototypes.h"         // Prototypes for global functions within the .c files.
#include "PeripheralHeaderIncludes.h"
int count =0;
void CAN_send_isr(CAN_ID ID, Uint32 dataH, Uint32 dataL, Uint16 length, int mbox_num) {
	puts("Can sent!");
}
void CAN_receive_isr(CAN_ID ID, Uint32 dataH, Uint32 dataL, Uint16 length, int mbox_num) {
	puts("Can received");
}

// This array describes what ID CAN sends, and send and receive callbacks
CAN_INFO CAN_info_array[] = {
		{
				PEDALS,
				&CAN_send_isr,
				&CAN_receive_isr // Interrupts are not actually called
		}
};


void initialize_CAN() {
	InitSysCtrl();  // Initialize System Control registers, PLL, WatchDog, Clocks to default state

	DINT;           // Disable interrupts
	InitPieCtrl();  // Initialize and clear PIE control registers. Clear all interrupt flags.
	IER = 0x0000;   // Disable CPU interrupts and clear all CPU interrupt flags:
	IFR = 0x0000;
	InitPieVectTable(); //Initialize the PIE vector table with pointers to the shell Interrupt Service Routines (ISR).

	EINT;   // Enable Global interrupt INTM
	ERTM;   // Enable Global realtime interrupt DBGM
	CAN_init(CAN_info_array, 1, 1); // Initialize CAN with the number of CAN ID's we intend to be sending/receiving from, in this case, just "MOTOR_CONTROLLER" Don't use interrupts.
}

int main(void) {
	puts("started");
	initialize_CAN();
	CAN_receive(PEDALS, 12, 4, 1);
	while(1);
	return 0;
}
