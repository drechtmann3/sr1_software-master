#include "F2806x_Device.h"
#include <math.h>
#include "BMS.h"
#include "F2806x_PieVect.h"
#include <stdlib.h>

// Global Variables
int aaa;
int Index;
int dummyy;

int calcPEC(Uint16 Command){
    char in0;
    char in1;
    char in2;
    int PEC = 0x41;
    int ii;

    for(ii = 0; ii < 8; ii++)
    {
        in0 = ((Command >> (7-ii)) & 1) ^ ((PEC >> 7) & 1);
        in1 = (PEC & 1) ^ in0;
        in2 = ((PEC >> 1) & 1) ^ in0;
        in1 = in1 << 1;
        in2 = in2 << 2;
        PEC = ((PEC << 1) & 248) | (((0 | in2) | in1) | in0);
    }
    return (int)PEC;
}

int calcPECMult(Uint16 cmd, Uint16 PEC){
    char in0;
    char in1;
    char in2;
    int ii;
    for (ii = 0; ii < 8; ii++){
        in0 = ((cmd >> (7-ii)) & 1) ^ ((PEC >> 7) & 1);
        in1 = (PEC & 1) ^ in0;
        in2 = ((PEC >> 1) & 1) ^ in0;
        in1 = in1 << 1;
        in2 = in2 << 2;
        PEC = ((PEC << 1) & 248) | (((0 | in2) | in1) | in0);
    }
    return (int)PEC;
}

void SpiSend(Uint16 Command){

	//Enabling conversation between master and slave

	SpiaRegs.SPITXBUF = (Command << 8);

	while(SpiaRegs.SPISTS.bit.BUFFULL_FLAG != 0){}
	aaa |= SpiaRegs.SPIRXBUF;
}

int receiveSPI(){
	//Disabling conversation between master and slave
	Uint16 ret = 0;

    SpiaRegs.SPITXBUF = 0 << 8;
    while(SpiaRegs.SPISTS.bit.BUFFULL_FLAG != 0 || SpiaRegs.SPISTS.bit.INT_FLAG == 0){}
    ret = SpiaRegs.SPIRXBUF;
    return ret;
}

void readCellVolts(Uint16 voltarray[]){
    int ii;
    Uint32 dum = 0;
    SpiSend(STCVDC);
    SpiSend(calcPEC(STCVDC));
    SpiSend(PLADC);
    SpiSend(calcPEC(PLADC));
    while (dum < 200000)
    {
    	dum++;
    }dum = 0;

    SpiSend(RDCV);
    while (!SpiaRegs.SPISTS.bit.INT_FLAG){}
    for(ii = 0; ii < 15; ii++){
        voltarray[ii] = receiveSPI();
    }
}

