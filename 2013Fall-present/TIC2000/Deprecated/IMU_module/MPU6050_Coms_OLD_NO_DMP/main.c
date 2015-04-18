#include <stdio.h>
#include "PeripheralHeaderIncludes.h"
#include "MPU6050_Constants.h"
#include "I2CFuncs.h"
#include "MPUFuncs.h"

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// FUNCTION PROTOTYPES
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

void DeviceInit(void);
void InitFlash(void);
void MemCopy(Uint16 *SourceAddr, Uint16* SourceEndAddr, Uint16* DestAddr);

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// VARIABLE DECLARATIONS - GENERAL
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

// Used for running BackGround in flash and the ISR in RAM
extern Uint16 RamfuncsLoadStart, RamfuncsLoadEnd, RamfuncsRunStart;


//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// MAIN CODE - starts here
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
void main(void)
{
//=================================
//	INITIALISATION - General
//=================================

	DeviceInit();	// Device Life support & GPIO mux settings

// Only used if running from FLASH
// Note that the variable FLASH is defined by the compiler (-d FLASH)
#ifdef FLASH		
// Copy time critical code and Flash setup code to RAM
// The  RamfuncsLoadStart, RamfuncsLoadEnd, and RamfuncsRunStart
// symbols are created by the linker. Refer to the linker files. 
	MemCopy(&RamfuncsLoadStart, &RamfuncsLoadEnd, &RamfuncsRunStart);

// Call Flash Initialization to setup flash waitstates
// This function must reside in RAM
	InitFlash();	// Call the flash wrapper init function
#endif //(FLASH)

// Enable Peripheral, global Ints and higher priority real-time debug events:
//	IER |= M_INT3; 
//	EINT;   // Enable Global interrupt INTM
//	ERTM;   // Enable Global realtime interrupt DBGM

	// Initialize the I2C
	puts("Initializing I2C Module...");
	I2CA_Init();

	// Wait for MPU to be connected...
	int status = get_MPU6050_status();
	while (status != 1) {
		puts("MPU is not responding. Maybe it's disconnected?");
		status = get_MPU6050_status();
	}

	// Set up MPU...
	puts("MPU6050 is connected and responding. Setting up...");
	int setup_status = setup_MPU6050();
	if (setup_status == 1) puts("MPU set up successfully.");
	else puts("MPU did not set up successfully.");

	// Calibrate MPU gyroscope...
	puts("Calibrating MPU6050 gyroscope...");
	calibrate_MPU6050();
	puts("Finished calibrating gyroscope.");

	// Collect data...
	while(1) {
		float32 lin_acc[3];
		get_linear_acceleration(lin_acc);
		float32 ang_vel[3];
		get_angular_velocity(ang_vel);

		char readings[128];
		sprintf(readings, "Lin. Acc. (%f, %f, %f) Ang. Vel. (%f, %f, %f)", lin_acc[0], lin_acc[1], lin_acc[2], ang_vel[0], ang_vel[1], ang_vel[2]);
		puts(readings);
	}
} //END MAIN CODE
