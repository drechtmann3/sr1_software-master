#include "cancom.h"
#include "GlobalDef.h"

int initCan(){

    RCONbits.IPEN = 1;//Enable interrupt priority
    IPR1bits.RCIP = 1;//Make receive interrupt high priority
    PIE1bits.RCIE = 1; //Enables the EUSART receive interrupt
    INTCONbits.GIE = 1; //Global interrupt enable
    
    OpenUSART(USART_TX_INT_ON &&
            USART_RX_INT_ON   &&
            USART_ASYNCH_MODE &&
            USART_CONT_RX     &&
            USART_EIGHT_BIT   &&
            USART_BRGH_HIGH
            ,125000/(16*(BAUD_RATE)+1));//TODO: get external oscillator and change this
 /*
 Asynchronous mode, high speed:
FOSC / (16 * (spbrg + 1))
Asynchronous mode, low speed:
FOSC / (64 * (spbrg + 1))
Synchronous mode:
FOSC / (4 * (spbrg + 1))
*/
    //TODO: read device ID


}

int sendMessage(int length, char* message){
    
}

void sendTestString(){
    WriteUSART('T');
    WriteUSART('E');
    WriteUSART('S');
    WriteUSART('T');
}