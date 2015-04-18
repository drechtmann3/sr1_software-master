#include "LED.h"
#include <p24HJ128GP202.h>

void setCritical(int in)
{
    if (in>=1){
        LATAbits.LATA3 = LED_ON;
    }
    else {
        LATAbits.LATA3 = LED_OFF;
    }
}

void setWarn1(int in)
{
    if (in>=1){
        LATAbits.LATA0 = LED_ON;
    }
    else {
        LATAbits.LATA0 = LED_OFF;
    }
}

void setWarn2(int in)
{
    if (in>=1){
        LATAbits.LATA1 = LED_ON;
    }
    else {
        LATAbits.LATA1 = LED_OFF;
    }
}
