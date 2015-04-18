#include "p24HJ64GP502.h"

void initUART(unsigned long clockFreq)
{
		U1MODE=0;
		U1STA=0;
		U1MODEbits.UARTEN = 0;		// Disable UART
        AD1PCFGL = AD1PCFGL | 0x1800;//Set AN12 to digital
  	//-------------------------configure USART ---------------------------------------------------------T6
		U1MODEbits.BRGH=1;//High Speed Baud Rate (Fosc/ 4)Not needed for BMS?
		U1MODEbits.ABAUD = 0;		// Auto-BAUD off
		U1MODEbits.PDSEL1=0;//8 bits, odd parity
		U1MODEbits.PDSEL0=0;
		U1MODEbits.STSEL=0;//1 stop bit

 		U1BRG = 15;//set baud rate


		
// the UxTXIF is set when the last character is shifted out of the Transmit
//Shift Register (UxTSR). This implies that all the transmit operations are completed. 
		U1STAbits.URXISEL1=0;
		U1STAbits.URXISEL0=1;
 		RPINR18bits.U1RXR=12;	 //UART1 receive set to RB12
   	    RPOR5bits.RP10R	=3;	 //UART1 transmit set to RB10
	

		IPC3bits.U1TXIP2 = 1; //Set Uart TX Interrupt Priority
		IPC3bits.U1TXIP1 = 0;
		IPC3bits.U1TXIP0 = 0;
		IPC2bits.U1RXIP2 = 1; //Set Uart RX Interrupt Priority
		IPC2bits.U1RXIP1 = 0;
		IPC2bits.U1RXIP0 = 0;	

	//start in receive mode	//
		U1STAbits.URXISEL1  = 0;            // Interrupt after one RX character is received
		U1STAbits.URXISEL0=0;
		U1STAbits.UTXISEL1  = 0;            // Interrupt after when TX buffer is empty
		U1STAbits.UTXISEL0=0;
		IEC0bits.U1TXIE = 0;//TX interrupts disabled
		IEC0bits.U1RXIE =1; //RX  Interrupt enabled
		IFS0bits.U1RXIF=0;
		IFS0bits.U1TXIF=0;

   
/*
The UTXEN bit should not be set until the UARTEN bit has been set; otherwise,
UART transmissions will not be enabled.
*/
		U1MODEbits.UARTEN=1;//Enabled
		U1STAbits.UTXEN=1;//UART Transmit enabled
}

void initTimer2( void )
{	
	T2CON = 0;						/* ensure Timer 1 is in reset state */
 	IFS0bits.T2IF = 0;				/* reset Timer 1 interrupt flag */
	IPC1bits.T2IP = 4;				/* set Timer1 interrupt priority level to 4 */
 	IEC0bits.T2IE = 0;				/* disable Timer 1 interrupt */
	PR1 = 0xFFFF;					/* set Timer 1 period register */
	T2CONbits.TCKPS1 = 0;			/* select Timer1 Input Clock Prescale */
	T2CONbits.TCS = 0;			 	/* select external timer clock */
	T2CONbits.TON = 1;			 	/* enable Timer 1 and start the count */ 	
}

//Not currently used in code
 void initCRC()
{
//Set <PLEN> to 7 for CRC8(for an n bit polynomial set PLEN=n-1)
CRCCONbits.PLEN3=0;
CRCCONbits.PLEN2=1;
CRCCONbits.PLEN1=1;
CRCCONbits.PLEN0=1;
//Set XORed polynomial for CRC8(x^8 + x^7 + x^6 + x^4 + x^2 + 1)
//1 and x^8 are understood to be Xored and ommited
CRCXOR = 0xD4;
CRCWDAT=0x0000; 
IFS4bits.CRCIF=0; 
}


