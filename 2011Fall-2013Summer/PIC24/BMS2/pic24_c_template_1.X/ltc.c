#include "ltc.h"
#include "ADC.h"
#include "main.h"
#include "relay.h"
#include <p24HJ128GP202.h>

//TODO:
//create a function that reads a single battery from the LTC
//create a function that determines if a battery is within range
//create a function to tell LTC to ballance cell
//create a function to read all batteries and update status accordingly

int checkCellVolts(int voltArray[]){
    int status = GREEN_STATUS;
    int i;
    for(i = 0; i<10; i++){
        if(voltArray[i] > 3.6 || voltArray[i] < 2.2 ){
            setRelay(RELAY_OFF);
            status |= RED_STATUS;
        }
        else if(voltArray[i] >= 3.4 || voltArray[i] <= 2.6 ){
            status |= YELLOW_STATUS;
        }
    }
    return status;
} 

void writeConfig(int address, int discharge){
    LATBbits.LATB8 = 0; //pull CS low
    
    sendSPI(WRCFG);
    sendSPI(calcPEC(WRCFG));

    if(address < 3){ //send to a specifc address (less than 3) or broadcast (3 or greater)
        sendSPI(128 + address);
        sendSPI(calcPEC(128 + address));
    }

    sendSPI(CFGR0); //Config register 0 (GPIO settings, LVL poll setting, 10 cell setting, Comparator duty cycle setting)
    int PECConfig = calcPEC(CFGR0);

    //Calculate discharging 1-8 (bitmap)
    sendSPI((char)discharge);
    PECConfig = calcPECMult((char)discharge, (char)PECConfig);

    //calculate discharging 9-12
    discharge = discharge >> 8;
    discharge = discharge & 0b00001111;
    sendSPI(0|discharge); //0 is mask. We dont want to mask any bits.
    PECConfig = calcPECMult(0|discharge, (char)PECConfig);

    sendSPI(0); //no bit masking
    PECConfig = calcPECMult(0, (char)PECConfig);

    sendSPI(LTC_UNDERVOLT);
    PECConfig = calcPECMult(LTC_UNDERVOLT, (char)PECConfig);

    sendSPI(LTC_OVERVOLT);
    PECConfig = calcPECMult(LTC_OVERVOLT, (char)PECConfig);
    sendSPI(PECConfig);
    LATBbits.LATB8 = 1; //pull CS high

}

int calcPEC(int cmd){
    char in0;
    char in1;
    char in2;
    char PEC = 0b01000001;
    int i;
    for(i = 0; i < 8; i++){
        in0 = ((cmd >> (7-i)) & 1) ^ ((PEC >> 7) & 1);
        in1 = (PEC & 1) ^ in0;
        in2 = ((PEC >> 1) & 1) ^ in0;
        in1 = in1 << 1;
        in2 = in2 << 2;
        PEC = ((PEC << 1) & 0b11111000) | (((0 | in2) | in1) | in0);
    }
    return (int)PEC;
}

int calcPECMult(int cmd, char PEC){
    char in0;
    char in1;
    char in2;
    int i;
    for(i = 0; i < 8; i++){
        in0 = ((cmd >> (7-i)) & 1) ^ ((PEC >> 7) & 1);
        in1 = (PEC & 1) ^ in0;
        in2 = ((PEC >> 1) & 1) ^ in0;
        in1 = in1 << 1;
        in2 = in2 << 2;
        PEC = ((PEC << 1) & 0b11111000) | (((0 | in2) | in1) | in0);
    }
    return (int)PEC;
}

void readCellVolts(int address, int voltarray[]){
    int i;
    LATBbits.LATB8 = 0; //pull CS high
    sendSPI(STCVAD);
    sendSPI(calcPEC(STCVAD));
    LATBbits.LATB8 = 1; //pull CS high
    LATBbits.LATB8 = 0; //pull CS low

    sendSPI(RDCV);
    sendSPI(calcPEC(RDCV));

    for(i = 0; i < 12; i++){
        voltarray[i] = receiveSPI(address, 12);
    }
    receiveSPI(address, 8);
    LATBbits.LATB8 = 1; //pull CS high
}
int receiveSPI(int address, int bits){
    int i;
    int ret = 0;
    for(i = 0; i < bits; i++){
        cycleClock();
        ret <<= 1;
        if(address == 0){
            ret |= PORTBbits.RB9;
        }
        else if(address == 1){
            ret |= PORTBbits.RB10;
        }
        else{
            ret |= PORTBbits.RB11;
        }
    }
    return ret;
}

void sendSPI(int cmd){
    int i;
    for(i = 1; i <= 8; i++){
        LATBbits.LATB7 = ((cmd >> (8-i)) & 1);
        cycleClock();
    }
}

void cycleClock(){
    LATBbits.LATB6 = 0;
    LATBbits.LATB6 = 1;
}