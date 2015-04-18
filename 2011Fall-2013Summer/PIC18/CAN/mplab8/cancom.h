/* 
 * File:   pic_can.h
 * Author: Andrey
 *
 * Created on October 13, 2012, 4:00 AM
 */

#ifndef CANCOM_H
#define	CANCOM_H
#include "usart.h"
#include "GenericTypeDefs.h"

#define BAUD_RATE (115200)
/**From wikipedia
Base frame format
The frame format is as follows:
Field name	Length (bits)	Purpose
Start-of-frame	1	Denotes the start of frame transmission
Identifier	11	A (unique) identifier for the data which also represents the message priority
Remote transmission request (RTR)	1	Dominant (0) (see Remote Frame below)
Identifier extension bit (IDE)	1	Must be dominant (0). Optional
Reserved bit (r0)	1	Reserved bit (it must be set to dominant (0), but accepted as either dominant or recessive)
Data length code (DLC)*	4	Number of bytes of data (0?8 bytes)
Data field	0?64 (0-8 bytes)	Data to be transmitted (length in bytes dictated by DLC field)
CRC	15	Cyclic redundancy check
CRC delimiter	1	Must be recessive (1)
ACK slot	1	Transmitter sends recessive (1) and any receiver can assert a dominant (0)
ACK delimiter	1	Must be recessive (1)
End-of-frame (EOF)	7	Must be recessive (1)
*/

enum CAN_MESSAGE_PART {SOF,ID,RTR,IDE,R0,DLC,DATA,CRC,CRCDelim,ACK,ACKDelim,EOF};
extern short int CAN_ID;

int initCan(void);
void sendTestString(void);
int sendMessage(int length, char* message);

struct canMessage{
    BOOL StartOfFrame;
    short int ID;
    BOOL RemoteTransmissionRequest;
    BOOL IdentifierExtensionBit;
    BOOL ReservedBit;
    char DataLength;
    char* Data;
    short int CRC;
    BOOL CRCDelim;
    BOOL ACK;
    BOOL ACKDelim;
    char EOF;
};
