//###########################################################################
//
//!  \addtogroup f2806x_example_list
//!  <h1>Timer based blinking LED(timed_led_blink)</h1>
//!
//!  This example configures CPU Timer0 for a 500 msec period, and toggles the GPIO34
//!  LED once per interrupt. For testing purposes, this example
//!  also increments a counter each time the timer asserts an interrupt.
//!
//!  \b Watch \b Variables \n
//!  - CpuTimer0.InterruptCount
//!
//! \b External \b Connections \n
//!  Monitor the GPIO34 LED blink on (for 500 msec) and off (for 500 msec) on 
//!  the 2806x control card.
//
//###########################################################################
// $TI Release: F2806x C/C++ Header Files and Peripheral Examples V136 $
// $Release Date: Apr 15, 2013 $
//###########################################################################


//#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File
#include "CAN.h"
#include "stdio.h"
#include "28069Common.h"

void test_send_isr(CAN_ID ID, Uint32 dataH, Uint32 dataL, Uint16 lengthInBytes, int mbox_num){
	puts("Send interrupt!");
}

void test_receive_isr(CAN_ID ID, Uint32 dataH, Uint32 dataL, Uint16 lengthInBytes, int mbox_num){
	puts("Receive interrupt!");
}

CAN_INFO TEST_INFO_ARRAY[] = {
		{
				IMU,
				&test_send_isr,
				&test_receive_isr
		}
};

void main(void) {
	Uint32 imu_test_arr[2];

	deviceInit();

	CAN_init(TEST_INFO_ARRAY, 8, 1); //  Ricky's Code
	//CAN_receive(IMU, 8, 0,0);

	imu_test_arr[0] = 0x12345678;
	imu_test_arr[1] = 0xFFFFFFFF;
	//CAN_send(imu_test_arr, 8, IMU, 0,0); // Mailbox 0
	CAN_receive(IMU, 8, 0, 0);
	//CAN_send(WIFI, 8, 0)
	while(1);
}
