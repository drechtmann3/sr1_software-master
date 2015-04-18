#include <p24HJ64GP502.h>

//Function 
void initRS485(char deviceType,unsigned int* data[], unsigned char address[]);
void initUART();
void initCRC();
void initTimer2( void );
void initial();
void rs485resetState();
void GetData();
void RS485processRX();
void ASCII();
void ASCII4Sign();
void ASCII4();
void rs485PopulateTXByteFIFO();
void UART2PutString(char* chars, int length);
void UART2PutChar(char);
unsigned char rs485findCommandType(unsigned char RXCommand[]);
void GeneratePicCRC(unsigned char generateFrom[],unsigned char size);
unsigned char generateCRC8(unsigned char generateFrom[],unsigned char size);
int ASCIIToHex(char convert[],char length);
void intToASCIIHex(int convert,char* result);
void charToASCIIHex( char convert,char* result);

extern unsigned char MPPT_On;
extern unsigned char MPPT_Off;
extern unsigned char BMS_On;
extern unsigned char BMS_Off;
extern unsigned char MPPT_Low;

#define TYPE_BMS (0)
#define TYPE_MPPT (1)

#define MAX_RX_BYTES (3)
#define MAX_TX_BYTES (4)
#define RS_485_MAX_RX_DATA_BYTES (12)
#define RS_485_RX_BYTE_FIFO_SIZE (15)
#define RS_485_TX_BYTE_FIFO_SIZE (155)
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
#define RS_485_BMS_STATUS_RESPONSE_LENGTH (153)
#define RS_485_MPPT_STATUS_RESPONSE_LENGTH (53)
#define RS_485_MPPT_STATUS_LENGTH (10)
#define RS_485_BMS_STATUS_LENGTH (35) 

#define RS_485_INTRA_MSG_TIME_OUT_H (0x180) 
#define RS_485_INTRA_MSG_TIME_OUT_L (0x00) 
#define RS_485_POST_CMD_DELAY_H (0x00FF)	
#define RS_485_POST_CMD_DELAY_L (0) 	
#define RS_485_POST_CMD_TIME_OUT_H	(0x6)	//40 bit times
#define RS_485_POST_CMD_TIME_OUT_L	(0x00)
#define RS_485_MASTER_ADR_0 (0x31)
#define RS_485_MASTER_ADR_1 (0x32)

//Old defines no longer used
/*
#define RS_485_WnR_PIN (PORTDbits.RD4)
#define RS_485_WRITE (1)
#define RS_485_READ (0)
#define FOREVER 1							// endless 
#define Delay(x) DELAY = x; while(--DELAY){ Nop(); Nop(); }
#define TXascii(in)  TXREG = in; while(!TXSTAbits.TRMT)
#define newLine() TXascii('\r'); TXascii('\n');               // Send carriage return and line feed
#define Ascii2Dec(IN) {ASC2DOUT = IN; ASC2DOUT -= 0x30;	if (ASC2DOUT >> 4)	ASC2DOUT -= 7;}
*/

