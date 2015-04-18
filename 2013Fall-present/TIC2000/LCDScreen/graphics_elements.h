/*
 * graphics_elements.h
 *
 *  Created on: Jun 23, 2014
 *      Author: Alex
 */

#ifndef GRAPHICS_ELEMENTS_H_
#define GRAPHICS_ELEMENTS_H_

#include "PeripheralHeaderIncludes.h"
#include "draw_funcs.h"

#define CURRENT_IVAL_MAX_CURRENT 100.0f // Amps, max current that can be displayed.
#define MOTOR_MAX_HEATSINK_TEMP 70.0f // In degrees Celcius
#define MOTOR_MAX_THROTTLE_CURRENT_AMPS 5.0f // In amps

void draw_throttle_regen(char refresh);
void draw_signal_strength(char refresh);
void draw_bat_temp(char refresh);
void draw_motor_temp(char refresh);
void draw_speed_mph(char refresh);
void draw_cruise_control();
void draw_SOC(char refresh);
void draw_mppt_value(char refresh);
void draw_currentI_value(char refresh);
void draw_motor_faults();
void draw_blinkers();
void draw_CAN_error();
void draw_motor_error();
void draw_motor_reverse_enabled();

extern volatile float32 throttleVal;
extern volatile float32 signalStrengthVal;
extern volatile float32 batTempVal;
extern volatile float32 motorTempVal;
extern volatile char speedMph;
extern volatile char cruiseControlEnabled;
extern volatile float32 SOCVal;
extern volatile float32 mpptVal;
extern volatile float32 currentIVal;
extern volatile Uint32 motorFaultRegisters;
extern volatile char blinkerState;
extern volatile char CANErrorActive;
extern volatile char motorErrorActive;
extern volatile char reverseModeEnabled;


#endif /* GRAPHICS_ELEMENTS_H_ */
