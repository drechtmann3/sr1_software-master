#include "LED.h"
#include <p24HJ128GP202.h>

void setStatusLEDs(int status){
    //use bit masks to determine the correct status bit, and set the leds properly
    if(((status << 3) & 0b1000) > 0){
        green(1);
    }else{
        green(0);
    }


    if(((status << 2) & 0b1000) > 0){
        yellow2(1);
    }else{
        yellow2(0);
    }

    if(((status << 1) & 0b1000) > 0){
        yellow1(1);
    }else{
       yellow1(0);
    }

    if((status & 0b1000) > 0){
        red(1);
    }else{
        red(0);
    }
}

void red(int in)
{
    if (in==1){
        LATAbits.LATA0 = 1;
    }
    else {
        LATAbits.LATA0 = 0;
    }
}

void yellow1(int in)
{
    if (in==1){
        LATAbits.LATA1 = 1;
    }
    else {
        LATAbits.LATA1 = 0;
    }
}

void yellow2(int in)
{
    if (in==1){
        LATAbits.LATA3 = 1;
    }
    else {
        LATAbits.LATA3 = 0;
    }
}

void green (int in)
{
    if (in==1){
        LATAbits.LATA4 = 1;
    }
    else {
        LATAbits.LATA4 = 0;
    }
}
