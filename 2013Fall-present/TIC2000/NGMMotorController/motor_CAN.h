/*
 * motor_CAN.h
 *
 *  Created on: Jun 20, 2014
 *      Author: Alex
 */

#ifndef MOTOR_CAN_H_
#define MOTOR_CAN_H_

#include "CAN.h"
#include <stdio.h>
#include "PeripheralHeaderIncludes.h"
#include "motor_CAN_message_ids.h"

void motor_CAN_receive_isr(CAN_ID ID, Uint32 dataH, Uint32 dataL, Uint16 length, int mbox_num);
void motor_CAN_send_isr(CAN_ID ID, Uint32 dataH, Uint32 dataL, Uint16 length, int mbox_num);
void initialize_CAN();

// CAN messages
void CAN_send_faults_msg(unsigned char* faults);
void CAN_send_drivestate_msg(unsigned char drivestate);
void CAN_send_speed_msg(Uint16 deciHz_speed);
void CAN_send_error_msg(char error_code);
void CAN_send_throttle_regen_msg(int16 throttle);
void CAN_send_temperature_voltage_msg(Uint16 temp, Uint16 h_temp, Uint16 voltage);
void CAN_send_cruise_control_enabled_msg(char cc_en);
void CAN_send_reverse_direction_enabled_msg(char rev_en);
void CAN_send_blinker_status_msg(char left_blinker_en, char right_blinker_en);


#endif /* MOTOR_CAN_H_ */
