/*
 * motor_basic_funcs.h
 *
 *  Created on: Jun 1, 2014
 *      Author: Alex
 */


#include "sci_funcs.h"
#include <stdlib.h>
#include "encoders.h"
#include "NGM_EVM_200_Constants.h"
#include "F2806x_Examples.h"   // Examples Include File
#include "logging.h"
#include "motor_CAN.h"

#ifndef MOTOR_BASIC_FUNCS_H_
#define MOTOR_BASIC_FUNCS_H_

extern char NGMSCM_error_buffer[17];
extern unsigned char NGMEV_fault_code_buffer[4]; // Stores fault codes received from motor controller.

signed char NGMEVAssignment(unsigned char memLoc, char inRAM, int32 value);
signed char sendNGMEVCommand(char *command_code);
int32 NGMEVQuery(unsigned char memLoc, char inRAM, signed char* status);

signed char testNGMEVComsAndOperation();
void getNGMEVMotorStats();
void getNGMEVMotorEEPROMVals();
signed char NGMEVGetFaults();
signed char setMotorWatchogTime(int32 tenthsOfSeconds);

void clearSCIFIFOAndNGMEVReceiveQueue();

void send_CAN_heartbeat_messages();



#endif /* MOTOR_BASIC_FUNCS_H_ */
