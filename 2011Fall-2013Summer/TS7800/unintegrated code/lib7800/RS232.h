/* Generic RS232 communication */

#ifndef RS232_H
#define RS232_H

#include <termios.h>

/* 	Set up connection. For the TS-7800, typically deviceFile will
 *	be something like "/dev/TTYS0" and devicefd is uninitialized,
 *	to be used as a device file pointer for use by other functions. */
void RS232_setup(char *deviceFile, int *devicefd, int timeout, speed_t baud);
// 	Close connection 
void RS232_close(int devicefd);   
// 	Send to RS232 line 
int RS232_write(char *cmd, int devicefd);
// 	Read from RS232 line 
int RS232_read(char rsp[], int devicefd, int response_length);

#endif
