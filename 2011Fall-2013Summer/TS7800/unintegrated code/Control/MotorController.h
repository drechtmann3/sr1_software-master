/* RS232 serial communication with the NGM motor controller and
 * macros related to the motor controller. */
#ifndef MOTORCONTROLLER_H
#define MOTORCONTROLLER_H

//#include <termios.h>
#include <stdio.h>

//Miscellaneous parameters
#define OPTIMUM_SUPPLY_VOLTAGE	(960)	//deci-Volts

void MC_Setup(void); //set up connection to motor controller
void MC_CloseConnection(void); //close connection

/* The following functions take as arguments the macros from MC_commands.h. */
/* Query a motor controller register. */
int MC_Query(char *q_code);
/* Send a command to the motor controller.*/
void MC_Command(char *command_code);
/* Set a motor controller register value. */
void MC_SetRegister(int register_number, int value);

/* Initialize motor controller EEPROM register. */
void MC_SetEEPROM(void);

#endif
