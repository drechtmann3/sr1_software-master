#include <stdio.h>
#include <termios.h>

typedef struct File{
	char* deviceFile;
	FILE* file;
	int devicefd;
} CommChannel;

CommChannel RS485_setup(char *deviceFile, speed_t baud);	
void RS485_close(CommChannel);   
char RS485_write(char *cmd, CommChannel);
char RS485_read(char *rsp, CommChannel);
char RS485_readWithTimeout(CommChannel com, char* res, long secs, long microsecs);



#define COM2_DEV	("/dev/ttyS1")
#define COM3_DEV	("/dev/ttyS2")
#define COM2_RS458_DEV	("/dev/ttts2")
#define SUCCESS (0)
#define FAILURE (1)
#define TIMEOUT (2)

