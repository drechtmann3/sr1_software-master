/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

#include <GenericTypeDefs.h>       /* For true/false definition */

#include <system.h>        /* System funct/params, like osc/peripheral config */
#include <user.h>          /* User funct/params, such as InitApp */
#include <cancom.h>
/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/

/* i.e. uint8_t <variable_name>; */

/******************************************************************************/
/* Main Program                                                               */
/******************************************************************************/

void main(void)
{
    /* Configure the oscillator for the device */
    ConfigureOscillator();

    /* Initialize I/O and Peripherals for application */
    InitApp();

    /* TODO <INSERT USER APPLICATION CODE HERE> */

    while(1)
    {
        sendTestString();
    }

}

