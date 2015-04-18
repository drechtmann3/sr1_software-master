#include "relay.h"
#include <p24HJ128GP202.h>

void setRelay(int status){
    if(status == RELAY_ON){
        LATBbits.LATB4 = 1;
    }
    else{
        LATBbits.LATB4 = 0;
    }
}
