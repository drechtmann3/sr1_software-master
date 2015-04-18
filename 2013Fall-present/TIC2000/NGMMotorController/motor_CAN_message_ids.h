/*
 * motor_CAN_message_ids.h
 *
 *  Created on: Jun 20, 2014
 *      Author: Alex
 */

#ifndef MOTOR_CAN_MESSAGE_IDS_H_
#define MOTOR_CAN_MESSAGE_IDS_H_

// Motor/Pedal messages are sent with the CAN IDs "MOTOR_CONTROLLER" or "PEDALS"
//
// CAN Frame Format for Motor/Pedals: (8 bytes):
// Byte#  7-1          0
//        [Data Bytes] [Motor/Pedal Message ID Byte]
//
// Provides a motor/pedal message ID, as well as seven other possible bytes to be used for data transmission.
// The number format will be dependent on the Motor/Pedal Message ID Byte.

#define CAN_SPEED_MSG 0x00
#define CAN_THROTTLE_REGEN_VALUE_MSG 0x01
#define CAN_TEMPERATURE_VOLTAGE_MSG 0x02

#define CAN_MOTOR_STATUS_MSG 0x03
#define CAN_MOTOR_FAULT_MSG 0x04
#define CAN_MOTOR_ERROR_MSG 0x05
#define CAN_MOTOR_CC_EN_MSG 0x06
#define CAN_MOTOR_REV_EN_MSG 0x07
#define CAN_BLINKER_EN_MSG 0x08


#endif /* MOTOR_CAN_MESSAGE_IDS_H_ */
