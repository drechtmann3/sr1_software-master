#ifndef MOTOR_H

#define MOTOR_H



#define THROTTLE_CHANNEL			(3)

#define REGEN_CHANNEL				(4)



#define STEP0	(0)

#define STEP1	(1)

#define STEP2	(2)

#define STEP3	(3)

#define STEP4	(4)



#define DEADBAND					(25)



// Datastore names

#define DS_DIRECTION				("Direction")

#define DS_MC_DIRECTION				("MC_Direction")

#define DS_CONTROL_MODE				("Control_Mode")

#define DS_MC_TARGET_CURRENT		("MC_Target_Current")

#define DS_MC_SPEED_RPM				("MC_Speed_RPM")

#define DS_MC_DIRECTION				("MC_Direction")

#define DS_MC_TARGET_SPEED			("MC_Target_Speed")

#define DS_THROTTLE					("Throttle")

#define DS_TARGET_CURRENT			("Target_Current")

#define DS_TARGET_SPEED				("Target_Speed")

#define DS_TARGET_DIRECTION			("Target_Direction")

#define DS_FAULT1					("Fault1")

#define DS_FAULT2					("Fault2")

#define DS_FAULT3					("Fault3")

#define DS_FAULT4					("Fault4")

#define DS_THROTTLE_SCALE			("Throttle_Scale")

#define DS_MAX_THROTTLE				("Max_Throttle")

#define DS_MIN_THROTTLE				("Min_Throttle")

#define DS_MECH_BRAKE				("Mechanical_Brake")

#define DS_REGEN_BRAKE				("Regen_Brake")

#define DS_CRUISE_SPEED				("Cruise_Speed")

#define DS_SPEED_LIMIT				("Speed_Limit")

#define DS_SWITCH_MODE				("Switch_Mode")



#define BRAKE_ON					(1)

#define BRAKE_OFF					(0)



#define MAX_PHASE_CURRENT			(1000)





// State machine macros

#define DIRECTION_FORWARD			(1)

#define DIRECTION_REVERSE			(0)

#define SPEED_CONTROL_INCREMENT		(25)		//dHz

#define MINIMUM_SPEED				(0)			//dHz

/* max speed derived from speed tests performed by Chris McManus et al */

#define MAXIMUM_SPEED				(1400)		//dHz

#define DHZ_TO_RPM					(6)			//1dHz = 6rpm



#define TORQUE_CONTROL				(1)

#define SPEED_CONTROL				(0)

// Airgap macros

// Minimum and maximum reading from potentiometer. Need to calibrate.

#define MIN_GAP 					(100)

#define MAX_GAP 					(1000)

// Number of positions the airgap can stay at. MUST be integer > 1.

#define GAP_POS_NUM (3)

#define GAP_POS_TO_POTEN			(x) (MIN_GAP + (MAX_GAP - MIN_GAP)*x/(GAP_POS_NUM - 1))



#define AIRGAP_PWR_ON  				(1)

#define AIRGAP_PWR_OFF 				(0)



#define DEBUG_AIRGAP_HW

#define MSGSIZE						(10) 			//size of messages to controller

#define RSPSIZE						(20) 			//size of responses from controller

#define TIMEOUT						(1)				//serial timeout (seconds)



#define Q_DESIRED_SPEED				("00?\n")  //serial speed in dHz

#define Q_ACTUAL_SPEED				("0C?\n")  //actual speed in dHz

#define Q_INFORWARD					("A0?\n")  //motor direction (1:=forward)

#define Q_DESIRED_PHASEI			("60?\n")  //desired phase current in dA

#define Q_SUPPLY_VOLTAGE			("64?\n")  //supply voltage in dV

#define Q_MOTOR_TEMP				("65?\n")  //motor temperature (degreesC*10)

#define Q_HEATSINK_TEMP				("66?\n")  //heatsink temp (degreesC*10)

#define Q_DRIVESTATE				("96?\n")  //operating status

#define Q_FAULT1LATCH				("98?\n")

#define Q_FAULT1					("99?\n")

#define Q_FAULT2					("9A?\n")

#define Q_FAULT3					("9B?\n")

#define Q_FAULT4					("9C?\n")



//	Commands

#define ENABLE_COMMAND				("00!\n")  	//Enable controller output

#define DISABLE_COMMAND				("01!\n")  	//Disable controller output

#define SET_THROTTLE_EN				("02!\n")  	//Enable motor throttle

#define UNSET_THROTTLE_EN			("03!\n")  	//Disable motor throttle

#define SET_REVERSE					("04!\n")	//Set the motor to go in reverse

#define SET_FORWARDS				("05!\n")	//Set the motor to go forwards

#define SET_TORQUE_CONTROL			("06!\n")  	//change to torque control mode

#define SET_SPEED_CONTROL			("07!\n")  	//change to speed control mode

#define SET_COAST					("08!\n")  	//force desired current to zero

#define SET_PROGRAM_MODE			("0A!\n")  	//set controller in program mode

#define SET_OPERATE_MODE			("0B!\n")  	//set controller in operate mode



//	EEPROM settings

#define SET_SERIAL_MODE				("99<0\n")	//set controller to serial mode

#define DISABLE_SERIAL_ECHO			("90<0\n")	// disable serial echo

#define SET_DIR_CONTROL				("9B<0\n")	//set the motor to use serial direction rather than discrete

#define SET_WATCHDOG				("93<0\n")  //set the watchdog to time out in 5/10 of a second



//  Register numbers

#define MC_THROTTLE_REGISTER  		(60)

#define MC_SPEED_REGISTER			(0)





//  Drive states

#define DS_POWERUP					(32)	//initial state.

//(states 33-62 are all powering-up states.)

#define D_S_POWERUPEND				(63)	//power-up period over.

#define D_S_SHUTDOWN				(64)	//stopped and disabled.

#define D_S_DISABLECOAST			(65)	//disabled but not stopped.

#define D_S_INTERLOCK				(66)	//type 1 fault detected; waiting for disable command.

#define D_S_INTERLOCKCOAST			(67)	//type 1 fault detected, waiting for disable command, not stopped.

#define D_S_STOPPED					(74)	//enabled but not moving or throttling.

#define D_S_COASTING				(75)	//enabled and moving but not throttling.

#define D_S_NO_LONGER_THR			(76)	//leaving DS_THR mode.

#define D_S_NO_LONGER_BRK			(77)	//leaving DS_BRK mode.

#define D_S_THR						(78)	//throttling.

#define D_S_BRK						(79)	//braking.

#define D_S_PROGRAM					(1)		//shutdown with programming enabled.



//MOTOR FAULT MACROS: to be used as masks on register values



//Type 1: faults that immediately disable controller and prevent operation.

#define FA1_UNDERVOLT				(0x1)	//supply voltage less than CG_ABSMINV

#define FA1_OVERVOLT				(0x2)	//supply voltage more than CG_ABSMAXV

#define FA1_NOFETDR					(0x4)	//supply V to gate drives low, internal fault or low supply voltage spike.

#define FA1_NOPHASELEADS			(0x8)	//most likely a phase lead is disconnected.

#define FA1_INVALIDHALLS			(0x10)	//a hall effect input is invalid (probably a cable is disconnected).

#define FA1_LOSTCOMM				(0x20)	//serial I/O watchdog has tripped due to inactivity on serial input.

//Type 2: sensor problems.

#define FA2_MOTORT					(0x1)	//motor temp reads <-50 C or >150 C.

#define FA2_HEATSINKT				(0x2)	//controller temp reads <-50 C or >150 C.

#define FA2_SUPPLYI					(0x4)	//logic supply current less than CG_MINSUPPLY.

//Type 3: warnings.

#define FA3_FAN						(0x1)	//logic supply current outside fan supply range. fan may be disconnected or jammed.

#define FA3_STATORSHORT				(0x2)	//stator short to ground or phase detected.

#define FA3_MAXTORQUE				(0x4)	//motor has reached max throttle or regen current for current speed.

#define FA3_SOFTSTART				(0x10)	//controller is soft-starting because IN_DESIREDPHASE was != 0 when controller was enabled.

#define FA3_OBDIRBACKWARDS			(0x20)	//observed direction is opposite of input direction. controller coasting.

//Type 4: conditions which lead to reduction in output torque.

#define FA4_MOTORTLIM				(0x1)	//current limit due to motor temperature.

#define FA4_HEATSINKTLIM			(0x2)	//current limit due to controller temperature.

#define FA4_UNDERVOLT				(0x4)	//supply voltage less than CG_MINVGUARD.

#define FA4_OVERVOLT				(0x8)	//supply voltage more than CG_MAXVGUARD.

#define FA4_ABSLIM					(0x10)	//desired current greater than either CG_MAXTHR or GC_MAXRGN.

#define FA4_SOFTLIM					(0x20)	//desired current greater than either SV_THRPHASEILIM or CG_RGNPHASEILIM.

#define FA4_THRDISABLED				(0x40)	//throttle current zero because throttle enable input is FALSE.

#define FA4_BRAKEPHASEILIM			(0x80)	//when in discrete speed control, target regen current greater than limit set by regen input.



void SetupPedals();

void runMotor();

void torqueControl();

void getMotorStatus();

void getFaults();

int GetThrottle();

int GetRegen();

int GetBrake();

void MC_Setup();

void MC_CloseConnection();

void MC_SetEEPROM();

int MC_Query(char *q_code);

void MC_Command(char *command_code);

void MC_SetRegister(int register_number, int value);

void setCruiseSpeed(int speed);

void switchToTorque();

void switchToSpeed();

void cruiseControl();

void sendCommand(char *cmd);

void testMotor();

float calculateSpeedMPH(int rpm);


/**
 * Send an entire string. Sends characters one at a time with scia_xmit().
 * @author PK
 */
void RS232_write(char *msg);



/**
 * Receives a full message by making calls to scia_xceive().//Behavior not yet supported
 * @author PK
 */
void receiveMessage(char * response, int size);






#endif
