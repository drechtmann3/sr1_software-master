//Commands that can be sent to the NGM-EV-C200 motor controller.
#ifndef MC_COMMANDS_H
#define MC_COMMANDS_H

//	Queries
#define Q_DESIRED_SPEED		("00?\n")  //serial speed in dHz
#define Q_ACTUAL_SPEED		("0C?\n")  //actual speed in dHz
#define Q_INFORWARD			("A0?\n")  //motor direction (1:=forward)
#define Q_DESIRED_PHASEI	("60?\n")  //desired phase current in dA
#define Q_SUPPLY_VOLTAGE	("64?\n")  //supply voltage in dV
#define Q_MOTOR_TEMP		("65?\n")  //motor temperature (degreesC*10)
#define Q_HEATSINK_TEMP		("66?\n")  //heatsink temp (degreesC*10)
#define Q_DRIVESTATE		("96?\n")  //operating status
#define Q_FAULT1LATCH		("98?\n")
#define Q_FAULT1			("99?\n")
#define Q_FAULT2			("9A?\n")
#define Q_FAULT3			("9B?\n")
#define Q_FAULT4			("9C?\n")

//	Commands
#define ENABLE_COMMAND		("00!\n")  //Enable controller output
#define DISABLE_COMMAND		("01!\n")  //Disable controller output
#define SET_THROTTLE_EN		("02!\n")  //Enable motor throttle
#define UNSET_THROTTLE_EN	("03!\n")  //Disable motor throttle
#define SET_TORQUE_CONTROL	("06!\n")  //change to torque control mode
#define SET_SPEED_CONTROL	("07!\n")  //change to speed control mode
#define SET_COAST			("08!\n")  //force desired current to zero
#define SET_PROGRAM_MODE	("0A!\n")  //set controller in program mode
#define SET_OPERATE_MODE	("0B!\n")  //set controller in operate mode

//	EEPROM settings
#define SET_SERIAL_MODE		("99<0\n") //set controller to serial mode
#define DISABLE_SERIAL_ECHO		("90<0\n") // disable serial echo

//  Register numbers
#define MC_THROTTLE_REGISTER   (60)
#define MC_SPEED_REGISTER		(0)

//  Drive states
#define DS_POWERUP			(32)	//initial state.
//(states 33-62 are all powering-up states.)
#define DS_POWERUPEND		(63)	//power-up period over.
#define DS_SHUTDOWN			(64)	//stopped and disabled.
#define DS_DISABLECOAST		(65)	//disabled but not stopped.
#define DS_INTERLOCK		(66)	//type 1 fault detected; waiting for disable command.
#define DS_INTERLOCKCOAST	(67)	//type 1 fault detected, waiting for disable command, not stopped.
#define DS_STOPPED			(74)	//enabled but not moving or throttling.
#define DS_COASTING			(75)	//enabled and moving but not throttling.
#define DS_NO_LONGER_THR	(76)	//leaving DS_THR mode.
#define DS_NO_LONGER_BRK	(77)	//leaving DS_BRK mode.
#define DS_THR				(78)	//throttling.
#define DS_BRK				(79)	//braking.
#define DS_PROGRAM			(1)		//shutdown with programming enabled.


#endif /* #ifndef MC_COMMANDS_H */
