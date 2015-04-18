#include "wrapper.h"
#ifndef LCD_H
#define LCD_H
#include "DIO.h"
//display commands
#define DISPLAY_SELECT	 	(0) //select the display using cs
#define DISPLAY_NOTSELECT	(1) //deselect the display using cs
#define DISPLAY_DATA		(1) //set A0 so that the displays will recieve data
#define DISPLAY_CMD			(0) //set A0 so that the displays will receive commands
#define LCD_COLS			(128)
#define LCD_PAGES			(8)
#define FIRST_PAGE			(0xb0)
#define FIRST_COL_MSB		(0x10)
#define FIRST_COL_LSB		(0x00)
#define MAX_PAGE			(7)
#define MIN_PAGE			(0)
#define MAX_COL				(128)
#define MIN_COL				(0)
#define LCD_RESET			(0xe0)

//Button Directions
#define BUTTON_LEFT			(0)
#define BUTTON_CENTER		(1)
#define BUTTON_RIGHT		(2)

//Blinker Directions
#define BLINKER_OFF			(0)
#define BLINKER_LEFT		(1)
#define BLINKER_RIGHT		(2)
#define BLINKER_HAZARD		(3)

//Error Screen pages
#define ERRORS_PAGE	(0)
#define MAIN_PAGE		(1)
#define VOLTAGES_PAGE	(2)
#define CURRENTS_PAGE	(3)
#define TEMPS_PAGE	(4)
#define SPEED_PAGE	(5)

//PLACEMENT DEFINITIONS
#define BLINKER_LEFT_START			(0)
#define BLINKER_RIGHT_START			(116)
#define BLINKER_COLS				(12)
#define BLINKER_PAGE				(0)
#define SPEED_CRUISE_PAGE			(6)
#define SPEED_BARGRAPH_PAGE 		(7)
#define SPEED_UNIT_PAGE 			(1)
#define SPEED_UNIT_COLUMN			(75)
#define SPEED_BAT_COLUMN 			(0)
#define SPEED_CRUISE_COLUMN 		(40)
#define MAX_CHARS_PER_LINE			(21)
#define ERROR_START_COL				(0)
#define ERROR_HEADER_PAGE			(0)
#define MAX_CRUISE_COLS				(66)
#define COLS_PER_CHAR				(6)
#define MAX_CRUISE_LENGTH			(12)
#define MIN_COL						(0)
#define MAX_BAT_COLS				(48)
#define MAX_BAT_LENGTH				(9)
#define SPEED_DIGIT_START_PAGE		(2)
#define SPEED_DIGIT_START_COL_MSB	(1)
#define SPEED_DIGIT_START_COL_LSB	(0x0d)
#define SPEED_DIGIT_TOTAL_COLS		(45)
#define SPEED_DIGIT_COLS_PER_ROW	(15)
#define SPEED_DIGIT_MAX_PAGES		(3)
#define ERROR_PER_PAGE				(7)
#define SPEED_TYPE_COLS				(23)
#define SPEED_TYPE_COL				(105)
#define SPEED_TYPE_TOP_PAGE			(1)
#define SPEED_TYPE_GPS_PAGE			(SPEED_TYPE_TOP_PAGE+1)
#define SPEED_TYPE_RPM_PAGE			(SPEED_TYPE_TOP_PAGE+2)
#define SPEED_TYPE_TXT_PAD			(2)

//initializations
#define LCDSPI_CLK_INIT		(1)
#define LCDSPI_MOSI_INIT	(0)
#define RPM_TYPE			(0)
#define GPS_TYPE			(1)

//SETTINGS
#define UNIT 				("MPH")
#define INIT_BAT 			(75)
#define INIT_CRUISE			(80)
#define INIT_SPEED			(0)
#define DEFAULT_CLK			(1)

static const char LCD_General_Text[ERROR_PER_PAGE][MAX_CHARS_PER_LINE] = {"Date: ", "Time: ", "Direction: ", "RPM: ", "Battery: ", "Regen: ", "Airgap: "};
static const char LCD_Voltage_Text[ERROR_PER_PAGE][MAX_CHARS_PER_LINE] = {"Voltage 1: ", "Voltage 2: ", "Voltage 3: ", "Voltage 4: ", "Voltage 5: ", "Voltage 6: ", "Voltage 7: "};
static const char LCD_Current_Text[ERROR_PER_PAGE][MAX_CHARS_PER_LINE] = {"Current 1: ", "Current 2: ", "Current 3: ", "Current 4: ", "Current 5: ", "Current 6: ", "Current 7: "};
static const char LCD_Temp_Text[ERROR_PER_PAGE][MAX_CHARS_PER_LINE] = {"Temp 1: ", "Temp 2: ", "Temp 3: ", "Temp 4: ", "Temp 5: ", "Temp 6: ", "Temp 7: "};



struct LCD_screen{  
	int ss;
	int ss_row;
	int clk;
	int clk_row;
	int mosi;
	int mosi_row;
	int A0;
	int A0_row;
	int speed;
	int cruise;
	int blinker;
	int battery;
	int page;
	int errorPage;
	int pageSwitch;
	int clear;
	int reset;
	int speedType;
	char errors[NUM_DEF_ERRORS][LCD_CHAR_PER_LINE_NULL];
	char general[ERROR_PER_PAGE][LCD_CHAR_PER_LINE_NULL];
	char voltages[ERROR_PER_PAGE][LCD_CHAR_PER_LINE_NULL];
	char currents[ERROR_PER_PAGE][LCD_CHAR_PER_LINE_NULL];
	char temps[ERROR_PER_PAGE][LCD_CHAR_PER_LINE_NULL];
};

//initialize the LCDs
void InitLCD();
// clear the display
void clearDisplay(struct LCD_screen *device);
void LCDButtonPush(struct LCD_screen *device);
// update the speed
void updateSpeed(struct LCD_screen *device, int speed);
//initialize the speedometer screen
void InitSpeed(struct LCD_screen *device);
//write a string
void writeString(struct LCD_screen *device, int page, int column, char text[]);
//create a bar graph
void createGraph(struct LCD_screen *device, int page, int percent);
//update the battery graph
void updateBat(struct LCD_screen *device, int bat);
//update the cruise graph
void updateCruise(struct LCD_screen *device, int cruise);
//clear a portion of the screen
void clearArea(struct LCD_screen *device, int pageStart, int pageEnd, int colStart, int colEnd);
//initialize the SPI function
void writeLCDSPI_bit(int data, struct LCD_screen *device);
void writeLCDSPI(unsigned char data, struct LCD_screen *device);
void SPIclockCycle(struct LCD_screen *device);
void updateBlinker(struct LCD_screen *device);
void updateLCD(struct LCD_screen *device);
void updateSpeedometer(struct LCD_screen *device);
void displayReset(struct LCD_screen *device);
void writeInvertString(struct LCD_screen *device, int page, int column, char text[]);
void writeSpeedType(struct LCD_screen *device);
void writeUnderlineString(struct LCD_screen *device, int page, int column, char text[]);
#endif
