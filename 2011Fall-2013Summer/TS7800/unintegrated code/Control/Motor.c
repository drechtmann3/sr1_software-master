/* Motor control state machine. 
 *
 * Implemented as a struct with pointer to one function.
 * The function acts as the current state; it is passed a pointer
 * to its parent struct and thus can change the current state
 * by changing the function pointer. The state machine is 
 * clocked forward by calling the function pointed to by the
 * structure. */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <err.h>
#include <time.h>
#include <pthread.h>

#include "Motor.h"
#include "MotorController.h"
#include "mc_fault_codes.h"
#include "wrapper.h"
#include "shared_data.h"
#include "MC_commands.h"
#include "DIO.h"
#include "ADC.h"

// State machine macros
#define FORWARD						(1)
#define REVERSE						(0)
#define SPEED_CONTROL_INCREMENT		(25)		//dHz
#define MINIMUM_SPEED				(0)			//dHz
/* max speed derived from speed tests performed by Chris McManus et al */
#define MAXIMUM_SPEED				(1400)		//dHz
#define DHZ_TO_RPM					(6)			//1dHz = 6rpm

// Airgap macros
// Minimum and maximum reading from potentiometer. Need to calibrate.
#define MIN_GAP (100)
#define MAX_GAP (1000)
// Number of positions the airgap can stay at. MUST be integer > 1.
#define GAP_POS_NUM (3)
#define GAP_POS_TO_POTEN(x) (MIN_GAP + (MAX_GAP - MIN_GAP)*x/(GAP_POS_NUM - 1))

#define AIRGAP_PWR_ON  (1)
#define AIRGAP_PWR_OFF (0)

#define DEBUG_AIRGAP_HW

struct TargetState 
{ 	//desired state of the motor, e.g. target speed.
	int speed;		//motor rotation, dHz.
	int direction;		//FORWARD or REVERSE.
	int phaseI;		//phase current, dA, proportional to torque.

	int speedUp;
	int speedDown;	
	int brake;	//brake pedal is currently pressed
} target ;

typedef struct StateMachine TSM;

typedef void (*StateFunc)(TSM *sm);

struct StateMachine
{
	StateFunc currentState;
};

// motor control state machine functions
static void SMinit	(TSM *);
static void SMtorque	(TSM *);
#ifdef USE_SPEED_CONTROL
static void SMspeed	(TSM *);
static int  CheckBrake      (void);
#endif /* #ifdef USE_SPEED_CONTROL */
static int  GetThrottle     (void);
static int  GetRegen        (void);
//static int CalculateSpeedMPH	(int ); //TODO

// Airgap functions
static void AirgapInit(void);
static int CheckCommandGapOpen();
static int CheckCommandGapClose();
#ifdef ENABLE_AIRGAP_KILLSWITCH
static int CheckAirgapKillswitch();
#endif


// for airgap functionality
int GapGoalPos;
int GapGoalOver;

// ADC device structure
static struct ADC_device adc0 = {
	.ss = SPI_SS,
	.ss_row = GPIO_DAT_A,
	.ss_dir = GPIO_DIR_A,

	.clk = SPI_CLK,
	.clk_row = GPIO_DAT_A,
	.clk_dir = GPIO_DIR_A,

	.mosi = SPI_MOSI,
	.mosi_row = GPIO_DAT_A,
	.mosi_dir = GPIO_DIR_A,

	.miso = SPI_MISO,
	.miso_row = GPIO_DAT_A,
	.miso_dir = GPIO_DIR_A,


	.calibration_values[CHAN_THR] = {
			.min = CHAN_THR_MIN,
			.max = CHAN_THR_MAX
	},
	.calibration_values[CHAN_REGEN] = {
			.min = CHAN_REGEN_MIN,
			.max = CHAN_REGEN_MAX
	},
	.calibration_values[CHAN_GAP] = {
			.min = CHAN_GAP_MIN,
			.max = CHAN_GAP_MAX
	}
};

TSM sm = {SMinit}; //initialize state machine

void *MotorControl(void *thread_id)
{ //clock the state machine.


	MC_Setup();
	InitADC(&adc0);

	while(1) {
		#ifdef ENABLE_MOTOR_KILLSWITCH
			//Check for emergency software killswitch.
			if ( CheckKillswitch() ) {
				MC_SetRegister(MC_THROTTLE_REGISTER, 0);	//phase current 0dA.
				MC_SetRegister(MC_SPEED_REGISTER, 0); //speed 0dHz.
				#ifdef DEBUG
					printf("Software killswitch pressed. Motor stopped.\n");
				#endif
				pthread_exit(NULL);
			}
		#endif

		sm.currentState(&sm); //clock the state machine
		report_motor_status();
		report_fault_status();
	}

	pthread_exit( NULL );
}

void report_motor_status()
{ // update the shared Motor_info_struct

	// gather data before entering critical section
	int speed_rpm = DHZ_TO_RPM * MC_Query(Q_ACTUAL_SPEED); // rpm
//	int airgap_pos = GetGap(); //TODO add airgap functionality
	int direction = MC_Query(Q_INFORWARD);  // 1 == forward
	int target_speed  = MC_Query(Q_DESIRED_SPEED); // dHz
	int target_phase_current = MC_Query(Q_DESIRED_PHASEI); // dA
	int throttle = GetThrottle() - GetRegen();
//	int brake_indicator //TODO: brake indicator sensor
//	int target_dir; // 1 == forward TODO: figure out how to go in reverse

	pthread_mutex_lock(&Motor_info_mutex);
	Motor_info.speed_rpm = speed_rpm;
	//Motor_info.airgap_pos = airgap_pos; //TODO add airgap functionality
	Motor_info.direction = direction;
	Motor_info.target_speed  = target_speed; // dHz
	Motor_info.target_phase_current = target_phase_current; // dA
	Motor_info.throttle = throttle;
//	Motor_info.brake_indicator //TODO: brake indicator sensor
//	Motor_info.target_dir; // 1 == forward TODO: figure out how to go in reverse
	pthread_mutex_unlock(&Motor_info_mutex);

#ifdef MOTORTEST_DEBUG_OUTPUT
//write status output to console for testing
	printf("current speed: %d rpm\n", Motor_info.speed_rpm);
#endif
}

void report_fault_status()
{ //update the shared MC_faults_struct

	// gather data before entering critical section
	int fault1 = MC_Query(Q_FAULT1LATCH);
	int fault2 = MC_Query(Q_FAULT2);
	int fault3 = MC_Query(Q_FAULT3);
	int fault4 = MC_Query(Q_FAULT4);

	pthread_mutex_lock(&MC_faults_mutex);
	MC_faults.fault_1 = fault1;
	MC_faults.fault_2 = fault2;
	MC_faults.fault_3 = fault3;
	MC_faults.fault_4 = fault4;
	pthread_mutex_unlock(&MC_faults_mutex);
}


static void SMinit(TSM *sm)
{ //Initialize state.
	InitDIO_direction(COMMAND_SPEED_UP, CONTROL_GPIO_DIR_ROW, GPIO_INPUT);
	InitDIO_direction(COMMAND_SPEED_DOWN, CONTROL_GPIO_DIR_ROW, GPIO_INPUT);
	InitDIO_direction(COMMAND_BRAKE, CONTROL_GPIO_DIR_ROW, GPIO_INPUT);
	InitDIO_direction(COMMAND_CRUISE, CONTROL_GPIO_DIR_ROW, GPIO_INPUT);

	target.speed 		= 0;
	target.phaseI		= 0;
	target.direction 	= FORWARD;
	MC_SetRegister(MC_THROTTLE_REGISTER, 0); //phase current 0dA.
	MC_SetRegister(MC_SPEED_REGISTER, 0); //speed 0dHz.

	sm->currentState = SMtorque;
	MC_Command(SET_TORQUE_CONTROL);
	return;
}


static void SMtorque(TSM *sm) //TODO implement reverse
{ // torque control mode.

#ifdef USE_SPEED_CONTROL
	// Transition to speed control mode
	if (CheckPin(COMMAND_CRUISE, CONTROL_GPIO_DAT_ROW)) {
		//switch operating mode
		sm->currentState = SMspeed;
		target.speed = MC_Query(Q_ACTUAL_SPEED); //set cruise speed to current speed
		MC_SetRegister(MC_SPEED_REGISTER, target.speed);
		MC_Command(SET_SPEED_CONTROL);
		return;
	}
#endif

	int phaseI = GetThrottle() - GetRegen();  // Get target phase current from pedal input
	if (phaseI != target.phaseI) {  // update phase current command
		target.phaseI = phaseI;
		MC_SetRegister(MC_THROTTLE_REGISTER, phaseI);
	}
}

#ifdef USE_SPEED_CONTROL
static void SMspeed(TSM *sm)
{ // speed control mode.
	if ( CheckBrake() ) {
		// switch operating mode
		sm->currentState = SMtorque;
		MC_Command(SET_TORQUE_CONTROL);
		return;
	}
	if (CheckPin(COMMAND_CRUISE, CONTROL_GPIO_DAT_ROW) ) {
		// switch operating mode
		sm->currentState = SMtorque;
		MC_Command(SET_TORQUE_CONTROL);
		return;
	}
	if (CheckPin(COMMAND_SPEED_DOWN, CONTROL_GPIO_DAT_ROW)) {
		if (target.speed > MINIMUM_SPEED + SPEED_CONTROL_INCREMENT)
			target.speed -= SPEED_CONTROL_INCREMENT;
		else
			target.speed = MINIMUM_SPEED;
		MC_SetRegister(MC_SPEED_REGISTER, target.speed);
	} else if (CheckPin(COMMAND_SPEED_UP, CONTROL_GPIO_DAT_ROW)) {
		if (target.speed < MAXIMUM_SPEED - SPEED_CONTROL_INCREMENT)
			target.speed += SPEED_CONTROL_INCREMENT;
		else
			target.speed = SPEED_CONTROL_INCREMENT;
		MC_SetRegister(MC_SPEED_REGISTER, target.speed);
	}
}
#endif /* #ifdef USE_SPEED_CONTROL */

int GetThrottle()
{ //Poll ADC for throttle pedal position
	return (ADCread(CHAN_THR, &adc0));
}
int GetRegen()
{ //Poll ADC for regen pedal position
	return (ADCread(CHAN_REGEN, &adc0));
}
#ifdef USE_SPEED_CONTROL
int CheckBrake(void)
{ //check whether friction brake is being pressed.
	return ( CheckPin(COMMAND_BRAKE, CONTROL_GPIO_DAT_ROW));
}
#endif /* #ifdef USE_SPEED_CONTROL */

#ifdef ENABLE_MOTOR_KILLSWITCH
int CheckKillswitch (void)
{ //check for killswitch.
	return ( CheckPin(KILLSWITCH, CONTROL_GPIO_DAT_ROW));
}
#endif

/* TODO fix CalculateSpeedMPH
int CalculateSpeedMPH(int speed_dHz)
{ 	//calculate the speed in MPH given dHz.
	return ((int)((60 * speed_dHz * 18 * 3.14159) / (5280 * 12))); 
}
*/




// Airgap functions

static int CheckCommandGapOpen()
{
	return CheckPin(COMMAND_AIRGAP_OPEN, CONTROL_GPIO_DAT_ROW);
}

static int CheckCommandGapClose()
{
	return CheckPin(COMMAND_AIRGAP_CLOSE, CONTROL_GPIO_DAT_ROW);
}

#ifdef ENABLE_AIRGAP_KILLSWITCH
int CheckAirgapKillswitch()
{
	return CheckPin(AIRGAP_KILLSWITCH, CONTROL_GPIO_DAT_ROW);
}
#endif

int GetGap()
{	// Poll the ADC for current potentiometer position.
	return (ADCread(CHAN_GAP, &adc0));
}

static void AirgapInit()
{
	/* initialize dio pin directions */
	InitDIO_direction(GAP_MOTOR_PWR, CONTROL_GPIO_DIR_ROW, GPIO_OUTPUT);
	InitDIO_direction(GAP_MOTOR_DIR, CONTROL_GPIO_DIR_ROW, GPIO_OUTPUT);

	GapGoalPos = 0;
	GapGoalOver = 0;
}

void *AirgapControl(void *thread_id)
{
	int pwr;
#ifndef DEBUG_AIRGAP_HW
	int goalPoten;
#endif
	AirgapInit();

	while(1) {
		#ifdef ENABLE_AIRGAP_KILLSWITCH
		if (CheckAirgapKillswitch()) {
			//exit safely
			SetPin(GAP_MOTOR_PWR, CONTROL_GPIO_DAT_ROW, AIRGAP_PWR_OFF);
			#ifdef DEBUG
				printf("Software killswitch pressed. Airgap motor stopped.\n");
			#endif
			pthread_exit(NULL);
		}
		#endif
	#ifdef DEBUG_AIRGAP_HW
		if (CheckCommandGapOpen()) {
			pwr = AIRGAP_PWR_ON;
			SetPin(GAP_MOTOR_DIR, CONTROL_GPIO_DAT_ROW, 1);
			usleep(1000);

		} else if (CheckCommandGapClose()) {
			pwr = AIRGAP_PWR_ON;
			SetPin(GAP_MOTOR_DIR, CONTROL_GPIO_DAT_ROW, 0);
			usleep(1000);
		}
		SetPin(GAP_MOTOR_PWR, CONTROL_GPIO_DAT_ROW, pwr);

	#else
		int curPoten = GetGap();
		if (CheckCommandGapOpen() && GapGoalPos < GAP_POS_NUM - 1) {
			GapGoalPos++;
			GapGoalOver = GAP_POS_TO_POTEN(GapGoalPos) > curPoten;
		}
		if (CheckCommandGapClose() && GapGoalPos > 0) {
			GapGoalPos--;
			GapGoalOver = GAP_POS_TO_POTEN(GapGoalPos) > curPoten;
		}
		SetPin_w(GAP_MOTOR_DIR, GapGoalOver);

		int goalPoten = GAP_POS_TO_POTEN(GapGoalPos);

		if ( (GapGoalOver && goalPoten > curPoten) || (!GapGoalOver && goalPoten < curPoten) ) {
			pwr = AIRGAP_PWR_ON;
		} else {
			pwr = AIRGAP_PWR_OFF;
		}


		SetPin_w(GAP_MOTOR_PWR, pwr);
	#endif
	}

	pthread_exit(NULL);
}
