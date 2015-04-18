#ifndef COMM_H
#define COMM_H
#include <termios.h>
void RS232_close(int devicefd);
int RS232_read(char rsp[], int devicefd, int response_length);
int RS232_write(char *cmd, int devicefd);
void RS232_setup(char *deviceFile, int *devicefd, int timeout, speed_t baud);
#endif
