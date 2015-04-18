#include "RS485ControlCom.h"
#include <stdio.h>
#include <stdlib.h>
#include "string.h"

#include "RS485.h"
#include "shared_data.h"

#define EOL_CHAR (0X0D)

#define RS_485_NUM_ADDRESS_BYTES 	(2)
#define RS_485_NUM_KNOWN_CMDS		(11)
#define RS_485_COMMAND_LENGTH 		(4)
#define RS_485_NUM_DATALENGTH_BYTES 	(4)
#define RS_485_NUM_CHECKSUM_BYTES 	(2)
#define CMD_LENGTH (13)
#define PING_LENGTH (13)

#define NUM_BMS (4)
#define NUM_MPPT (0)

#define MAX_RX_BYTES (3)
#define MAX_TX_BYTES (4)
#define RS_485_RX_BYTE_FIFO_SIZE (185)
#define RS_485_TX_BYTE_FIFO_SIZE (15)
#define RS_485_RX_TEMP_FIELD_SIZE (12)

#define RESPONSE_LENGTH (141)
#define VARS_COUNT (15)

#define MESSAGE_DEVICE_ADDRESS_INDEX  (0)
#define MESSAGE_TYPE_INDEX (2)
#define MESSAGE_DATA_LENGTH_INDEX (6)
#define MESSAGE_DATA_INDEX (10)
#define MESSAGE_CRC_INDEX (RESPONSE_LENGTH-3)
#define MESSAGE_EOL_INDEX (RESPONSE_LENGTH-1)

#define RS485_INIT_TIMEOUT_COUNTER (3) //number of times to attempt initPicCom()

int ASCIIToHex(unsigned char convert[]);
void intToASCIIHex(unsigned int convert,unsigned char* result);
void charToASCIIHex(unsigned char convert,unsigned char* result);
unsigned char generateCRC8(unsigned char generateFrom[],unsigned char size);
unsigned int expectedResponseLength();
char sendString(char* address,char* string, unsigned int dataLength);
char checkValidPing(char* checkRsp);
char sendState();

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
const char NULL_ADDRESS[2]="~~";
const char READ_ERROR_ADDRESS[2]="ER";

void bigIntToASCIIHex(unsigned int convert, unsigned char* result);

CommChannel RS485_Stream;

/**
@author Matt Olson <matt.a.olson@gmail.com> 404-680-0566

@brief Thread for polling and responding to pings on the RS485 network.
@param thread_id needed to start thread
*/
void *RS485_Control(void *thread_id)
{
	int failCounter=0;

	//init
	#ifdef DEBUG
		printf("Attempting initPicCom()...\n");
	#endif
	while ( initPicCom() != SUCCESS && failCounter < RS485_INIT_TIMEOUT_COUNTER ) {
		failCounter++;
		#ifdef DEBUG
			printf("initPicCom() failed %d time(s)\n", failCounter);
		#endif
		if (failCounter == RS485_INIT_TIMEOUT_COUNTER) {
			#ifdef DEBUG
				printf("initPicCom() failed too many times, giving up - quitting thread...\n");
			#endif
			pthread_exit(NULL);
		}
	}

	#ifdef DEBUG
		printf("initPicCom() successful\n");
	#endif


//Only reach here if initPicCom() is successful
	Message message;
	while(1) {
		message = checkRS485();
		if(strcmp(message.address, NULL_ADDRESS) == 0) {//strcmp returns 0 if strings are equal
			continue;
		}
		else if(strcmp(message.address, READ_ERROR_ADDRESS)==0){
			continue;//TODO: handle this somehow?
		}
		else{//if received something and not read_error
			sendState();//for now this is needed
		}
	}

	endPicCom();
	pthread_exit(NULL);
}

/**
@author Andrey Kurenkov <akurenkov3@gatech.edu> 678-900-4326

@brief This function initializes communication to the pic24 microncontrollers

@details Starts up RS485 communication on port2 with the default setup. ALso initializes
variables as appropriate.

@return char that is an error code as defined by SUCCESS and FAILURE
*/
char initPicCom()
{
	RS485_Stream=RS485_setup(COM2_DEV, B115200);
	if(RS485_Stream.devicefd==-1)
		return FAILURE;
	return SUCCESS;
}

void endPicCom() 
{ //close connection.
	RS485_close(RS485_Stream);
}

/**
@author Andrey Kurenkov <akurenkov3@gatech.edu> 678-900-4326

@brief This function handles listening for a PING or other command and sending back anything it receives

@details Sets up and handles listening for pings and requests
@return if a response or message is received, a Message is returned as appropriate. 
Otherwise, NULL is returned. 

*/
Message checkRS485()
{
	//Use these to indicate that a full response has not been received in this call
	Message message;
	unsigned int i;
	char ping[CMD_LENGTH];

	if(RS485_read(ping, RS485_Stream) == FAILURE) {
		printf("COM2 read() error\n");
		strcpy(message.address,READ_ERROR_ADDRESS);
		return message;
	} 
	if(checkValidPing(ping)) {
		message.length=PING_LENGTH;
		for(i=MESSAGE_DEVICE_ADDRESS_INDEX;i<MESSAGE_TYPE_INDEX;i++)  
		        message.address[i]=ping[i];
		for(i=MESSAGE_TYPE_INDEX;i<MESSAGE_DATA_INDEX;i++)  
			message.messageType[i]=ping[i];
		for(i=MESSAGE_DATA_INDEX;i<message.length-3;i++)  //stores all data(skips address and command type,stops before CRC and EOL)
			message.dataAsciiArr[i]=ping[i];
		return message;
	}//Can have other messages besides thing-parsing only depend on length



	//If message not returned with something elsewhere
	strcpy(message.address,NULL_ADDRESS);
	return message;       
}

/**
@author Andrey Kurenkov <akurenkov3@gatech.edu> 678-900-4326

@brief This function sends out the state of the Control SBC over the RS485 connection

@return char that is an error code as defined by SUCCESS and FAILURE
*/
char sendState()
{
	char send[RESPONSE_LENGTH];//array to hold entire response
	int i;//iteration variable
	snprintf(send,MESSAGE_DATA_INDEX,"CCMCST000E");//Fill out with address, command code, and amount of data.

	pthread_mutex_lock(&Motor_info_mutex);	//read in motor state data from MC_faults (shared_data.h)
	int stateData[]= { Motor_info.speed_rpm,
			Motor_info.airgap_pos,
			Motor_info.direction,
			Motor_info.target_speed,
			Motor_info.target_phase_current,
			Motor_info.throttle,
			Motor_info.brake_indicator 
	};
	pthread_mutex_unlock(&Motor_info_mutex);

	for(i=0; i<8; i++){
		char convert[8];
		bigIntToASCIIHex(stateData[i], convert);
		strcat(send, convert);
	}

	pthread_mutex_lock(&MC_faults_mutex);	//read in fault data from Motor_info (shared_data.h)
	int faultData[]={MC_faults.fault_1,
			MC_faults.fault_2,
			MC_faults.fault_3,
			MC_faults.fault_4};
	pthread_mutex_unlock(&MC_faults_mutex);

	for(i=0; i<3; i++){
		char convert[8];
		bigIntToASCIIHex(faultData[i], convert);
		strcat(send, convert);
	}

	char TXCRC[2];
	charToASCIIHex(generateCRC8(send,MESSAGE_CRC_INDEX),TXCRC);//Generate CRC for everything up to CRC
	send[MESSAGE_CRC_INDEX]=TXCRC[0];
	send[MESSAGE_CRC_INDEX+1]=TXCRC[1];
	send[MESSAGE_EOL_INDEX]=EOL_CHAR;
	return RS485_write(send,RS485_Stream);
}

/**
@author Andrey Kurenkov <akurenkov3@gatech.edu> 678-900-4326

@brief This functions returns the expectedLength of the next thing this SBC will receive

@details currently this SBC is only getting pinged, but better to have this and 
change it in the future if RS485 becomes more important (which, with redundancies is likley)

@return length of next command to be received(currently just PING)
*/
unsigned int expectedResponseLength()
{
	return PING_LENGTH;//Only sending state data, so should be just this
}

/**
@author Andrey Kurenkov <akurenkov3@gatech.edu> 678-900-4326

@brief A more generic communication function that send a given string

@param address the address of the device to which this is to be sent
@param string the String to send
@param dataLength the length of the string to send

@return char that is an error code as defined by SUCCESS and FAILURE
*/
char sendString(char* address,char* string, unsigned int dataLength)
{
	char dataASCII[4];
	intToASCIIHex(dataLength,dataASCII);

	char cmdForCRC[10]; 
	snprintf(cmdForCRC, 11, "%s%s%s",address, string, dataASCII);
	//Generate CRC of command up to its CRC
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

/**
@author Andrey Kurenkov <akurenkov3@gatech.edu> 678-900-4326

@brief Converts a series of chars reprsenting a hex value to the represented int value

@return returns the hex value of the ascii
*/
int ASCIIToHex(unsigned char convert[])
{ //convert hex char representation to int.
	int n;
	sscanf(convert, "%x", &n);
	return (n);
}

//Still using intToASCIIHex instead of this because everything else uses 2 byte ints - if needed will be used instead
void bigIntToASCIIHex(unsigned int convert, unsigned char* result)
{ //convert int up to (2^32 - 1) to hex char representation
	snprintf(result, 9, "%08x", convert);
}

void intToASCIIHex(unsigned int convert, unsigned char* result)
{ //convert int up to (2^16 - 1) to hex char representation
	snprintf(result, 5, "%04x", convert);
}

void charToASCIIHex(unsigned char convert, unsigned char* result)
{ //convert char up to (2^8 - 1) to hex char representation
	snprintf(result, 4, "%03x", convert);
}

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

/**
@author Andrey Kurenkov <akurenkov3@gatech.edu> 678-900-4326

@brief checks if a response received in return for a ping is valid or not.
@param checkRsp the received response to check for validity
@return returns TRUE is valid and false otherwise
*/
char checkValidPing(char* checkRsp){
	//Check address
	if(checkRsp[0]!='C'|| checkRsp[1]!='C')
		return FALSE;
	unsigned int length=sizeof(checkRsp)/sizeof(checkRsp[0]);
	if(length!=CMD_LENGTH-1)//Check length
		return FALSE;
	char crc=generateCRC8(checkRsp, (unsigned char)(length-3));
	char crcASCII[2];
	charToASCIIHex(crc,crcASCII);
	if(crcASCII[0]!=checkRsp[length-2] || crcASCII[1]!=checkRsp[length-1])//Check CRC
		return FALSE;
	return TRUE;
}


