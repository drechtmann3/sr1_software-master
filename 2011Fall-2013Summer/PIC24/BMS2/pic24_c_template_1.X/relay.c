#include "relay.h"
#include <p24HJ128GP202.h>

void setRelay(int status){
    if(status == RELAY_ON){
        LATBbits.LATB5 = 1;
    }
    else{
        LATBbits.LATB5 = 0;
    }
}
