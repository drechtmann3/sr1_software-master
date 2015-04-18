#include <stdlib.h>
#include <stdio.h>
#include <termios.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/time.h>
#include <sys/select.h>

#include "RS232.h"

//#define USE_SELECT_FOR_RS232

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

	setup.c_lflag |= ICANON; //canonical
	setup.c_lflag &= ~(ECHO); //no echo

	setup.c_cc[VTIME] = timeout * 10;
	setup.c_cc[VMIN] = 0;

	cfsetispeed(&setup, baud);	//input baud	
	cfsetospeed(&setup, baud);	//output baud
	tcsetattr(*devicefd, TCSANOW, &setup);
}

int RS232_write(char *cmd, int devicefd)
{
#ifdef RS232_DEBUG
	printf("	RS232_write %s", cmd);
#endif /* #ifdef RS232_DEBUG */
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

#ifdef USE_SELECT_FOR_RS232
	/* stuff for select() (here for convenience if it's decided
		that a select() call is desirable). see
		www.easysw.com/~mike/serial/serial.html, under the advanced serial
		programming section, for more info on how this works. */
	
	int n;
	int max_fd = devicefd + 1;
	fd_set input;
	struct timeval timeout;
	FD_ZERO(&input);
	FD_SET(devicefd, &input);
	timeout.tv_sec = 5;
	timeout.tv_usec = 0;
	n = select(max_fd, &input, NULL, NULL, &timeout);
	if (n < 0)
		perror("select failed");
	else if (n == 0)
		puts("select timeout");
	else {
#endif  /* #ifdef USE_SELECT_FOR_RS232 */

	memset(rsp, 0, strlen(rsp)); //clear rsp 

	ssize_t rsize = read( devicefd, rsp, (ssize_t)response_length );
	if( rsize == -1 )	{
		perror("RS232 read error"); 
		return 1;
	} else if( rsize == 0 ) {
		perror("Connection timeout");
		return 1;
	}

#ifdef RS232_DEBUG
		printf( "	RS232 read returned: %s", rsp );
#endif /* #ifdef RS232_DEBUG */

#ifdef USE_SELECT_FOR_RS232
	}
#endif  /* #ifdef USE_SELECT_FOR_RS232 */

	return rsize;
}

void RS232_close(int devicefd) 
{
	close(devicefd);
}
