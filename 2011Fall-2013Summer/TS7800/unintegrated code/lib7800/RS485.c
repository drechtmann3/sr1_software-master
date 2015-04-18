#include "RS485.h"
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>
#include <err.h>

//#define DEBUG 1
//RS-485 is selected by clearing bit 15 of register 0xE800000C
#define SERIAL_BASE	(0xE800000C) 
#define RS485_ENABLE 	(15)

int timeout_mill;
int timeout_sec;
int waitForIn(long secs, long microsecs, int devicefd);

/**
@author Andrey Kurenkov <akurenkov3@gatech.edu> 678-900-4326

@brief This function sets up RS485 communication for the TS7800 SBC

@details a generic RS485 setup function that sets up a standard configuration given 
the defined parameters

@param deviceFile a string linking to a specific 
@param timeout the timeout for read/write operations. If 0 timeout is not enabled. 
@param baud the desired baud rate (read manual for supported rates)
@return the pointer to the stream from which data can be read and written to
*/
CommChannel RS485_setup(char *deviceFile, speed_t baud)
{

	struct termios setup; // COM2 attribute structure.


	//Set up COM2 serial port.
	// Open COM2 for reading and writing
	CommChannel com;
	com.deviceFile=deviceFile;
	com.devicefd = open(deviceFile, O_RDWR|O_NOCTTY);

	if(com.devicefd  == -1) {
		// Print error message if unable to open COM2
		perror("error opening COM2");
		return com;	
	} else if(tcgetattr(com.devicefd , &setup)) {// Get COM2 port attributes
		//unable to get attributes
		perror("tcgetattr() error");	
		return com;
	}
	
	setup.c_cflag=CS8|CREAD|CLOCAL;
	setup.c_lflag |= (ICANON);
	setup.c_lflag &= ~(ECHO);
	setup.c_cflag &= ~PARENB; // Mask the character size to 8 bits, no parity 
 	setup.c_cflag &= ~CSTOPB;
 	setup.c_cflag &= ~CSIZE;
 	setup.c_cflag |=  CS8;        //Select 8 data bits 
	
	cfsetispeed(&setup, baud);	
	cfsetospeed(&setup, baud);	
	//fcntl(devicefd, F_SETFL, FNDELAY);// use to set to non-blocking mode 
	tcsetattr(com.devicefd, TCSANOW, &setup); 	//set attributes
	com.file=fdopen(com.devicefd,"r+");//r+ opens file for reading and writing
	return com;
}

/**
@author Andrey Kurenkov <akurenkov3@gatech.edu> 678-900-4326

@brief This function writes a message to an RS485 connection

@details given a connection that has already been setup, writes the given message 
and returns an error code as appropriate RS485_setup must have been called prior
to calling this function.

@param cmd the message desired to write 
@param file that is the i/o stream to write to
@return char that is an error code as defined by SUCCESS and FAILURE
*/
char RS485_write(char *cmd, CommChannel com)
{
#ifdef DEBUG
	printf("RS485_write %s   \n", cmd);
#endif
	int result=fprintf(com.file,"%s", cmd);
#ifdef DEBUG
	printf("result %d\n", result);
#endif
	if (result<0){
		printf("RS485write() failed!");
		return FAILURE;

	}
	return SUCCESS;
}

/**
@author Andrey Kurenkov <akurenkov3@gatech.edu> 678-900-4326

@brief This function reads data from an RS485 connection

@details given a connection that has already been setup, reads whatever data has
been sent to the SBC and returns it via the appropriate parameter

@param res the character pointer which will be set to point to the received message
@param file that is the i/o stream to read from
@return char that is an error code as defined by SUCCESS and FAILURE
*/
char RS485_read(char *res, CommChannel com)
{

	memset(res, 0, strlen(res)); //clear rsp 
	
	int result= fscanf(com.file,"%s",res); 
	if(result==EOF){
		printf("RS485 read error"); 
		return FAILURE;
	}
#ifdef DEBUG
		printf("RS485 read %s\n", res);
#endif
return SUCCESS;
}

/**
@author Andrey Kurenkov <akurenkov3@gatech.edu> 678-900-4326

@brief This function reads closes an RS485 connection

@details given a connection that has already been setup, this functions fress it

@param file that is the i/o stream to close
*/
char RS485_readWithTimeout(CommChannel com, char* res, long secs, long microsecs)
{
  
   if(!waitForIn(secs, microsecs,com.devicefd))
   {
      printf("RS_485 read timeout\n");	
      return TIMEOUT;
   }
   
   int result=fscanf(com.file,"%s",res);

   if(result==EOF){
	printf("RS485 read error");
	return FAILURE;
   }	
	#ifdef DEBUG
	printf("RS485 read %s\n", res);
	#endif
   return SUCCESS;
}

int waitForIn(long secs, long microsecs, int devicefd)
{ 
    struct timeval timeout = { secs, microsecs};
    fd_set set;
    FD_ZERO(&set);
    FD_SET(devicefd, &set);
    return select(devicefd+1, &set, NULL, NULL, &timeout) == 1;
}
 


/**
@author Andrey Kurenkov <akurenkov3@gatech.edu> 678-900-4326

@brief This function reads closes an RS485 connection

@details given a connection that has already been setup, this functions fress it

@param file that is the i/o stream to close
*/
void RS485_close(CommChannel com) 
{ 
	fclose(com.file);
}




