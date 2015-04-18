#ifndef bms_h
#define bms_h

//#includes
#include "ltc6802-1.h"

// System settings
_FWDT(FWDTEN_OFF);              //Watchdog timer off
_FOSCSEL(IESO_OFF & FNOSC_PRI); // External Oscillator Selected
//_FOSCSEL(FNOSC_FRC);

// globals
//#define TEST_STACK 0	
#ifdef TEST_STACK
	#define NUM_LTCs (2)
	#define CELLCNT	(8)
#else
	#define NUM_LTCs (3)
	#define CELLCNT (30)
#endif
#define STATE_CNT	60		// Total number of states in the state buffer
// #defines
#define PERIOD  0xFFFF
// #define utility functions
// globals
unsigned char tempBuffer;  	// SPI usage buffer
typedef struct _t{            // timer state struct
    short ovrflw;			// The timer has overflwed the avalible BMS states
    int   cnt;				//
}_timer;
typedef struct _sb{
	// Buffer Status
	unsigned char active;
	unsigned short length;
	unsigned short cnt;  
	unsigned short write;
	// Data
	unsigned char out[50];
	unsigned char in[50];
	unsigned char cmd;
}_SPIbuff;
typedef struct{
	LTCcontrol LTCstate[NUM_LTCs];
    double temp[4];
    double curr;
    short voltage[30];
}BMSstate;

BMSstate BMS;					// The state of the system
_timer timer;					// The state of the timer
unsigned short cBMS_s;			// The current BMS state
LTCcontrol LTCwrite[NUM_LTCs];	// LTC write buffer
unsigned short activeLTC;		// The LTC currently being written/read (CS is high for this chip)
_SPIbuff comBuffer;
unsigned char cellVoltageBytes[30];
unsigned char tempBytes[5];
/////// Function declarations
int main();
// Config Functions
void configPins();
void configSPI1();
void configLTC();
void configTimer();
// SPI Communication Functions
void spiStartCom(unsigned short LTCsel);
void spiStopCom(unsigned short LTCsel);
void spicom(unsigned short LTCsel,unsigned short state);
void sendCommunication(unsigned char command,unsigned char* data,int length,unsigned char write);
void sendCommand(unsigned char data);
unsigned char runSPI1(unsigned char);
// UART communicatino functions
void writeUART(unsigned char data);
unsigned char readUART();
//// Utility Functions
void debugLed(unsigned char);
void ReadHallEffect(void);
void ReadHallEffectFunction(void);
//// Support Functions
// The following functions Modify the BMS structure
// Edit: TO DO these functions
void processCellBytes(unsigned char numLTC); // Convert the Bytes to the cell voltages
// ^ Cell Bytes come from the comBuffer when Cell Stack is read 
void processTempBytes(unsigned char numLTC); // Covert to the actual temp
// ^ Temp Bytes come from the comBuffer when temp is read 
void processCurrBytes(); // Convert the Current to the actual Current amount
//^ Current Byte comes from ADC Convertion 
void checkRelay(void);		 // Does the relay need to be actuated
void checkDischarge();
///////////////////
#endif
