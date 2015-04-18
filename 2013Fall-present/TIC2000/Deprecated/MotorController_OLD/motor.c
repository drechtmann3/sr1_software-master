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
#include "F2806x_Gpio.h"
#include <string.h>

void scia_init(void);
void scia_fifo_init(void);
char scia_xceive();
void scia_xmit(char a);

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

/*
 * A test main to eventually be merged with other test mains
 * into the one main to rule them all.
 * Note: The system is x28, which means sizeof(char) = sizeof(int) = 16 bits = 1
 * @author PK with help from TI
 */
void main(void) {
	InitSysCtrl(); //PLL, WatchDog, enable Peripheral Clocks. This function is found in the F2806x_SysCtrl.c file.
    InitGpio(); //This function is found in the F2806x_Gpio.c file and illustrates how to set the GPIO to its default state.
    InitSciaGpio(); //Init the pins for the SCI-A port. This function is found in the F2806x_Sci.c file.
    scia_fifo_init();
    scia_init();
	GpioDataRegs.GPADAT.bit.GPIO0 = 1;//make gpio0 and output
    totransmit = getMessage();
    while(1) {
    	sendMessage(totransmit);
    	//puts(".");
    	loopCount++;
    }

    /**
     * UART test sequence. Make sure io out and io in pins (pins 8 and 7,
     * respectively for controlSTICK) are connected to each other and run.
     * @author PK
     */
    /*msg = "Hello World!\0";
    int i;
   	for(i=0; i<strlen(msg); i++) {
    	char transmitChar = msg[i];
   		scia_xmit(transmitChar);
   		printf("Sending: %c\n", transmitChar);
    	receivedChar = scia_xceive.();
        printf("Received: %c\n", receivedChar);
        scia_xmit(receivedChar);
    }*/

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
	puts("speed = %f\n", calculateSpeedMPH(speed));
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
		puts("target current = %d \n", targetCurrent);
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
		puts("regen ON\n");
		regen = 1;
	}
	else{
		puts("regen OFF\n");
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
	puts("FAULT 1: %d\nFAULT 2: %d\nFAULT 3: %d\nFAULT 4: %d\n", MC_Query(Q_FAULT1LATCH), MC_Query(Q_FAULT2), MC_Query(Q_FAULT3),MC_Query(Q_FAULT4));
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
	puts("dthrottle = %f\n", dthrottle);
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
	puts("dregen = %f\n", dregen);
	return 0;//(int)dregen;
}
/**
@author Matt Olson <matt.a.olson@gmail.com> 404-680-0566
@author Reid Kersey <reidkersey@gmail.com> 678-736-0899
@todo funtion place holder. No function actually exists for this.
*/
int GetBrake()
{ //Poll GPIO for brake
//TODO: get from encoders
}

/**
@author Matt Olson <matt.a.olson@gmail.com> 404-680-0566
@author Reid Kersey <reidkersey@gmail.com> 678-736-0899
@todo Make it cleaner and nicer. variables match. etc.
@brief Sets up the motorcontroller(serial com and EEPROM)
*/
void MC_Setup()
{
	//TODO rewrite with correct pins/dio dirction setting
	InitDIO_direction(MECH_BRAKE_1_I, 	MECH_BRAKE_1_I_ROW, 	GPIO_INPUT);
	InitDIO_direction(MECH_BRAKE_2_I, 	MECH_BRAKE_2_I_ROW, 	GPIO_INPUT);
	InitDIO_direction(MECH_BRAKE_1_O, 	MECH_BRAKE_1_O_ROW, 	GPIO_OUTPUT);
	InitDIO_direction(MECH_BRAKE_2_O, 	MECH_BRAKE_2_O_ROW, 	GPIO_OUTPUT);

	RS232_setup(COM1_DEV, &com1fd, TIMEOUT, B9600);	//set up serial comm
	puts("set eeprom\n");
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
@brief Set up motor controller EEPROM registers.
@todo clean up the RS232 reads and writes. Make a nicer function to handle motor controll comand read and writes.

*/
void MC_SetEEPROM()
{
	puts("command1\n");
	sendCommand(DISABLE_COMMAND, com1fd); // disable commands for EEPROM programming.
	puts("command1\n");
	sendCommand(SET_PROGRAM_MODE, com1fd); // enable EEPROM programming.
	/* write EEPROM registers */
	puts("send commands\n");
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
	RS232_write(cmd); // re-enable commands.
	do {
		RS232_read(response, RSPSIZE);
		i++;
		if(i > 1){
			RS232_write(cmd);
			puts("I reset\n");
		}
	} while ( strcmp(response, "Ok\n") );
	puts("FEEDBACK = %d\n", RS232_read(response, com1fd, RSPSIZE));
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

	snputs(cmd, MSGSIZE, "%02d=%d\n", register_number, value); // set up command string
	RS232_write(cmd, com1fd);
	RS232_read(response, com1fd, RSPSIZE);
	puts("FEEDBACK = %s\n", response);
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

	RS232_write(command_code);
	RS232_read(response, RSPSIZE);
	puts("RS232 feedback");

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

	RS232_write(q_code);
	RS232_read(response, RSPSIZE);

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

/*
 * Send an entire string. Sends characters one at a time with scia_xmit().
 * @author PK
 */
void sendMessage(char *message) {
    int i;
    int len = strlen(message);
    for(i=0; i<len; i++) {
      	scia_xmit(message[i]);
    }
}

/*
 * Send a character to the SCI pin. User probably doesn't ever call
 * this directly.
 * @author TI
 */
void scia_xmit(char c) {
    while (SciaRegs.SCIFFTX.bit.TXFFST != 0) {}//wait for current transmit to finish
    SciaRegs.SCITXBUF = c;//write new message element (16 bits)
}

/*
 * Receives a full message by making calls to scia_xceive().//Not using this one yet
 * @author PK
 */
void receiveMessage(char * response, int size) {
	char c = 'a';
	int i = 0;
	while(c != '\0') {
		c = scia_xceive();
		response[i++] = c;
	}
}

/*
 * Read from the RX register when its value changes. User probably never
 * needs to call this directly.
 * @author PK
 */
char scia_xceive() {
    while (SciaRegs.SCIFFRX.bit.RXFFST == 0) {} //wait for a change
    return SciaRegs.SCIRXBUF.all;//return that character (16 bits)
}

//___________________________________________TI code below

/*
 * Test 1, SCIA  DLB, 8-bit word, baud rate 0x000000017, default, 1 STOP bit, no parity
 * @author TI
 */
void scia_init() {
    // Note: Clocks were turned on to the SCIA peripheral
    // in the InitSysCtrl() function
	/**
 	SciaRegs.SCICCR.all =0x0007;   // 1 stop bit,  No loopback. No parity,8 char bits, async mode, idle-line protocol
	SciaRegs.SCICTL1.all =0x0003;  // enable TX, RX, internal SCICLK, Disable RX ERR, SLEEP, TXWAKE
	SciaRegs.SCICTL2.bit.TXINTENA =1;
	SciaRegs.SCICTL2.bit.RXBKINTENA =1;
	SciaRegs.SCIHBAUD    =0x00A0;  // 9600 baud @LSPCLK = 22.5MHz (90 MHz SYSCLK).
    SciaRegs.SCILBAUD    =0x0024;
	SciaRegs.SCICTL1.all =0x0023;  // Relinquish SCI from Reset
	*/
    // Note: Clocks were turned on to the SCIA peripheral
    // in the InitSysCtrl() function

 	SciaRegs.SCICCR.all = 0x0007;   // 1 stop bit,  No loopback
                                   // No parity,8 char bits,
                                   // async mode, idle-line protocol
	SciaRegs.SCICTL1.all = 0x0003;  // enable TX, RX, internal SCICLK,
                                   // Disable RX ERR, SLEEP, TXWAKE
	SciaRegs.SCICTL2.bit.TXINTENA = 1;
	SciaRegs.SCICTL2.bit.RXBKINTENA = 1;//TODO: set to correct baud (something like 19600)
	SciaRegs.SCIHBAUD = 0x0000;  // 115.2k baud @LSPCLK = 22.5MHz (90 MHz SYSCLK).
    SciaRegs.SCILBAUD = 0x0017;
	SciaRegs.SCICTL1.all = 0x0023;  // Relinquish SCI from Reset
}

/*
 * Initalize the SCI FIFO
 * @author TI
 */
void scia_fifo_init() {
    SciaRegs.SCIFFTX.all=0xE040;
    SciaRegs.SCIFFRX.all=0x2044;
    SciaRegs.SCIFFCT.all=0x0;
}

/**
@}
*/
