//Wireless Test
#include <stdlib.h>
#include <stdio.h>
#include <termios.h>

#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>
#include <err.h>

FILE* wirelessStream;
char initWireless();
void sendChar(char ch);
FILE* wireless_setup(char *deviceFile, int timeout, speed_t baud);
int main(){
	char i = initWireless();
	while(i == 'S'){
		sendChar('~');
		printf("char i printed\n");
		usleep(1000000);
	}
	
}


void sendChar(char ch){
	fprintf(wirelessStream, "Hello World!\n");
}

char initWireless()
{
	wirelessStream= wireless_setup("/dev/ttts6", 10,B9600);
	if(wirelessStream==NULL)
		return 'F';
	return 'S';
}

FILE* wireless_setup(char *deviceFile, int timeout, speed_t baud)
{

	struct termios setup; // COM2 attribute structure.
	int memfd;
	int devicefd;

	// Open onboard shared memory
	memfd = open("/dev/mem", O_SYNC | O_RDWR); 
        if(memfd == -1) { 
                perror("error opening /dev/mem"); 
                return NULL;
        }
	//Set up COM2 serial port.
	// Open COM2 for reading and writing
	devicefd = open(deviceFile, O_RDWR|O_NOCTTY);

	if(devicefd  == -1) {
		// Print error message if unable to open COM2
		perror("error opening COM2");	
		return NULL;
	} else if(tcgetattr(devicefd , &setup)) {// Get COM2 port attributes
		//unable to get attributes
		perror("tcgetattr() error");	
		return NULL;
	}
	setup.c_cflag=CS8|CREAD|CLOCAL;
	setup.c_lflag = 0;
	setup.c_cflag = 0;
 	setup.c_cflag |=  CS8;        //Select 8 data bits 
	setup.c_cc[VTIME] = timeout *10;
	setup.c_cc[VMIN] = 0;
	cfsetispeed(&setup, baud);	
	cfsetospeed(&setup, baud);	
	//fcntl(devicefd, F_SETFL, FNDELAY);// use to set to non-blocking mode 
	tcsetattr(devicefd, TCSANOW, &setup); 	//set attributes
	FILE* file=fdopen(devicefd,"r+");//r+ opens file for reading and writing
	fflush(file);
	return file;
}
