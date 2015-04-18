/**
* @ingroup telemetry
* @defgroup lcd LCD
* @brief LCD functions
* 
* @{
*/

#include "lcd.h"
#include "../lib7800/DIO.h"
#include "bitmaps.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "main.h"
#include "wrapper.h"
#include <string.h>
#include <stdbool.h>

/**
@author Reid Kersey <reidkersey@gmail.com> 678-736-0899

@brief The function initializes the DOGM128 LCD Screens

@details The function intializes the DOGM128 LCD Screens
by initializing the pins (set in lcd.h), and then writing
commands to the lcd spi bus.

@warning This function must be called before using any function that attempts to update the LCD screens

@todo remove "Magic numbers" that represent the commands

@param device The pin structure that tells the function what pins to set high and low
*/
void InitLCD(struct LCD_screen *device)
{//initialize the display with the correct commands
    InitDIO_direction(device->ss, device->ss_row+4, GPIO_OUTPUT );//set the pins io direction
    InitDIO_direction(device->clk, device->clk_row+4, GPIO_OUTPUT );
    InitDIO_direction(device->A0, device->A0_row+4, GPIO_OUTPUT );
    InitDIO_direction(device->mosi,device->mosi_row+4, GPIO_OUTPUT );
    InitDIO_direction(BUTTON_LEFT_PIN, GPIO_DIR_A, GPIO_INPUT);
    InitDIO_direction(BUTTON_CENTER_PIN, GPIO_DIR_A, GPIO_INPUT);
    InitDIO_direction(BUTTON_RIGHT_PIN, GPIO_DIR_A, GPIO_INPUT);

    SetPin(device->ss, device->ss_row, DISPLAY_SELECT);//set each display to be selected based on function inputs 
    SetPin(device->A0, device->A0_row, DISPLAY_CMD );//set A0 to be a command
    writeLCDSPI(0x40, device);//set the start line to 0
    writeLCDSPI(0xA1, device);//adc reverse
    writeLCDSPI(0xC0, device);//normal com0~com63
    writeLCDSPI(0xA6, device);//display normal
    writeLCDSPI(0xA2, device);//set bias 1/9(duty 1/65)
    writeLCDSPI(0x2F, device);//booster regulator and follow on
    writeLCDSPI(0xF8, device);//set internal booster to 4x
    writeLCDSPI(0x00, device);//see above
    writeLCDSPI(0x27, device);//contrast set
    writeLCDSPI(0x81, device);//see above
    writeLCDSPI(0x16, device);//see above
    writeLCDSPI(0xAC, device);//no static indicator
    writeLCDSPI(0x00, device);//see above
    writeLCDSPI(0xAF, device);//display on
    writeLCDSPI(0xB0, device);//set the ram page address to 0
    writeLCDSPI(0x10, device);//set the column to 0
    writeLCDSPI(0x00, device);//see above
    clearDisplay(device); //clear the displays to clear any residual memory
	
	logMessage("LCD device initialized successfully", 0);
}

void writeSpeedType(struct LCD_screen *device){
	int column;

	SetPin(device->ss, device->ss_row, DISPLAY_SELECT);//set each display to be selected based on function inputs 
	
	SetPin(device->A0, 	device->A0_row, DISPLAY_CMD);
	writeLCDSPI(0xb0+SPEED_TYPE_TOP_PAGE, device);//select the page
	writeLCDSPI(0x10+(SPEED_TYPE_COL>>4), device);//select the first column MSB
	writeLCDSPI(0x00+(SPEED_TYPE_COL&0xF), device);//select the first column LSB
	SetPin(device->A0, 	device->A0_row, DISPLAY_DATA);//set to data mode
	for (column=0; column<SPEED_TYPE_COLS; column++)//do the following for each column
	{
		writeLCDSPI(underline, device);//write _'s
	}
	
	SetPin(device->A0, 	device->A0_row, DISPLAY_CMD);
	writeLCDSPI(0xb0+SPEED_TYPE_GPS_PAGE, device);//select the page
	writeLCDSPI(0x10+(SPEED_TYPE_COL>>4), device);//select the first column MSB
	writeLCDSPI(0x00+(SPEED_TYPE_COL&0xF), device);//select the first column LSB
	SetPin(device->A0, 	device->A0_row, DISPLAY_DATA);//set to data mode
	writeLCDSPI(pageLine, device);//write a |
	
	if(getUseGPSSpeed()){
		for (column=0; column<SPEED_TYPE_TXT_PAD; column++)//do the following for each column
		{
			writeLCDSPI(pageLine, device);//write 
		}
		writeInvertString(device, SPEED_TYPE_GPS_PAGE, SPEED_TYPE_COL+SPEED_TYPE_TXT_PAD+1, "GPS");
		for (column=0; column<SPEED_TYPE_TXT_PAD-1; column++)//do the following for each column
		{
			writeLCDSPI(pageLine, device);//write 
		}
		writeLCDSPI(pageLine, device);//write a |
		
		SetPin(device->A0, 	device->A0_row, DISPLAY_CMD);
		writeLCDSPI(0xb0+SPEED_TYPE_RPM_PAGE, device);//select the page
		writeLCDSPI(0x10+(SPEED_TYPE_COL>>4), device);//select the first column MSB
		writeLCDSPI(0x00+(SPEED_TYPE_COL&0xF), device);//select the first column LSB
		SetPin(device->A0, 	device->A0_row, DISPLAY_DATA);//set to data mode
		writeLCDSPI(pageLine, device);//write a |
		
		for (column=0; column<SPEED_TYPE_TXT_PAD; column++)//do the following for each column
		{
			writeLCDSPI(underline, device);//write 
		}
		writeUnderlineString(device, SPEED_TYPE_RPM_PAGE, SPEED_TYPE_COL+SPEED_TYPE_TXT_PAD+1, "RPM");
		for (column=0; column<SPEED_TYPE_TXT_PAD-1; column++)//do the following for each column
		{
			writeLCDSPI(underline, device);//write 
		}
		writeLCDSPI(pageLine, device);//write a |
		
		
	}else{
		for (column=0; column<SPEED_TYPE_TXT_PAD; column++)//do the following for each column
		{
			writeLCDSPI(underline, device);//write 
		}
		writeUnderlineString(device, SPEED_TYPE_GPS_PAGE, SPEED_TYPE_COL+SPEED_TYPE_TXT_PAD+1, "GPS");
		for (column=0; column<SPEED_TYPE_TXT_PAD-1; column++)//do the following for each column
		{
			writeLCDSPI(underline, device);//write 
		}
		writeLCDSPI(pageLine, device);//write a |
		
		SetPin(device->A0, 	device->A0_row, DISPLAY_CMD);
		writeLCDSPI(0xb0+SPEED_TYPE_RPM_PAGE, device);//select the page
		writeLCDSPI(0x10+(SPEED_TYPE_COL>>4), device);//select the first column MSB
		writeLCDSPI(0x00+(SPEED_TYPE_COL&0xF), device);//select the first column LSB
		SetPin(device->A0, 	device->A0_row, DISPLAY_DATA);//set to data mode
		writeLCDSPI(pageLine, device);//write a |
		
		for (column=0; column<SPEED_TYPE_TXT_PAD; column++)//do the following for each column
		{
			writeLCDSPI(pageLine, device);//write 
		}
		writeInvertString(device, SPEED_TYPE_RPM_PAGE, SPEED_TYPE_COL+SPEED_TYPE_TXT_PAD+1, "RPM");
		for (column=0; column<SPEED_TYPE_TXT_PAD-1; column++)//do the following for each column
		{
			writeLCDSPI(pageLine, device);//write 
		}
		writeLCDSPI(pageLine, device);//write a |
	}
		
	SetPin(device->ss, device->ss_row, DISPLAY_NOTSELECT); //set the CS back to normal
}

void writeUnderlineString(struct LCD_screen *device, int page, int column, char text[])
{
	int i;
	int j;
	int index;
	char c;
	
	SetPin(device->A0, 	device->A0_row, DISPLAY_CMD); //set the display to cmd mode
	writeLCDSPI(0xB0+page, device); //set the page
	writeLCDSPI(0x10+(column>>4), device); //set the column MSB
	writeLCDSPI(0x00+(column&15), device); //set the column LSB
	
	SetPin(device->A0, 	device->A0_row, DISPLAY_DATA); //set the display to data mode
	
	for(i = 0; i < strlen(text); i++) {
		c = toupper(text[i]);

		if(isdigit(c)) {
			index = 5 * (c - '0');//set the starting point to the right spot in the array each character is 5 columns wide
			for(j = 0; j < 5; j++){//write out the 5 columns for the character
				writeLCDSPI(num[index + j]|underline, device);//send the line
			}
		}else if(isalpha(c)) {
			index = 5 * (c - 'A');//set the starting point to the right spot in the array each character is 5 columns wide
			for(j = 0; j < 5; j++){//write out the 5 columns for the character
				writeLCDSPI(alpha[index + j]|underline, device);//send the line
			}
		}else if(c == ':') {
			for(j = 0; j < 5; j++){//write out the 5 columns for the character
				writeLCDSPI(colon[j]|underline, device);//write a colon
			}
		}else if(c == ' ') {
			for(j = 0; j < 4; j++){//write out the 5 columns for the character
				writeLCDSPI(emptyLine|underline, device);
			}
		}

		writeLCDSPI(emptyLine|underline, device);//make the characters spaced out
	}
}

void writeInvertString(struct LCD_screen *device, int page, int column, char text[])
{
	int i;
	int j;
	int index;
	char c;
	
	SetPin(device->A0, 	device->A0_row, DISPLAY_CMD); //set the display to cmd mode
	writeLCDSPI(0xB0+page, device); //set the page
	writeLCDSPI(0x10+(column>>4), device); //set the column MSB
	writeLCDSPI(0x00+(column&15), device); //set the column LSB
	
	SetPin(device->A0, 	device->A0_row, DISPLAY_DATA); //set the display to data mode
	
	for(i = 0; i < strlen(text); i++) {
		c = toupper(text[i]);

		if(isdigit(c)) {
			index = 5 * (c - '0');//set the starting point to the right spot in the array each character is 5 columns wide
			for(j = 0; j < 5; j++){//write out the 5 columns for the character
				writeLCDSPI(~num[index + j], device);//send the line
			}
		}else if(isalpha(c)) {
			index = 5 * (c - 'A');//set the starting point to the right spot in the array each character is 5 columns wide
			for(j = 0; j < 5; j++){//write out the 5 columns for the character
				writeLCDSPI(~alpha[index + j], device);//send the line
			}
		}else if(c == ':') {
			for(j = 0; j < 5; j++){//write out the 5 columns for the character
				writeLCDSPI(~colon[j], device);//write a colon
			}
		}else if(c == ' ') {
			for(j = 0; j < 4; j++){//write out the 5 columns for the character
				writeLCDSPI(~emptyLine, device);
			}
		}

		writeLCDSPI(~emptyLine, device);//make the characters spaced out
	}
}

/**
@author Reid Kersey <reidkersey@gmail.com> 678-736-0899

@brief This function writes one byte(1 char value) to the SPI line of the device specified.

@details This function writes one byte to the SPI line of the device specified.
This function \b should \b not be used to cycle the clock line, or to
write null bits. The general purpose of this function is to write commands
to an SPI bus.

@param device The pin structure that tells the function what pins to set high and low
@param data The character value that represents the 8 bits of data to be sent.
*/
void writeLCDSPI(unsigned char data, struct LCD_screen *device){
	int i; //set up the ideration
	for(i=0; i < 8; i++) { //write to the spi line 8 times (one byte)
		if ((data << i )& 0x80) {//if the current bit is a one
			writeLCDSPI_bit(1, device);
		}else { //if the current bit is a 0
			writeLCDSPI_bit(0, device);
		}
	}
	SetPin(device->clk	,device->clk_row, LCDSPI_CLK_INIT); //set the clock high (this is the idle state)
	SetPin(device->mosi	,device->mosi_row, LCDSPI_MOSI_INIT); //set the data low (this is the idle state)
}

/**
@author Reid Kersey <reidkersey@gmail.com> 678-736-0899

@brief This function writes one bit to the SPI line of the device specified.

@details This function writes one bit to the SPI line of the device specified.
It can be used to cycle the clock line, or to write null bits. Any data that
is not a 1 is treated as a 0.

@warning This function does not put the data lines back to the original
state. That is up to the calling function.

@param data The integer value of the bit to be sent. Either one or zero.
@param device The pin structure that tells the function what pins to set high and low
*/
void writeLCDSPI_bit(int data, struct LCD_screen *device){
	if(data == 1){
		SetPin(device->mosi, device->mosi_row, PIN_HIGH); //set the data line high
		SPIclockCycle(device);
	}else{
		SetPin(device->mosi, device->mosi_row, PIN_LOW); //set the data line high
		SPIclockCycle(device);
	}
}

/**
@author Reid Kersey <reidkersey@gmail.com> 678-736-0899

@brief This function will cycle the clock cycle

@details This function relies on the definition of DEFAULT_CLK in lcd.h.

@details This function cycles the clock line

@warning This function assumes that the clock line is in the default state already.

@param device The pin structure that tells the function what pins to set high and low
*/
void SPIclockCycle(struct LCD_screen *device){
	SetPin(device->clk, device->clk_row, !DEFAULT_CLK);
	SetPin(device->clk, device->clk_row, DEFAULT_CLK);
}

/**
@author Reid Kersey <reidkersey@gmail.com> 678-736-0899

@brief This function will take a button press direction, and change the pages accordingly

@details This function takes the button direction, and the pages associated with the 
error LCD screen. It will then modify the pages, to the users requested page. The
function dynamically creates additional pages for errors to display on if there are
more than 7 errors.

@warning updateErrorScreen must be called \b after calling this function.

@param device The pin structure that tells the function what pins to set high and low
*/
void LCDButtonPush(struct LCD_screen *device){
	int direction;
	int buttonDB = getButtonDB();
	
	if(CheckPinRaw(BUTTON_LEFT_PIN, GPIO_DAT_A)&& !buttonDB)
	{
		direction = BUTTON_LEFT;
		setButtonDB(1);
	}else if(CheckPinRaw(BUTTON_RIGHT_PIN, GPIO_DAT_A)&& !buttonDB)
	{
		direction = BUTTON_RIGHT;
		setButtonDB(1);
	}else if(CheckPinRaw(BUTTON_CENTER_PIN, GPIO_DAT_A)&& !buttonDB)
	{
		device->reset = 1;
		direction = BUTTON_CENTER;
		setButtonDB(1);
	}else
	{
		return;
	}
	switch(direction){
		case BUTTON_LEFT:
			if(device->page >= 1){
				device->page -= 1;
				device->clear = 1;
				device->pageSwitch = 1;
			}else if(getNumErrors() > (device->errorPage+1)*ERROR_PER_PAGE){
				device->errorPage += 1;
				device->clear = 1;
				device->pageSwitch = 1;
			}
			break;
		case BUTTON_RIGHT:
			if(device->page < SPEED_PAGE && device->errorPage == 0){
				device->page += 1;
				device->clear = 1;
				device->pageSwitch = 1;
			}else if(device->errorPage > 0){
				device->errorPage -= 1;
				device->clear = 1;
				device->pageSwitch = 1;
			}
			break;
		case BUTTON_CENTER:
			device->page = MAIN_PAGE;
			device->errorPage = 0;
			device->clear = 1;
			device->pageSwitch = 1;
			break;
	}
}


/**
@author Reid Kersey <reidkersey@gmail.com> 678-736-0899

@brief This function will reset and reinitialize the screens

@details This function issues the reset command and then calls the
LCD initialization function function

@param device The pin structure that tells the function what pins to set high and low and
hold different variables.
*/
void displayReset(struct LCD_screen *device){
	SetPin(device->ss, device->ss_row, DISPLAY_SELECT);//set each display to be selected based on function inputs 
	SetPin(device->A0, 	device->A0_row, DISPLAY_CMD);
	writeLCDSPI(LCD_RESET, device);//DO A SOFT RESET
	InitLCD(device);
	SetPin(device->ss, device->ss_row, DISPLAY_NOTSELECT);//make sure to de-select the display
	device->reset = 0;
	device->pageSwitch = 1;
}

/**
@author Reid Kersey <reidkersey@gmail.com> 678-736-0899

@brief This function will update the screen passed in to be the error screen

@details This function takes in all of the nesasary values, and the page
to write the data to the error screen. It will then based  on the page,
execute the appropriate routine to display the data. The Error Screen
has multiple pages, that show different values, and different items.

@warning Every second element of the arrays must be 21 characters long.

@todo make out of range values flash
@todo update LCD with changed values

@param device The pin structure that tells the function what pins to set high and low
*/
void updateLCD(struct LCD_screen *device)
{
	int i;
	int pageBreak = 0;
	if(device->clear == 1){
		clearDisplay(device);
	}
	switch(device->page){
		case ERRORS_PAGE:
			for(i = 0;i < getNumErrors(); i++)
			{
				if(strcmp(getErrors(i),device->errors[i]) || device->pageSwitch){
					pageBreak = 1;
				}
			}
			if(pageBreak || device->pageSwitch){
				device->pageSwitch = 0;
				writeString(device, ERROR_HEADER_PAGE, ERROR_START_COL, "Errors:");
				for(i = 0; i < ERROR_PER_PAGE && i < getNumErrors(); i++)
				{
					writeString(device, ERROR_HEADER_PAGE+1+i, ERROR_START_COL, getErrors(i));
					strcpy(device->errors[i], getErrors(i));
				}
			}
			break;
		case MAIN_PAGE:
			for(i = 0; i < ERROR_PER_PAGE; i++)
			{
				if(strcmp(getLCDGeneral(i),device->general[i]) || device->pageSwitch){
					pageBreak = 1;
				}
			}
			if(pageBreak){
				device->pageSwitch = 0;
				writeString(device, ERROR_HEADER_PAGE, ERROR_START_COL, "Main Page:");
				for(i = 0; i < ERROR_PER_PAGE; i++)
				{
					writeString(device, ERROR_HEADER_PAGE+1+i, ERROR_START_COL, getLCDGeneral(i));
					strcpy(device->general[i], getLCDGeneral(i));
				}
			}
			break;
		case VOLTAGES_PAGE:
			for(i = 0; i < ERROR_PER_PAGE; i++)
			{
				if(strcmp(getLCDVoltages(i),device->voltages[i]) || device->pageSwitch){
					pageBreak = 1;
					break;
				}
			}
			if(pageBreak){
				device->pageSwitch = 0;
				writeString(device, ERROR_HEADER_PAGE, ERROR_START_COL, "Voltages Page:");
				for(i = 0; i < ERROR_PER_PAGE; i++)
				{
					writeString(device, ERROR_HEADER_PAGE+1+i, ERROR_START_COL, getLCDVoltages(i));
					strcpy(device->voltages[i], getLCDVoltages(i));
				}
			}
			break;
		case CURRENTS_PAGE:
			for(i = 0; i < ERROR_PER_PAGE; i++)
			{
				if(strcmp(getLCDCurrents(i),device->currents[i]) || device->pageSwitch){
					pageBreak = 1;
				}
			}
			if(pageBreak){
				device->pageSwitch = 0;
				writeString(device, ERROR_HEADER_PAGE, ERROR_START_COL, "Currents Page:");
				for(i = 0; i < ERROR_PER_PAGE; i++)
				{
					writeString(device, ERROR_HEADER_PAGE+1+i, ERROR_START_COL, getLCDCurrents(i));
					strcpy(device->currents[i], getLCDCurrents(i));
				}
			}
			break;
		case TEMPS_PAGE:
			for(i = 0; i < ERROR_PER_PAGE; i++)
			{
				if(strcmp(getLCDTemps(i),device->temps[i]) || device->pageSwitch){
					pageBreak = 1;
				}
			}
			if(pageBreak){
				device->pageSwitch = 0;
				writeString(device, ERROR_HEADER_PAGE, ERROR_START_COL, "Temperature Page:");
                                for(i = 0; i < ERROR_PER_PAGE; i++)
				{
					writeString(device, ERROR_HEADER_PAGE+1+i, ERROR_START_COL, getLCDTemps(i));
					strcpy(device->temps[i], getLCDTemps(i));
				}
			}
			break;
		case SPEED_PAGE:
			updateSpeedometer(device);
			break;
	}
}

/**
@author Reid Kersey <reidkersey@gmail.com> 678-736-0899

@brief This function clears the display

@details This function will go page by page to the display
and write zeros

@todo get rid of magic numbers

@param device The pin structure that tells the function what pins to set high and low
*/
void clearDisplay(struct LCD_screen *device)
{
	int page=0;//the "page" (row multiplier)
	int column=0;//the column 
	
	SetPin(device->ss, device->ss_row, DISPLAY_SELECT);//set each display to be selected based on function inputs 

	
	for (page=0; page<LCD_PAGES; page++)//do the following for each page
	{
		SetPin(device->A0, 	device->A0_row, DISPLAY_CMD);
		writeLCDSPI(0xb0+page, device);//select the page
		writeLCDSPI(0x10, device);//select the first column MSB
		writeLCDSPI(0x00, device);//select the first column LSB
		SetPin(device->A0, 	device->A0_row, DISPLAY_DATA);//set to data mode
		for (column=0; column<LCD_COLS; column++)//do the following for each column
		{
			writeLCDSPI(0x00, device);//write 0's
		}
	}
	SetPin(device->ss, device->ss_row, DISPLAY_NOTSELECT); //set the CS back to normal
	device->clear = 0;

}

/**
@author Reid Kersey <reidkersey@gmail.com> 678-736-0899

@brief This function updates the cruise text on the spedometer page

@details This function will clear the area on the screen
that corsponds to the position of the cruise text, and re-write
the cruise speed text with the given value

@param device The pin structure that tells the function what pins to set high and low
@param cruise This is the speed that the cruise control is set at
*/
void updateCruise(struct LCD_screen *device, int cruise)
{
	char cruiseStr[MAX_CRUISE_LENGTH];
	sprintf(cruiseStr, "CRUISE: %d", cruise);
	clearArea(device, SPEED_CRUISE_PAGE, SPEED_CRUISE_PAGE, MAX_COL-MAX_CRUISE_COLS, MAX_COL);
	writeString(device, SPEED_CRUISE_PAGE, MAX_COL-(strlen(cruiseStr)*COLS_PER_CHAR), cruiseStr);
}

/**
@author Reid Kersey <reidkersey@gmail.com> 678-736-0899

@brief This function updates the battery charge text, and battery bar on the spedometer page

@details This function will clear the area on the screen
that corasponds to the position of the battery text, battery bar
and re-write the battery text, and battery bar with the given value

@param device The pin structure that tells the function what pins to set high and low
@param bat This is the percentage of the battery 
*/
void updateBat(struct LCD_screen *device, int bat)
{
	char batteryStr[MAX_BAT_LENGTH];//create the character array for the battery string
	sprintf(batteryStr, "BAT: %d", bat); //make the battery text
	clearArea(device, SPEED_CRUISE_PAGE, SPEED_CRUISE_PAGE, MIN_COL,MAX_BAT_COLS);
	writeString(device, SPEED_CRUISE_PAGE, MIN_COL, batteryStr);
	createGraph(device, SPEED_BARGRAPH_PAGE, bat);
}

/**
@author Reid Kersey <reidkersey@gmail.com> 678-736-0899

@brief This function updates the speed text on the speedometer page

@details This function will clear the area on the screen
that corasponds to the position of the speed text, and re-write
the speed text with the given value

@param device The pin structure that tells the function what pins to set high and low
@param speed This is the current speed that the car is going
*/
void updateSpeed(struct LCD_screen *device, int speed)
{
	int speed_digit0 = speed / 100; //get the leading digit (100's)
	int speed_digit1 = (speed / 10)-(10*speed_digit0); //get the first digit (10's)
	int speed_digit2 = speed % 10; //get the second digit (1's)
	
	int page=0;//the "page"(row multiplier) for the data k
	int column=0;//the column for the data l
	int index; //the index for the bitmap array
	SetPin(device->ss, 	device->ss_row, DISPLAY_SELECT );//toggle the cip select to the desired values
	for (page=0; page<SPEED_DIGIT_MAX_PAGES; page++)//Go page by page
	{
		SetPin(device->A0, 	device->A0_row, DISPLAY_CMD); //set the display to cmd mode
		writeLCDSPI(FIRST_PAGE+SPEED_DIGIT_START_PAGE+page, device); //set the page
		writeLCDSPI(FIRST_COL_MSB+SPEED_DIGIT_START_COL_MSB, device); //set the column MSB
		writeLCDSPI(FIRST_COL_LSB+SPEED_DIGIT_START_COL_LSB, device); //set the column LSB
		
		index = speed_digit0*SPEED_DIGIT_TOTAL_COLS + page*SPEED_DIGIT_COLS_PER_ROW; //find the starting index in the array
		
		SetPin(device->A0, 	device->A0_row, DISPLAY_DATA);//set the displays to data mode
		if(speed_digit0){
			for (column=0; column<SPEED_DIGIT_COLS_PER_ROW; column++){
				writeLCDSPI(speedNum[index+column], device);
			}
		}else{
			for (column=0; column<SPEED_DIGIT_COLS_PER_ROW; column++){
				writeLCDSPI(emptyLine, device);
			}
		}
		
		index = speed_digit1*SPEED_DIGIT_TOTAL_COLS + page*SPEED_DIGIT_COLS_PER_ROW;
		
		for (column=0; column<SPEED_DIGIT_COLS_PER_ROW; column++)
		{ //write out the numbers column by column
			writeLCDSPI(speedNum[index+column], device); //send the data in the array
		}

		index = speed_digit2*SPEED_DIGIT_TOTAL_COLS + page*SPEED_DIGIT_COLS_PER_ROW; //find the starting index in the array
		
		for (column=0; column<SPEED_DIGIT_COLS_PER_ROW; column++)
		{//write out the numbers column by column
			writeLCDSPI(speedNum[index+column], device);//send the data in the array
		}
	}
	SetPin(device->ss, 	device->ss_row, DISPLAY_NOTSELECT );//toggle the cip select to the desired values
}

/**
@author Reid Kersey <reidkersey@gmail.com> 678-736-0899

@brief This function clears an area on the screen

@details This function takes takes in the pages (rows 
in multiples of 8) start and end values, and the columns
start and end values. It then procedes to write all zero's
to the selected area on the given device.

@param device The pin structure that tells the function what pins to set high and low
@param pageStart The page (0-7) that the top of the rectange to be cleared is located
@param pageEnd The page (0-7) that the bottom of the rectange to be cleared is located
@param colStart The column (0-127) that the left hand side of the rectangle to be cleared is located
@param colEnd The column (0-127) that the right hand side of the rectangle to be cleared is located
*/
void clearArea(struct LCD_screen *device, int pageStart, int pageEnd, int colStart, int colEnd){
	int i,j;

	if(pageStart < MIN_PAGE || pageEnd > MAX_PAGE || colStart < MIN_COL || colEnd > MAX_COL){
		return;
	}
	
	SetPin(device->ss, 	device->ss_row, DISPLAY_SELECT );//toggle the cip select to the desired values
	
	for(i = 0; i <= (pageEnd - pageStart); i++)
	{
		SetPin(device->A0, 	device->A0_row, DISPLAY_CMD);
		writeLCDSPI(FIRST_PAGE+pageStart+i, device); //set the page
		writeLCDSPI(FIRST_COL_MSB+(colStart>>4), device); //set the column MSB
		writeLCDSPI(FIRST_COL_LSB+(colStart&0xf), device); //set the column LSB
		SetPin(device->A0, 	device->A0_row, DISPLAY_DATA);
		for(j = 0; j <= (colEnd-colStart); j++)
		{
			writeLCDSPI(emptyLine, device); //write a zero
		}
	}
	SetPin(device->ss, 	device->ss_row, DISPLAY_NOTSELECT );//toggle the cip select to the desired values
}

/**
@author Reid Kersey <reidkersey@gmail.com> 678-736-0899

@brief This function creates a horizontal bar graph

@details This function takes in a page number (0-7)
and a percentage to fill the bar. It will create a full page
horizontal bar graph, filled to the percentage given.

@todo remove "Magic numbers" that represent the commands

@param device The pin structure that tells the function what pins to set high and low
@param percent The percentage (0-100) that the bar is supposed to be filled
@param page The page that the graph is supposed to be displayed on (0-7)
*/
void createGraph(struct LCD_screen *device, int page, int percent)
{
	int i;
	
	SetPin(device->ss, 	device->ss_row, DISPLAY_SELECT );//toggle the cip select to the desired values
	
	SetPin(device->A0, 	device->A0_row, DISPLAY_CMD); //set the displays into command mode
	writeLCDSPI(FIRST_PAGE+page, device); //set the page
	writeLCDSPI(FIRST_COL_MSB, device); //set the column MSB
	writeLCDSPI(FIRST_COL_LSB, device); //set the column LSB
	
	SetPin(device->A0, 	device->A0_row, DISPLAY_DATA); //set the display into data mode
	writeLCDSPI(fullBar, device);//write the begining of the graph
	
	for(i = 0; i < MAX_COL-2; i++) //omit the begining and ends of the graph due to setting up the bar structure
	{
		if(i < (((float)(percent))/100)*(MAX_COL-2)){ //if the column is supposed to be filled
			writeLCDSPI(fullBar, device); //write a full line
		}else
		{
			writeLCDSPI(emptyBar, device); //write just the tops and bottoms of the bar graph
		}
	}
	writeLCDSPI(fullBar, device); //write the end of the bar graph
	SetPin(device->ss, 	device->ss_row, DISPLAY_NOTSELECT );//toggle the cip select to the desired values
}

/**
@author Reid Kersey <reidkersey@gmail.com> 678-736-0899

@brief This function writes text to the page and column specified

@details This function takes in a page number (0-7),
a column (0-127), and text to be written.

@todo remove "Magic numbers" that represent the commands
@todo check if the string will fit on the screen.

@note Each line can have a maximum of 2l characters. Each character is 6 cols wide.

@param device The pin structure that tells the function what pins to set high and low
@param page The page (0-7) that the text is going to be written to
@param column The column (0-127) that the text is going to start being written to
@param text The character array of text that is to be written
*/
void writeString(struct LCD_screen *device, int page, int column, char text[])
{
	int i;
	int j;
	int index;
	char c;
	
	SetPin(device->ss, 	device->ss_row, DISPLAY_SELECT);//toggle the cip selects to the desired values
	
	SetPin(device->A0, 	device->A0_row, DISPLAY_CMD); //set the display to cmd mode
	writeLCDSPI(0xB0+page, device); //set the page
	writeLCDSPI(0x10+(column>>4), device); //set the column MSB
	writeLCDSPI(0x00+(column&15), device); //set the column LSB
	
	SetPin(device->A0, 	device->A0_row, DISPLAY_DATA); //set the display to data mode
	
	for(i = 0; i < strlen(text); i++) {
		c = toupper(text[i]);

		if(isdigit(c)) {
			index = 5 * (c - '0');//set the starting point to the right spot in the array each character is 5 columns wide
			for(j = 0; j < 5; j++){//write out the 5 columns for the character
				writeLCDSPI(num[index + j], device);//send the line
			}
		}else if(isalpha(c)) {
			index = 5 * (c - 'A');//set the starting point to the right spot in the array each character is 5 columns wide
			for(j = 0; j < 5; j++){//write out the 5 columns for the character
				writeLCDSPI(alpha[index + j], device);//send the line
			}
		}else if(c == ':') {
			for(j = 0; j < 5; j++){//write out the 5 columns for the character
				writeLCDSPI(colon[j], device);//write a colon
			}
		}else if(c == ' ') {
			for(j = 0; j < 4; j++){//write out the 5 columns for the character
				writeLCDSPI(emptyLine, device);
			}
		}

		writeLCDSPI(emptyLine, device);//make the characters spaced out
	}
	SetPin(device->ss, 	device->ss_row, DISPLAY_NOTSELECT );//toggle the cip select to the desired values
}

/**
@author Reid Kersey <reidkersey@gmail.com> 678-736-0899

@brief This function initializes the spedometer page.

@details This function takes in two constants indicating
the chip select value. It will then intialize the spedometer page.
It sets up the bar graphs, text, numbers, and units.

@todo make the function not run if both screens are not selected

@param device The pin structure that tells the function what pins to set high and low

@warning This function must be called before displaying speedometer data
*/
void InitSpeed(struct LCD_screen *device)
{	
	updateSpeed(device, INIT_SPEED); //display the speedometer
	updateBat(device, INIT_BAT); //display the battery text
	writeString(device, SPEED_UNIT_PAGE, SPEED_UNIT_COLUMN, UNIT); //display the unit of speed
        updateCruise(device, INIT_CRUISE); //initialize the cruise display
}

/**
@author Reid Kersey <reidkersey@gmail.com> 678-736-0899

@brief This updates the blinker bitmap on the screen.

@param device The pin structure that tells the function what pins to set high and low
*/
void updateBlinker(struct LCD_screen *device)
{
	int i;
	SetPin(device->ss, 	device->ss_row, DISPLAY_SELECT );//toggle the cip select to the desired values
	switch(getBlinker()){
		case BLINKER_OFF:
			clearArea(device, BLINKER_PAGE, BLINKER_PAGE, BLINKER_LEFT_START, BLINKER_RIGHT_START + BLINKER_COLS);
			break;
		case BLINKER_LEFT:
			SetPin(device->A0, 	device->A0_row, DISPLAY_CMD); //set the displays into command mode
			writeLCDSPI(FIRST_PAGE+BLINKER_PAGE, device); //set the page
			writeLCDSPI(FIRST_COL_MSB+(BLINKER_LEFT_START>>4), device); //set the column MSB
			writeLCDSPI(FIRST_COL_LSB+(BLINKER_LEFT_START&0xf), device); //set the column LSB
			SetPin(device->A0, 	device->A0_row, DISPLAY_DATA); //set the display into data mode
			for(i = 0; i < BLINKER_COLS; i++) //omit the begining and ends of the graph due to setting up the bar structure
			{
				writeLCDSPI(leftArrow[i], device);
			}
			break;
		case BLINKER_RIGHT:
			SetPin(device->A0, 	device->A0_row, DISPLAY_CMD); //set the displays into command mode
			writeLCDSPI(FIRST_PAGE+BLINKER_PAGE, device); //set the page
			writeLCDSPI(FIRST_COL_MSB+(BLINKER_RIGHT_START>>4), device); //set the column MSB
			writeLCDSPI(FIRST_COL_LSB+(BLINKER_RIGHT_START&0xf), device); //set the column LSB
			SetPin(device->A0, 	device->A0_row, DISPLAY_DATA); //set the display into data mode
			for(i = 0; i < BLINKER_COLS; i++) //omit the begining and ends of the graph due to setting up the bar structure
			{
				writeLCDSPI(rightArrow[i], device);
			}
			break;
		case BLINKER_HAZARD:
			SetPin(device->A0, 	device->A0_row, DISPLAY_CMD); //set the displays into command mode
			writeLCDSPI(FIRST_PAGE+BLINKER_PAGE, device); //set the page
			writeLCDSPI(FIRST_COL_MSB+(BLINKER_LEFT_START>>4), device); //set the column MSB
			writeLCDSPI(FIRST_COL_LSB+(BLINKER_LEFT_START&0xf), device); //set the column LSB
			SetPin(device->A0, 	device->A0_row, DISPLAY_DATA); //set the display into data mode
			for(i = 0; i < BLINKER_RIGHT_START + BLINKER_COLS; i++) //omit the begining and ends of the graph due to setting up the bar structure
			{
				if(i < BLINKER_COLS){
					writeLCDSPI(leftArrow[i], device);
				}else if(i >= BLINKER_RIGHT_START){
					writeLCDSPI(rightArrow[i-BLINKER_RIGHT_START], device);
				}else{
					writeLCDSPI(emptyLine, device);
				}
			}
			break;
	}
	SetPin(device->ss, 	device->ss_row, DISPLAY_NOTSELECT );//toggle the chip select to the desired values
}

/**
@author Reid Kersey <reidkersey@gmail.com> 678-736-0899
 
 * @todo GPS v. RPM

@brief This function checks if any of the "global" variables have changes, and then calls their respective functions

@param device The pin structure that tells the function what pins to set high and low
*/
void updateSpeedometer(struct LCD_screen *device)
{
	int speed = (int)(getSpeed() + .5);
	int bat = getBattery();
	int cruise = getCruise();
	int blinker = getBlinker();
	int speedType = getUseGPSSpeed();
	
	if(speed != device->speed || device->clear || device->pageSwitch)
	{
		updateSpeed(device, speed);
		device->speed = speed;
	}
	if(bat != device->battery || device->clear || device->pageSwitch)
	{
		updateBat(device, bat);
		device->battery = bat;
	}
	if(cruise != device->cruise || device->clear || device->pageSwitch)
	{
		updateCruise(device, cruise || device->clear || device->pageSwitch);
		device->cruise = cruise;
	}
	if(blinker != device->blinker || device->clear || device->pageSwitch)
	{ 
		updateBlinker(device);
		device->blinker = blinker;
	}
	if(speedType != device->speedType || device->clear || device->pageSwitch){
		writeSpeedType(device);
		device->speedType = speedType;
	}
	if(device->clear || device->pageSwitch){
		writeString(device, SPEED_UNIT_PAGE, SPEED_UNIT_COLUMN, UNIT); //display the unit of speed
	}
	device->clear = 0;
	device->pageSwitch = 0;
}

/**
* @}
*/
