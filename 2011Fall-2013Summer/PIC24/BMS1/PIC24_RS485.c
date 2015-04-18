#include "PIC24_RS485.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"

/*******************************
 * Private Functions
 *******************************
 */
AsciiData* convertDataToAsciiString();
unsigned char rs485findCommandType(unsigned char RXCommand[]);
unsigned char generateCRC8(unsigned char generateFrom[],unsigned int size);

void initTimer2( void );
void rs485resetState();
void rs485PopulateTXByteFIFO();

/*******************************
 * Data Arrays
 *******************************
 */
unsigned char RXByteFIFO[RS_485_RX_BYTE_FIFO_SIZE];
unsigned char TXByteFIFO[RS_485_TX_BYTE_FIFO_SIZE];
unsigned char RXdata[RS_485_MAX_RX_DATA_BYTES];


/*******************************
 * Global variables
 *******************************
 */
unsigned char rs485msgType = 0;
unsigned int RXByteFIFOindex = 0;//Used by RXByteFIFO array while receiving messages
unsigned int TXByteFIFOindex = 0;//Used by TXByteFIFO array when filling out the response to a message
unsigned char rs485state;////keep track of where you are in e.g., RXMsgType array. reset on state changes.
unsigned char rs485tempIndex = 0; 
unsigned char rs485postCmdDlyDone = 0;
unsigned int rs485DataLength;
unsigned char rs485intraMsgTimedOut;//Time out flag dependent on timer1
unsigned char rs485ResponseLength=0;//Assigned according to message type in rs485PopulateTXByteFIFO()
unsigned char i = 0;//General purpose loop variable used throughout the code

/*******************************
 * Constant strings
 *******************************
 */
const char rs485KnownCommands[RS_485_NUM_KNOWN_CMDS][4] = {{ 'P','I','N','G'},
															{'B','M','S','T'},
															{'A','C','K','N'}};


/*A typical acknowledge response with placeholders for address and checksum*/
const char rs485AckResponse[] = { '0','0','A','C','K','N','0','0','0','0','8','B',0x0D };

/*Used for CRC calculations. Precomputed with a program to be rewritten and added later(TODO). Good coverage here:http://www.repairfaq.org/filipg/LINK/F_crc_v3.html. */
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

/*******************************
 * Pivotal information holders
 *******************************
 */
DeviceIdentifiers myIdentifiers;/*Pivotal identifiers of the device being used that will be supplied by other code that this is combined with*/
unsigned int* data;
unsigned int dataLength;

/**
* Initiates RS485 communication given information as to what type of device it is being used for.
* 
* @param givenType - an instance of the Device_Type  struct that identifies what device this code is joined with
* @param givenGetData - allows for robust code by having code that uses this module define how to store it as ascii
*/
void initRS485(DeviceIdentifiers givenType, unsigned int length, unsigned int* deviceData)
{		
	/*Store identifying/data info*/
	dataLength=length;
	data=deviceData;
	myIdentifiers=givenType;
	
	TRISB = TRISB&0XF7FF;						// Set all RB11 to output
	/*Initialise state to appropriate values*/
	rs485state = RS_485_IDLE;
	RXByteFIFOindex = 0;
	rs485tempIndex = 0;
	rs485intraMsgTimedOut = 0;
	rs485postCmdDlyDone = 0;
    LATB=LATB&0xF7FF;//Set RB11 pin to low
	
	for (i = 0; i < RS_485_RX_BYTE_FIFO_SIZE; i++)
		RXByteFIFO[i] = 0;	
	for (i = 0; i < RS_485_MAX_RX_DATA_BYTES; i++)
		RXdata[i] = 0;			

	/*init*/
	initUART(givenType.clockFreq);
	initTimer2();
}

//TODO: have var to keep track whether it has been initialized?
/*
* Sends out a character through UART1 (assuming it has been initialized properly.
*
* @param Ch the char to send
*/
void UART1PutChar(char Ch)
{
   while (U1STAbits.UTXBF);// wait while Tx buffer full
   U1TXREG = Ch;
}

/**
* Sends out a string through UART1 (assuming it has been initialized properly.
*
* @param chars
* @param length
*/
void UART1PutString(char* chars, int length){
	for(i=0;i<length;i++)
		UART1PutChar(chars[i]);
}

void RS485processRX()
{
	unsigned char RXTempField[RS_485_RX_TEMP_FIELD_SIZE];
	unsigned int rs485tempFIFOindex=0;
    rs485tempIndex=0;
	
		if (rs485intraMsgTimedOut &&  !(RXByteFIFO[RXByteFIFOindex-1] == EOL_CHAR) && (rs485state <= RS_485_LISTEN_EOL)) //Reset state if message timed out while parsing unless all but the EOL has been parsed.
		{
			rs485resetState();
		}
	
//Wait until a full message has been received to start parsing (when UART stops receiving)
if (!IEC0bits.U1RXIE)
	{
			//RXByeFIFOindex gets cleared on any call of rs485resetState();
            while(RXByteFIFOindex!=0)
            {
			switch (rs485state)
				{
					/*IDLE state: waiting to be addressed.  In this state,
					all bytes will be ignored until we see our address.  
					If we see our address, we enter the "LISTEN for 
					message type" state.*/
					case(RS_485_IDLE):
					{
						if (rs485tempIndex < RS_485_NUM_ADDRESS_BYTES) //check only the address bits
						{
							if (RXByteFIFO[rs485tempFIFOindex] == myIdentifiers.deviceAddress[rs485tempIndex])//if the bytes match our address
								rs485tempIndex++; //increase the index of the address array
                            else  //if the message is not for our address
							{
                                rs485resetState();
							}
                                 rs485tempFIFOindex++; //increase the index of the data array
						}	
						else //next step
						{
							rs485state = RS_485_LISTEN_MSGTYPE;
							rs485tempIndex = 0;
						}
						break;
					}
				
					//LISTEN for message type
					case(RS_485_LISTEN_MSGTYPE):
					{
						
						if (rs485tempIndex < RS_485_NUM_MSGTYPE_BYTES) //check only the message type bits
						{
							RXTempField[rs485tempIndex] = RXByteFIFO[rs485tempFIFOindex]; //add the message type bits to an array
							rs485tempIndex++;//increase the arrray index
							rs485tempFIFOindex++; //increase the byte index
						}
						else //parse the message type
						{
							//function will return 1 if command type is known
							if(rs485findCommandType(RXTempField)) //call the function to see if the command type is known if so move on to the next step
							{
								rs485state = RS_485_LISTEN_DATALENGTH; 
								rs485tempIndex = 0;
								rs485DataLength = 0;
							}
							else //if the message type is not recognized
								rs485resetState();
						}
						break;
					}
					case(RS_485_LISTEN_DATALENGTH):
					{
						if (rs485tempIndex < RS_485_NUM_DATALENGTH_BYTES) //check only the data length bits
						{	
							unsigned short charValue=0;
							unsigned short decValue=1;
							char currentChar=RXByteFIFO[rs485tempFIFOindex];
							if(currentChar>47 && currentChar<58)//Case where char is 0-9
								charValue=currentChar-'0';
							else if(currentChar>64)//Case where char is A-F
								charValue=currentChar-55;//'A' is 65, 65-55=10
							for(i=3;i>rs485tempIndex;i--)
								decValue*=16;
							decValue*=charValue;
							rs485DataLength += decValue; 
							rs485tempIndex++;
							rs485tempFIFOindex++;
						}
						else //once completed
						{
							if (rs485DataLength < RS_485_MAX_RX_DATA_BYTES) //if the number of data bytes does not excede 
							{
								rs485state = RS_485_LISTEN_DATA;
								rs485tempIndex = 0;
							}	
							else
								rs485resetState();
						}
						break;
					}

					case(RS_485_LISTEN_DATA):
					{								

						//if rs485DataLength is 0, the latest byte will NOT be taken
						//out of the RXByteFIFO, because this if statement will be false.
						if (rs485tempIndex < rs485DataLength)
						{	
							RXdata[rs485tempIndex] = RXByteFIFO[rs485tempFIFOindex];
							rs485tempIndex++;
							rs485tempFIFOindex++;
						}	
						else
						{
							rs485state = RS_485_LISTEN_CHECKSUM;
							rs485tempIndex = 0;
						}
						break;
					}	
					case(RS_485_LISTEN_CHECKSUM):
					{
						if (rs485tempIndex < RS_485_NUM_CHECKSUM_BYTES)
						{	
							RXTempField[rs485tempIndex] = RXByteFIFO[rs485tempFIFOindex];
							rs485tempIndex++;
							rs485tempFIFOindex++;
						}	
						else
						{
							rs485state = RS_485_LISTEN_EOL;
							rs485tempIndex = 0;
						}

						break;
					}
					//if we reached this state, the next thing we see should be an EOL.
					//if we do, we just need to validate the checksum and then the message
					//can be considered complete
					case(RS_485_LISTEN_EOL):
					{                       

						if (RXByteFIFO[rs485tempFIFOindex] == (unsigned char)EOL_CHAR)
						{ 
                              	rs485state = RS_485_EVAL_CHECKSUM;
						}	
						else
                        {//if we see something else, that's wrong.                      
							rs485tempFIFOindex=0;
							rs485resetState();
							rs485tempFIFOindex++; 
                        }
						break;
					}
					
				case(RS_485_EVAL_CHECKSUM):
				{
					char crcSent=ASCIIToHex(RXTempField,2);
					char crc=generateCRC8(RXByteFIFO,10);
					#ifdef DEBUG
					char result[2];
					charToASCIIHex(crc,result);
					UART2PutString(result,2);
					#endif
					if(crcSent==crc)
					{	
						rs485postCmdDlyDone=1;
						PR1 =RS_485_POST_CMD_DELAY_H;
						TMR1 =  RS_485_POST_CMD_DELAY_L ;
						rs485state = RS_485_POST_CMD_DELAY;
					//	IEC0bits.T2IE =1;
					//	IFS0bits.T2IF=0;//Need to clear flag manually each time
						
					}
					else
					rs485resetState();
				break;
				}				
			//this state just waits until the post-cmd delay time is up.
			//the rs485postCmdDlyDone flag will be set via an intra msg timeout occurring
			//after the final byte of the command has been received.
			case(RS_485_POST_CMD_DELAY):
			{               
				if (rs485postCmdDlyDone){
				
					rs485state = RS_485_TX_ADR;
				    IEC0bits.T2IE = 0;	//disable timer interrupts
					IEC0bits.U1RXIE=0;	//disable receive interrupes
					rs485tempIndex = 0;		
					rs485PopulateTXByteFIFO();//Fill TX array with response
                    LATB=LATB | 0x1F00;//Set FX pin(RB11) to high
					TXByteFIFOindex=0;//Reset TX index for use in interrupt
					IEC0bits.U1TXIE = 1;//Enable TX interrupts - execute whenever the TX buffer is empty and more data can be put into the buffer					
				}
				break;
			}
			case(RS_485_TX_ADR):
			{
			if (TXByteFIFOindex > rs485ResponseLength)
				{
					//if the final byte has finished sending, reset state.
						if (U1STAbits.TRMT)
						{
							rs485tempFIFOindex=0;
							rs485resetState();
						}
					}
	
				break;
			}
		}
	}
  }
}


void rs485resetState()
{
                //flush FIFO
                RXByteFIFOindex = 0;
                //reset state machine
                rs485state = RS_485_IDLE;
                rs485ResponseLength=0;
                IEC0bits.T2IE =0;       //disable timer interrupts
                rs485tempIndex = 0;
                rs485intraMsgTimedOut = 0;
                IEC0bits.U1RXIE = 1;
                LATB=LATB&0xF7FF;//Set RB11 pin to low
                rs485postCmdDlyDone = 0;
                //clear RX buffer overrun bit-empties the RX buffer
                U1STAbits.OERR = 0;
}


unsigned char rs485findCommandType(unsigned char RXTempField[])
{
	for (i = 0; i < RS_485_NUM_KNOWN_CMDS; i++) //cycle through the known command index
	{
		if (RXTempField[0] == rs485KnownCommands[i][0]
			&& RXTempField[1] == rs485KnownCommands[i][1]
			&& RXTempField[2] == rs485KnownCommands[i][2]
			&& RXTempField[3] == rs485KnownCommands[i][3])
		{
			rs485msgType = i; //if the command matches set the number to be that command
			return 1;
		}
	}
	return 0;
}

void rs485PopulateTXByteFIFO()
{
	//If device pinged then a full status response needed
	if (rs485msgType==RS_485_PING_CMD)
	{
		//Start off message with address of device
		TXByteFIFO[0] = myIdentifiers.deviceAddress[0];
		TXByteFIFO[1] = myIdentifiers.deviceAddress[1];
		
		//Composed message type with <myIdentifiers>ST(atus) 
		TXByteFIFO[2]= myIdentifiers.deviceType[0];
		TXByteFIFO[3]= myIdentifiers.deviceType[1];
		TXByteFIFO[4]='S';
		TXByteFIFO[5]='T';

		//Fill in value of data length
		unsigned char dataLengthChar[4];
		intToASCIIHex(dataLength,dataLengthChar);
		TXByteFIFO[6]=dataLengthChar[0];
		TXByteFIFO[7]=dataLengthChar[1];
		TXByteFIFO[8]=dataLengthChar[2];
		TXByteFIFO[9]=dataLengthChar[3];
		unsigned char ASCIIRepresentation[4];
		int index=0;
		TXByteFIFOindex=10;
		for(i=0;i<dataLength;i++)
		{
			intToASCIIHex(data[i],ASCIIRepresentation);
			for(index=0;index<4;index++)
			{
				TXByteFIFO[TXByteFIFOindex++]=ASCIIRepresentation[index];
			}	
		}
			
		char TXCRC[2];
		charToASCIIHex(generateCRC8(TXByteFIFO,TXByteFIFOindex),TXCRC);
		TXByteFIFO[TXByteFIFOindex++]= TXCRC[0];
		TXByteFIFO[TXByteFIFOindex++]= TXCRC[1];
		TXByteFIFO[TXByteFIFOindex++]=EOL_CHAR;
		rs485ResponseLength=dataLength*4+13;
}
	//Unless the message is a status response or an acknowledge response, respond with an acknowledge response
	else if(!(rs485msgType==RS_485_BMST_CMD || rs485msgType==RS_485_ACKNOWLEDGE))
	{
		TXByteFIFO[0] = myIdentifiers.deviceAddress[0];
		TXByteFIFO[1] = myIdentifiers.deviceAddress[1];
        TXByteFIFOindex=2;	
		rs485ResponseLength=RS_485_ACK_RESPONSE_LENGTH;
		for (i = 2; i < RS_485_ACK_RESPONSE_LENGTH; i++)
		{
			TXByteFIFO[TXByteFIFOindex] = rs485AckResponse[i];
            TXByteFIFOindex++;
		}	
	}//End of else if
	else//If its a status message or an acknowledge response, dont respond
	{
	rs485ResponseLength=0;
		switch(rs485msgType)
		{
			case(RS_485_BMST_CMD ):
			{
				break;
			}
			case(RS_485_ACKNOWLEDGE):
			{
				break;
			}
		}//End of switch	
	}//end of else			
}//End of method

	
void __attribute__((interrupt, no_auto_psv, shadow)) _U1RXInterrupt(void) 
{ 
	IFS0bits.U1RXIF = 0;//Need to clear flag manually each time
	unsigned char receivedChar=U1RXREG;//All recieved char should be ASCII/EOL and so unsigned
	static unsigned char receiving=0;//Keep track of state
	if(!receiving)
	{	
		if(receivedChar==myIdentifiers.deviceAddress[0])//Dont start filling the recieve array until the first character of myAdress is received
		{
			receiving=1;
			IEC0bits.T2IE = 1;
			PR1 = RS_485_INTRA_MSG_TIME_OUT_H;
			TMR1 = RS_485_INTRA_MSG_TIME_OUT_L;	
		}
	}
	if(receiving)
	{
					
		//if FIFO not full, and we're currently listening, and an intra msg timeout hasn't yet occurred
		if(rs485state <= RS_485_LISTEN_EOL && !rs485intraMsgTimedOut)	
		{
		
		RXByteFIFO[RXByteFIFOindex] = receivedChar;	//Store the received char in the receive array
		/*
		Start timer after each RX'd byte for the
		intra-message timeout. If we don't receive
		another byte before the timer is up, a timeout
		has occurred and the TMR1 interrupt code below will handle it.  
		*/
		PR1 = RS_485_INTRA_MSG_TIME_OUT_H;
		TMR1 = RS_485_INTRA_MSG_TIME_OUT_L;						
				
		/*
		if a timer 1 interrupt occurred after we started servicing
		this interrupt, give the sender the benefit of the doubt, and
		don't count it as "timed out."  i.e., clear the flag so the TMR1
		code below doesn't run.
		*/
		IFS0bits.T2IF = 0;				
		RXByteFIFOindex++;//increment FIFO index						
		} //end if FIFO not full
		if (RXByteFIFOindex >= RS_485_RX_BYTE_FIFO_SIZE || RXByteFIFO[RXByteFIFOindex-1]==EOL_CHAR)
		{
		receiving=0;
		IEC0bits.U1RXIE =0; //RX  Interrupt disabled					
		}
	} //end if receiving 
} //end RX interrupt

void __attribute__((interrupt, auto_psv)) _T2Interrupt( void )
{
	IFS0bits.T2IF=0;//Need to clear flag manually each time
	//if the timer timed out and we were in an RX state, notify the state machine
	if (rs485state < RS_485_POST_CMD_DELAY) {
		/*
		This will tell the RX interrupt not to listen anymore,
		and tell the state machine a time out has occurred.  Timing out
		is okay if we already received all the bytes in the message.
		*/
		rs485intraMsgTimedOut = 1;
		/*
		if the message is over, then one of these will be true:
		a) the last character we received was the EOL_CHAR, and the state machine hasn't gotten to it yet
		b) we received it and the state machine processed it, so we're in eval_checksum or post_cmd_delay
		If the message is over, and a timeout occurs, then the Post Cmd Delay has passed.
		*/

	}	//end if in a listening state
	if (rs485state == RS_485_POST_CMD_DELAY) {
			rs485postCmdDlyDone = 1;
			rs485intraMsgTimedOut = 0;	//Don't bother with this then; it's meaningless once the command has successfully ended
	}
}	//end Tmr1 interrupt	

void __attribute__((interrupt, no_auto_psv, shadow)) _U1TXInterrupt(void)
{
	IFS0bits.U1TXIF = 0; //Need to clear the flag manually each time
	UART1PutChar(TXByteFIFO[TXByteFIFOindex]);
	TXByteFIFOindex++;			
	//If final byte in response of FIFO
	if (TXByteFIFOindex >= rs485ResponseLength)
	{
	IEC0bits.U1TXIE = 0;
	/*
	Indicates to the state machine that the response is over by
	making TXByteFIFOindex > response length
	*/
	TXByteFIFOindex++;
	}	
} 


unsigned char generateCRC8(unsigned char generateFrom[],unsigned int size)
{
/*
Poly: x^8 + x^7 + x^6 + x^4 + x^2 + 1
Custom software implementation of CRC based on a lookup table-
CRC is MSB first - no reflections or final xor value.
*/
unsigned char CRC=0;
for(i=0;i<size;i++)
	CRC=crc8Table[generateFrom[i]^CRC];
return CRC;
}

/*Convenience conversion functions*/

int ASCIIToHex(char convert[], unsigned char length)
{
	int n;
	sscanf(convert,"%x",&n);
	return n;
}

void intToASCIIHex(unsigned int convert, unsigned char* result)
{
		snprintf(result, 5, "%04x",convert);
}

/**
* Converts a given char to its Ascii representation. 
* A char here is assumed to be sized 1 byte.
*/
void charToASCIIHex(unsigned char convert,unsigned char* result)
{
	result[1]='A'+convert-10;
	snprintf(result, 3, "%02x",convert);
}

/**
* Converts a given short to its Ascii representation. 
* A short here is assumed to be sized 2 byte.
*/
void shortToASCIIHex(short convert,unsigned char* result)
{
		snprintf(result, 5, "%04x",convert);
}

void doubleToASCIIHex(double convert,unsigned char* result)
{
	snprintf(result, 5, "%04f",convert);
}
