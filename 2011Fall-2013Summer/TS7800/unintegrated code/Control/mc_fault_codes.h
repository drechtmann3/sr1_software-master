/* These are mask values for all possible fault codes sent from
	the motor controller. The controller sends one 32-bit value
	for each fault type (the fault types are enumerated below),
	into which all the applicable faults of that type are muxed.
	The four different fault types are enumerated along with 
	their macros below.

   Example:
	To check whether there is an undervoltage which is causing
	the controller to disable the motor:

	// int type_1_fault_status is returned by the controller
	if (type_1_fault_status & FA1_UNDERVOLT) {
		//this gets executed if there is an undervoltage fault
	}

*/
	
#ifndef MC_FAULT_CODES_H
#define MC_FAULT_CODES_H

//motor fault macros: to be used as masks on register values

//Type 1: faults that immediately disable controller and prevent operation.
//
//supply voltage less than CG_ABSMINV
#define FA1_UNDERVOLT		(0x1)
//supply voltage more than CG_ABSMAXV
#define FA1_OVERVOLT		(0x2)	
//supply V to gate drives low, internal fault or low supply voltage spike.
#define FA1_NOFETDR		(0x4)	
//most likely a phase lead is disconnected.
#define FA1_NOPHASELEADS	(0x8)	
//a hall effect input is invalid (probably a cable is disconnected).
#define FA1_INVALIDHALLS	(0x10)	
//serial I/O watchdog has tripped due to inactivity on serial input.
#define FA1_LOSTCOMM		(0x20)	

//Type 2: sensor problems.
//
//motor temp reads <-50 C or >150 C.
#define FA2_MOTORT		(0x1)	
//controller temp reads <-50 C or >150 C.
#define FA2_HEATSINKT		(0x2)	
//logic supply current less than CG_MINSUPPLY.
#define FA2_SUPPLYI		(0x4)	

//Type 3: warnings.
//
//logic supply current outside fan supply range. fan may be disconnected or jammed.
#define FA3_FAN			(0x1)	
//stator short to ground or phase detected.
#define FA3_STATORSHORT		(0x2)	
//motor has reached max throttle or regen current for current speed.
#define FA3_MAXTORQUE		(0x4)	
//controller is soft-starting because IN_DESIREDPHASE was != 0 when controller was enabled.
#define FA3_SOFTSTART		(0x10)	
//observed direction is opposite of input direction. controller coasting.
#define FA3_OBDIRBACKWARDS	(0x20)	

//Type 4: conditions which lead to reduction in output torque.
//
//current limit due to motor temperature.
#define FA4_MOTORTLIM		(0x1)	
//current limit due to controller temperature.
#define FA4_HEATSINKTLIM	(0x2)	
//supply voltage less than CG_MINVGUARD.
#define FA4_UNDERVOLT		(0x4)	
//supply voltage more than CG_MAXVGUARD.
#define FA4_OVERVOLT		(0x8)	
//desired current greater than either CG_MAXTHR or GC_MAXRGN.
#define FA4_ABSLIM		(0x10)	
//desired current greater than either SV_THRPHASEILIM or CG_RGNPHASEILIM.
#define FA4_SOFTLIM		(0x20)	
//throttle current zero because throttle enable input is FALSE.
#define FA4_THRDISABLED		(0x40)	
//when in discrete speed control, target regen current greater than limit set by regen input.
#define FA4_BRAKEPHASEILIM	(0x80)	

#endif
