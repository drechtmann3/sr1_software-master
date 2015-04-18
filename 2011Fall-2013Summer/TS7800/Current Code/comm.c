#include "comm.h"
#include <stdlib.h>
#include <stdio.h>
#include <termios.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

void RS232_setup(char *deviceFile, int *devicefd, int timeout, speed_t baud)
{ 
	struct termios setup; // attribute structure
	*devicefd = open( deviceFile, O_RDWR|O_NOCTTY|O_NDELAY );

	fcntl( *devicefd, F_SETFL, 0 ); // set reads to blocking.

	if( *devicefd == -1 ) {
		perror("error opening COM1");	
		return;
	} else if( tcgetattr(*devicefd, &setup) ) {
		perror( "tcgetattr() error" );
		return;
	}
	setup.c_iflag |= ICRNL; //input CR -> NL

	setup.c_oflag |= ONLCR; //output NL -> CR

	setup.c_cflag |= CS8 | CREAD;
	setup.c_cflag &= ~CRTSCTS; //no HW flow control

	setup.c_lflag |= ICANON; //not-canonical
	setup.c_lflag &= ~(ECHO); //no echo

	setup.c_cc[VTIME] = timeout;
	setup.c_cc[VMIN] = 3;

	cfsetispeed(&setup, baud);	//input baud	
	cfsetospeed(&setup, baud);	//output baud
	tcsetattr(*devicefd, TCSANOW, &setup);
}

int RS232_write(char *cmd, int devicefd)
{
	tcflush(devicefd, TCOFLUSH);  // clear output buffer
	if ( write(devicefd, cmd, strlen(cmd)) != strlen(cmd) ) {
		perror("write() failed!\n");
		return 1;
	}
	tcflush(devicefd, TCIFLUSH);  // clear input buffer
	return 0;
}

int RS232_read(char rsp[], int devicefd, int response_length)
{
/*
	memset(rsp, 0, strlen(rsp)); //clear rsp 
	
	ssize_t rsize = read( devicefd, rsp, (ssize_t)response_length );
	if( rsize == -1 )	{
		perror("RS232 read error"); 
		return 1;
	} else if( rsize == 0 ) {
		perror("Connection timeout");
		return 1;
	}
*/
	memset(rsp, 0, strlen(rsp)); //clear rsp
	fd_set set;
	struct timeval timeout;
	int rv;
	int filedesc = devicefd;

	FD_ZERO(&set); /* clear the set */
	FD_SET(filedesc, &set); /* add our file descriptor to the set */

	timeout.tv_sec = 0;
	timeout.tv_usec = 200000;

	rv = select(filedesc + 1, &set, NULL, NULL, &timeout);
	if(rv == -1)
		perror("select"); /* an error accured */
	else if(rv == 0)
		printf("timeout"); /* a timeout occured */
	else
		read( devicefd, rsp, (ssize_t)response_length ); /* there was data to read */
	
	return rv;
}

void RS232_close(int devicefd) 
{
	close(devicefd);
}

