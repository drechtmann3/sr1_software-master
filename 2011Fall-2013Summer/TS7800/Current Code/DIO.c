#include "DIO.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <err.h>

volatile unsigned int *dio; // memory-mapped pin registers
/**
@author Michelle Van Enige <mave3@gatech.edu> 727-433-2927
@brief Initializes PC104 connecter.
@detail Opens the memory, sets header to GPIO mode.
**/
void InitDIO()
{
	int memfd;
	// Open onboard shared memory
	memfd = open("/dev/mem", O_SYNC | O_RDWR);
	if(memfd == -1) {
		printf("error opening /dev/mem");
		return;
	}
	// Map DIO section of shared memory
	dio = (unsigned int*)(mmap(0, getpagesize(),
			PROT_READ | PROT_WRITE, MAP_SHARED, memfd, DIO_BASE));
	if(dio == MAP_FAILED) {
		printf("error mapping /dev/mem");
		return;
	}

	/* Set PC/104 header to GPIO mode (TS7800 manual claims
	   that the PC/104 header starts up in GPIO mode by default
	   but this doesn't seem to be strictly true,
	   so the mode is set explicitly) */
	dio[GPIO_MODE_A] = 0;
	dio[GPIO_MODE_B] = 0;
	dio[GPIO_MODE_C] = 0;
	dio[GPIO_MODE_D] = 0;

}
/**
@author Michelle Van Enige <mave3@gatech.edu> 727-433-2927
@brief This function initializes DIO direction. 
@detail Direction is determined by the Row Offset +4.
**/
void InitDIO_direction(int pinNum, int RowOffset, int direction)
{
	SetPin(pinNum, RowOffset+4, direction); //initializes DIO direction. Direction is determined by the Row Offset +4. 
}
/**
@author Michelle Van Enige <mave3@gatech.edu> 727-433-2927
@brief This function returns value of pin.
@detail Using the IsGroundRaw function.
**/
int CheckPin(int pinNum, int rowOffset)
{ 
// Non-debounced GPIO pin read, for use on clean signals.
	// Returns false if grounded
	if (IsGroundRaw(dio[rowOffset], pinNum))
		return 0;
	else
		return 1;
}
/**
@author Michelle Van Enige <mave3@gatech.edu> 727-433-2927
@brief Helper function for CheckPin function
@detail It checks if the pin is grounded.
**/
int IsGroundRaw(int row, int pinNum)
{ //raw pin checking
	return (~(row) & (1 << pinNum));
}
/**
@author Michelle Van Enige <mave3@gatech.edu> 727-433-2927
@brief This function assigns values to pins.
@detail If there is value to be assigned to a pin, it is ORed with a bitshift. If there is no value, it is "unset": ANDed with a one's complement
**/
void SetPin(unsigned int pinNumber, unsigned int pageOffset, int val)
{ //Set the pin [pinNumber] on row [pageOffset] to [val].
	if (val)
		dio[pageOffset] |= (1<<pinNumber);  //set
	else
		dio[pageOffset] &= ~(1<<pinNumber); //unset
}

/**
@author Brian Kuo <brian.kuo@gatech.edu> 703-606-9686
@brief This function debounces button presses
**/



int checkPinDebounce(int pinNum, int rowOffset){
	int o = CheckPin(pinNum, rowOffset);
	int i;
	int count = 0;
	while (count > 40){
		i = CheckPin(pinNum, rowOffset);
		
		if (i == o){
			count++;
		}else{
			count = 0;
			o = i;
		}	
	}
	return o;
}
