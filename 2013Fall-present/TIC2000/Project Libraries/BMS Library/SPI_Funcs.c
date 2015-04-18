#include "BMS.h"

/*
 * This file contains the SPI functions.
 */

//Sends the command over SPI
void SpiSend(Uint16 Command){
	int clear_SPI_flag = 0;

	SpiaRegs.SPITXBUF = (Command << 8);

	while(SpiaRegs.SPISTS.bit.BUFFULL_FLAG != 0){}
	clear_SPI_flag |= SpiaRegs.SPIRXBUF; //Using |= instead of = to avoid generating compiler warning
}

//Receive data over SPI
int SpiReceive(){
	Uint16 ret = 0;

	SpiaRegs.SPITXBUF = 0 << 8;
	while(SpiaRegs.SPISTS.bit.BUFFULL_FLAG != 0 || SpiaRegs.SPISTS.bit.INT_FLAG == 0){}
	ret = SpiaRegs.SPIRXBUF;
	return ret;
}


