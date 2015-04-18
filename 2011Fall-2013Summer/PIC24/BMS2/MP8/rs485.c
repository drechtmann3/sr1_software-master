#include "rs485.h"
#include <p24HJ128GP202.h>

//UART receive function, returns the value received.
char RS485_getChar()
{
   char Temp;
   //wait for buffer to fill up, wait for interrupt
   while(IFS0bits.U1RXIF == 0);
   Temp = U1RXREG;
   //reset interrupt
   IFS0bits.U1RXIF = 0;
   //return my received byte
   return Temp;
}

void RS485_putChar(char Ch)
{
   //transmit ONLY if TX buffer is empty
   while(U1STAbits.UTXBF == 1);
   U1TXREG = Ch;
}

//make function that sends and receives relevant data over RS485
//the spec for the data may need to be re-created
void initRS485(){
	U1BRG = BAUDRATE; //set the baud rate
	U1MODE = 0x8000; //turn on uart module
	U1STA = 0x8400; //turn on transmissions and tx/rx interupts
	IFS0bits.U1RXIF = 0; //reset RX interupt flag
}

char RS485_PEC(char PEC, char data){
	return (data ^ PEC);
}