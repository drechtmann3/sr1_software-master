#ifndef WIRELESS_H
#define WIRELESS_H
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>
#include <err.h>
#include <termios.h>

#define WIRELESS_UART		("/dev/ttts6")
#define WIRELESS_BAUD		(B115200)
#define WIRELESS_TIMEOUT	(100)

struct WirelessPins{  
	int cmd;
	int cmd_row;
	speed_t baud;
	char *uart;
};

void sendWirelessData(struct WirelessPins *device, char* component, char** data, int numDataElements);
void sendWirelessPacket(struct WirelessPins *device, char* packet);
int waitForResponse(struct WirelessPins *device);
int parseACK(char* ack, struct WirelessPins *device);
void setPowerLevel(struct WirelessPins *device);
int initWireless(struct WirelessPins *device);

#endif
