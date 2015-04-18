/*
 * main.c
 */

void encoderGPIOSetup();
#include "F2806x_Device.h"
#include "F2806x_Examples.h"
#include <stdio.h>
#include <string.h>

// Global variables used in this example
char LoopCount;
char ErrorCount;
char* totransmit;
char message[32];
char received[32];
char print[32];
int loopCount = 0;

void main(void) {
	InitSysCtrl();
	DINT;
	InitPieCtrl();
	IER = 0x0000;
	IFR = 0x0000;
	InitPieVectTable();
	InitGpio();
	encoderGPIOSetup();

	int16 bits[16];
	char string[32];
	int conversionArray[256] = {
			-1, 56, 40, 55, 24, -1, 39, 52, 8, 57, -1, -1, 23, -1, 36, 13, 120, -1, 41,
			54, -1, -1, -1, 53, 7, -1, -1, -1, 20, 19, 125, 18, 104, 105, -1, -1, 25, 106, 38,
			-1, -1, 58, -1, -1, -1, -1, 37, 14, 119, 118, -1, -1, -1, 107, -1, -1, 4, -1, 3,
			-1, 109, 108, 2, 1, 88, -1, 89, -1, -1, -1, -1, 51, 9, 10, 90, -1, 22, 11, -1,
			12, -1, -1, 42, 43, -1, -1, -1, -1, -1, -1, -1, -1, 21, -1, 126, 127, 103, -1, 102,
			-1, -1, -1, -1, -1, -1, -1, 91, -1, -1, -1, -1, -1, 116, 117, -1, -1, 115, -1, -1,
			-1, 93, 94, 92, -1, 114, 95, 113, 0, 72, 71, -1, 68, 73, -1, -1, 29, -1, 70, -1,
			69, -1, -1, 35, 34, 121, -1, 122, -1, 74, -1, -1, 30, 6, -1, 123, -1, -1, -1, 124,
			17, -1, -1, -1, 67, 26, -1, 27, 28, -1, 59, -1, -1, -1, -1, -1, 15, -1, -1, -1,
			-1, -1, -1, -1, -1, 5, -1, -1, -1, 110, -1, 111, 16, 87, 84, -1, 45, 86, 85, -1,
			50, -1, -1, -1, 46, -1, -1, -1, 33, -1, 83, -1, 44, 75, -1, -1, 31, -1, -1, -1,
			-1, -1, -1, -1, 32, 100, 61, 101, 66, -1, 62, -1, 49, 99, 60, -1, 47, -1, -1, -1,
			48, 77, 82, 78, 65, 76, 63, -1, 64, 98, 81, 79, 80, 97, 96, 112};
	int i = 0;
	int index = 0;
	int mult = 1;
	while (1){
		bits[0] = GpioDataRegs.GPADAT.bit.GPIO0;
		bits[1] = GpioDataRegs.GPADAT.bit.GPIO1;
		bits[2] = GpioDataRegs.GPADAT.bit.GPIO2;
		bits[3] = GpioDataRegs.GPADAT.bit.GPIO3;
		bits[4] = GpioDataRegs.GPADAT.bit.GPIO4;
		bits[5] = GpioDataRegs.GPADAT.bit.GPIO5;
		bits[6] = GpioDataRegs.GPADAT.bit.GPIO6;
		bits[7] = GpioDataRegs.GPADAT.bit.GPIO7;

		bits[8] = GpioDataRegs.GPADAT.bit.GPIO8;
		bits[9] = GpioDataRegs.GPADAT.bit.GPIO9;
		bits[10] = GpioDataRegs.GPADAT.bit.GPIO10;
		bits[11] = GpioDataRegs.GPADAT.bit.GPIO11;
		bits[12] = GpioDataRegs.GPADAT.bit.GPIO12;
		bits[13] = GpioDataRegs.GPADAT.bit.GPIO13;
		bits[14] = GpioDataRegs.GPADAT.bit.GPIO14;
		bits[15] = GpioDataRegs.GPADAT.bit.GPIO15;


		index = 0;
		mult = 1;
		for(i=0;i<8;i++){
			index+=mult*bits[i];
			mult*=2;
		}
		sprintf(string, "Encoder 1: %d",conversionArray[index]);
		puts(string);

		index = 0;
		mult = 1;
		for(i=8;i<16;i++){
			index+=mult*bits[i];
			mult*=2;
		}
		sprintf(string, "Encoder 2: %d\n",conversionArray[index]);
		puts(string);
	}
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

	// Enable an GPIO input on GPIO6, set it high
	GpioCtrlRegs.GPAPUD.bit.GPIO6 = 0;   // Enable pullup on GPIO6
	GpioDataRegs.GPASET.bit.GPIO6 = 1;   // Load output latch
	GpioCtrlRegs.GPAMUX1.bit.GPIO6 = 0;  // GPIO6 = GPIO6
	GpioCtrlRegs.GPADIR.bit.GPIO6 = 0;   // GPIO6 = input

	// Enable eCAP2 on GPIO7
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
