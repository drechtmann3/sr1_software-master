#include "F2806x_Device.h"
#include <math.h>
#include "Header.h"
#include "F2806x_PieVect.h"
#include <stdlib.h>
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
        //PEC = ((PEC << 1) & 0b11111000) | (((0 | in2) | in1) | in0);
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

void SpiSend(Uint16 Command)
{			//Enabling conversation between master and slave

	SpiaRegs.SPITXBUF = (Command << 8);
//	while(dummyy < 60)
//	{
//		dummyy++;
//	}
	while(SpiaRegs.SPISTS.bit.BUFFULL_FLAG != 0){}
	aaa |= SpiaRegs.SPIRXBUF;
	//while(SpiaRegs.SPISTS.bit.BUFFULL_FLAG != 0) {}
	//aaa |= SpiaRegs.SPIRXBUF;
}



int receiveSPI(){
			//Disabling conversation between master and slave
	Uint16 ret = 0;

    SpiaRegs.SPITXBUF = 0 << 8;
    while(SpiaRegs.SPISTS.bit.BUFFULL_FLAG != 0 || SpiaRegs.SPISTS.bit.INT_FLAG == 0){}
    ret = SpiaRegs.SPIRXBUF;
//    while(SpiaRegs.SPISTS.bit.INT_FLAG == 0) {}
////    while(Index < 50)
////    {	Index ++;}
////    Index = 0;
//    ret = SpiaRegs.SPIDAT;
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

    //receiveSPI(8);
    //LATBbits.LATB8 = 1; //pull CS high
}

//void balanceCell(int Cell[])
//{
//	int Counter;
//	int CFGR1or2 = 0;
//	for (Counter = 0; Counter<9; Counter++)
//	{
//	if (0 < Cell[Counter+1] < 9)								//Iterate Cell array to check if any cell needs balance.
//															//Since cell 1-8 is controlled by CFGR2, and cell 9 is controlled by CFGR3, there needs to be a if statement checking cells names.
//	{
//		CFGR1 = CFGR1 + (int)(pow(2,(Cell[Counter]-1)));
//		CFGR1or2 = 1;
//		/*
//		 *
//		 */
//	}
//	else if (Cell[Counter+1] == 9)
//	{
//		CFGR2 = 1;
//		CFGR1or2 = 2;
//	}
//	}
//    SpiSend(WRCFG);
//
//    if (CFGR1or2 == 1)
//    {
//    	SpiSend(CFGR1);
//    }
//    else if (CFGR1or2 == 2)
//    {
//    	SpiSend(CFGR2);
//    }
//
//}
//
//void clearBalance(int Cell[])
//{
//	int Counter;
//	int CFGR1or2 = 0;
//	for (Counter = 0; Counter<9; Counter++)
//	{
//		if (0 < Cell[Counter+1] < 9)
//		{
//			CFGR1 = CFGR1 - (int)(pow(2,(Cell[Counter]-1)));
//			CFGR1or2 = 1;
//		}
//		else if (Cell[Counter+1] == 9)
//		{
//			CFGR2 = 0;
//			CFGR1or2 = 2;
//		}
//	}
//
//    SpiSend(WRCFG);
//    if (CFGR1or2 == 1)
//    {
//    	SpiSend(CFGR1);
//    }
//    else if (CFGR1or2 == 2)
//    {
//    	SpiSend(CFGR2);
//    }
//
//
//}
