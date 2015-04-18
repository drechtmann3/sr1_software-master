/*
 * LDC_Main.h
 *
 *  Created on: Jun 22, 2014
 *      Author: Alex
 */

#ifndef LDC_MAIN_H_
#define LDC_MAIN_H_

#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File
#include <stdio.h>
#include "sci_funcs.h"
#include "draw_funcs.h"
#include "graphics_elements.h"
#include "LCD_CAN.h"

extern Uint16 RamfuncsLoadStart;
extern Uint16 RamfuncsLoadSize;
extern Uint16 RamfuncsRunStart;

void refreshAllElementsToDefaultState();
signed char initializeuCANndSerialComs();


#endif /* LDC_MAIN_H_ */
