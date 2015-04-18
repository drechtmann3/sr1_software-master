/* ------------------------------------------------------
BMS.C
version 0.5

Battery management system firmware for Solar Jackets.
- Uses PIC24HJ128GP502 microcontroller interfacing to three LTC6802-1 battery stack monitors via SPI
- Monitors 30 LiFePO4 cells (3.2v each) wired in series, and balances voltages across the cells
-------------------------------------------------------*/

#include <p24Hxxxx.h>
#include "bms.h"
#include "string.h"
#include "PIC24_RS485.h"
int led;
int test_temp;
double Tester;
//RS485 stuff
#define NUM_DATA_INT (35)
unsigned int converted[NUM_DATA_INT];

char readAddress(){
	TRISA=TRISA|0x0003;//Set RA0 and RA1 input
	TRISB=TRISB|0x0001;//Set RB0 to input
	char lsb=LATAbits.LATA0;
	char sec=LATAbits.LATA1;
	char msb=LATBbits.LATB0;
	return lsb+sec*2+msb*4;

}

int main(){
	//unsigned char tempBytes[40] = {0};
	unsigned long int i = 0;
	
	DeviceIdentifiers identifier;
	identifier.deviceAddress[0]='B';
	identifier.deviceAddress[1]='0'+readAddress();
	identifier.deviceType[0]='B';
	identifier.deviceType[1]='M';
	identifier.clockFreq=14700000;
	/////////////
	////////////
	// Config 
    //configTimer();
	configPins();
	configSPI1();
	configLTC();
	initRS485(identifier,NUM_DATA_INT,converted);//TODO: figure out address
//	while(1){ //Test Functions Loop
//		spiStartCom(2);		// Start ADC
//		sendCommand(STTMPAD);
//		while(comBuffer.active);
//		Nop();Nop();
//		spiStopCom(2);		// Stop communication
//		for(i = 0; i < 10000;i++); // Wait for conversion
//		spiStartCom(2);		// Start Cell read
//		sendCommunication(RDTMP,0,8,0);		// Read 20 bytes of data
//		while(comBuffer.active);
//		Nop();Nop();
//		spiStopCom(2);		// Stop communication
//		for(i = 0; i < 5;i++) tempBytes[i] = comBuffer.in[i]; // Wait for conversion
//		processTempBytes(2);
//		checkRelay();
//		//configLTC();
//		//ReadHallEffectFunction();
//	}

	while(1){
	int i2=0;
		for(i2=0;i2<3;i2++){//TODO: check if for loop actually totally good 
/////////////////////////////Cell Voltage LTC 2 BTM of Stack
			spiStartCom(i2);		// Start ADC Cell Voltage	
			sendCommand(STCVAD);
			while(comBuffer.active);	
			Nop();
			Nop();
			spiStopCom(i2);		// Stop communication
			for(i = 0; i < 10000;i++); // Wait for conversion
	
			spiStartCom(i2);						// Start Cell Read MID of Stack
			sendCommunication(RDCV,0,20,0);		// Read 20 bytes of data
			while(comBuffer.active);	
			Nop();
			Nop();
			spiStopCom(i2);
			
			for(i = 0; i < 20;i++) 
				cellVoltageBytes[i] = comBuffer.in[i]; // Wait for conversion
			processCellBytes(i2);				// Process BTM of Stack
		}
		for(i2=1;i2<3;i2++){
			spiStartCom(i2);		// Start ADC
			sendCommand(STTMPAD);
			while(comBuffer.active);
			Nop();Nop();
			spiStopCom(i2);		// Stop communication
			for(i = 0; i < 10000;i++); // Wait for conversion
			spiStartCom(i2);		// Start Cell read
			sendCommunication(RDTMP,0,8,0);		// Read 20 bytes of data
			while(comBuffer.active);
			Nop();Nop();
			spiStopCom(i2);		// Stop communication
			for(i = 0; i < 5;i++) tempBytes[i] = comBuffer.in[i]; // Wait for conversion
			processTempBytes(i2);			//  Set BMS Temp for LTC 2
	/////////////////////////////
			//ReadHallEffectFunction();		// Set BMS state Curr
			//checkRelay();	// Actuate Relay
		}
		for(i2=0;i2<10;i2++)//Try enough times to get sending started
			RS485processRX();				
		}
	}



/* --- Config Functions ---------------------------------
Functions to configure PIC and LTC during startup or reset
-------------------------------------------------------*/
void configPins(){

	TRISB = 0xFFFF;						// Set all Reg B pins to inputs
	// Current Sensor /////////////////////////

//TRISBbits.TRISB1 = 1;
//LATBbits.LATB1 = 0;
	///////////////////////////////////////////
	// SPI Mapping /////////////////////////////
	RPOR4bits.RP9R = 0b01000; 			// SCLK: Map SPI1 clock output on pin RP9
	RPOR4bits.RP8R = 0b00111; 			// SDO: Map SPI1 data output on pin RP8
	// LTC Mapping (Remapping SPI) ////////////
	//RPINR20bits.SDI1R = 0b00000;	    // SDI: Initial Map SPI1 data input on RP7
	RPINR20bits.SDI1R = 0b00111;	    // SDI: Initial Map SPI1 data input on RP7
	TRISBbits.TRISB7 = 1;				// Set pin B7 to be an input (SD0_LTC0 -> PIC_SDI_B7)
	// LTC 1-2 will need to change
	TRISBbits.TRISB3 = 1;				// Set pin B3 to be an input (SD0_LTC1 -> PIC_SDI_B3)
	TRISBbits.TRISB2 = 1;				// Set pin B2 to be an input (SD0_LTC2 -> PIC_SDI_B2)
	TRISBbits.TRISB13 = 0; 				// CS0: (LTC0 CS output enable)
	TRISAbits.TRISA4 = 0; 				// CS1: (LTC1 CS output enable)
	TRISBbits.TRISB14 = 0; 				// CS2: (LTC2 CS output enable)
	LATBbits.LATB14 = 1; 				// Set CS high to start
	LATAbits.LATA4 = 1; 				// Set CS high to start
	LATBbits.LATB15 = 1; 				// Set CS high to start
	//////////////////////////////////////////
	TRISBbits.TRISB15 = 0; 				// Relay pin is an output
}
void configSPI1(){
	int i =0;
	SPI1BUF = 0;
	IFS0bits.SPI1IF = 0; 		//Clear the SPI Interrupt Flag
	IEC0bits.SPI1IE = 0; 		//Disable the SPI Interrupt
	SPI1CON1bits.MSTEN = 1; 	// Master Mode Enabled (clock output)
	SPI1CON1bits.DISSCK = 0; 	// Internal Serial Clock is Enabled
	SPI1CON1bits.SSEN = 1;
	SPI1CON1bits.DISSDO = 0; 	// SDOx pin is controlled by the module
	SPI1CON1bits.MODE16 = 0; 	// Communication is 8 bits
	SPI1CON1bits.SMP = 0; 		// Input Data is sampled at the middle of data output time
	SPI1CON1bits.CKE = 0; 		//
	SPI1CON1bits.CKP = 1; 		//
	SPI1CON1bits.SPRE = 0b001;  // Secondary prescale 1:1
	SPI1CON1bits.PPRE = 0b01; 	// Primary prescale 16:1

	SPI1CON2bits.FRMEN = 0; 	// Disable framed SPI mode (the LTC doesn't use framed mode, but enabling this gives continuous clock signal output from PIC which we need)
	SPI1CON2bits.FRMDLY = 1;	// Frame Delay enabled
	SPI1CON2bits.FRMPOL = 1;	// Active Low frame pulse
	SPI1CON2bits.SPIFSD = 0; 	// ^SSx pin used as frame sync pulse output
	
	comBuffer.active = 0;
	for(i=0;i < 50; i++){comBuffer.in[i] = 0;comBuffer.out[i] = 0;}
	comBuffer.length = 0;
	comBuffer.cnt = 0;

	SPI1STATbits.SPIROV = 0; 	// Reset overflow status
	IEC0bits.SPI1IE = 1; 		// Enable the SPI Interrupt
	SPI1STATbits.SPIEN = 1; 	// Enable SPI Module

}
void configLTC(){
	static unsigned short i;
	static unsigned short j;
	static unsigned char tempBuff[7];
	activeLTC = 0;
	for(i=0; i < 3; i++){	// Config the write sector
		spicom(i,1);				// Turn off all LTC communication
		LTCwrite[i].CFGRbytes[0]=0b10001110;	//bitwise: {WDT(read only)|GPIO2|GPIO1|LVLPL|CELL10|CDC[3]}
		LTCwrite[i].CFGRbytes[1]=0b00000000;	//bitwise: {DCCx[8..1]}
		LTCwrite[i].CFGRbytes[2]=0b00000000;	//bitwise: {MCxI[4..1]|DCCx[12..9]}
		LTCwrite[i].CFGRbytes[3]=0b11111111;	//bitwise: {MCxI[12..5]}
		LTCwrite[i].CFGRbytes[4]=95;			//bitwise: {VUV[8]}
		LTCwrite[i].CFGRbytes[5]=146;		//bitwise: {VOV[8]}
	}
	//LTC write
	for(j=0; j <3; j++){
		spiStartCom(j);
		for(i=0; i <6;i++) tempBuff[i] = LTCwrite[j].CFGRbytes[i];
		Nop();Nop();							// Start talking to LTC#j
		sendCommunication(WRCFG,tempBuff,6,1);	// Command plus data
		while(comBuffer.active);
		spiStopCom(j);							// Stop communicating to active LTC
	}	
}

void configTimer( void ){
    timer.ovrflw = 0;
    timer.cnt = 0;
	led = 0;
    T1CON = 0;          	/* ensure Timer 1 is in reset state */
    IFS0bits.T1IF = 0;  	/* reset Timer 1 interrupt flag */
    IPC0bits.T1IP = 4;  	/* set Timer1 interrupt priority level to 4 */
    IEC0bits.T1IE = 1;  	/* enable Timer 1 interrupt */
    PR1 = PERIOD;       	/* set Timer 1 period register */
    T1CONbits.TCKPS = 0b10;	/* select Timer1 Input Clock Prescale */
    T1CONbits.TCS = 0;  	/* select external timer clock */
    T1CONbits.TON = 1;  	/* enable Timer 1 and start the count */
}

/* UART done with RS485
void configUART(){
	// UART 1
	U1MODEbits.UARTEN = 0;		// Disable UART
	U1BRG = 22;
	U1MODEbits.UEN = 0b00;		// Rx and Tx only
	U1MODEbits.ABAUD = 0;		// Auto-BAUD off
	U1MODEbits.PDSEL = 0b00;	// PDSEL 8-bit no-parity
	U1MODEbits.STSEL = 0;		// Single Stop Bit
	U1STAbits.UTXEN = 1;		// UTX enabled
	TRISBbits.TRISB12 = 1;		// Make RB12 an input
	TRISBbits.TRISB10 = 0;		// Make RB10 an output
	RPINR18bits.U1RXR = 0b01100;// Map Rx to RP12 which is Tx of Rs-485 converter
	RPOR5bits.RP10R = 0b00011; 	// Map Tx to RP10 which is Rx of Rs-485 converter
	U1MODEbits.UARTEN = 1;		// Enable UART
}*/

/* --- Utility functions --------------------------------
Other useful functions
-------------------------------------------------------*/
//void __attribute__((interrupt, auto_psv)) _T1Interrupt( void ){
//	IEC0bits.T1IE = 0;  	/* enable Timer 1 interrupt */
//#ifdef TEST_STACK		// Development mode
//	led = !led; debugLed(led);
//#endif
//	timer.ovrflw = 1;
//	IFS0bits.T1IF = 0;  	/* reset Timer 1 interrupt flag */
//	IEC0bits.T1IE = 1;  	/* enable Timer 1 interrupt */
//}


void writeUART(unsigned char data){
	while(!U1STAbits.TRMT);
	U1TXREG = data;
}
unsigned char readUART(){
	while(!U1STAbits.URXDA);
	return U1RXREG;
}
void debugLed(unsigned char state){
	LATBbits.LATB15 = state; //Control the LED state
}
//////////////////////////////////////////////////////
// SPI Communication Functions
//////////////////////////////////////////////////////
void __attribute__((interrupt, auto_psv)) _SPI1Interrupt( void ){
	static unsigned char i;
	if(comBuffer.cnt == 0) i = SPI1BUF;				// just finished sending the command byte
	else comBuffer.in[comBuffer.cnt-1] = SPI1BUF; // Read the SPI buffer to clear the SPIRBF bit
	if(comBuffer.cnt == comBuffer.length)comBuffer.active = 0;		// Communication is finished
	else{ 															// Shift out data or send to read
		if(comBuffer.write)	SPI1BUF = comBuffer.out[comBuffer.cnt];
		else 				SPI1BUF = 0xFF;
		comBuffer.cnt++;
	}
	IFS0bits.SPI1IF = 0; 			// Clear the SPI Interrupt Flag
}
unsigned char runSPI1(unsigned char data)
{
	tempBuffer = SPI1BUF; 		// Read the SPI buffer to clear the SPIRBF bit
	SPI1BUF = data;
	// Wait for all input bits to be shifted into the SPI bitshift register
	// (warning: this bit is reset to zero when the SPI buffer is read, including debugger reads during step-by-step debug mode)
	while(!SPI1STATbits.SPIRBF); 
	return SPI1BUF;

}
void spiStartCom(unsigned short LTCsel){
	activeLTC = LTCsel;
	// Map the SDI to a different port
//	RPINR20bits.SDI1R = 0b00111;
	if(activeLTC == 2)	
		RPINR20bits.SDI1R = 0b00111; // Map to RB7 (RP7)
	if(activeLTC == 1) 
		RPINR20bits.SDI1R = 0b00011; // Map to RB1 (RP3)
	if(activeLTC == 0) 	
		RPINR20bits.SDI1R = 0b00010; // Map to RB0 (RP2)
	spicom(LTCsel,0);
}
void spiStopCom(unsigned short LTCsel){
	spicom(LTCsel,1);
}
void spicom(unsigned short LTCsel,unsigned short state){
	switch(LTCsel){
		case 0:LATBbits.LATB13 = state;break;	// Toggle CS1 LTC0
		case 1:LATAbits.LATA4 = state;break;	// Toggle CS2 LTC1
		case 2:LATBbits.LATB14 = state;break;	// Toggle CS3 LTC2
		default: spicom(0,0);
	}
}
void sendCommunication(unsigned char command,unsigned char* data,int length,unsigned char write){
	static unsigned char i;
	while(comBuffer.active)Nop();
	comBuffer.active = 0;
	comBuffer.length = length;
	comBuffer.write = write;
	comBuffer.cmd = command;
	if(write) for(i=0;i<length;i++)comBuffer.out[i] = data[i];
	comBuffer.cnt = 0;
	comBuffer.active = 1;
	SPI1BUF = comBuffer.cmd;
}
void sendCommand(unsigned char data){
	static unsigned char com;
	com = data;
	sendCommunication(com,0,0,0);
}
//////////////////////////////////////////////
// Support Functions
void processCellBytes(unsigned char numLTC){
	static unsigned long voltages[10];
	static unsigned char i,j,v,bc;
// 2 is the btm of the stack 0 is the top
	if(numLTC == 2) 
		numLTC = 0;
	else if(numLTC == 0) 
		numLTC = 2;
	
	v = 0;
	bc = 0;
	for(i = 0; i< 10;i++) 
		voltages[i] = 0;
	for(i=0;i<15;i++){
		for(j = 0; j < 8;j++){
			if(bc == 12){v++; bc = 0;}	// increment voltage offset
			voltages[v]|= ((cellVoltageBytes[i] >> j)&0x01) << bc;
			bc++;
		}
	}
	for(i=0;i<10;i++)
	{
		int volNum=i+(10*numLTC);
		 voltages[i]	= (voltages[i] *15)/10;
		 BMS.voltage[volNum] = (1095*(voltages[i])+243000)/1000;
		 converted[5+volNum]=BMS.voltage[volNum];
	}
}

void ReadHallEffect(){
	   //Turn on, auto sample start, auto-convert
   AD1CON1 = 0x80E4;

   //Vref+, Vref-, int every conversion, MUXA only
   AD1CON2 = 0x0000;

   //31 Tad auto-sample, Tad = 5*Tcy
   AD1CON3 = 0xFFFF;//0x1F05;

   AD1CHS0 = 0x0300;
   AD1PCFGLbits.PCFG3 = 0;  //Disable digital input on AN3
   AD1CSSL = 0;	 //No scanned inputs
	
	long wait;
	int i;

	//for(wait=0;wait<100000;wait++){
	   while (!AD1CON1bits.DONE);
}

void ReadHallEffectFunction()
{
	unsigned int ADCNUM;
	unsigned int IntRefVoltage;
	double CurrentValue = 0.0;		// Current value as calculated from the ADC
	double RefVoltage;	
	double FinalRefVoltage;
	unsigned int round;

	ReadHallEffect();
	ADCNUM = ADC1BUF0;
	RefVoltage = (3.3/1024.0)*((double) ADCNUM);
	if(RefVoltage > 2){
		TRISBbits.TRISB9 = 0;
		LATBbits.LATB9 = 0;
 	}
	IntRefVoltage = (int) (RefVoltage*1000);
	round = IntRefVoltage%10;
	IntRefVoltage /=10;
	//IntRefVoltage = IntRefVoltage/10;
    //asm("mov w1, _round");
	if (round >4)
	{
		IntRefVoltage +=1;
		FinalRefVoltage = (double) (IntRefVoltage/100.0);
	}
	else
		FinalRefVoltage = (double) (IntRefVoltage/100.0);
//	if (FinalRefVoltage < 2.55)
//		FinalRefVoltage = 2.54;
	CurrentValue = (FinalRefVoltage - 2.44)*43.47; // The 2.43 is the quiescent voltage at 0A load current
	BMS.curr = (long)(CurrentValue*1000);
	converted[0]=(unsigned int)(CurrentValue*10);
}
void checkRelay()
{
	int counter = 0;
	static unsigned char i;
	i = 0;
	if (BMS.curr > 18000)									// Checks if discharging current is greater than 5A
		 i = 1;									// Turns the relay on, causing the battery pack to shut down
	if (BMS.curr < -18000)									// Checks if charging current is less than -5A
		i = 1;
	for (counter = 0; counter < 4; counter++)			// Loop to check if all the four temperature sensors are within specified limits
	{
	 	if (BMS.temp[counter] > 45.0)						// The pre-set turn-off point for the battery pack is > 45C
			i = 1;
	}
	for (counter = 0; counter < 30; counter++)			// Loop to check if all the individual cell voltages are within specified limits
	{
		if (BMS.voltage[counter] > 3600)				// The pre-set turn-off point for the battery pack is > 3.6V
			i = 1;
		if (BMS.voltage[counter] < 2300)				// The pre-set turn-off point for the battery pack is < 2.3V
			i = 1;
	}
	_LATB15 = !i;								// Set Latch
}

void processTempBytes(unsigned char numLTC)
{
	static unsigned long temp[2];
	static double out[2];
	// 2 is the btm of the stack 0 is the top
	temp[0] =  ((tempBytes[1] & 0b1111) << 8)| tempBytes[0]; 
	temp[1] = (tempBytes[1]>>4)| (tempBytes[2]<<4);
 	out[0] = (((double)(temp[0]))*1.5)/10;
	out[1] = (((double)temp[1])*1.5)/10;
	if(numLTC == 2){
	 	BMS.temp[0] = (long)(out[0]*1000);
		BMS.temp[1] = (long)(out[1]*1000);
		converted[1]=(unsigned int)(out[0]*10);
		converted[2]=(unsigned int)(out[1]*10);
	}
	else if(numLTC == 1) {
		BMS.temp[2] = (long)(out[0]*1000);
		BMS.temp[3] = (long)(out[1]*1000);
		converted[3]=(unsigned int)(out[0]*10);
		converted[4]=(unsigned int)(out[1]*10);
	}
}



