//CONFIGURATION REGISTERS

//Config register 0 sets GPIO settings, LVL poll setting, 10 cell setting, comparator duty cycle setting, comparison voltages
//GPIO0 and GPIO1 are low
//Level polling
//10 cell setting
//Comparator duty cycle = 13 ms
#define CFGR0 0x1A
#define CFGR1 0
#define CFGR2 0
#define CFGR3 0x20 //Mask out cells 11 and 12 so that they will not trigger unecessary interrupts
//CFGR4 and CFGR5 are not defined here because they are calculated from the OVvoltages UVvoltages

//LTC CHIP COMMANDS AND PEC

#define WRCFG 0x01 //Write configuration registers
#define WRCFG_PEC 0xC7
#define RDCFG 0x02 //Read configuration registers
#define RDCFG_PEC 0xCE
#define RDCV 0x04 //Read all cell voltages
#define RDCV_PEC 0xDC
#define RDFLG 0x0C //Read flag registers
#define RDFLG_PEC 0xE4
#define STCVAD 0x10 //Start ADC conversions for all cells
#define STCVAD_PEC 0xB0
#define PLADC 0x40 //Poll ADC conversion status
#define PLADC_PEC 0x07
#define STCVDC 0x60 //Start ADC conversions for all cells with discharge permitted
#define STCVDC_PEC 0xE7

// MAXIMUM BATTERY MODULE VOLTAGES
#define MAX_MODULE_VOLTAGE 3.65f
#define MAX_MODULE_VOLTAGE_WARNING 3.6f
#define MIN_MODULE_VOLTAGE 2.5f

//PROTOTYPES

void startCellRead(void); //Initialize ADC conversions
void waitforCells(void); //Wait for ADC conversions to finish
void readVoltages(void); //Fetch raw values of 30 cell voltages from the LTC chip over SPI
void writeConfig(void); //Write to configuration registers of the LTC chips
void readConfig(void); //Read configuration registers from the LTC chips
int calcPEC(Uint16 cmd); //Calculates PEC for a single command
int calcPECMult(Uint16 cmd, Uint16 PEC); //Calculates PEC for multiple sets of 8 bytes
void translateVoltage(volatile Uint16 CVR[], volatile float32 CellVoltages[], volatile float32* min_Voltage, volatile float32* max_Voltage, float32* sum);
float32 vAverage(float32 CellVoltages[]); //Calculate average voltage of 10 cells

//GLOBAL VARIABLES

//Battery Stack Monitor Variables
extern int32 OVthresh; //Overvoltage comparison voltage = (VOV � 32) � 16 � 1.5mV
extern int32 UVthresh; //Undervoltage comparison voltage = (VUV � 31) � 16 � 1.5mV
extern volatile Uint16 bCVR[18]; //Bottom cell voltage readings (raw)
extern volatile Uint16 mCVR[18]; //Middle cell voltage readings (raw)
extern volatile Uint16 tCVR[18]; //Top cell voltage readings (raw)
extern volatile float32 bVoltages[10]; //Bottom cell voltage readings (decimal)
extern volatile float32 mVoltages[10]; //Middle cell voltage readings (decimal)
extern volatile float32 tVoltages[10]; //Top cell voltage readings (decimal)
extern volatile char voltagesTripped[30];
extern float32 minVoltage; //Minimum battery voltage
extern float32 maxVoltage; //Maximum battery voltage
extern float32 averageVoltage; //Average battery voltage
