/*
 * graphics_elements.c
 *
 *  Created on: Jun 23, 2014
 *      Author: Alex
 */
#include "graphics_elements.h"
#define SCREEN_WIDTH 160
#define SCREEN_HEIGHT 128

/**
 * \brief Draw throttle/regen graph.
 */
volatile float32 throttleVal = 0; // -1 to +1
float32 drawnThrottleVal = 0;
void draw_throttle_regen(char refresh) {
	float32 throttleVal_s = throttleVal;
	int xStart=3, height=60, width=12, yStart=30, y1, y2;
	if (throttleVal_s > 1) throttleVal_s = 1;
	if (throttleVal_s < -1) throttleVal_s = -1;
	if (refresh) {
		// Throttle bar graph
		LCD_printText("T", 7, 22);
		DELAY_US(1e4);
		LCD_throttleGraphV(xStart, yStart, height, width, throttleVal_s*100);
	} else if (throttleVal_s != drawnThrottleVal) {
		y1 = yStart+height/2-((height/2-1) * drawnThrottleVal);
		y2 = yStart+height/2-((height/2-1) * throttleVal_s);
		if ((throttleVal_s < drawnThrottleVal && throttleVal_s >= 0) || (throttleVal_s > drawnThrottleVal && throttleVal_s < 0)) LCD_eraseBox(4, y1, 3+12-1, y2); // Erase changed area
		else LCD_fillBox(4, y1, 3+12-1, y2); // Only fill changed area.
		if (throttleVal_s < 0 && drawnThrottleVal >= 0 || throttleVal_s > 0 && drawnThrottleVal <= 0) {
			LCD_eraseBox(4, yStart+1, 3+12-1, yStart+height - 1);
			LCD_fillBox(4, yStart+height/2, 3+12-1, y2);
		}
		if (throttleVal_s > -0.1 && throttleVal_s < 0.1) LCD_drawLine(xStart-1, yStart+height/2, xStart + width+1, yStart+height/2); // Redraw middle line.
	}
	if (throttleVal_s != drawnThrottleVal) {
		LCD_eraseBox(5, 80, 13, 89); // Erase for R
		LCD_printText("R", 7, 82); // Draw "R"
		DELAY_US(1e4);
	}
	drawnThrottleVal = throttleVal_s;
}

volatile float32 signalStrengthVal = 0; // 0 to +1
float32 drawnSignalStrengthVal = 0;
void draw_signal_strength(char refresh) {
	float32 signalStrengthVal_s = signalStrengthVal;
	int xCenter=24, yStart=31, height=58, width=12;
	if (signalStrengthVal_s > 1) signalStrengthVal_s = 1;
	if (refresh) {
		LCD_printText("Wi", 20, 22);
		DELAY_US(1e4);
		LCD_vertical_line_slider(xCenter, yStart, height, width, signalStrengthVal_s*100);
	} else if (signalStrengthVal_s != drawnSignalStrengthVal) {
		LCD_eraseBox(xCenter-width/2+1, yStart+(1-drawnSignalStrengthVal)*height-1, xCenter+width/2-1, yStart+(1-drawnSignalStrengthVal)*height+1);
		LCD_drawLine(xCenter, yStart+(1-drawnSignalStrengthVal)*height-1, xCenter, yStart+(1-drawnSignalStrengthVal)*height+1);
		LCD_fillBox(xCenter-width/2+1, yStart+(1-signalStrengthVal_s)*height-1, xCenter+width/2-1, yStart+(1-signalStrengthVal_s)*height+1); // Draw new cursor
		if (drawnSignalStrengthVal < 0.05 || drawnSignalStrengthVal > 0.95 || (drawnSignalStrengthVal < 0.6 && drawnSignalStrengthVal >0.4)) { // Refresh marks.
			LCD_drawLine(xCenter-width/2, yStart+height+1, xCenter+width/2, yStart+height+1);
			LCD_drawLine(xCenter-width/2+3, yStart+height/2, xCenter+width/2-3, yStart+height/2);
			LCD_drawLine(xCenter-width/2, yStart-1, xCenter+width/2, yStart-1);
		}
	}
	drawnSignalStrengthVal = signalStrengthVal_s;
}

volatile float32 batTempVal = 0; // 0 to +1
float32 drawnBatTempVal = 0;
void draw_bat_temp(char refresh) {
	float32 batTempVal_s = batTempVal;
	int xStart=SCREEN_WIDTH-31, yStart=30, height=60, width=12, y1, y2;
	int yWarning = 10; // Warning level, in px from top of chart.
	if (batTempVal_s > 1) batTempVal_s = 1;
	if (refresh) {
		LCD_printText("Bt", SCREEN_WIDTH-30, 22);
		DELAY_US(1e4);
		LCD_barGraphV(xStart, yStart, height, width, batTempVal_s*100, 1);
		LCD_drawLine(SCREEN_WIDTH-32, yStart+yWarning, SCREEN_WIDTH-32+14, yStart+yWarning);
	} else {
		y1 = yStart+height - (height * drawnBatTempVal);
		y2 = yStart+height - (height * batTempVal_s);
		if (y2 < y1) LCD_fillBox(xStart+1, y1, xStart+width-1, y2);
		else LCD_eraseBox(xStart+1, y1, xStart+width-1, y2);
		if (drawnBatTempVal < 0.1 || drawnBatTempVal > 0.9) LCD_drawBox(xStart, yStart, xStart+width, yStart+height); // Redraw box
		if (height - height * drawnBatTempVal <= yWarning+1)
			LCD_drawLine(SCREEN_WIDTH-32, yStart+yWarning, SCREEN_WIDTH-32+14, yStart+yWarning);
	}
	if (height - height * batTempVal_s <= yWarning) LCD_eraseBox(SCREEN_WIDTH-32+1, yStart+yWarning, SCREEN_WIDTH-32+14-1, yStart+yWarning); // Invert color

	drawnBatTempVal = batTempVal_s;
}

volatile float32 motorTempVal = 0; // 0 to +1
float32 drawnMotorTempVal = 0;
void draw_motor_temp(char refresh) {
	float32 motorTempVal_s = motorTempVal;
	int xStart=SCREEN_WIDTH-16, yStart=30, height=60, width=12, y1, y2;
	int yWarning = 20; // Warning level, in px from top of chart.
	if (motorTempVal_s > 1) motorTempVal_s = 1;
	if (refresh) {
		LCD_printText("Mt", SCREEN_WIDTH-15, 22);
		DELAY_US(1e4);
		LCD_barGraphV(xStart, yStart, height, width, motorTempVal_s*100, 1);
		LCD_drawLine(SCREEN_WIDTH-17, yStart+yWarning, SCREEN_WIDTH-17+14, yStart+yWarning);
	} else {
		y1 = yStart+height - (height * drawnMotorTempVal);
		y2 = yStart+height - (height * motorTempVal_s);
		if (y2 < y1) LCD_fillBox(xStart+1, y1, xStart+width-1, y2);
		else LCD_eraseBox(xStart+1, y1, xStart+width-1, y2);
		if (drawnMotorTempVal < 0.1 || drawnMotorTempVal > 0.9) LCD_drawBox(xStart, yStart, xStart+width, yStart+height); // Redraw box
		if (height - height * drawnMotorTempVal <= yWarning+1)
			LCD_drawLine(SCREEN_WIDTH-17, yStart+yWarning, SCREEN_WIDTH-17+14, yStart+yWarning);
	}
	if (height - height * motorTempVal_s <= yWarning) LCD_eraseBox(SCREEN_WIDTH-17+1, yStart+yWarning, SCREEN_WIDTH-17+14-1, yStart+yWarning); // Invert color

	drawnMotorTempVal = motorTempVal_s;
}

volatile char speedMph = 0;
char drawnSpeedMph = 0;
void draw_speed_mph(char refresh) {
	char speedMph_s = speedMph; // Save speed to protect from interrupts.
	if (speedMph_s > 99) speedMph_s = 99; // 99 is max speed that can be displayed
	if (refresh) {
		LCD_Helvetica24x32Bitmap(SCREEN_WIDTH/2 - 24, 40, speedMph_s/10);
		LCD_Helvetica24x32Bitmap(SCREEN_WIDTH/2, 40, speedMph_s%10);
		DELAY_US(0.1e6);
		LCD_printText("mph", SCREEN_WIDTH/2-8, 75);
		DELAY_US(1e4);
	} else if (drawnSpeedMph != speedMph_s) {
		if (speedMph_s<10) {
			if (drawnSpeedMph >= 10) {
				LCD_eraseBox(SCREEN_WIDTH/2 - 24, 40, SCREEN_WIDTH/2+24, 40+32); // Clear first number
				DELAY_US(50e4); // Wait to clear
			}
			LCD_Helvetica24x32Bitmap(SCREEN_WIDTH/2, 40, speedMph_s);
			DELAY_US(0.1e6);
		} else {
			if (speedMph_s/10 != drawnSpeedMph/10) {
				LCD_Helvetica24x32Bitmap(SCREEN_WIDTH/2 - 24, 40, speedMph_s/10);
				DELAY_US(0.1e6);
			}
			if (speedMph_s%10 != drawnSpeedMph%10) {
				LCD_Helvetica24x32Bitmap(SCREEN_WIDTH/2, 40, speedMph_s%10);
				DELAY_US(0.1e6);
			}

		}
	}
	drawnSpeedMph = speedMph_s;
}

volatile char cruiseControlEnabled = 0;
char drawnCruiseControlEnabled = 0;
void draw_cruise_control() {
	char cruiseControlEnabled_s = cruiseControlEnabled;
	if (drawnCruiseControlEnabled != cruiseControlEnabled_s) {
		if (cruiseControlEnabled_s) {
			LCD_printText("CC", SCREEN_WIDTH/2-40, 38);
			DELAY_US(1e4);
			LCD_drawBox(SCREEN_WIDTH/2-42, 36, SCREEN_WIDTH/2-28, 46);
		} else {
			LCD_eraseBox(SCREEN_WIDTH/2-42, 36, SCREEN_WIDTH/2-28, 46);
		}
	}
	drawnCruiseControlEnabled = cruiseControlEnabled_s;
}

volatile float32 SOCVal = 0;
float32 drawnSOCVal = 0;
void draw_SOC(char refresh) {
	float32 SOCVal_s = SOCVal;
	int xStart=SCREEN_WIDTH/2-38, yStart=5, height=10, width=74, x1, x2;
	if (SOCVal_s > 1) SOCVal_s = 1;
	char str[5];
	if (refresh) {
		LCD_printText("SoC", SCREEN_WIDTH/2-56, 7);
		DELAY_US(1e4);
		LCD_barGraphH(xStart, yStart, height, width, SOCVal_s*100, 1);
		sprintf(str, "%d%%", (int)(SOCVal_s*100.0f));
		LCD_printText(str, SCREEN_WIDTH/2+38, 7);
		DELAY_US(1e4);
	} else {
		x1 = xStart + (width * drawnSOCVal);
		x2 = xStart + (width * SOCVal_s);
		if (x2 > x1) LCD_fillBox(x1, yStart+1, x2, yStart+height-1);
		else LCD_eraseBox(x1, yStart+1, x2, yStart+height-1);
		if (drawnSOCVal < 0.1 || drawnSOCVal > 0.9) LCD_drawBox(xStart, yStart, xStart+width, yStart+height); // Redraw box
		if (SOCVal_s != drawnSOCVal) { // Redraw percent figure
			LCD_eraseBox(SCREEN_WIDTH/2+38, 7, SCREEN_WIDTH/2+38+22, 7+10);
			DELAY_US(1e4);
			sprintf(str, "%d%%", (int)(SOCVal_s*100.0f));
			LCD_printText(str, SCREEN_WIDTH/2+38, 7);
			DELAY_US(1e4);
		}
	}
	drawnSOCVal = SOCVal_s;
}

volatile float32 mpptVal = 0;
float32 drawnMpptVal = 0;
void draw_mppt_value(char refresh) {
	float32 mpptVal_s = mpptVal;
	int xStart=32, yStart=96, height=7, width=95, x1, x2;
	char str[5];
	if (mpptVal_s > 1) mpptVal_s = 1;
	if (refresh) {
		LCD_printText("mppt", 5, 96);
		DELAY_US(1e4);
		LCD_barGraphH(xStart, yStart, height, width, mpptVal_s*100, 1);
		sprintf(str, "%d%%", (int)(mpptVal_s*100.0f));
		LCD_printText(str, 134, 96);
		DELAY_US(1e4);
	} else {
		x1 = xStart + (width * drawnMpptVal);
		x2 = xStart + (width * mpptVal_s);
		if (x2 > x1) LCD_fillBox(x1, yStart+1, x2, yStart+height-1);
		else LCD_eraseBox(x1, yStart+1, x2, yStart+height-1);
		if (drawnMpptVal < 0.1 || drawnMpptVal > 0.9) LCD_drawBox(xStart, yStart, xStart+width, yStart+height); // Redraw box
		if (mpptVal_s != drawnMpptVal) { // Redraw percent figure
			LCD_eraseBox(134, 96, 134+22, 96+10);
			DELAY_US(1e4);
			sprintf(str, "%d%%", (int)(mpptVal_s*100.0f));
			LCD_printText(str, 134, 96);
			DELAY_US(1e4);
		}
	}
	drawnMpptVal = mpptVal_s;
}

volatile float32 currentIVal = 0; // From 0 to 1.
float32 drawnCurrentIVal = 0;
void draw_currentI_value(char refresh) {
	float32 currentIVal_s = currentIVal;
	int xStart=32, yStart=105, height=7, width=95, x1, x2;
	char str[5];
	if (currentIVal_s > 1) currentIVal_s = 1;
	if (refresh) {
		LCD_printText("I", 23, 105);
		DELAY_US(1e4);
		LCD_barGraphH(xStart, yStart, height, width, currentIVal_s*100, 1);
		sprintf(str, "%dA", (int)(currentIVal_s*CURRENT_IVAL_MAX_CURRENT));
		LCD_printText(str, 134, 105);
		DELAY_US(1e4);
	} else {
		x1 = xStart + (width * drawnCurrentIVal);
		x2 = xStart + (width * currentIVal_s);
		if (x2 > x1) LCD_fillBox(x1, yStart+1, x2, yStart+height-1);
		else LCD_eraseBox(x1, yStart+1, x2, yStart+height-1);
		if (drawnCurrentIVal < 0.1 || drawnCurrentIVal > 0.9) LCD_drawBox(xStart, yStart, xStart+width, yStart+height); // Redraw box
		if (currentIVal_s != drawnCurrentIVal) { // Redraw percent figure
			LCD_eraseBox(134, 105, 134+22, 105+10);
			DELAY_US(1e4);
			sprintf(str, "%dA", (int)(currentIVal_s*CURRENT_IVAL_MAX_CURRENT));
			LCD_printText(str, 134, 105);
			DELAY_US(1e4);
		}
	}
	drawnCurrentIVal = currentIVal_s;
}

volatile Uint32 motorFaultRegisters = 0; // Direct fault registers from motor
// Formatted like [F4][F3][F2][F1]
Uint32 drawnMotorFaultRegisters = 0;
void draw_motor_faults() {
	Uint32 motorFaultRegisters_s = motorFaultRegisters;
	char str[32] = "";
	char tmpstr[5];
	int i;
	if (drawnMotorFaultRegisters != motorFaultRegisters_s) {
		for (i = 0; i < 32; i++) {
			if ( (motorFaultRegisters_s>>i) & (Uint32)1 ) {
				tmpstr[0] = '0' + i/8 + 1; // Fault type
				tmpstr[1] = ':';
				tmpstr[2] = '0' + i%8 + 1; // Fault number
				tmpstr[3] = ' ';
				tmpstr[4] = '\0';
				strcat(str, tmpstr);
				if (strlen(str) > 20) break; // Too long.
			}
		}
		LCD_eraseBox(5, SCREEN_HEIGHT-10, 155, SCREEN_HEIGHT);
		DELAY_US(50e4);
		LCD_printText(str, 5, SCREEN_HEIGHT-10);
	}
	drawnMotorFaultRegisters = motorFaultRegisters_s;
}

volatile char blinkerState = 0; // 0 = off, 1 = left  blinker, 2 = right blinker, 3 = both blinkers
char drawnBlinkerState = 0;
void draw_blinkers() {
	char blinkerState_s = blinkerState;
	if (drawnBlinkerState != blinkerState_s) {
		switch (blinkerState_s) {
		case 0: // No blinkers
			LCD_eraseBox(SCREEN_WIDTH-20, 0, SCREEN_WIDTH, 20);
			DELAY_US(20e4);
			LCD_eraseBox(0, 0, 20, 20);
			DELAY_US(20e4);
			break;
		case 1: // Left blinker
			LCD_eraseBox(SCREEN_WIDTH-20, 0, SCREEN_WIDTH, 20);
			DELAY_US(20e4);
			LCD_BlinkerArrowBitmap(0, 0, 0); // L blinker
			break;
		case 2: // Right blinker
			LCD_eraseBox(0, 0, 20, 20);
			DELAY_US(20e4);
			LCD_BlinkerArrowBitmap(SCREEN_WIDTH-20, 0, 1); // R blinker
			break;
		case 3: // Both blinkers
			LCD_BlinkerArrowBitmap(SCREEN_WIDTH-20, 0, 1); // R blinker
			LCD_BlinkerArrowBitmap(0, 0, 0); // L blinker
			break;
		default:
			break;
		}
	}
	drawnBlinkerState = blinkerState_s;
}

volatile char CANErrorActive = 0;
char drawnCANErrorActive = 0;
void draw_CAN_error() {
	char CANErrorActive_s = CANErrorActive;
	int xStart=SCREEN_WIDTH/2-40, yStart=25, width=34, height=6;
	if (drawnCANErrorActive != CANErrorActive_s) {
		if (CANErrorActive_s) {
			LCD_printText("CANERR", xStart, yStart);
			DELAY_US(1e4);
			LCD_drawBox(xStart-2, yStart-2, xStart+width+2, yStart+height+2);
		} else {
			LCD_eraseBox(xStart-2, yStart-2, xStart+width+2, yStart+height+2);
		}
	}
	drawnCANErrorActive = CANErrorActive_s;
}

volatile char motorErrorActive = 0;
char drawnMotorErrorActive = 0;
void draw_motor_error() {
	char motorErrorActive_s = motorErrorActive;
	int xStart=SCREEN_WIDTH/2+4, yStart=25, width=34, height=6;
	if (drawnMotorErrorActive != motorErrorActive_s) {
		if (motorErrorActive_s) {
			LCD_printText("MOTERR", xStart, yStart);
			DELAY_US(1e4);
			LCD_drawBox(xStart-2, yStart-2, xStart+width+2, yStart+height+2);
		} else {
			LCD_eraseBox(xStart-2, yStart-2, xStart+width+2, yStart+height+2);
		}
	}
	drawnMotorErrorActive = motorErrorActive_s;
}

volatile char reverseModeEnabled = 0;
char drawnReverseModeEnabled = 0;
void draw_motor_reverse_enabled() {
	char reverseModeEnabled_s = reverseModeEnabled;
	int xStart=SCREEN_WIDTH/2-40, yStart=80, width=16, height=6;
	if (drawnReverseModeEnabled != reverseModeEnabled_s) {
		if (reverseModeEnabled_s) {
			LCD_printText("REV", xStart, yStart);
			DELAY_US(1e4);
			LCD_drawBox(xStart-2, yStart-2, xStart+width+2, yStart+height+2);
		} else {
			LCD_eraseBox(xStart-2, yStart-2, xStart+width+2, yStart+height+2);
		}
	}
	drawnReverseModeEnabled = reverseModeEnabled_s;
}
