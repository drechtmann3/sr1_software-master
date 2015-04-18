#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <string.h>

#include "MotorController.h"
#include "mc_fault_codes.h"
#include "MC_commands.h"
#include "RS232.h"

#define COM1_DEV	("/dev/ttyS0")	//device file for COM1
#define MSGSIZE		(10) 			//size of messages to controller
#define RSPSIZE		(20) 			//size of responses from controller
#define TIMEOUT		(1)				//serial timeout (seconds)

static int com1fd;		  			// File descriptor for serial port access.

/**
@author Matt Olson <matt.a.olson@gmail.com> 404-680-0566

@brief Sets up the motorcontroller(serial com and EEPROM)
*/
void MC_Setup(void)
{
	#ifdef MC_DEBUG
		printf("Running MCsetup...\n");
	#endif

	RS232_setup(COM1_DEV, &com1fd, TIMEOUT, B9600);	// set up serial comm
	MC_SetEEPROM(); // initialize EEPROM registers

	#ifdef MC_DEBUG
		printf("MCsetup finished.\n");
	#endif
}

/**
@author Matt Olson <matt.a.olson@gmail.com> 404-680-0566

@brief closes RS232 connection
*/
void MC_CloseConnection(void)
{
	RS232_close(com1fd);
}

/**
@author Matt Olson <matt.a.olson@gmail.com> 404-680-0566

@brief Set up motor controller EEPROM registers. 
*/
void MC_SetEEPROM()
{ 
	/* NOTE: the do-while loops on reads are here to catch
	 * echoes that occur before echo is disabled. */

	char response[RSPSIZE];

	RS232_write(DISABLE_COMMAND, com1fd); // disable commands for EEPROM programming.
	do {
		RS232_read(response, com1fd, RSPSIZE);
	} while ( strcmp(response, "Ok\n") );

	RS232_write(SET_PROGRAM_MODE, com1fd); // enable EEPROM programming.
	do {
		RS232_read(response, com1fd, RSPSIZE);
	} while ( strcmp(response, "Ok\n") );

	/* write EEPROM registers */
	RS232_write(SET_SERIAL_MODE, com1fd); // set controller in serial mode.
	do {
		RS232_read(response, com1fd, RSPSIZE);
	} while ( strcmp(response, "Ok\n") );

	RS232_write(DISABLE_SERIAL_ECHO, com1fd); // disable serial echo from motor controller.
	do {
		RS232_read(response, com1fd, RSPSIZE);
	} while ( strcmp(response, "Ok\n") );
	/* finished writing EEPROM registers */

	RS232_write(SET_OPERATE_MODE, com1fd); // disable EEPROM programming.
	do {
		RS232_read(response, com1fd, RSPSIZE);
	} while ( strcmp(response, "Ok\n") );

	RS232_write(ENABLE_COMMAND, com1fd); // re-enable commands.
	do {
		RS232_read(response, com1fd, RSPSIZE);
	} while ( strcmp(response, "Ok\n") );

}

/**
@author Matt Olson <matt.a.olson@gmail.com> 404-680-0566

@brief  Set a motor controller register. 
*/
void MC_SetRegister(int register_number, int value)
{
	char cmd[MSGSIZE];
	char response[RSPSIZE];

#ifdef MC_DEBUG
	printf("MC_SetRegister(): setting register %02d to value %d\n", register_number, value);
#endif /* #ifdef DEBUG */

	snprintf(cmd, MSGSIZE, "%02d=%d\n", register_number, value); // set up command string
	RS232_write(cmd, com1fd);
	RS232_read(response, com1fd, RSPSIZE);
}

/**
@author Matt Olson <matt.a.olson@gmail.com> 404-680-0566

@brief  Send a command to the motor controller. 
@param command_code the code to send
*/
void MC_Command(char *command_code)
{	
	char response[RSPSIZE];

#ifdef MC_DEBUG
	printf("MC_Command sending %s\n", command_code);
#endif /* #ifdef DEBUG */

	RS232_write(command_code, com1fd);
	RS232_read(response, com1fd, RSPSIZE);
}

/**
@author Matt Olson <matt.a.olson@gmail.com> 404-680-0566

@brief   MC_Query a motor controller register value.  
@param q_code the code of the value to query
*/
int MC_Query(char *q_code)
{  
	char response[RSPSIZE];

#ifdef MC_DEBUG
	printf("MC_Query sending %s\n", q_code);
#endif /* #ifdef DEBUG */

	RS232_write(q_code, com1fd);
	RS232_read(response, com1fd, RSPSIZE);

#ifdef MC_DEBUG
	printf("	MC_Query got back %s\n", response);
#endif /* #ifdef DEBUG */

	return atoi(response);
}


