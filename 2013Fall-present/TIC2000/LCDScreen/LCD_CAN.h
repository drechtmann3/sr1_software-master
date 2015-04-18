/*
 * LCD_CAN.h
 *
 *  Created on: Jun 24, 2014
 *      Author: Alex
 */

#ifndef LCD_CAN_H_
#define LCD_CAN_H_

#include "CAN.h"
#include <stdio.h>
#include "PeripheralHeaderIncludes.h"
#include "motor_CAN_message_ids.h"
#include "graphics_elements.h"
#include "logging.h"

void LCD_Initialize_CAN(); // Initialize CAN
void LCD_CAN_send_isr(CAN_ID ID, Uint32 dataH, Uint32 dataL, Uint16 length, int mbox_num);
void LCD_CAN_receive_isr(CAN_ID ID, Uint32 dataH, Uint32 dataL, Uint16 length, int mbox_num);

#endif /* LCD_CAN_H_ */
