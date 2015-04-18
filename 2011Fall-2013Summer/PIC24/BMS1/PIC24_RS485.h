#include "p24HJ64GP502.h"


typedef struct RS485_Ascii_Data{
 char* asciiData;
 int length;
}AsciiData;

typedef struct Device_Identifiers{
 char deviceType[2];//two char description of device
 char deviceAddress[2];
 unsigned long clockFreq;
}DeviceIdentifiers;


//RS485 specific functions and conversion helper functions
void initRS485(DeviceIdentifiers givenType, unsigned int length, unsigned int deviceData[]);
int ASCIIToHex(char convert[], unsigned char length);
void intToASCIIHex(unsigned int convert,unsigned char* result);
void charToASCIIHex(unsigned char convert,unsigned char* result);
void shortToASCIIHex(short convert,unsigned char* result);
void doubleToASCIIHex(double convert,unsigned char* result);


//UART specific functions 
void initUART(unsigned long clockFreq);
void UART1PutString(char* chars, int length);
void UART1PutChar(char);
void RS485processRX();

#define MAX_RX_BYTES (3)
#define MAX_TX_BYTES (4)
#define RS_485_MAX_RX_DATA_BYTES (12)
#define RS_485_RX_BYTE_FIFO_SIZE (15)
#define RS_485_TX_BYTE_FIFO_SIZE (153)
#define RS_485_RX_TEMP_FIELD_SIZE (12)
#define EOL_CHAR 0x0D

#define RS_485_NUM_ADDRESS_BYTES 	(2)
#define RS_485_NUM_MSGTYPE_BYTES 	(4)
#define RS_485_NUM_KNOWN_CMDS		(9)
#define RS_485_NUM_DATALENGTH_BYTES (4)
#define RS_485_NUM_CHECKSUM_BYTES 	(2)
#define PING_LENGTH (13)
#define RS_485_DATALENGTH_INDEX (6)

//RS-485 states
#define RS_485_IDLE (0)
#define RS_485_LISTEN_MSGTYPE (1)
#define RS_485_LISTEN_DATALENGTH (2)
#define RS_485_LISTEN_DATA (3)
#define RS_485_LISTEN_CHECKSUM (4)
#define RS_485_LISTEN_EOL (5)
#define RS_485_EVAL_CHECKSUM (6)
#define RS_485_POST_CMD_DELAY (7)
#define RS_485_TX_ADR (8)

//RS-485 messages
#define RS_485_PING_CMD (0)
#define RS_485_MP_ON_CMD 	(1)
#define RS_485_MP_OFF_CMD 	(2)
#define RS_485_MP_LOW_CMD 	(3)
#define RS_485_BMS_ON_CMD 	(4)
#define RS_485_BMS_OFF_CMD 	(5)
#define RS_485_MPST_CMD 	(6)
#define RS_485_BMST_CMD 	(7)
#define RS_485_ACKNOWLEDGE 	(8)
#define RS_485_ACK_RESPONSE_LENGTH (13)
#define RS_485_BMS_STATUS_RESPONSE_LENGTH (185)
#define RS_485_MPPT_STATUS_RESPONSE_LENGTH (53)
#define RS_485_MPPT_STATUS_LENGTH (10)
#define RS_485_BMS_STATUS_LENGTH (43) 

#define RS_485_INTRA_MSG_TIME_OUT_H (0x180)	// 10 bits of send time + 4 bits timeout 
#define RS_485_INTRA_MSG_TIME_OUT_L (0x00)  // at 115200 baud
#define RS_485_POST_CMD_DELAY_H (0x00FF)		//512 ticks for 4 bits worth at 115200
#define RS_485_POST_CMD_DELAY_L (0) 	//yup.
#define RS_485_POST_CMD_TIME_OUT_H	(0xF6)	//40 bit times
#define RS_485_POST_CMD_TIME_OUT_L	(0x00)
