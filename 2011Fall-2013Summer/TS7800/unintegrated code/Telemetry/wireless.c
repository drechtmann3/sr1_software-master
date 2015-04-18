/**
* @ingroup telemetry
* @defgroup wireless Wireless
* @brief Wireless functions
* 
* @{
*/

#include "wireless.h"
#include <stdlib.h>
#include <stdio.h>
#include <termios.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>
#include <err.h>
#include "datalog.h"
#include "DIO.h"


static FILE * wirelessFile;
static int packetNum;
static int powerLevel;
static int devicefd;
/**
@author Reid Kersey <reidkersey@gmail.com> 678-736-0899

@brief This function initializes the wireless device

@warning This function must be run before any of the send/receive wireless data functions are called

@details This function takes in the pins of a wireless device, opens the UART, sets the file stream, and then initilaizes the CMD pin direction

@param device This is a sturcture of settings for the wireless device
@return This function returns a 0 if it does not work, and a 1 if it does.
*/
int initWireless(struct WirelessPins *device)
{
	struct termios setup; // COM2 attribute structure.
	int memfd;
	
	// Open onboard shared memory
	memfd = open("/dev/mem", O_SYNC | O_RDWR); 
        if(memfd == -1) { 
                logMessage("error opening /dev/mem", 5);
                return 0;
        }
	//Set up COM2 serial port.
	// Open COM2 for reading and writing
	devicefd = open(device->uart, O_RDWR|O_NOCTTY);

	if(devicefd  == -1) {
		// Print error message if unable to open COM2
		perror("error opening COM3 UART");
		logMessage("error opening COM3 UART", 4);
		return 0;
	} else if(tcgetattr(devicefd , &setup)) {// Get COM2 port attributes
		//unable to get attributes
		perror("tcgetattr() error");	
		logMessage("error opening COM3 UART", 4);
		return 0;
	}
	setup.c_cflag=CS8|CREAD|CLOCAL;
	setup.c_lflag = 0;
	setup.c_cflag = 0;
 	setup.c_cflag |=  CS8;        //Select 8 data bits 
	setup.c_cc[VTIME] = 10 *10;
	setup.c_cc[VMIN] = 0;
	cfsetispeed(&setup, device->baud);	
	cfsetospeed(&setup, device->baud);	
	tcsetattr(devicefd, TCSANOW, &setup); 	//set attributes
	FILE* file=fdopen(devicefd,"r+");//r+ opens file for reading and writing
	fflush(file);
	wirelessFile = file;
	
	InitDIO_direction(device->cmd, device->cmd_row+4, GPIO_OUTPUT);
	logMessage("Wireless device initialized successfully", 0);
	return 1;
}

/**
@author Reid Kersey <reidkersey@gmail.com> 678-736-0899

@brief This sends data back to the HMI telem computer, and checks for a response. This function is the only one that should be accessed by outside sources

@details This function sends the data in the format of 'date, time, component, data, packet#, termination' This function will then wait for a response
and may send instructions to increase the signal power.

@note DATA_String an example string would be someting like: 071512|~233715|~BMS|~07|~{etc}|~1|~~|$

@param device This is a sturcture of settings for the wireless device
@param component This is a character representation of the general name of the data you are to be sending
@param data	This is a character array with each "string" being one piece of data
@param numDataElements This is the number of "strings" that are to be sent
*/
void sendWirelessData(struct WirelessPins *device, char* component, char** data, int numDataElements){
	int i;
	char wirelessString[10240];
	sprintf(wirelessString, "%s|~%s|~%s|~", getDate(), getTime(), component);
	for(i = 0; i < numDataElements; i++){
		sprintf(wirelessString, "%s|~", data[i]);
	}
	sprintf(wirelessString, "%d|~", packetNum);
	sprintf(wirelessString, "~|$");
	sendWirelessPacket(device, wirelessString);
}

/**
@author Reid Kersey <reidkersey@gmail.com> 678-736-0899

@brief This packet will keep sending data until an appropriate ACK sequence is received.

@details This packet will keep sending data until an appropriate ACK sequence is received. 
If an ACK sequence is not received after two messages are sent, the function will increase the power level.

@param device This is a sturcture of settings for the wireless device
@param packet This is the finished packetized string, formated by sendWirelessData. It could be exceptionally long.
*/
void sendWirelessPacket(struct WirelessPins *device, char* packet){
	int i;
	int response = 0;
	for(i = 0; response == 0; i++){
		if(i > 2){
			powerLevel += 1;
			setPowerLevel(device);
			i = 0;
		}
		fprintf(wirelessFile, "%s", packet);
		response = waitForResponse(device);
	}
}

/**
@author Reid Kersey <reidkersey@gmail.com> 678-736-0899

@brief This function waits a set interval to receive an ACK packet from the Telemetry computer.

@param device This is a sturcture of settings for the wireless device
*/
int waitForResponse(struct WirelessPins *device){
	char ack[50];
	struct timeval timeout = { 0, WIRELESS_TIMEOUT};
    fd_set set;
    FD_ZERO(&set);
    FD_SET(devicefd, &set);
	
	if(!select(1, &set, NULL, NULL, &timeout) == 1)
	{
      logMessage("Wireless Read Timeout", 2);
      return 0;
	}
	
	int result=fscanf(wirelessFile,"%s",ack);

	if(result==EOF){
		logMessage("Wireless read error", 2);
		return 0;
	}
	
	if(parseACK(ack, device) != 0){
		return 1;
	}else{
		return 0;
	}
}

/**
@author Reid Kersey <reidkersey@gmail.com> 678-736-0899

@brief This packet checks the ACK repsonse to make sure that is correct

@details This packet checks the ACK repsonse to make sure that is correct.
The ACK should be in the format of 'ACK String, lower TX level (0 is no, 1 is yes), termination string
This function checks the ACK packet for a TX level down command, and if it is received, it will lower the
power level of the device.

@note ACK_String device should receive a response like: ACK|~0|~~|$

@param device This is a sturcture of settings for the wireless device
@param ack This is the acknowlegement string received by the device
@return This function will return a 0 if the ACK is incorrect or a 1 if the ACK is correct
*/
int parseACK(char* ack, struct WirelessPins *device){
	int i;
	int changePowerLevel = 0;
	char ack_check[5] = {'A', 'C', 'K', '|', '~'};
	char term_check[3] = {'~', '|', '$'};
	for(i = 0; i < 5; i++){
		if(ack[i] != ack_check[i]){
			return 0;
		}
	}
	if(ack[5] == 1){
		changePowerLevel -= 1;
	}
	for(i = 0; i < 5; i++){
		if(ack[i+6] != term_check[i]){
			return 0;
		}
	}
	if(changePowerLevel == 1){
		powerLevel -= 1;
		setPowerLevel(device);
	}
	return 1;
}

/**
@author Reid Kersey <reidkersey@gmail.com> 678-736-0899

@brief This function changes the TX power level to be higher or lower

@details This function sets the devices CMD pin, and then sends the code
for setting the power level, and then it sets the power level. 100uS sleep
times are adhered to.

@param device This is a sturcture of settings for the wireless device
*/
void setPowerLevel(struct WirelessPins *device){
	SetPin(device->cmd, device->cmd_row, 1);
	usleep(100);
	fprintf(wirelessFile, "%c", (char)0x3A);
	if(powerLevel < 0) powerLevel = 0;
	if(powerLevel > 4) powerLevel = 4;
	fprintf(wirelessFile, "%c", (char)powerLevel);
	usleep(100);
	logMessage("TX Transmit power level changed", 0);
	SetPin(device->cmd, device->cmd_row, 1);
}

/**
* @}
*/
