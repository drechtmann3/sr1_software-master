/**
* @ingroup telemetry
* @defgroup rs485bms RS485BMS
* @brief RS485 for BMS. Still needed?
* 
* @{
*/

#include <stdio.h>
#include <stdlib.h>
#include "string.h"

#include "../lib7800/RS485.h"
#include "RS485BMSCom.h"

//#define DEBUG 1

#define EOL_CHAR (0X0D)

#define RS_485_NUM_ADDRESS_BYTES 	(2)
#define RS_485_NUM_MSGTYPE_BYTES 	(4)
#define RS_485_NUM_KNOWN_CMDS		(11)
#define RS_485_COMMAND_LENGTH 		(4)
#define RS_485_NUM_DATALENGTH_BYTES 	(4)
#define RS_485_NUM_CHECKSUM_BYTES 	(2)

#define RS_485_DATALENGTH_INDEX (6)

#define NUM_BMS (4)
#define NUM_MPPT (0)

#define MAX_RX_BYTES (3)
#define MAX_TX_BYTES (4)
#define RS_485_MAX_RX_DATA_BYTES (12)
#define RS_485_RX_BYTE_FIFO_SIZE (185)
#define RS_485_TX_BYTE_FIFO_SIZE (15)
#define RS_485_RX_TEMP_FIELD_SIZE (12)

//Set timeout to half a second
#define T_SEC (0)
#define T_MICROSEC (500000)

enum State {
	PING,
	WAITING_RESPONSE,
	RECEIVED_RESPONSE,
	RECEIVED_INVALID_RESPONSE,
	TIMED_OUT_WAITING,
	READ_ERROR
};

struct RS485State{
	enum State currentState;
	int currentDeviceNum;
	char inChargeBlinkers;
};


void intToASCIIHex(unsigned int convert,unsigned char* result);
void charToASCIIHex(unsigned char convert, char* result);
void GeneratePicCRC(unsigned char generateFrom[],unsigned char size);
unsigned char generateCRC8(unsigned char generateFrom[],unsigned char size);
void progressToNextDevice();
char checkValidResponse(char* checkRsp);
char sendString(int deviceNum, char* string, unsigned int dataLength);

struct RS485State communicationState;

//Table used to calculate CRCs efficiently (precalculated using Netbeans C program TODO: rewrite && upload precalculation program)
const unsigned char crc8Table[]=
{0x00,0xd5,0x7f,0xaa,0xfe,0x2b,0x81,0x54,0x29,0xfc,0x56,0x83,0xd7,0x2,0xa8,0x7d,0x52,0x87,0x2d,0xf8,0xac,0x79,0xd3,0x6,0x7b,0xae,0x4,0xd1,0x85,0x50,0xfa,
		0x2f,0xa4,0x71,0xdb,0xe,0x5a,0x8f,0x25,0xf0,0x8d,0x58,0xf2,0x27,0x73,0xa6,0xc,0xd9,0xf6,0x23,0x89,0x5c,0x8,0xdd,0x77,0xa2,0xdf,0xa,0xa0,0x75,0x21,
		0xf4,0x5e,0x8b,0x9d,0x48,0xe2,0x37,0x63,0xb6,0x1c,0xc9,0xb4,0x61,0xcb,0x1e,0x4a,0x9f,0x35,0xe0,0xcf,0x1a,0xb0,0x65,0x31,0xe4,0x4e,0x9b,0xe6,0x33,0x99,
		0x4c,0x18,0xcd,0x67,0xb2,0x39,0xec,0x46,0x93,0xc7,0x12,0xb8,0x6d,0x10,0xc5,0x6f,0xba,0xee,0x3b,0x91,0x44,0x6b,0xbe,0x14,0xc1,0x95,0x40,0xea,0x3f,0x42,
		0x97,0x3d,0xe8,0xbc,0x69,0xc3,0x16,0xef,0x3a,0x90,0x45,0x11,0xc4,0x6e,0xbb,0xc6,0x13,0xb9,0x6c,0x38,0xed,0x47,0x92,0xbd,0x68,0xc2,0x17,0x43,0x96,0x3c,
		0xe9,0x94,0x41,0xeb,0x3e,0x6a,0xbf,0x15,0xc0,0x4b,0x9e,0x34,0xe1,0xb5,0x60,0xca,0x1f,0x62,0xb7,0x1d,0xc8,0x9c,0x49,0xe3,0x36,0x19,0xcc,0x66,0xb3,0xe7,
		0x32,0x98,0x4d,0x30,0xe5,0x4f,0x9a,0xce,0x1b,0xb1,0x64,0x72,0xa7,0xd,0xd8,0x8c,0x59,0xf3,0x26,0x5b,0x8e,0x24,0xf1,0xa5,0x70,0xda,0xf,0x20,0xf5,0x5f,
		0x8a,0xde,0xb,0xa1,0x74,0x9,0xdc,0x76,0xa3,0xf7,0x22,0x88,0x5d,0xd6,0x3,0xa9,0x7c,0x28,0xfd,0x57,0x82,0xff,0x2a,0x80,0x55,0x1,0xd4,0x7e,0xab,0x84,
		0x51,0xfb,0x2e,0x7a,0xaf,0x5,0xd0,0xad,0x78,0xd2,0x7,0x53,0x86,0x2c,0xf9};

char rs485Addressess[NUM_BMS][2];
//RX and TX FIFOs, sized for maximum size of current commands
unsigned char RXByteFIFO[RS_485_RX_BYTE_FIFO_SIZE];
unsigned char TXByteFIFO[RS_485_TX_BYTE_FIFO_SIZE];

unsigned int RXByteFIFOindex;//Used by RXByteFIFO array while receiving messages
CommChannel RS485_Stream;

int** stateData;
/**
@author Andrey Kurenkov <akurenkov3@gatech.edu> 678-900-4326

@brief This function initializes communication to the pic24 microncontrollers

@details Starts up RS485 communication on port2 with the default setup. ALso initializes
variables as appropriate.

@return char that is an error code as defined by SUCCESS and FAILURE
 */
char initPicCom(int** data)
{
	stateData=data;
	RXByteFIFOindex=0;
	RS485_Stream=RS485_setup(COM2_RS458_DEV,B115200);
	if(RS485_Stream.devicefd==-1)
		return FAILURE;
	unsigned int i=0;
	//Initialize addresses
	for(i=0;i<NUM_BMS;i++){
		rs485Addressess[i][0]='C';
		rs485Addressess[i][1]='C';
	}
	//Control computer address
	rs485Addressess[i][0]='C';
	rs485Addressess[i][1]='C';
	//Start by sending ping to first device
	communicationState.currentDeviceNum=0;
	communicationState.currentState=PING;
	return SUCCESS;
}

void endPicCom() 
{ //close connection.
	RS485_close(RS485_Stream);
	return;
}

/**
@author Andrey Kurenkov <akurenkov3@gatech.edu> 678-900-4326

@brief This function handles sending pings to pics

@details Sets up and handles sending status requests to pics and 
receiving responses.

@todo make interrupt based
 */
void pingPics(char* deviceType, char* deviceNum, char* asciiArr){
	//Use these to indicate that a full response has not been received in this call
	static int failCount=0;
	unsigned int i;
	*deviceType='~';
	*deviceNum=0;
	switch(communicationState.currentState){
	case PING:
		if(sendPing()==SUCCESS){
			communicationState.currentState=WAITING_RESPONSE;
			RXByteFIFOindex=0;
		}
		break;
	case WAITING_RESPONSE:{
		char response[expectedResponseLength()];
		//char readSuccess=RS485_read(response,RS485_Stream);
		char readSuccess=RS485_readWithTimeout(RS485_Stream,response,T_SEC,T_MICROSEC);

		endPicCom();
		RS485_Stream=RS485_setup(COM2_RS458_DEV, B115200);
		if(readSuccess!=SUCCESS){
			if(readSuccess==TIMEOUT){
				communicationState.currentState=TIMED_OUT_WAITING;
			}
			else
				communicationState.currentState=READ_ERROR;
		}
		else{
			for(i=0; i<strlen(response) && (i+RXByteFIFOindex)<expectedResponseLength(); i++){
				RXByteFIFO[i+RXByteFIFOindex]=response[i];
			}
			RXByteFIFOindex+=strlen(response);

			if(RXByteFIFOindex>=expectedResponseLength()){
				if(checkValidResponse(RXByteFIFO)){
					communicationState.currentState=RECEIVED_RESPONSE;
#ifdef DEBUG
					printf("Received response: %s\n",RXByteFIFO);
#endif
				}
				else{
					communicationState.currentState=RECEIVED_INVALID_RESPONSE;
#ifdef DEBUG
					printf("Received invalid response: %s\n",RXByteFIFO);
#endif
				}
			}
		}          
	}
	break;
	case RECEIVED_RESPONSE:
		for(i=10; i<expectedResponseLength()-2; i++){
			asciiArr[i-10]=RXByteFIFO[i];
		}
		*deviceType=RXByteFIFO[0];
		*deviceNum=RXByteFIFO[1]-'0';
		progressToNextDevice();
		communicationState.currentState=PING;
		break;
	case RECEIVED_INVALID_RESPONSE:
		communicationState.currentState=PING;
		break;
	case TIMED_OUT_WAITING:
		if(failCount>=3){
			failCount=0;
			progressToNextDevice();
		}
		else{
			failCount++;
		}
		communicationState.currentState=PING;
		break;
	case READ_ERROR:
		if(failCount>=3){
			failCount=0;
			progressToNextDevice();
		}
		else{
			failCount++;
		}
		communicationState.currentState=PING;
		break;
	}
}

char sendString(int deviceNum,char* string, unsigned int dataLength)
{
	char dataASCII[4];
	intToASCIIHex(dataLength,dataASCII);

	char cmdForCRC[10]; 
	snprintf(cmdForCRC, 11, "%c%c%s%s", rs485Addressess[deviceNum][0],rs485Addressess[deviceNum][1], string, dataASCII);
	char cmdCRC=generateCRC8(cmdForCRC,(unsigned char)(CMD_LENGTH-3));

	char cmdCRCASCII[2];
	charToASCIIHex(cmdCRC,cmdCRCASCII);

	char fullPing[13];
	snprintf(fullPing, 14, "%s%s%c", cmdForCRC, cmdCRCASCII, EOL_CHAR);


	char writeFailure=RS485_write(fullPing, RS485_Stream);
	if(writeFailure){
		perror("COM2 write failed!");
		return FAILURE;
	}
	return SUCCESS;
}

char sendPing(){
	return sendString(communicationState.currentDeviceNum,"PING",0);
}

/*Gives the expected length of the response given the current device number*/
unsigned int expectedResponseLength(){
	if(communicationState.currentDeviceNum<=NUM_BMS)
		return RS_485_BMS_STATUS_RESPONSE_LENGTH-1;//-1 to not accoutn for eol;
	else
		return RS_485_MC_STATUS_RESPONSE_LENGTH-1;
}

/*Moves to pinging the next device*/
void progressToNextDevice(){
	communicationState.currentDeviceNum++;

	if(communicationState.currentDeviceNum==(NUM_BMS+NUM_MPPT+1))//Add one for control computer
		communicationState.currentDeviceNum=0;
}


int ASCIIToHex(unsigned char convert[])
{ //convert hex char representation to int.
	int n;
	sscanf(convert, "%x", &n);
	return (n);
}

void intToASCIIHex(unsigned int convert, unsigned char* result)
{ //convert int up to (2^16 - 1) to hex char representation
	snprintf(result, 5, "%04x", convert);
}

void charToASCIIHex(unsigned char convert, char* result)
{ //convert char up to (2^8 - 1) to hex char representation
	snprintf(result, 3, "%02x", convert);
}

/**
@todo find best source for explanation of the algorithm followed here - put in appropriate 
documentation setting (figure out where)
 */
unsigned char generateCRC8(unsigned char generateFrom[],unsigned char size)
{
	/*
	Poly: x^8 + x^7 + x^6 + x^4 + x^2 + 1
	Custom software implementation of CRC based on a lookup table-
	CRC is MSB first - no reflections or final xor value.
	 */
	unsigned int i;
	unsigned char CRC=0;
	for(i=0;i<size;i++)
		CRC=crc8Table[generateFrom[i]^CRC];
	return CRC;	
}

char checkValidResponse(char* checkRsp){
	//Check address
	if(checkRsp[0]!=rs485Addressess[communicationState.currentDeviceNum][0] || checkRsp[1]!=rs485Addressess[communicationState.currentDeviceNum][1]){
#ifdef DEBUG
		printf("Response with invalid address\n");
#endif
		return FALSE;
	}
	unsigned int length=strlen(checkRsp);
	if(length!=expectedResponseLength()){//Check length
#ifdef DEBUG
		printf("Response with invalid length\n");
#endif
		return FALSE;
	}
	char crc=generateCRC8(checkRsp, (unsigned char)(length-2));
	char crcASCII[2];
	charToASCIIHex(crc,crcASCII);
	if(crcASCII[0]!=checkRsp[length-2] || crcASCII[1]!=checkRsp[length-1])//Check CRC
	{
#ifdef DEBUG
		printf("Response with invalid CRC %s %c%c\n",crcASCII,checkRsp[length-2],checkRsp[length-1]);
#endif
		return FALSE;
	}
	return TRUE;
}

/**
* @}
*/
