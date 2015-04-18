/**
	@file motor.c
	@author Reid Kersey <reidkersey@gmail.com> 678-736-0899
	@brief This file contains functions that control the motor.
	@details This file contains functions that communicate with
	the Motor Controller via a RS-232 line. The data coming into
	this file, is mainly from the ADC pedal inputs. The output to
	the motor controller is determined by a veriety of factors, 
	including the current pedal status, speed limit, and airgap.
	@warning The function MC_Setup must be run before any communication
	is attempted with the motor controller.
	@todo Cruise Control (Speed Mode)
	@todo Airgap
	@todo Startup procedure
	@ingroup motor
	@addtogroup motor Motor
	@brief Contains the functions for contolling the motor controller.
	@{
*/

#include "motor.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "comm.h"
#include "ADC.h"
#include "DIO.h"
#include "datastore.h"
#include "LCD.h"
#include "pins.h"

static int com1fd;	// File descriptor for serial port access.
static int throttleMax;
static int regenMax;
static int throttleMin;
static int regenMin;
static int targetCurrent;
static int currentCurrent;
static int speed;
static int regen;
static int throttle;
const float WHEEL_DIAMETER=18.5; //in inches

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
void SetupPedals(){
	GetBrake();
	printf("Take foot off pedals\n");
	setStep(STEP0);
	getchar();
	regenMin = ADCAverage(REGEN_CHANNEL, 10)+DEADBAND;
	throttleMin = ADCAverage(THROTTLE_CHANNEL, 10)+DEADBAND;
	printf("Press throttle down fully.\n");
	setStep(STEP1);
	getchar();
	throttleMax = ADCAverage(THROTTLE_CHANNEL, 10)-DEADBAND;
	printf("Press regen down fully.\n");
	setStep(STEP2);
	getchar();
	regenMax = ADCAverage(REGEN_CHANNEL, 10)-DEADBAND;
	printf("throttle max = %d\n throttle min = %d \n regen min = %d \n regen max = %d\n", throttleMax, throttleMin, regenMin, regenMax);
	setRegenMax(regenMax);
	setRegenMin(regenMin);
	setThrottleMax(throttleMax);
	setThrottleMin(throttleMin);
	setStep(STEP3);
	getchar();
	setStep(STEP4);
}

/**
@author Reid Kersey <reidkersey@gmail.com> 678-736-0899
@brief This function is what is run in the thread. It should take care of everything that the motor controller needs to keep track of.
@todo Change between torque and speed
*/
void runMotor()
{	
	GetBrake();
	getFaults();
	getMotorStatus();
	torqueControl();
	printf("speed = %f\n", calculateSpeedMPH(speed));
}

/**
@author Michelle Van Enige <mave3@gatech.edu> 727-433-2927
@author Reid Kersey <reidkersey@gmail.com> 678-736-0899
@brief This function updates the target current.
@note The max value for the Throttle Register should be around 950, meaning 95A.
*/
void torqueControl()
{	
	if(currentCurrent != targetCurrent) {  // update phase current command
		//Update the phase current
		printf("target current = %d \n", targetCurrent);
		MC_SetRegister(MC_THROTTLE_REGISTER, targetCurrent); 
		currentCurrent = targetCurrent;
	}
}

/**
@author Michelle Van Enige <mave3@gatech.edu> 727-433-2927
@author Reid Kersey <reidkersey@gmail.com> 678-736-0899
@brief Updates current motor status, airgap, and brake.
@todo Add airgap functionality
*/
void getMotorStatus()
{ // Update the current motor status
	speed = DHZ_TO_RPM * MC_Query(Q_ACTUAL_SPEED);
	int Throttle = GetThrottle() - GetRegen();
	if(Throttle < 0){
		printf("regen ON\n");
		regen = 1;
	}
	else{
		printf("regen OFF\n");
		regen = 0;
	}
	throttle = Throttle;
	targetCurrent = Throttle;
}
/** 
@author Michelle Van Enige <mave3@gatech.edu> 727-433-2927
@author Reid Kersey <reidkersey@gmail.com> 678-736-0899
@brief This function gets the faults.
*/
void getFaults()
{
	printf("FAULT 1: %d\nFAULT 2: %d\nFAULT 3: %d\nFAULT 4: %d\n", MC_Query(Q_FAULT1LATCH), MC_Query(Q_FAULT2), MC_Query(Q_FAULT3),MC_Query(Q_FAULT4));
}

/**
@author Matt Olson <matt.a.olson@gmail.com> 404-680-0566
@author Reid Kersey <reidkersey@gmail.com> 678-736-0899
*/
int GetThrottle()
{ //Poll ADC for throttle pedal position
	int throttle = 0;
	throttle = getThrottle();
	throttle = throttle - throttleMin;
	double dthrottle = (double)throttle;
	dthrottle = (dthrottle/((double)throttleMax-(double)throttleMin)) * (double)MAX_PHASE_CURRENT;
	if(dthrottle < 0){
		dthrottle = 0;
	}
	printf("dthrottle = %f\n", dthrottle);
	return (int)dthrottle;
}
/**
@author Matt Olson <matt.a.olson@gmail.com> 404-680-0566
@author Reid Kersey <reidkersey@gmail.com> 678-736-0899
*/
int GetRegen()
{ //Poll ADC for regen pedal position
	int regen = 0;
	regen = ADCAverage(REGEN_CHANNEL, 10);
	regen = regen - regenMin;
	double dregen = (double)regen;
	dregen = (dregen/((double)regenMax-(double)regenMin)) * (double)MAX_PHASE_CURRENT;
	if(dregen < 0){
		dregen = 0;
	}
	if(dregen > MAX_PHASE_CURRENT){
		dregen = 0;
	}
	printf("dregen = %f\n", dregen);
	return 0;//(int)dregen;
}
/**
@author Matt Olson <matt.a.olson@gmail.com> 404-680-0566
@author Reid Kersey <reidkersey@gmail.com> 678-736-0899
@todo funtion place holder. No function actually exists for this.
*/
int GetBrake()
{ //Poll GPIO for brake

	InitDIO_direction(MECH_BRAKE_1_I, 	MECH_BRAKE_1_I_ROW, 	GPIO_INPUT);
	InitDIO_direction(MECH_BRAKE_2_I, 	MECH_BRAKE_2_I_ROW, 	GPIO_INPUT);
	InitDIO_direction(MECH_BRAKE_1_O, 	MECH_BRAKE_1_O_ROW, 	GPIO_OUTPUT);
	InitDIO_direction(MECH_BRAKE_2_O, 	MECH_BRAKE_2_O_ROW, 	GPIO_OUTPUT);
	
	SetPin(MECH_BRAKE_1_O, MECH_BRAKE_1_O_ROW, 1);
	SetPin(MECH_BRAKE_2_O, MECH_BRAKE_2_O_ROW, 1);
	
	printf("cp1 = %d\ncp2 = %d\n", CheckPin(MECH_BRAKE_2_I, MECH_BRAKE_2_I_ROW), CheckPin(MECH_BRAKE_1_I, MECH_BRAKE_1_I_ROW));
	
	if(checkPinDebounce(MECH_BRAKE_2_I, MECH_BRAKE_2_I_ROW) == 1 && checkPinDebounce(MECH_BRAKE_1_I, MECH_BRAKE_1_I_ROW) == 1 ){
		SetPin(LIGHT_BRAKE, LIGHT_BRAKE_ROW, 1);
		printf("mech brake on\n");
	}else if(regen == 1){
		SetPin(LIGHT_BRAKE, LIGHT_BRAKE_ROW, 1);
		printf("regen brake on\n");
	}else{
		printf("brake off\n");
		SetPin(LIGHT_BRAKE, LIGHT_BRAKE_ROW, 0);
	}
	return 1;
}

/**
@author Matt Olson <matt.a.olson@gmail.com> 404-680-0566
@author Reid Kersey <reidkersey@gmail.com> 678-736-0899
@todo Make it cleaner and nicer. variables match. etc.
@brief Sets up the motorcontroller(serial com and EEPROM)
*/
void MC_Setup()
{
	InitDIO_direction(MECH_BRAKE_1_I, 	MECH_BRAKE_1_I_ROW, 	GPIO_INPUT);
	InitDIO_direction(MECH_BRAKE_2_I, 	MECH_BRAKE_2_I_ROW, 	GPIO_INPUT);
	InitDIO_direction(MECH_BRAKE_1_O, 	MECH_BRAKE_1_O_ROW, 	GPIO_OUTPUT);
	InitDIO_direction(MECH_BRAKE_2_O, 	MECH_BRAKE_2_O_ROW, 	GPIO_OUTPUT);
	
	RS232_setup(COM1_DEV, &com1fd, TIMEOUT, B9600);	//set up serial comm
	printf("set eeprom\n");
	MC_SetEEPROM(); // initialize EEPROM registers
	
	targetCurrent = 0;
	MC_SetRegister(MC_THROTTLE_REGISTER, 0); //phase current 0dA.
	MC_SetRegister(MC_SPEED_REGISTER, 0); //speed 0dHz.
	currentCurrent = 0;
	MC_Command(SET_TORQUE_CONTROL);
}

/**
@author Matt Olson <matt.a.olson@gmail.com> 404-680-0566
@author Reid Kersey <reidkersey@gmail.com> 678-736-0899
@brief closes RS232 connection
@todo we are only using one rs232. We should not have to give the 232 function the device code
*/
void MC_CloseConnection()
{
	RS232_close(com1fd);
}

/**
@author Matt Olson <matt.a.olson@gmail.com> 404-680-0566
@author Reid Kersey <reidkersey@gmail.com> 678-736-0899
@brief Set up motor controller EEPROM registers. 
@todo clean up the RS232 reads and writes. Make a nicer function to handle motor controll comand read and writes.

*/
void MC_SetEEPROM()
{ 
	printf("command1\n");
	sendCommand(DISABLE_COMMAND, com1fd); // disable commands for EEPROM programming.
	printf("command1\n");
	sendCommand(SET_PROGRAM_MODE, com1fd); // enable EEPROM programming.
	/* write EEPROM registers */
	printf("send commands\n");
	sendCommand(SET_SERIAL_MODE, com1fd); // set controller in serial mode.
	sendCommand(DISABLE_SERIAL_ECHO, com1fd); // disable serial echo from motor controller.
	sendCommand(SET_WATCHDOG, com1fd); //set watchdog
	sendCommand(SET_OPERATE_MODE, com1fd); // disable EEPROM programming.
	sendCommand(ENABLE_COMMAND, com1fd); // re-enable commands.
	
}

/**
@author Reid Kersey <reidkersey@gmail.com> 678-736-0899
@brief  This sends a command to the motor controller
@warning All commands must have a "\\n" at the begining
@param cmd This is the character array(string) of the command to be sent
@param devicefd This is the device that the command will be sent to
*/
void sendCommand(char *cmd, int devicefd){
	char response[RSPSIZE];
	int i = 0;
	RS232_write(cmd, devicefd); // re-enable commands.
	do {
		RS232_read(response, devicefd, RSPSIZE);
		i++;
		if(i > 1){
			RS232_write(cmd, devicefd);
			printf("I reset\n");
		}
	} while ( strcmp(response, "Ok\n") );
	printf("FEEDBACK = %d\n", RS232_read(response, com1fd, RSPSIZE));
}

/**
@author Matt Olson <matt.a.olson@gmail.com> 404-680-0566
@author Reid Kersey <reidkersey@gmail.com> 678-736-0899
@brief  Set a motor controller register. 
*/
void MC_SetRegister(int register_number, int value)
{
	char cmd[MSGSIZE];
	char response[RSPSIZE];

	snprintf(cmd, MSGSIZE, "%02d=%d\n", register_number, value); // set up command string
	RS232_write(cmd, com1fd);
	RS232_read(response, com1fd, RSPSIZE);
	printf("FEEDBACK = %s\n", response);
}

/**
@author Matt Olson <matt.a.olson@gmail.com> 404-680-0566
@author Reid Kersey <reidkersey@gmail.com> 678-736-0899
@brief  Send a command to the motor controller. 
@param command_code the code to send
*/
void MC_Command(char *command_code)
{	
	char response[RSPSIZE];
	
	RS232_write(command_code, com1fd);
	RS232_read(response, com1fd, RSPSIZE);
	printf("RS232 feedback %s\n", response);
	
}

/**
@author Matt Olson <matt.a.olson@gmail.com> 404-680-0566
@author Reid Kersey <reidkersey@gmail.com> 678-736-0899
@brief   MC_Query a motor controller register value.  
@param q_code the code of the value to query
*/
int MC_Query(char *q_code)
{  
	char response[RSPSIZE];

	RS232_write(q_code, com1fd);
	RS232_read(response, com1fd, RSPSIZE);

	return atoi(response);
}

/**
@author Andrey Kurenkov <akurenkov3@gatech.edu> 678-900-4326
@brief converts rpm to mph
*/
float calculateSpeedMPH(int rpm)
{ 	//calculate the speed in MPH given dHz.
	float PI=3.14159;
	int rph=rpm*60;
	return ((int)((WHEEL_DIAMETER * PI * rph) / (5280 * 12))); 
}


/**
@}
*/


