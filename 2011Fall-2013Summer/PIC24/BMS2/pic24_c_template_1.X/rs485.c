#include "rs485.h"
#include <p24HJ128GP202.h>

void UART1PutChar(char Ch)
{
   //transmit ONLY if TX buffer is empty
   while(U1STAbits.UTXBF == 1);
   U1TXREG = Ch;
}

//make function that sends and receives relevant data over RS485
//the spec for the data may need to be re-created
