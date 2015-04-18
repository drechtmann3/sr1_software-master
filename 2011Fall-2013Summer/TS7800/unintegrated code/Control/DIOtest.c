#include <stdlib.h>
#include <stdio.h>
#include "wrapper.h"
#include "DIO.h"

/**
@author Matt Olson <matt.a.olson@gmail.com> 404-680-0566

@brief  DIO input check. Usage:
 DIOtest [channel] 

@return (to stdout) either '1' (grounded) or '0' (not grounded). 
*/
int main(int argc, char *argv[])
{
	int pin_num, output_level = 1;

	// DIO setup
	InitDIO(TOTAL_GPIO);
	for ( pin_num = 0; pin_num < 32; pin_num++ ) {
		InitDIO_direction(pin_num, CONTROL_GPIO_DIR_ROW, GPIO_OUTPUT);
	}

	// put out square waves on all Row A pins
	while ( 1 ) {
		output_level ^= 1; // flip bit
		for ( pin_num = 0; pin_num < 32; pin_num++ )
			SetPin( pin_num, CONTROL_GPIO_DAT_ROW, output_level );
	}

}
