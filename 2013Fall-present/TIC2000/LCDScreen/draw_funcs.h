/*
 * draw_funcs.h
 *
 *  Created on: Jun 22, 2014
 *      Author: Alex
 */

#ifndef DRAW_FUNCS_H_
#define DRAW_FUNCS_H_

#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File
#include "sci_funcs.h"
#include "PeripheralHeaderIncludes.h"

void LCD_Helvetica24x32Bitmap(char xpos, char ypos, char number);
void LCD_BlinkerArrowBitmap(char xpos, char ypos, char isRight);
void LCD_barGraphH(int xStart, int yStart, int height, int width, double percent, char rewrite);
void LCD_barGraphV(int xStart, int yStart, int height, int width, double percent, char rewrite);
void LCD_throttleGraphV(int xStart, int yStart, int height, int width, float32 percent);
void LCD_vertical_line_slider(int xCenter, int yStart, int height, int width, float32 percent);

// Primitive drawing functions:
void LCD_clearScreen();
void LCD_toggleReverse();
void LCD_setBacklight(int duty);
void LCD_demo();
void LCD_setX(int posX);
void LCD_setY(int posY);
void LCD_resetXY();
void LCD_drawLine(int xStart, int yStart, int xEnd, int yEnd);
void LCD_drawBox(int xStart, int yStart, int xEnd, int yEnd);
void LCD_drawCircle(int xStart, int yStart, int radius);
void LCD_eraseBox(int xStart, int yStart, int xEnd, int yEnd);
void LCD_setPixel(int x, int y, int set);
void LCD_fillBox(int xStart, int yStart, int xEnd, int yEnd);
void LCD_printText(char *text, int x, int y);

#endif /* DRAW_FUNCS_H_ */
