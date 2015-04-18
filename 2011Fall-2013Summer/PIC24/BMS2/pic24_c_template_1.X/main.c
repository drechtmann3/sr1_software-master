/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

/* Device header file */
#if defined(__XC16__)
    #include <xc.h>
#elif defined(__C30__)
    #if defined(__PIC24E__)
    	#include <p24Exxxx.h>
    #elif defined (__PIC24F__)||defined (__PIC24FK__)
	#include <p24Fxxxx.h>
    #elif defined(__PIC24H__)
	#include <p24Hxxxx.h>
    #endif
#endif

#include "ADC.h"
#include "LED.h"
#include "main.h"
#include "ltc.h"
#include "relay.h"
#include "rs485.h"

#include <p24HJ128GP202.h>
#include <stdint.h>        /* Includes uint16_t definition                    */
#include <stdbool.h>       /* Includes true/false definition                  */

#include "system.h"        /* System funct/params, like osc/peripheral config */
#include "user.h"          /* User funct/params, such as InitApp              */

/******************************************************************************/
/* Global Variable Declaration                                                */
/******************************************************************************/

/* i.e. uint16_t <variable_name>; */

/******************************************************************************/
/* Main Program                                                               */
/******************************************************************************/
//TODO: maks sure that once status goes yellow, it can come back to green
//TODO: RS485
int16_t main(void)
{
    init();
    writeConfig(3, 0);
    int cellVolts0[13];
    int cellVolts1[13];
    int cellVolts2[13];
    int discharge0 = 0;
    int discharge1 = 0;
    int i;
    int dischrrge2 = 0;
    int status = GREEN_STATUS;
    writeConfig(3, 0x00);
    while(1)
    {
        readCellVolts(2, cellVolts0);
        readCellVolts(0, cellVolts1);
        readCellVolts(1, cellVolts2);
        status |= checkCellVolts(cellVolts0);
        status |= checkCellVolts(cellVolts1);
        status |= checkCellVolts(cellVolts2);
        status |= checkCurrentSensor(0);
        status |= checkTemperature(1);
        status |= checkTemperature(2);
        status |= checkTemperature(3);
        status |= checkTemperature(4);
        setStatusLEDs(status);
    }
}

void init(){

    TRISAbits.TRISA0 = 0;
    TRISAbits.TRISA1 = 0;
    TRISAbits.TRISA3 = 0;
    TRISAbits.TRISA4 = 0;

    TRISBbits.TRISB5 = 0;

    TRISBbits.TRISB12 = 0;
    TRISBbits.TRISB13 = 1;
    TRISBbits.TRISB14 = 0;
    TRISBbits.TRISB15 = 0;

    TRISBbits.TRISB11 = 1; //chip 3 output
    TRISBbits.TRISB10 = 1; //chip 2 output
    TRISBbits.TRISB9 = 1; //chip 1 output
    TRISBbits.TRISB8 = 0; //CS
    TRISBbits.TRISB7 = 0; //SDI
    TRISBbits.TRISB6 = 0; //SDKI


    AD1PCFGL = 0xFFFF;
    
    //the below lines are commented out until we get the correct chip on the board
    //What was ordered was a MAX3444e, and we need a MAX3440e

    //RPOR2bits.RP4R = 0b00011;

    //U1BRG = BAUDRATE;	//set baud speed
    //U1MODE = 0x8000;	 //turn on module

    //setRelay(RELAY_ON);
    
}
