#include "Gyrocode.h"
#include "pins.h"
#include "stdio.h"
#include "DIO.h"

void InitGyro()
{

	// Initiates pins
	    // initialize pin directions 
        InitDIO_direction(GYRO_SPC,  GYRO_SPC_ROW, GPIO_OUTPUT);
        InitDIO_direction(GYRO_SDI,  GYRO_SDI_ROW, GPIO_OUTPUT);
        InitDIO_direction(GYRO_SDO,  GYRO_SDO_ROW, GPIO_INPUT);
        InitDIO_direction(GYRO_CS,   GYRO_CS_ROW, GPIO_OUTPUT);
        InitDIO_direction(GYRO_INT2, GYRO_INT2_ROW, GPIO_INPUT);
        InitDIO_direction(GYRO_INT1, GYRO_INT1_ROW, GPIO_INPUT);
       
        // initialize outputs
        SetPin(GYRO_SPC,  GYRO_SPC_ROW, 1);
        SetPin(GYRO_CS,  GYRO_CS_ROW, 1);
		
}
int wrt;
int bit1;
int j;
int writeData(char command, char command_data)
{
	SetPin(GYRO_CS, GYRO_CS_ROW,0);
	for (j = 0; j < 8; j++)
	{
		bit1 = command & (1<<(7-j))>>(7-j);
		SetPin(GYRO_SDI, GYRO_SDI_ROW, bit1);
		SPCclockCycle(GYRO_SPC, GYRO_SPC_ROW);
		
	}
	
	for (j = 0; j < 8; j++)
	{
	
		wrt =  command_data & (1<<(7-j))>>(7-j);
		SetPin(GYRO_SDI, GYRO_SDI_ROW, wrt);
		SPCclockCycle(GYRO_SPC, GYRO_SPC_ROW_);
	}
	
	return 0;
}
		



int ret;//sets variable for storage
int readData(char command);//data reading function
{
	int i;
	SetPin(GYRO_CS,GYRO_CS_ROW,0);//set cs low
	int bit = 1;
	SetPin(GYRO_SDI, GYRO_SDI_ROW, bit);//sets the bit to be given to the pin
	SPCclockCycle(GYRO_SPC, GYRO_SPC_ROW);
	for (i = 0; i < 7; i++)
	{
		bit = (command & (1<<(6-i))>>(6-i);
		SetPin(GYRO_SDI, GYRO_SDI_ROW, bit);//sets the bit to be given to the pin
		SPCclockCycle(GYRO_SPC, GYRO_SPC_ROW);
	}
	
	for (i = 0; i < 8 ; i++) //gather data one bit at a time and store it in ret
	{
		SPCclockCycle(GYRO_SPC, GYRO_SPC_ROW);
		ret <<= 1;
		ret |= CheckPin(GYRO_SDO, GYRO_SDO_ROW);//
		
		
	}
	SetPin(GYRO_CS,GYRO_CS_ROW,1);//set cs high to end transmission of data
	return ret;
}


//set clock high, set clock low function
void SPCclockCycle(int clk,int clk_row)
{
SetPin(clk,clk_row,1);
SetPin(clk,clk_row,0);
}