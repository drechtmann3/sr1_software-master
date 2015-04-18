// #include "LCD.h"
// #include "LCD.h"
// #include "DIO.h" 
// #include "bitmap.h" 
// #include <stdio.h>
// #include <string.h>
// #include <ctype.h>
// #include "pins.h"
// #include "lights.h"
// #include <stdbool.h>
// #include "motor.h"
// #include "datastore.h"


// /**
// @author Reid Kersey <reidkersey@gmail.com> 678-736-0899

// @brief The function initializes the DOGM128 LCD Screens

// @details The function intializes the DOGM128 LCD Screens
// by initializing the pins (set in lcd.h), and then writing
// commands to the lcd spi bus.

// @warning This function must be called before using any function that attempts to update the LCD screens

// @todo remove "Magic numbers" that represent the commands

// @param device The pin structure that tells the function what pins to set high and low
// */

// void InitLCD()
// {//initialize the display with the correct commands

	// //set the pins io direction
	// InitDIO_direction(CS1, CS1_ROW, GPIO_OUTPUT ); //device->ss corresponds to CS1
    // InitDIO_direction(SCL, SCL_ROW, GPIO_OUTPUT );
    // InitDIO_direction(A0, A0_ROW, GPIO_OUTPUT );
    // InitDIO_direction(SI, SI_ROW, GPIO_OUTPUT );
	// InitDIO_direction(CS2, CS2_ROW, GPIO_OUTPUT);
	// InitDIO_direction(RESET1, RESET1_ROW, GPIO_OUTPUT);
	// InitDIO_direction(RESET2, RESET2_ROW, GPIO_OUTPUT);
	
	
	// //toggle chip selects
	// SetPin(CS1, CS1_ROW, DISPLAY_SELECT);
	// SetPin(CS1, CS1_ROW, DISPLAY_NOTSELECT);
	// SetPin(CS2, CS2_ROW, DISPLAY_SELECT);
	// SetPin(CS2, CS2_ROW, DISPLAY_NOTSELECT);
	// //Set the pins to initialize to the correct value
    // SetPin(CS1, CS1_ROW, DISPLAY_SELECT); //select displays
	// SetPin(CS2, CS2_ROW, DISPLAY_SELECT); //select displays
    // SetPin(A0, A0_ROW, DISPLAY_CMD );//set A0 to be a command
	// SetPin(RESET1, RESET1_ROW, RESET_INIT);
	// SetPin(RESET2, RESET2_ROW, RESET_INIT);
	
	// //Init display
    // writeLCDSPI(0x40);//set the start line to 0
    // writeLCDSPI(0xA1);//adc reverse
    // writeLCDSPI(0xC0);//normal com0~com63
    // writeLCDSPI(0xA6);//display normal
    // writeLCDSPI(0xA2);//set bias 1/9(duty 1/65)
    // writeLCDSPI(0x2F);//booster regulator and follow on
    // writeLCDSPI(0xF8);//set internal booster to 4x
    // writeLCDSPI(0x00);//see above
    // writeLCDSPI(0x27);//contrast set
    // writeLCDSPI(0x81);//see above
    // writeLCDSPI(0x16);//see above
    // writeLCDSPI(0xAC);//no static indicator
    // writeLCDSPI(0x00);//see above
    // writeLCDSPI(0xAF);//display on
    // writeLCDSPI(0xB0);//set the ram page address to 0
    // writeLCDSPI(0x10);//set the column to 0
    // writeLCDSPI(0x00);//see above
    // clearDisplay(LCD1); //clear the displays to clear any residual memory
	// clearDisplay(LCD2); //clear the displays to clear any residual memory
	
	// //deselect displays
	// SetPin(CS1, CS1_ROW, DISPLAY_NOTSELECT);
	// SetPin(CS2, CS2_ROW, DISPLAY_NOTSELECT);
// }

// /**
// @author Reid Kersey <reidkersey@gmail.com> 678-736-0899

// @brief This function writes one byte(1 char value) to the SPI line of the device specified.

// @details This function writes one byte to the SPI line of the device specified.
// This function \b should \b not be used to cycle the clock line, or to
// write null bits. The general purpose of this function is to write commands
// to an SPI bus.

// @param device The pin structure that tells the function what pins to set high and low
// @param data The character value that represents the 8 bits of data to be sent.
// */

// void writeLCDSPI(unsigned char data){
	// int i; //set up the ideration
	// for(i=0; i < 8; i++) { //write to the spi line 8 times (one byte)
		// if ((data << i )& 0x80) {//if the current bit is a one
			// writeLCDSPI_bit(1);
		// }else { //if the current bit is a 0
			// writeLCDSPI_bit(0);
		// }
	// }
	// SetPin(SCL, SCL_ROW, LCDSPI_CLK_INIT); //set the clock high (this is the idle state)
	// SetPin(SI, SI_ROW, LCDSPI_MOSI_INIT); //set the data low (this is the idle state)
// }

// /**
// @author Reid Kersey <reidkersey@gmail.com> 678-736-0899

// @brief This function writes one bit to the SPI line of the device specified.

// @details This function writes one bit to the SPI line of the device specified.
// It can be used to cycle the clock line, or to write null bits. Any data that
// is not a 1 is treated as a 0.

// @warning This function does not put the data lines back to the original
// state. That is up to the calling function.

// @param data The integer value of the bit to be sent. Either one or zero.
// @param device The pin structure that tells the function what pins to set high and low
// */

// void writeLCDSPI_bit(int data){
	// if(data == 1){
		// SetPin(SI, SI_ROW, PIN_HIGH); //set the data line high
		// SPIclockCycle();
	// }else{
		// SetPin(SI, SI_ROW, PIN_LOW); //set the data line high
		// SPIclockCycle();
	// }
// }

// /**
// @author Reid Kersey <reidkersey@gmail.com> 678-736-0899

// @brief This function will cycle the clock cycle

// @details This function relies on the definition of DEFAULT_CLK in lcd.h.

// @details This function cycles the clock line

// @warning This function assumes that the clock line is in the default state already.

// @param device The pin structure that tells the function what pins to set high and low
// */
// void SPIclockCycle(){
	// SetPin(SCL, SCL_ROW, !DEFAULT_CLK);
	// SetPin(SCL, SCL_ROW, DEFAULT_CLK);
// }

// void writeUnderlineString(int device, int page, int column, char text[])
// {
	// int i;
	// int j;
	// int index;
	// char c;
	
	// if(device == LCD1){
		// SetPin(CS1, CS1_ROW, DISPLAY_SELECT );//toggle the cip select to the desired values
	// }else{
		// SetPin(CS2, CS2_ROW, DISPLAY_SELECT );//toggle the cip select to the desired values
	// }
	
	// SetPin(A0, A0_ROW, DISPLAY_CMD); //set the display to cmd mode
	// writeLCDSPI(FIRST_PAGE+page); //set the page
	// writeLCDSPI(FIRST_COL_MSB+(column>>4)); //set the column MSB
	// writeLCDSPI(FIRST_COL_LSB+(column&15)); //set the column LSB
	
	// SetPin(A0, A0_ROW, DISPLAY_DATA); //set the display to data mode
	
	// for(i = 0; i < strlen(text); i++) {
		// c = toupper(text[i]);

		// if(isdigit(c)) {
			// index = 5 * (c - '0');//set the starting point to the right spot in the array each character is 5 columns wide
			// for(j = 0; j < 5; j++){//write out the 5 columns for the character
				// writeLCDSPI(num[index + j]|underline);//send the line
			// }
		// }else if(isalpha(c)) {
			// index = 5 * (c - 'A');//set the starting point to the right spot in the array each character is 5 columns wide
			// for(j = 0; j < 5; j++){//write out the 5 columns for the character
				// writeLCDSPI(alpha[index + j]|underline);//send the line
			// }
		// }else if(c == ':') {
			// for(j = 0; j < 5; j++){//write out the 5 columns for the character
				// writeLCDSPI(colon[j]|underline);//write a colon
			// }
		// }else if(c == ' ') {
			// for(j = 0; j < 4; j++){//write out the 5 columns for the character
				// writeLCDSPI(emptyLine|underline);
			// }
		// }
		
		// writeLCDSPI(emptyLine|underline);//make the characters spaced out
	// }
	
	// if(device == LCD1){
		// SetPin(CS1, CS1_ROW, DISPLAY_NOTSELECT );//toggle the cip select to the desired values
	// }else{
		// SetPin(CS2, CS2_ROW, DISPLAY_NOTSELECT );//toggle the cip select to the desired values
	// }
// }

// void writeInvertString(int device, int page, int column, char text[])
// {
	// int i;
	// int j;
	// int index;
	// char c;
	
	// if(device == LCD1){
		// SetPin(CS1, CS1_ROW, DISPLAY_SELECT );//toggle the cip select to the desired values
	// }else{
		// SetPin(CS2, CS2_ROW, DISPLAY_SELECT );//toggle the cip select to the desired values
	// }
	
	// SetPin(A0, A0_ROW, DISPLAY_CMD); //set the display to cmd mode
	// writeLCDSPI(FIRST_PAGE+page); //set the page
	// writeLCDSPI(FIRST_COL_MSB+(column>>4)); //set the column MSB
	// writeLCDSPI(FIRST_COL_LSB+(column&15)); //set the column LSB
	
	// SetPin(A0, A0_ROW, DISPLAY_DATA); //set the display to data mode
	
	// for(i = 0; i < strlen(text); i++) {
		// c = toupper(text[i]);

		// if(isdigit(c)) {
			// index = 5 * (c - '0');//set the starting point to the right spot in the array each character is 5 columns wide
			// for(j = 0; j < 5; j++){//write out the 5 columns for the character
				// writeLCDSPI(~num[index + j]);//send the line
			// }
		// }else if(isalpha(c)) {
			// index = 5 * (c - 'A');//set the starting point to the right spot in the array each character is 5 columns wide
			// for(j = 0; j < 5; j++){//write out the 5 columns for the character
				// writeLCDSPI(~alpha[index + j]);//send the line
			// }
		// }else if(c == ':') {
			// for(j = 0; j < 5; j++){//write out the 5 columns for the character
				// writeLCDSPI(~colon[j]);//write a colon
			// }
		// }else if(c == ' ') {
			// for(j = 0; j < 4; j++){//write out the 5 columns for the character
				// writeLCDSPI(~emptyLine);
			// }
		// }

		// writeLCDSPI(~emptyLine);//make the characters spaced out
	// }
	
	// if(device == LCD1){
		// SetPin(CS1, CS1_ROW, DISPLAY_NOTSELECT );//toggle the cip select to the desired values
	// }else{
		// SetPin(CS2, CS2_ROW, DISPLAY_NOTSELECT );//toggle the cip select to the desired values
	// }
	
// }

// /**
// @author Reid Kersey <reidkersey@gmail.com> 678-736-0899

// @brief This function will reset and reinitialize the screens

// @details This function issues the reset command and then calls the
// LCD initialization function function

// @param device The pin structure that tells the function what pins to set high and low and
// hold different variables.
// */
// void displayReset(int device){
	// if(device == LCD1){
		// SetPin(CS1, CS1_ROW, DISPLAY_SELECT );//toggle the cip select to the desired values
	// }else{
		// SetPin(CS2, CS2_ROW, DISPLAY_SELECT );//toggle the cip select to the desired values
	// }	
	
	// SetPin(A0, A0_ROW, DISPLAY_CMD);
	// writeLCDSPI(LCD_RESET);//DO A SOFT RESET
	// InitLCD();
	
	// if(device == LCD1){
		// SetPin(CS1, CS1_ROW, DISPLAY_NOTSELECT );//toggle the cip select to the desired values
	// }else{
		// SetPin(CS2, CS2_ROW, DISPLAY_NOTSELECT );//toggle the cip select to the desired values
	// }
// }


// /**
// @author Reid Kersey <reidkersey@gmail.com> 678-736-0899

// @brief This function clears the display

// @details This function will go page by page to the display
// and write zeros

// @todo get rid of magic numbers

// @param device The pin structure that tells the function what pins to set high and low
// */
// void clearDisplay(int device)
// {
	// int page=0;//the "page" (row multiplier)
	// int column=0;//the column 
	
	// if(device == LCD1){
		// SetPin(CS1, CS1_ROW, DISPLAY_SELECT );//toggle the cip select to the desired values
	// }else{
		// SetPin(CS2, CS2_ROW, DISPLAY_SELECT );//toggle the cip select to the desired values
	// }
	
	// for (page=0; page<LCD_PAGES; page++)//do the following for each page
	// {
		// SetPin(A0, A0_ROW, DISPLAY_CMD);
		// writeLCDSPI(FIRST_PAGE+page);//select the page
		// writeLCDSPI(FIRST_COL_MSB);//select the first column MSB
		// writeLCDSPI(FIRST_COL_LSB);//select the first column LSB
		// SetPin(A0, A0_ROW, DISPLAY_DATA);//set to data mode
		// for (column=0; column<LCD_COLS; column++)//do the following for each column
		// {
			// writeLCDSPI(0x00);//write 0's
		// }
	// }
	
	// if(device == LCD1){
		// SetPin(CS1, CS1_ROW, DISPLAY_NOTSELECT );//toggle the cip select to the desired values
	// }else{
		// SetPin(CS2, CS2_ROW, DISPLAY_NOTSELECT );//toggle the cip select to the desired values
	// }

// }

// /**
// @author Reid Kersey <reidkersey@gmail.com> 678-736-0899

// @brief This function updates the speed text on the speedometer page

// @details This function will clear the area on the screen
// that corasponds to the position of the speed text, and re-write
// the speed text with the given value

// @param device The pin structure that tells the function what pins to set high and low
// @param speed This is the current speed that the car is going
// */
// void updateSpeed(int device, int speed)
// {
	// int speed_digit0 = speed / 100; //get the leading digit (100's)
	// int speed_digit1 = (speed / 10)-(10*speed_digit0); //get the first digit (10's)
	// int speed_digit2 = speed % 10; //get the second digit (1's)
	
	// int page=0;//the "page"(row multiplier) for the data k
	// int column=0;//the column for the data l
	// int index; //the index for the bitmap array
	
	// //select LCD
	// if(device == LCD1){
		// SetPin(CS1, CS1_ROW, DISPLAY_SELECT );//toggle the cip select to the desired values
	// }else{
		// SetPin(CS2, CS2_ROW, DISPLAY_SELECT );//toggle the cip select to the desired values
	// }
	
	// for (page=0; page<SPEED_DIGIT_MAX_PAGES; page++)//Go page by page
	// {
		// SetPin(A0, 	A0_ROW, DISPLAY_CMD); //set the display to cmd mode
		// writeLCDSPI(FIRST_PAGE+SPEED_DIGIT_START_PAGE+page); //set the page
		// writeLCDSPI(FIRST_COL_MSB+SPEED_DIGIT_START_COL_MSB); //set the column MSB
		// writeLCDSPI(FIRST_COL_LSB+SPEED_DIGIT_START_COL_LSB); //set the column LSB
		
		// index = speed_digit0*SPEED_DIGIT_TOTAL_COLS + page*SPEED_DIGIT_COLS_PER_ROW; //find the starting index in the array
		
		// SetPin(A0, A0_ROW, DISPLAY_DATA);//set the displays to data mode
		// if(speed_digit0){
			// for (column=0; column<SPEED_DIGIT_COLS_PER_ROW; column++){
				// writeLCDSPI(speedNum[index+column]);
			// }
		// }else{
			// for (column=0; column<SPEED_DIGIT_COLS_PER_ROW; column++){
				// writeLCDSPI(emptyLine);
			// }
		// }
		
		// index = speed_digit1*SPEED_DIGIT_TOTAL_COLS + page*SPEED_DIGIT_COLS_PER_ROW;
		
		// for (column=0; column<SPEED_DIGIT_COLS_PER_ROW; column++)
		// { //write out the numbers column by column
			// writeLCDSPI(speedNum[index+column]); //send the data in the array
		// }

		// index = speed_digit2*SPEED_DIGIT_TOTAL_COLS + page*SPEED_DIGIT_COLS_PER_ROW; //find the starting index in the array
		
		// for (column=0; column<SPEED_DIGIT_COLS_PER_ROW; column++)
		// {//write out the numbers column by column
			// writeLCDSPI(speedNum[index+column]);//send the data in the array
		// }
	// }	
	
	// //select LCD
	// if(device == LCD1){
		// SetPin(CS1, CS1_ROW, DISPLAY_NOTSELECT );//toggle the cip select to the desired values
	// }else{
		// SetPin(CS2, CS2_ROW, DISPLAY_NOTSELECT );//toggle the cip select to the desired values
	// }
// }

// /**
// @author Reid Kersey <reidkersey@gmail.com> 678-736-0899

// @brief This function clears an area on the screen

// @details This function takes takes in the pages (rows 
// in multiples of 8) start and end values, and the columns
// start and end values. It then procedes to write all zero's
// to the selected area on the given device.

// @param device The pin structure that tells the function what pins to set high and low
// @param pageStart The page (0-7) that the top of the rectange to be cleared is located
// @param pageEnd The page (0-7) that the bottom of the rectange to be cleared is located
// @param colStart The column (0-127) that the left hand side of the rectangle to be cleared is located
// @param colEnd The column (0-127) that the right hand side of the rectangle to be cleared is located
// */
// void clearArea(int device, int pageStart, int pageEnd, int colStart, int colEnd){
	// int i,j;

	// if(pageStart < MIN_PAGE || pageEnd > MAX_PAGE || colStart < MIN_COL || colEnd > MAX_COL){
		// return;
	// }
	
	// //select LCD
	// if(device == LCD1){
		// SetPin(CS1, CS1_ROW, DISPLAY_SELECT );//toggle the cip select to the desired values
	// }else{
		// SetPin(CS2, CS2_ROW, DISPLAY_SELECT );//toggle the cip select to the desired values
	// }
	
	// for(i = 0; i <= (pageEnd - pageStart); i++)
	// {
		// SetPin(A0, A0_ROW, DISPLAY_CMD);
		// writeLCDSPI(FIRST_PAGE+pageStart+i); //set the page
		// writeLCDSPI(FIRST_COL_MSB+(colStart>>4)); //set the column MSB
		// writeLCDSPI(FIRST_COL_LSB+(colStart&0xf)); //set the column LSB
		// SetPin(A0, A0_ROW, DISPLAY_DATA);
		// for(j = 0; j <= (colEnd-colStart); j++)
		// {
			// writeLCDSPI(emptyLine); //write a zero
		// }
	// }	
	
	// //select LCD
	// if(device == LCD1){
		// SetPin(CS1, CS1_ROW, DISPLAY_NOTSELECT );//toggle the cip select to the desired values
	// }else{
		// SetPin(CS2, CS2_ROW, DISPLAY_NOTSELECT );//toggle the cip select to the desired values
	// }
// }

// /**
// @author Reid Kersey <reidkersey@gmail.com> 678-736-0899

// @brief This function creates a horizontal bar graph

// @details This function takes in a page number (0-7)
// and a percentage to fill the bar. It will create a full page
// horizontal bar graph, filled to the percentage given.

// @todo remove "Magic numbers" that represent the commands

// @param device The pin structure that tells the function what pins to set high and low
// @param percent The percentage (0-100) that the bar is supposed to be filled
// @param page The page that the graph is supposed to be displayed on (0-7)
// */
// void createGraph(int device, int page, int percent)
// {
	// int i;
	
	// //select LCD
	// if(device == LCD1){
		// SetPin(CS1, CS1_ROW, DISPLAY_SELECT );//toggle the cip select to the desired values
	// }else{
		// SetPin(CS2, CS2_ROW, DISPLAY_SELECT );//toggle the cip select to the desired values
	// }
	
	// SetPin(A0, A0_ROW, DISPLAY_CMD); //set the displays into command mode
	// writeLCDSPI(FIRST_PAGE+page); //set the page
	// writeLCDSPI(FIRST_COL_MSB); //set the column MSB
	// writeLCDSPI(FIRST_COL_LSB); //set the column LSB
	
	// SetPin(A0, A0_ROW, DISPLAY_DATA); //set the display into data mode
	// writeLCDSPI(fullBar);//write the begining of the graph
	// for(i = 0; i < MAX_COL-2; i++) //omit the begining and ends of the graph due to setting up the bar structure
	// {
		// if(i < (((float)(percent))/100)*(MAX_COL-2)){ //if the column is supposed to be filled
			// writeLCDSPI(fullBar); //write a full line
		// }else
		// {
			// writeLCDSPI(emptyBar); //write just the tops and bottoms of the bar graph
		// }
	// }
	// writeLCDSPI(fullBar); //write the end of the bar graph
	
	// //deselect LCD
	// if(device == LCD1){
		// SetPin(CS1, CS1_ROW, DISPLAY_NOTSELECT );//toggle the cip select to the desired values
	// }else{
		// SetPin(CS2, CS2_ROW, DISPLAY_NOTSELECT );//toggle the cip select to the desired values
	// }
// }


// /**
// @author Reid Kersey <reidkersey@gmail.com> 678-736-0899

// @brief This function writes text to the page and column specified

// @details This function takes in a page number (0-7),
// a column (0-127), and text to be written.

// @todo remove "Magic numbers" that represent the commands
// @todo check if the string will fit on the screen.

// @note Each line can have a maximum of 2l characters. Each character is 6 cols wide.

// @param device The pin structure that tells the function what pins to set high and low
// @param page The page (0-7) that the text is going to be written to
// @param column The column (0-127) that the text is going to start being written to
// @param text The character array of text that is to be written
// */
// void writeString(int device, int page, int column, char text[])
// {
	// int i;
	// int j;
	// int index;
	// char c;
	
	// //select LCD
	// if(device == LCD1){
		// SetPin(CS1, CS1_ROW, DISPLAY_SELECT );//toggle the cip select to the desired values
	// }else{
		// SetPin(CS2, CS2_ROW, DISPLAY_SELECT );//toggle the cip select to the desired values
	// }
	
	// SetPin(A0, A0_ROW, DISPLAY_CMD); //set the display to cmd mode
	// writeLCDSPI(FIRST_PAGE+page); //set the page
	// writeLCDSPI(FIRST_COL_MSB+(column>>4)); //set the column MSB
	// writeLCDSPI(FIRST_COL_LSB+(column&15)); //set the column LSB
	
	// SetPin(A0, A0_ROW, DISPLAY_DATA); //set the display to data mode
	
	// for(i = 0; i < strlen(text); i++) {
		// c = toupper(text[i]);

		// if(isdigit(c)) {
			// index = 5 * (c - '0');//set the starting point to the right spot in the array each character is 5 columns wide
			// for(j = 0; j < 5; j++){//write out the 5 columns for the character
				// writeLCDSPI(num[index + j]);//send the line
			// }
		// }else if(isalpha(c)) {
			// index = 5 * (c - 'A');//set the starting point to the right spot in the array each character is 5 columns wide
			// for(j = 0; j < 5; j++){//write out the 5 columns for the character
				// writeLCDSPI(alpha[index + j]);//send the line
			// }
		// }else if(c == ':') {
			// for(j = 0; j < 5; j++){//write out the 5 columns for the character
				// writeLCDSPI(colon[j]);//write a colon
			// }
		// }else if(c == ' ') {
			// for(j = 0; j < 4; j++){//write out the 5 columns for the character
				// writeLCDSPI(emptyLine);
			// }
		// }

		// writeLCDSPI(emptyLine);//make the characters spaced out
	// }	
	
	// //select LCD
	// if(device == LCD1){
		// SetPin(CS1, CS1_ROW, DISPLAY_NOTSELECT );//toggle the cip select to the desired values
	// }else{
		// SetPin(CS2, CS2_ROW, DISPLAY_NOTSELECT );//toggle the cip select to the desired values
	// }
// }

// /**
// @author Reid Kersey <reidkersey@gmail.com> 678-736-0899

// @brief This updates the blinker bitmap on the screen.

// @param device The pin structure that tells the function what pins to set high and low
// */
// void updateBlinker(int device)
// {
	// int i;
	// //select LCD
	// if(device == LCD1){
		// SetPin(CS1, CS1_ROW, DISPLAY_SELECT );//toggle the cip select to the desired values
	// }else{
		// SetPin(CS2, CS2_ROW, DISPLAY_SELECT );//toggle the cip select to the desired values
	// }

	// switch(getInt("blinker")){
		// case BLINKER_OFF:
			// clearArea(device, BLINKER_PAGE, BLINKER_PAGE, BLINKER_LEFT_START, BLINKER_RIGHT_START + BLINKER_COLS);
			// break;
		// case BLINKER_LEFT:
			// SetPin(A0, A0_ROW, DISPLAY_CMD); //set the displays into command mode
			// writeLCDSPI(FIRST_PAGE+BLINKER_PAGE); //set the page
			// writeLCDSPI(FIRST_COL_MSB+(BLINKER_LEFT_START>>4)); //set the column MSB
			// writeLCDSPI(FIRST_COL_LSB+(BLINKER_LEFT_START&0xf)); //set the column LSB
			// SetPin(A0, A0_ROW, DISPLAY_DATA); //set the display into data mode
			// for(i = 0; i < BLINKER_COLS; i++) //omit the begining and ends of the graph due to setting up the bar structure
			// {
				// writeLCDSPI(leftArrow[i]);
			// }
			// break;
		// case BLINKER_RIGHT:
			// SetPin(A0, A0_ROW, DISPLAY_CMD); //set the displays into command mode
			// writeLCDSPI(FIRST_PAGE+BLINKER_PAGE); //set the page
			// writeLCDSPI(FIRST_COL_MSB+(BLINKER_RIGHT_START>>4)); //set the column MSB
			// writeLCDSPI(FIRST_COL_LSB+(BLINKER_RIGHT_START&0xf)); //set the column LSB
			// SetPin(A0, A0_ROW, DISPLAY_DATA); //set the display into data mode
			// for(i = 0; i < BLINKER_COLS; i++) //omit the begining and ends of the graph due to setting up the bar structure
			// {
				// writeLCDSPI(rightArrow[i]);
			// }
			// break;
		// case BLINKER_HAZARD:
			// SetPin(A0, A0_ROW, DISPLAY_CMD); //set the displays into command mode
			// writeLCDSPI(FIRST_PAGE+BLINKER_PAGE); //set the page
			// writeLCDSPI(FIRST_COL_MSB+(BLINKER_LEFT_START>>4)); //set the column MSB
			// writeLCDSPI(FIRST_COL_LSB+(BLINKER_LEFT_START&0xf)); //set the column LSB
			// SetPin(A0, A0_ROW, DISPLAY_DATA); //set the display into data mode
			// for(i = 0; i < BLINKER_COLS; i++) //omit the begining and ends of the graph due to setting up the bar structure
			// {
				// writeLCDSPI(leftArrow[i]);
			// }
			
			// SetPin(A0, A0_ROW, DISPLAY_CMD); //set the displays into command mode
			// writeLCDSPI(FIRST_PAGE+BLINKER_PAGE); //set the page
			// writeLCDSPI(FIRST_COL_MSB+(BLINKER_RIGHT_START>>4)); //set the column MSB
			// writeLCDSPI(FIRST_COL_LSB+(BLINKER_RIGHT_START&0xf)); //set the column LSB
			// SetPin(A0, A0_ROW, DISPLAY_DATA); //set the display into data mode
			// for(i = 0; i < BLINKER_COLS; i++) //omit the begining and ends of the graph due to setting up the bar structure
			// {
				// writeLCDSPI(rightArrow[i]);
			// }
			// break;
	// }
	// //select LCD
	// if(device == LCD1){
		// SetPin(CS1, CS1_ROW, DISPLAY_NOTSELECT );//toggle the cip select to the desired values
	// }else{
		// SetPin(CS2, CS2_ROW, DISPLAY_NOTSELECT );//toggle the cip select to the desired values
	// }	
// }

// void updateMainLCD(int device){
	// char cruise[12] = {};
	// char battery[10] = {};
	
	// if(getInt("LCDLoop") == LCD_MAIN_LOOP){
		// static int change1 = -1;
		// if(change1 != 0){
			// clearDisplay(device);
			// change1 = 0;
		// }
		// //blinkers
		// updateBlinker(device);
		
		// //speedometer
		// updateSpeed(device, 0);//getInt(DS_MC_SPEED_RPM)); //TODO make RPM into MPH
		// writeString(device, 2, 76, "MPH");
		// //Cruise Control
		// if(getInt(DS_CONTROL_MODE) == SPEED_CONTROL){
			// sprintf(cruise, "Cruise: %d", getInt(DS_CRUISE_SPEED));
		// }
		// else{
			// sprintf(cruise, "Cruise: OFF");
		// }
		// writeString(device, 6, 60,  cruise);
		
		// //battery remaining
		// sprintf(battery, "Bat: %d%%", getInt("Battery"));
		// writeString(device, 6, 5, battery);
		// createGraph(device, 7, getInt("Battery"));

	// }else if(getInt("LCDLoop") == LCD_INIT_LOOP){
		// static int change = -1;
		// switch(getInt("initStep")){
			// case STEP0:
				// if(change != 0){
					// clearDisplay(device);
					// change = 0;
				// }
				// writeString(device, 1, 19, "Initialization:");
				// writeString(device, 3, 4, "take foot off pedals");
				// writeString(device, 5, 13, "Then press select");
			// break;
			// case STEP1:
				// if(change != 1){
					// clearDisplay(device);
					// change = 1;
				// }
				// writeString(device, 1, 19, "Initialization:");
				// writeString(device, 3, 4, "Press throttle pedal");
				// writeString(device, 4, 34, "down fully");
				// writeString(device, 6, 13, "Then press select");
			// break;
			// case STEP2:
				// if(change != 2){
					// clearDisplay(device);
					// change = 2;
				// }
				// writeString(device, 1, 19, "Initialization:");
				// writeString(device, 3, 13, "Press regen pedal");
				// writeString(device, 4, 34, "down fully");
				// writeString(device, 6, 13, "then press select");
			// break;
			// case STEP3:
				// if(change != 3){
					// clearDisplay(device);
					// change = 3;
				// }
				// writeString(device, 1, 19, "Initialization:");
				// writeString(device, 3, 10, "Calibrating airgap");
				// writeString(device, 4, 31, "please wait");
			// break;
			// default:
				// writeString(device, 0, 1, "?????????????????????????");
				// writeString(device, 1, 1, "?????????????????????????");
				// writeString(device, 2, 1, "?????????????????????????");
				// writeString(device, 3, 1, "?????????????????????????");
				// writeString(device, 4, 1, "?????????????????????????");
				// writeString(device, 5, 1, "?????????????????????????");
				// writeString(device, 6, 1, "?????????????????????????");
				// writeString(device, 7, 1, "?????????????????????????");
			// break;
		
		// }
	// }

// }


