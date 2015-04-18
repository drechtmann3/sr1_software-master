/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

#if defined(__XC)
    #include <xc.h>        /* XC8 General Include File */
#elif defined(HI_TECH_C)
    #include <htc.h>       /* HiTech General Include File */
#elif defined(__18CXX)
    #include <p18cxxx.h>   /* C18 General Include File */
#endif

#if defined(__XC) || defined(HI_TECH_C)

#include <stdint.h>        /* For uint8_t definition */
#include <stdbool.h>       /* For true/false definition */

#endif
#include <p18f4321.h>
#include "system.h"        /* System funct/params, like osc/peripheral config */
#include "user.h"          /* User funct/params, such as InitApp */

/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/

/* i.e. uint8_t <variable_name>; */

/******************************************************************************/
/* Main Program                                                               */
/******************************************************************************/
#pragma config MCLRE     =    ON
#pragma config OSC      =   INTIO1
#pragma config PBADEN = DIG

void main(void)
{
    /* Configure the oscillator for the device */
  //  ConfigureOscillator();

    /* Initialize I/O and Peripherals for application */
    //InitApp();

    /* TODO <INSERT USER APPLICATION CODE HERE> */
    //ANSELA=0x0;
    TRISA=0;
    long i=0;
    while(1)
    {
        LATA=0xFF;
        for(i=0;i<1000;i++);
        LATA=0;
        for(i=0;i<1000;i++);
    }

}

