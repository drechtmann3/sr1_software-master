#include "BMS.h"

/*
 * This file contains the functions for talking with the LTC chip.
 */

//Battery Stack Monitor Variables
int32 OVthresh = 4200; //Overvoltage comparison voltage
int32 UVthresh = 3200; //Undervoltage comparison voltage
volatile Uint16 bCVR[18]; //Bottom cell voltage readings (raw)
volatile Uint16 mCVR[18]; //Middle cell voltage readings (raw)
volatile Uint16 tCVR[18]; //Top cell voltage readings (raw)
volatile float32 bVoltages[10]; //Bottom cell voltage readings (decimal)
volatile float32 mVoltages[10]; //Middle cell voltage readings (decimal)
volatile float32 tVoltages[10]; //Top cell voltage readings (decimal)
volatile char voltagesTripped[30]; // If modules were tripped.
 float32 minVoltage = -1; //Minimum battery voltage
 float32 maxVoltage = -1; //Maximum battery voltage
 float32 averageVoltage; //Average battery voltage

//Calculates PEC for a single command
//#pragma CODE_SECTION(calcPEC,"ramfuncs");
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

//Calculates PEC for multiple sets of 8 bytes
//#pragma CODE_SECTION(calcPECMult,"ramfuncs");
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

//Write to configuration registers of the LTC chips
//#pragma CODE_SECTION(writeConfig,"ramfuncs");
void writeConfig()
{
	int OVvalue, UVvalue, CFGR4, CFGR5, CFGR_PEC;
	//Calculate comparison voltages for the thresholds
	OVvalue = (int) OVthresh/24+31;
	UVvalue = (int) UVthresh/24+32;
	CFGR4 = (Uint16) UVvalue;
	CFGR5 = (Uint16) OVvalue;
	//Calculate PEC
	CFGR_PEC = calcPEC(CFGR0);
	CFGR_PEC = calcPECMult(CFGR1,CFGR_PEC);
	CFGR_PEC = calcPECMult(CFGR2,CFGR_PEC);
	CFGR_PEC = calcPECMult(CFGR3,CFGR_PEC);
	CFGR_PEC = calcPECMult(CFGR4,CFGR_PEC);
	CFGR_PEC = calcPECMult(CFGR5,CFGR_PEC);
	//Write to the 3 registers
	SpiSend(WRCFG);
	SpiSend(calcPEC(WRCFG));
	SpiSend(CFGR0);
	SpiSend(CFGR1);
	SpiSend(CFGR2);
	SpiSend(CFGR3);
	SpiSend(CFGR4);
	SpiSend(CFGR5);
    SpiSend(CFGR_PEC);
	SpiSend(CFGR0);
	SpiSend(CFGR1);
	SpiSend(CFGR2);
	SpiSend(CFGR3);
	SpiSend(CFGR4);
	SpiSend(CFGR5);
	SpiSend(CFGR_PEC);
	SpiSend(CFGR0);
	SpiSend(CFGR1);
	SpiSend(CFGR2);
	SpiSend(CFGR3);
	SpiSend(CFGR4);
	SpiSend(CFGR5);
	SpiSend(CFGR_PEC);
}

//Read configuration registers from the LTC chips
//TODO readConfig is out of date, but only needed for debugging purposes

/*void readConfig()
{
	int dummy = 0;

	//Necessary wait time
	while(dummy < 100)
	{
		dummy++;
	}
	SpiSend(RDCFG);
	SpiSend(RDCFG_PEC);
	SpiReceive();

	for (testPurposes=0; testPurposes<8; testPurposes++)
	{
		ConfigBytes[testPurposes] = SpiReceive();
	}
}*/


//Initialize ADC conversions
//#pragma CODE_SECTION(startCellRead,"ramfuncs");
void startCellRead()
{
	int wait = 0;
	//Necessary wait time
	while(wait < 100)
	{
		wait++;
	}
	SpiSend(STCVAD);
	SpiSend(calcPEC(STCVAD));
}

//Wait for ADC conversions to finish
//#pragma CODE_SECTION(waitforCells,"ramfuncs");
void waitforCells()
{

	int ready = 0;
	int result = 0;
	while(!ready) {
		SpiSend(PLADC);
		SpiSend(calcPEC(PLADC));
		SpiReceive();
		result = SpiReceive();
		if (result!=0) {
			ready = 1;
		}
	}
	//DELAY_US(12e3L); // 10ms delay
}

//Fetch raw values of 30 cell voltages from the LTC chip over SPI
//#pragma CODE_SECTION(readVoltages,"ramfuncs");
void readVoltages() {
	volatile int dummy = 0;
	int i = 0;
	float32 sum = 0;
	float32 max_Voltage = -1;
	float32 min_Voltage = -1;
	volatile Uint16 received_PEC_bottom=0;
	volatile Uint16 received_PEC_middle=0;
	volatile Uint16 received_PEC_top=0;
	volatile Uint16 calculated_PEC_bottom=0;
	volatile Uint16 calculated_PEC_middle=0;
	volatile Uint16 calculated_PEC_top=0;

	while(dummy < 100)
	{
		dummy++;
	}
	dummy = 0;
	//SpiSend(RDFLG);
	//SpiSend(calcPEC(RDFLG));
	/*
	bFLG[0]=SpiReceive();
	bFLG[1]=SpiReceive();
	bFLG[2]=SpiReceive();
	if (bFLG[0] == 1 || bFLG[1] == 1 || bFLG[2] == 1)
	{
		//send error to CAN
		GpioDataRegs.GPACLEAR.bit.GPIO9 = 1;//packCutoffRelay = 0;
		GpioDataRegs.GPACLEAR.bit.GPIO28 = 1;
		bVoltageBad = 1;
	}
	*/
	//Necessary wait time
	while(dummy < 100)
	{
		dummy++;
	}
	dummy = 0;

	SpiSend(RDCV);
	SpiSend(calcPEC(RDCV));
	SpiReceive(); //Ignore echo //WORKS WHEN UNCOMMENTED
	//Read in 15 registers from bottom device
	for (i=0;i<15;i++)
	{
		bCVR[i]=SpiReceive();
	}
	received_PEC_bottom = SpiReceive(); //received bottom PEC

	//Read in 15 registers from middle device
	for (i=0;i<15;i++)
	{
		mCVR[i]=SpiReceive();
	}
	received_PEC_middle = SpiReceive(); //received bottom PEC

	//Read in 15 registers from bottom device
	for (i=0;i<15;i++)
	{
		tCVR[i]=SpiReceive();
	}
	received_PEC_top = SpiReceive(); //received bottom PEC

	//Calculate PECs for each group of raw cell data
	calculated_PEC_bottom = calcPEC(bCVR[0]); //calculate the PEC of the first byte
	for (i=1;i<15;i++)
	{
		calculated_PEC_bottom = calcPECMult(bCVR[i], calculated_PEC_bottom); // calculate the final PEC through consecutive shifting
	}

	calculated_PEC_middle = calcPEC(mCVR[0]); //calculate the PEC of the first byte
	for (i=1;i<15;i++)
	{
		calculated_PEC_middle = calcPECMult(mCVR[i], calculated_PEC_middle); // calculate the final PEC through consecutive shifting
	}

	calculated_PEC_top = calcPEC(tCVR[0]); //calculate the PEC of the first byte
	for (i=1;i<15;i++)
	{
		calculated_PEC_top = calcPECMult(tCVR[i], calculated_PEC_top); // calculate the final PEC through consecutive shifting
	}

	//Translate data into readable voltages if group PEC is calculated and matches the received group PEC
	//Keeps track of min, max, average
	
	if(received_PEC_bottom==calculated_PEC_bottom)
	{
		translateVoltage(bCVR, bVoltages, &min_Voltage, &max_Voltage, &sum);
	}
	if(received_PEC_middle==calculated_PEC_middle)
	{
		translateVoltage(mCVR, mVoltages, &min_Voltage, &max_Voltage, &sum);
	}
	if(received_PEC_top==calculated_PEC_top)
	{
		translateVoltage(tCVR, tVoltages, &min_Voltage, &max_Voltage, &sum);
	}

	//Put battery voltage statistics to global scope
	minVoltage = min_Voltage;
	maxVoltage = max_Voltage;
	averageVoltage = sum/30;
}

//Translates the raw data received from the LTC chip into decimal voltages while calculating min, max, and sum
//#pragma CODE_SECTION(translateVoltage,"ramfuncs");
void translateVoltage(volatile Uint16 CVR[], volatile float32 CellVoltages[], volatile float32* min_Voltage, volatile float32* max_Voltage, float32* sum)
{
	int bits = 0;
	int i;
	int vtgcnt = 0;
	Uint16 CellVolts[12];

	for(i = 0; i < 12; i++){
		if(i % 2 == 0){
			CellVolts[i] = CVR[bits] | ((CVR[bits+1]&0x0F)<<8);
			bits++;
		}else{
			CellVolts[i] = (CVR[bits]>>4)|(CVR[bits+1]<<4);
			bits += 2;
		}
	}



	for (vtgcnt = 0; vtgcnt <= 9; vtgcnt++)
	{
		CellVoltages[vtgcnt] = (CellVolts[vtgcnt]-512)*1.500/1000.000;
//		if(CellVoltages[vtgcnt]>90){//TODO - fix! quick hack
//			CellVoltages[vtgcnt] = 3.2;
//		}
		if (*min_Voltage == -1 || CellVoltages[vtgcnt] < *min_Voltage){
			*min_Voltage = CellVoltages[vtgcnt];
		}
		if (*max_Voltage == -1 || CellVoltages[vtgcnt] > *max_Voltage){
			*max_Voltage = CellVoltages[vtgcnt];
		}
		*sum+=CellVoltages[vtgcnt];
	}
}

//Calculate average voltage of 10 cells
//#pragma CODE_SECTION(vAverage,"ramfuncs");
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
