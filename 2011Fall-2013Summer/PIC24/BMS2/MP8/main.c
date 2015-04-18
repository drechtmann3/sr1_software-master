//Files to be included
#include "main.h"
#include "ADC.h"
#include "ltc.h"
#include "relay.h"
//System Files
#include <p24HJ128GP202.h>
#include <stdint.h>        /* Includes uint16_t definition                    */
#include <stdbool.h>       /* Includes true/false definition                  */


int16_t main(void)
{
	//TODO discharge calculations
	int i = LTC3;
	int j;
	char voltages[19];
	int selfCheck = 0;

	configPins();
	configClock();
	

	//Comment out next 5 lines if debugging
	selfCheck += initLTC();
	selfCheck += initADC();//initADC();
	if(selfCheck == 2){
		setRelay(RELAY_ON);
	}

    while(1)
    {	
		//comment out next 4 lines if debugging
		for(i = LTC1; i < LTC_ALL; i++){
			LTC_readVoltages(i);
		}
		checkADC();


		//uncomment next 0 lines if debugging RS-485
		
		//unComment next 3 lines if debugging LTC
		//LTC_writeConfig(LTC_ALL, 0);
		//LTC_readVoltages(i);
		//LTC_analyzeVolts(i);

		//uncomment out next 3 lines if debugging ADC
//		j = ADCReadRaw(TEMP1_CHANNEL);
//		j++;
//		j--;
	}
}

void configPins(){

	AD1PCFGL = 0b1111111111111111; //set all bits not to be analog

	//TRISx defines the input/output state of pins. 1 represents input, while 0 represents output.
	TRISAbits.TRISA0 = 0;	// warn1
	TRISAbits.TRISA1 = 0;	// warn2 
	TRISAbits.TRISA3 = 0;	// Critical
	TRISAbits.TRISA4 = 0;	// DI/RO
	
	TRISBbits.TRISB2 = 0;	//MOSI
	TRISBbits.TRISB3 = 0;	//SCK
	TRISBbits.TRISB4 = 0;	//Relay
	TRISBbits.TRISB5 = 1;	//MISO LTC1
	TRISBbits.TRISB6 = 1;	//MISO LTC2	
	TRISBbits.TRISB7 = 1;	//MISO LTC3
	TRISBbits.TRISB8 = 1;	//MISO ADC
	TRISBbits.TRISB9 = 1;	//RX    
	TRISBbits.TRISB10 = 0;	//TX
	TRISBbits.TRISB11 = 0;	//FAULT
	TRISBbits.TRISB12 = 0;	//CS LTC1
	TRISBbits.TRISB13 = 0;	//CS LTC2
	TRISBbits.TRISB14 = 0;	//CS LTC3
	TRISBbits.TRISB15 = 0;	//CS ADC


	LATBbits.LATB3 = 0; //SET CLOCK LOW
	setRelay(RELAY_OFF); //make sure the relay is off
	LATAbits.LATA0 = 0; //set warn1 off
	LATAbits.LATA1 = 0; //set warn2 off
	LATAbits.LATA3 = 0; //set critical led off
	LATBbits.LATB12 = 1;
	LATBbits.LATB13 = 1;
	LATBbits.LATB14 = 1;
}

void configClock() {
        // Clock scaling settings
        CLKDIVbits.DOZEN = 0;                   // 0 = Processor clock/peripheral clock ratio forced to 1:1
        CLKDIVbits.PLLPRE = 0b0;                // PLL pre divider, 0b0 = 2
        CLKDIVbits.PLLPOST = 0b1;               // PLL post divider, 0b1 = 4
        PLLFBDbits.PLLDIV = 0b110000;   // PLL multipler (even though called "divider"), 0b110000 = 50 (default)

}
