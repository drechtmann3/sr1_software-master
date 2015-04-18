#line 1 "..\c\cancom.c"
#line 1 "..\c\cancom.c"



int initCan(){

    RCONbits.IPEN = 1;
    IPR1bits.RCIP = 1;
    PIE1bits.RCIE = 1; 
    INTCONbits.GIE = 1; 
    
    OpenUSART(USART_TX_INT_ON &&
            USART_RX_INT_ON   &&
            USART_ASYNCH_MODE &&
            USART_CONT_RX     &&
            USART_EIGHT_BIT   &&
            USART_BRGH_HIGH
            ,125000/(16*(BAUD_RATE)+1));
 
#line 25 "..\c\cancom.c"
 
    


}

int sendMessage(int length, char message[]){
    
}

void sendTestString(){
    WriteUSART('T');
    WriteUSART('E');
    WriteUSART('S');
    WriteUSART('T');
}