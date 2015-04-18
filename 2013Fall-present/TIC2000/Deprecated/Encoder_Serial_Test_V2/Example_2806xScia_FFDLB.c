//###########################################################################
//
//!  \addtogroup f2806x_example_list
//!  <h1>SCI Digital Loop Back(scia_loopback)</h1>
//!
//!  This program uses the internal loop back test mode of the peripheral.
//!  Other then boot mode pin configuration, no other hardware configuration
//!  is required.
//!  
//!  This test uses the loopback test mode of the SCI module to send
//!  characters starting with 0x00 through 0xFF.  The test will send
//!  a character and then check the receive buffer for a correct match.
//!
//!  \b Watch \b Variables \n
//!  - \b LoopCount , Number of characters sent
//!  - \b ErrorCount , Number of errors detected
//!  - \b SendChar , Character sent
//!  - \b ReceivedChar , Character received
//
//###########################################################################
// $TI Release: F2806x C/C++ Header Files and Peripheral Examples V136 $
// $Release Date: Apr 15, 2013 $
//###########################################################################

#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File
#include <stdio.h>
#include <string.h>

// Prototype statements for functions found within this file.
void scia_loopback_init(void);
void scia_fifo_init(void);
void scia_xmit(int a);
void error();
__interrupt void scia_rx_isr(void);
__interrupt void scia_tx_isr(void);

// Global counts used in this example
Uint16 LoopCount;
Uint16 ErrorCount;

void main(void)
{
    Uint16 SendChar;
    Uint16 ReceivedChar;

// Step 1. Initialize System Control registers, PLL, WatchDog, Clocks to default state:
// This function is found in the F2806x_SysCtrl.c file.
	InitSysCtrl();

	InitGpio(); //This function is found in the F2806x_Gpio.c file and illustrates how to set the GPIO to its default state.

// Step 2. Select GPIO for the device or for the specific application:
// This function is found in the F2806x_Gpio.c file.
// InitGpio(); skip this as this is example selects the I/O
// for SCI-A in this file itself
   InitSciGpio();

// Step 3. Initialize PIE vector table:
// The PIE vector table is initialized with pointers to shell Interrupt
// Service Routines (ISR).  The shell routines are found in F2806x_DefaultIsr.c.
// Insert user specific ISR code in the appropriate shell ISR routine in
// the DSP28_DefaultIsr.c file.
/*
// Disable and clear all CPU interrupts:
	DINT;
	IER = 0x0000;
	IFR = 0x0000;

      // Initialize Pie Control Registers To Default State:
      // This function is found in the F2806x_PieCtrl.c file.
	  // InitPieCtrl();  PIE is not used for this example

      // Initialize the PIE Vector Table To a Known State:
      // This function is found in F2806x_PieVect.c.
      // This function populates the PIE vector table with pointers
      // to the shell ISR functions found in F2806x_DefaultIsr.c.
	  InitPieVectTable();

      // Enable CPU and PIE interrupts
      // This example function is found in the F2806x_PieCtrl.c file.
      EnableInterrupts();
*/
// Step 4. Initialize all the Device Peripherals to a known state:
// This function is found in F2806x_InitPeripherals.c
// InitPeripherals(); skip this for SCI tests

// Step 5. User specific functions, Reassign vectors (optional), Enable Interrupts:

    LoopCount = 0;
    ErrorCount = 0;


    scia_fifo_init();	   // Initialize the SCI FIFO
    scia_loopback_init();  // Initalize SCI for digital loop back

    // Note: Autobaud lock is not required for this example

    // Send a character starting with 0
    SendChar = 0;

// Step 6. Send Characters forever starting with 0x00 and going through
// 0xFF.  After sending each, check the receive buffer for the correct value
/*
	for(;;)
    {
       scia_xmit(SendChar);
       while(SciaRegs.SCIFFRX.bit.RXFFST !=1) { } // wait for RRDY/RXFFST =1 for 1 data available in FIFO

       // Check received character
       ReceivedChar = SciaRegs.SCIRXBUF.all;
       if(ReceivedChar != SendChar) error();

       // Move to the next character and repeat the test
       SendChar++;
       // Limit the character to 8-bits
       SendChar &= 0x00FF;
       LoopCount++;
    }

*/
	int16 bits[8];
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
		bits[0] = GpioDataRegs.GPADAT.bit.GPIO8;
		bits[1] = GpioDataRegs.GPADAT.bit.GPIO9;
		bits[2] = GpioDataRegs.GPADAT.bit.GPIO10;
		bits[3] = GpioDataRegs.GPADAT.bit.GPIO11;
		bits[4] = GpioDataRegs.GPADAT.bit.GPIO12;
		bits[5] = GpioDataRegs.GPADAT.bit.GPIO13;
		bits[6] = GpioDataRegs.GPADAT.bit.GPIO14;
		bits[7] = GpioDataRegs.GPADAT.bit.GPIO15;

		index = 0;
		mult = 1;
		for(i=0;i<8;i++){
			index+=mult*bits[i];
			mult*=2;
		}
		int result = conversionArray[index];
		if (result == -1) {
			puts("ERROR! Check connections!");
		} else {
			sprintf(string, "%d", result);
			puts(string);

			for (i = 0; i < strlen(string); i++) {
				while (SciaRegs.SCIFFTX.bit.TXFFST != 0) {}//wait for current transmit to finish
				SendChar = (char)string[i];
				scia_xmit(SendChar);

				// Check received character
				ReceivedChar = SciaRegs.SCIRXBUF.all;
			}
			while (SciaRegs.SCIFFTX.bit.TXFFST != 0) {}//wait for current transmit to finish
			SendChar = (Uint16)10; // Send end of line character. (\n)
			scia_xmit(SendChar);
			while (SciaRegs.SCIFFTX.bit.TXFFST != 0) {}//wait for current transmit to finish
			SendChar = (Uint16)13; // Send end of carriage return character. (\r)
			scia_xmit(SendChar);
		}
	}
}


// Step 7. Insert all local Interrupt Service Routines (ISRs) and functions here:

void error()
{

      ErrorCount++;
//   __asm("     ESTOP0");  // Uncomment to stop the test here
//    for (;;);

}

// Test 1,SCIA  DLB, 8-bit word, baud rate 0x000F, default, 1 STOP bit, no parity
void scia_loopback_init()
{
    // Note: Clocks were turned on to the SCIA peripheral
    // in the InitSysCtrl() function

 	SciaRegs.SCICCR.all =0x0007;   // 1 stop bit,  No loopback
                                   // No parity, 8 char bits,
                                   // async mode, idle-line protocol
	SciaRegs.SCICTL1.all =0x0003;  // enable TX, RX, internal SCICLK,
                                   // Disable RX ERR, SLEEP, TXWAKE
	SciaRegs.SCICTL2.all =0x0003;
	SciaRegs.SCICTL2.bit.TXINTENA =1;
	SciaRegs.SCICTL2.bit.RXBKINTENA =1;

	// BAUD RATE REGISTERS:
	// SPI BAUD RATE = LSPCLK / (SCIHBAUD<<8 + SCILBAUD + 1) / 8. For 80MHz, LSPCLK=22,118,400Hz
    SciaRegs.SCIHBAUD    =0x0000;
    SciaRegs.SCILBAUD    =0x0017; // 115200 baud
	SciaRegs.SCICCR.bit.LOOPBKENA =0; // Disable loop back (internal connection TX-RX)
	SciaRegs.SCICTL1.all =0x0023;     // Relinquish SCI from Reset
}

// Transmit a character from the SCI'
void scia_xmit(int a)
{
    SciaRegs.SCITXBUF=a;
}

// Initalize the SCI FIFO
void scia_fifo_init()
{
    SciaRegs.SCIFFTX.all=0xE040;
    SciaRegs.SCIFFRX.all=0x2044;
    SciaRegs.SCIFFCT.all=0x0;

}






//===========================================================================
// No more.
//===========================================================================

