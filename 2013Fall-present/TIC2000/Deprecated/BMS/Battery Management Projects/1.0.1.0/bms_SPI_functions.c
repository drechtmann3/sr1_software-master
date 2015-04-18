/*
 * Georgia Tech Solar Racing
 * Battery Management System Source Code
 * Microcontroller: Texas Instruments Piccolo Series - TMS320F28069
 * Originator: Fred Chen (tm602502@gmail.com)
 * Contributor: Leonardo Bernal (leo.esteban.bernal@gmail.com)
 * Date: 06/03/2014
 * Version: 1.0.1.0
 */

#include "F2806x_Device.h"
#include <math.h>
#include "main.h"
#include "F2806x_PieVect.h"
#include <stdlib.h>

// Global Variables
int aaa;
int Index;
int dummyy;
//Added on 05/24/2014:
void bVoltage();
void mVoltage();
void tVoltage();

int bVoltageBad = 0;
int mVoltageBad = 0;
int tVoltageBad = 0 ;

Uint16 bFLG[3];
Uint16 mFLG[3];
Uint16 tFLG[3];

Uint16 bCVR[15];
Uint16 mCVR[15];
Uint16 tCVR[15];

float32 tVAvg = 0;
float32 bVAvg = 0;
float32 mVAvg = 0;

// SPI Variables


// CAN Variables
//float32 CellVoltages[10];
int32 CellVolts[10];
//float32 vAverage;
float32 t_vAverage;
float32 m_vAverage;
float32 b_vAverage;
float32 mVoltages[];
float32 bVoltages[];
float32 tVoltages[];
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

void bVoltage()
{
	int dummy = 0;
	int i = 0;
	while(dummy < 100)
	{
		dummy++;
	}dummy = 0;
	//..........................................
		SpiSend(BOTTOMCHIP);
		SpiSend(calcPEC(BOTTOMCHIP));
	//..........................................
	SpiSend(RDFLG);
	SpiSend(calcPEC(RDFLG));
	bFLG[0]=receiveSPI();
	bFLG[1]=receiveSPI();
	bFLG[2]=receiveSPI();
	if (bFLG[0] == 1 || bFLG[1] == 1 || bFLG[2] == 1)
	{
		//send error to CAN
		GpioDataRegs.GPACLEAR.bit.GPIO9 = 1;//packCutoffRelay = 0;
		GpioDataRegs.GPACLEAR.bit.GPIO28 = 1;
		bVoltageBad = 1;
		//break;
	}
	//VoltageBad = 0;
	while(dummy < 100)
	{
		dummy++;
	}dummy = 0;
	//..........................................
		SpiSend(BOTTOMCHIP);
		SpiSend(calcPEC(BOTTOMCHIP));
	//..........................................
	SpiSend(RDCV);
	SpiSend(calcPEC(RDCV));
	receiveSPI();
	for (i=0;i<15;i++)
	{
		bCVR[i]=receiveSPI();
	}
	//lightUpLED(1000);
	translateVoltage(bCVR, bVoltages);

}

void mVoltage()
{
	int dummy = 0;
	int i = 0;
	while(dummy < 100)
	{
		dummy++;
	}dummy = 0;
	//..........................................
		SpiSend(MIDDLECHIP);
		SpiSend(calcPEC(MIDDLECHIP));
	//..........................................
	SpiSend(RDFLG);
	SpiSend(calcPEC(RDFLG));
	mFLG[0]=receiveSPI();
	mFLG[1]=receiveSPI();
	mFLG[2]=receiveSPI();
	if (mFLG[0] == 1 || mFLG[1] == 1 || mFLG[2] == 1)
	{
		//send error to CAN
		GpioDataRegs.GPACLEAR.bit.GPIO9 = 1;//packCutoffRelay = 0;
		GpioDataRegs.GPACLEAR.bit.GPIO28 = 1;
		mVoltageBad = 1;
		//break;
	}
	//VoltageBad = 0;
	while(dummy < 100)
	{
		dummy++;
	}dummy = 0;
//..........................................
	SpiSend(MIDDLECHIP);
	SpiSend(calcPEC(MIDDLECHIP));
//..........................................
	SpiSend(RDCV);
	SpiSend(calcPEC(RDCV));
	receiveSPI();
	for (i=0;i<15;i++)
	{
		mCVR[i]=receiveSPI();
	}
	//lightUpLED(1000);
	translateVoltage(mCVR, mVoltages);
}

void tVoltage()
{
	int dummy = 0;
	int i = 0;
	while(dummy < 100)
	{
		dummy++;
	}dummy = 0;
	//..........................................
		SpiSend(TOPCHIP);
		SpiSend(calcPEC(TOPCHIP));
	//..........................................
	SpiSend(RDFLG);
	SpiSend(calcPEC(RDFLG));
	tFLG[0]=receiveSPI();
	tFLG[1]=receiveSPI();
	tFLG[2]=receiveSPI();
	if (tFLG[0] == 1 || tFLG[1] == 1 || tFLG[2] == 1)
	{
		//send error to CAN
		GpioDataRegs.GPACLEAR.bit.GPIO9 = 1;//packCutoffRelay = 0;
		GpioDataRegs.GPACLEAR.bit.GPIO28 = 1;
		tVoltageBad = 1;
		//break;
	}
	//VoltageBad = 0;
	while(dummy < 100)
	{
		dummy++;
	}dummy = 0;
	//..........................................
		SpiSend(TOPCHIP);
		SpiSend(calcPEC(TOPCHIP));
	//..........................................
	SpiSend(RDCV);
	SpiSend(calcPEC(RDCV));
	receiveSPI();
	for (i=0;i<15;i++)
	{
		tCVR[i]=receiveSPI();
	}
	//lightUpLED(1000);
	translateVoltage(tCVR, tVoltages);
	tVAvg = vAverage(tVoltages);
}

//void readCellVolts(Uint16 voltarray[]){
//    int ii;
//    Uint32 dum = 0;
//    SpiSend(STCVDC);
//    SpiSend(calcPEC(STCVDC));
//    SpiSend(PLADC);
//    SpiSend(calcPEC(PLADC));
//    while (dum < 200000)
//    {
//    	dum++;
//    }dum = 0;
//
//    SpiSend(RDCV);
//    while (!SpiaRegs.SPISTS.bit.INT_FLAG){}
//    for(ii = 0; ii < 15; ii++){
//        voltarray[ii] = receiveSPI();
//    }
//}

void translateVoltage(Uint16 CVRMtx[], float32 CellVoltages[])
{
	int vtgcnt = 0;
    CellVolts[0] = (CVRMtx[0] & 0xFF) | (CVRMtx[1] & 0x0F) << 8;
    CellVolts[1] = (CVRMtx[1] & 0xF0) >> 4 | (CVRMtx[2] & 0xFF) << 4;
    CellVolts[2] = (CVRMtx[3] & 0xFF) | (CVRMtx[4] & 0x0F) << 8;
    CellVolts[3] = (CVRMtx[4] & 0xF0) >> 4 | (CVRMtx[5] & 0xFF) << 4;
    CellVolts[4] = (CVRMtx[6] & 0xFF) | (CVRMtx[7] & 0x0F) << 8;
    CellVolts[5] = (CVRMtx[7] & 0xF0) >> 4 | (CVRMtx[8] & 0xFF) << 4;
    CellVolts[6] = (CVRMtx[9] & 0xFF) | (CVRMtx[10] & 0x0F) << 8;
    CellVolts[7] = (CVRMtx[10] & 0xF0) >> 4 | (CVRMtx[11] & 0xFF) << 4;
    CellVolts[8] = (CVRMtx[12] & 0xFF) | (CVRMtx[13] & 0x0F) << 8;
    CellVolts[9] = (CVRMtx[13] & 0xF0) >> 4 | (CVRMtx[14] & 0xFF) << 4;
    for (vtgcnt = 0; vtgcnt <= 9; vtgcnt++)
    {
    	CellVoltages[vtgcnt] = (CellVolts[vtgcnt]-512)*1.500/1000.000;
    }

}

float32 vAverage(float32 CellVoltages[])
{
	int vtgcnt = 0;
	float32 vAverage = 0;
	for (vtgcnt = 0; vtgcnt <= 9; vtgcnt++)
	    {
	    	vAverage = vAverage + CellVoltages[vtgcnt]/10.0;
	    }
	return vAverage;
}
