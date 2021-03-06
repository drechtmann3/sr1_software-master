#ifndef BMSHEADER_H_GUARD
#define BMSHEADER_H_GUARD

#define CFGR0 0x1A
#define WRCFG 0x01
#define WRCFG_PEC 0xC7
#define RDCV 0x04
#define STCVDC 0x60
#define STCVAD 0x10
#define PLADC 0x40
#define PEC_PLADC 0x07
#define RDCFG 0x02
#define RDCFG_PEC 0xCE
#define RDFLG 0x0C
#define BOTTOMCHIP 0x80
#define MIDDLECHIP 0x81
#define TOPCHIP 0x82

/*** Prototypes ***/
// Initialize Functions
void SysClkInit();
void GpioInit();
void SpiInit();
void TmrInit();
void AdcInit();

// Other
void testSPI();
void Delay();
void changeConfig_1();
void changeConfig_2();
void sendCommandGroups();
void gettingVoltageReadings();

void DataRecord();
void AdcRead();
void startCellRead();
void waitforCells();
void readVoltages();
void writeConfig();
void readConfig();
float checkSOC();

void lightUpLED(Uint32 Interval);
int calcPEC(Uint16 cmd);
int calcPECMult(Uint16 cmd, Uint16 PEC);
void readCellVolts(Uint16 voltarray[]);
int receiveSPI();

//int checkCellVolts(int voltArray[]);
void balanceCell(int Cell[]);
void clearBalance(int Cell[]);
void SpiSend();
void SpiReceive();
float32 getMin(float32 arr[], int arr_size);
float32 randRange(double min, double max);
float ArraySumInt(float a[], int num_elements);
float ArraySumFloat(float32 array[], int num_elements);

void translateVoltage(Uint16 CVRMtx[], float32 CellVoltages[]);

float32 vAverage(float32 CellVoltages[]);


void tVoltage();
void mVoltage();
void bVoltage();

#endif
