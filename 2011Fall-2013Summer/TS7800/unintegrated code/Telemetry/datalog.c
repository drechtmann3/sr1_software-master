/**
* @ingroup telemetry
* @defgroup datalog Datalog
* @brief Data logging functions
* 
* @{
*/

#include "lcd.h"
#include "datalog.h"
#include "string.h"
#include "stdbool.h"
#include "conversions.h"
#include "pthreads.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

//#define DEBUG 1

//DATE / TIME
static char DATE[DATE_CHARS];
static char TIME[TIME_CHARS];

//RS-485
static int CRUISE;
static int BLINKER;
static int RPM;
static int REGEN;
static int AIRGAP;
static double BMS[NUMBATS * BMS_NUM_VAR];
static double MPPT[NUMBATS * MPPT_NUM_VAR];


//ADC
static double ADC_TEMPS[NUM_ADC_TEMP_SENSORS];
static double ADC_VOLTS[NUM_ADC_VOLT_SENSORS];
static double ADC_CURRENT[NUM_ADC_CURRENT_SENSORS];

//CALCULATED
static int BATTERY;
static bool USE_GPS_SPEED;

//OTHER STORAGE
static int BUTTON_DB;

//ERRORS
static int ERROR_NUMS[NUM_DEF_ERRORS];
static int NUM_ERRORS;
static char DEF_ERRORS[NUM_DEF_ERRORS][MAX_ERROR_LENGTH];

//GPS
static char LAT[GPS_LAT_CHARS];
static char LONG[GPS_LONG_CHARS];
static char HEADING[GPS_HEADING_CHARS];
static int GPS_QUALITY;
static int GPS_NUMSAT;
static int GPS_FIX_TYPE;
static double ALTITUDE;
static double GPS_SPEED_KNOTS;
static double DOP;
static double HDOP;
static double VDOP;
static double ANGLE;

//USB
static char LOG_BUFFER[LOG_BUFFER_SIZE];

/**
@author Reid Kersey <reidkersey@gmail.com> 678-736-0899

@brief This funciton initializes the DATA to the initial settings
*/
void initDataLog(){
	LOG_BUFFER[0] = '\0';
	DATE[0] = '\0';
	strcpy(TIME, "00:00:00");
	LAT[0] = '\0';
	LONG[0] = '\0';
	HEADING[0] = '\0';
	logMessage("Datalog initialized successfully", 0);
}



//gets/////////////////////////////////////////////////////////////////
/**
@author Reid Kersey <reidkersey@gmail.com> 678-736-0899

@brief This function is used so that the variables can be kept in one place,
and mutexes are used so that race conditions do not occur

@return This function returns the time in a semicolon formatted ammount

@todo line by line comments
*/
char * getTime(){
	pthread_mutex_lock(&time_mutex);
	static char temp[TIME_CHARS];
	int i = 0;
	temp[i] = TIME[i];
	i++;
	temp[i] = TIME[i];
	i++;
	temp[i] = ':';
	i++;
	temp[i] = TIME[i-1];
	i++;
	temp[i] = TIME[i-1];
	i++;
	temp[i] = ':';
	i++;
	temp[i] = TIME[i-2];
	i++;
	temp[i] = TIME[i-2];
	i++;
	temp[i] = '\0';
	pthread_mutex_unlock(&time_mutex);
	return temp;
}

/**
@author Reid Kersey <reidkersey@gmail.com> 678-736-0899

@brief This function is used so that the variables can be kept in one place,
and mutexes are used so that race conditions do not occur

@return This function returns the date

@todo line by line comments
@todo format the date
*/
char * getDate(){
	pthread_mutex_lock(&date_mutex);
	static char temp[DATE_CHARS];
	strcpy(temp, DATE);
	pthread_mutex_unlock(&date_mutex);
	return temp;
}

//rs-485
/**
@author Reid Kersey <reidkersey@gmail.com> 678-736-0899

@brief This function is used so that the variables can be kept in one place,
and mutexes are used so that race conditions do not occur

@return This funciton returns the current cruise speed value
*/
int getCruise(){
	pthread_mutex_lock(&cruise_mutex);
	int temp = CRUISE;
	pthread_mutex_unlock(&cruise_mutex);
	return temp;
}

/**
@author Reid Kersey <reidkersey@gmail.com> 678-736-0899

@brief This function is used so that the variables can be kept in one place,
and mutexes are used so that race conditions do not occur

@return This funciton returns the current cruise speed value
*/
int getBlinker(){
	pthread_mutex_lock(&blinker_mutex);
	int temp = BLINKER;
	pthread_mutex_unlock(&blinker_mutex);
	return temp;
}

/**
@author Reid Kersey <reidkersey@gmail.com> 678-736-0899

@brief This function is used so that the variables can be kept in one place,
and mutexes are used so that race conditions do not occur

@return This funciton returns the current RPM value
*/
int getRPM(){
	pthread_mutex_lock(&rpm_mutex);
	int temp = RPM;
	pthread_mutex_unlock(&rpm_mutex);
	return temp;
}

/**
@author Reid Kersey <reidkersey@gmail.com> 678-736-0899

@brief This function is used so that the variables can be kept in one place,
and mutexes are used so that race conditions do not occur

@return This funciton returns the current Regen breaking value
*/
int getRegen(){
	pthread_mutex_lock(&regen_mutex);
	int temp = REGEN;
	pthread_mutex_unlock(&regen_mutex);
	return temp;
}

/**
@author Reid Kersey <reidkersey@gmail.com> 678-736-0899

@brief This function is used so that the variables can be kept in one place,
and mutexes are used so that race conditions do not occur

@return This funciton returns the current airgap position
*/
int getAirgap(){
	pthread_mutex_lock(&blinker_mutex);
	int temp = AIRGAP;
	pthread_mutex_unlock(&blinker_mutex);
	return temp;
}

/**
@author Reid Kersey <reidkersey@gmail.com> 678-736-0899

@brief This function is used so that the variables can be kept in one place,
and mutexes are used so that race conditions do not occur

@return This funciton returns the current BMS values

@todo account for multiple BMS Systems
*/
double* getBMS(){
	pthread_mutex_lock(&bms_mutex);
	static double temp[NUMBATS * BMS_NUM_VAR];
	int i;
	for(i = 0; i < NUMBATS * BMS_NUM_VAR; i++){
		temp[i] = BMS[i];
	}
	pthread_mutex_unlock(&bms_mutex);
	return temp;
}

/**
@author Reid Kersey <reidkersey@gmail.com> 678-736-0899

@brief This function is used so that the variables can be kept in one place,
and mutexes are used so that race conditions do not occur

@return This funciton returns the current MPPT values

@todo account for multiple MPPT systems, or orther MPPT formats
*/
double* getMPPT(){
	pthread_mutex_lock(&mppt_mutex);
	static double temp[NUMMPPT * MPPT_NUM_VAR];
	int i;
	for(i = 0; i < NUMMPPT * MPPT_NUM_VAR; i++){
		temp[i] = MPPT[i];
	}
	pthread_mutex_unlock(&mppt_mutex);
	return temp;
}

//adc
/**
@author Reid Kersey <reidkersey@gmail.com> 678-736-0899

@brief This function is used so that the variables can be kept in one place,
and mutexes are used so that race conditions do not occur

@return This funciton returns an array of Temepratures from the ADC board
*/
double* getADCTemps(){
	pthread_mutex_lock(&adc_temps_mutex);
	static double temp[NUM_ADC_TEMP_SENSORS];
	int i;
	for(i = 0; i < NUM_ADC_TEMP_SENSORS; i++){
		temp[i] = ADC_TEMPS[i];
	}
	pthread_mutex_unlock(&adc_temps_mutex);
	return temp;
}

/**
@author Reid Kersey <reidkersey@gmail.com> 678-736-0899

@brief This function is used so that the variables can be kept in one place,
and mutexes are used so that race conditions do not occur

@return This funciton returns an array of Voltages from the ADC board
*/
double* getADCVolts(){
	pthread_mutex_lock(&adc_volts_mutex);
	static double temp[NUM_ADC_VOLT_SENSORS];
	int i;
	for(i = 0; i < NUM_ADC_VOLT_SENSORS; i++){
		temp[i] = ADC_VOLTS[i];
	}
	pthread_mutex_unlock(&adc_volts_mutex);
	return temp;
}

/**
@author Reid Kersey <reidkersey@gmail.com> 678-736-0899

@brief This function is used so that the variables can be kept in one place,
and mutexes are used so that race conditions do not occur

@return This funciton returns an array of currents from the ADC board
*/
double* getADCCurrent(){
	pthread_mutex_lock(&adc_current_mutex);
	static double temp[NUM_ADC_CURRENT_SENSORS];
	int i;
	for(i = 0; i < NUM_ADC_CURRENT_SENSORS; i++){
		temp[i] = ADC_CURRENT[i];
	}
	pthread_mutex_unlock(&adc_current_mutex);
	return temp;
}

//calculated
/**
@author Reid Kersey <reidkersey@gmail.com> 678-736-0899

@brief This function is used so that the variables can be kept in one place,
and mutexes are used so that race conditions do not occur.

@details This funciton will return the speed calculated by the gps if the GPS is accurate
enough. Otherwise it will use the RPM to calculate the speed.

@return This funciton returns the current speed value in MPH

@todo make this funciton useable for KMH values as well
*/
double getSpeed(){
	if(getUseGPSSpeed()){
		return knotsToMPH(getSpeedGPSKnots());
	}else
	{
		return RPMToMPH(getRPM());
	}
}

/**
@author Reid Kersey <reidkersey@gmail.com> 678-736-0899

@brief This function is used so that the variables can be kept in one place,
and mutexes are used so that race conditions do not occur

@return This funciton returns the current battery value
*/
int getBattery(){
	pthread_mutex_lock(&battery_mutex);
	int temp = BATTERY;
	pthread_mutex_unlock(&battery_mutex);
	return temp;
}

/**
@author Reid Kersey <reidkersey@gmail.com> 678-736-0899

@brief This function is used so that the variables can be kept in one place,
and mutexes are used so that race conditions do not occur

@return This funciton returns weather or the GPS data is suitable for speedometer use
*/
bool getUseGPSSpeed(){
	pthread_mutex_lock(&use_gps_speed_mutex);
	int temp = USE_GPS_SPEED;
	pthread_mutex_unlock(&use_gps_speed_mutex);
	return temp;
}

//OTHER STORAGE
/**
@author Reid Kersey <reidkersey@gmail.com> 678-736-0899

@brief This function is used so that the variables can be kept in one place,
and mutexes are used so that race conditions do not occur

@return This funciton returns the current state of the button debounce
*/
int getButtonDB(){
	pthread_mutex_lock(&button_db_mutex);
	int temp = BUTTON_DB;
	pthread_mutex_unlock(&button_db_mutex);
	return temp;
}

//ERRORS
/**
@author Reid Kersey <reidkersey@gmail.com> 678-736-0899

@brief This function is used so that the variables can be kept in one place,
and mutexes are used so that race conditions do not occur

@param index The error code (index in the error array)

@return This funciton returns explanation of the error code provided
*/
char* getErrors(int index){
	pthread_mutex_lock(&errors_mutex);
	static char temp[MAX_ERROR_LENGTH];
	strcpy(temp, DEF_ERRORS[ERROR_NUMS[index]]);
	return temp;
}

///@todo create a function that returns an array of current errors

/**
@author Reid Kersey <reidkersey@gmail.com> 678-736-0899

@brief This function is used so that the variables can be kept in one place,
and mutexes are used so that race conditions do not occur

@return This funciton returns the current number of active errors
*/
int getNumErrors(){
	pthread_mutex_lock(&errors_mutex);
	int temp;
	temp = NUM_ERRORS;
	pthread_mutex_unlock(&errors_mutex);
	return temp;
}

//LCD
/**
@author Reid Kersey <reidkersey@gmail.com> 678-736-0899

@brief This function is used so that the variables can be kept in one place,
and mutexes are used so that race conditions do not occur

@return This funciton returns the current text and values for use on the LCD "main page"
*/
char* getLCDGeneral(int index){
	pthread_mutex_lock(&lcd_general_mutex);
	static char temp[LCD_CHAR_PER_LINE_NULL];
	switch(index){
		case 0:
			sprintf(temp, "%s%s", LCD_General_Text[0], getDate());
			break;
		case 1:
			sprintf(temp, "%s%s", LCD_General_Text[1], getTime());	
			break;
		case 2:
			sprintf(temp, "%s%s", LCD_General_Text[2], getHeading());
			break;
		case 3:
			sprintf(temp, "%s%d", LCD_General_Text[3], getRPM());
			break;
		case 4:
			sprintf(temp, "%s%d", LCD_General_Text[4], getBattery());
			break;
		case 5:
			sprintf(temp, "%s%d", LCD_General_Text[5], getRegen());
			break;
		case 6:
			sprintf(temp, "%s%d", LCD_General_Text[6], getAirgap());
			break;	
	}
	pthread_mutex_unlock(&lcd_general_mutex);
	return temp;
}

/**
@author Reid Kersey <reidkersey@gmail.com> 678-736-0899

@brief This function is used so that the variables can be kept in one place,
and mutexes are used so that race conditions do not occur

@return This funciton returns the current values and text for use on the LCD "voltages page"
*/
char* getLCDVoltages(int index){
	pthread_mutex_lock(&lcd_voltages_mutex);
	static char temp[LCD_CHAR_PER_LINE_NULL];
	switch(index){
		case 0:
			sprintf(temp, "%s%1.2f", LCD_Voltage_Text[0], BMS[0]);		
			break;
		case 1:
			sprintf(temp, "%s%1.2f", LCD_Voltage_Text[1], BMS[1]);		
			break;
		case 2:
			sprintf(temp, "%s%1.2f", LCD_Voltage_Text[2], BMS[2]);
			break;
		case 3:
			sprintf(temp, "%s%1.2f", LCD_Voltage_Text[3], BMS[3]);
			break;
		case 4:
			sprintf(temp, "%s%1.2f", LCD_Voltage_Text[4], BMS[4]);
			break;
		case 5:
			sprintf(temp, "%s%1.2f", LCD_Voltage_Text[5], BMS[5]);
			break;
		case 6:
			sprintf(temp, "%s%1.2f", LCD_Voltage_Text[6], BMS[6]);
			break;	
	}
	pthread_mutex_unlock(&lcd_voltages_mutex);
	return temp;
}

/**
@author Reid Kersey <reidkersey@gmail.com> 678-736-0899

@brief This function is used so that the variables can be kept in one place,
and mutexes are used so that race conditions do not occur

@return This funciton returns the current text and values for the LCD "currents page"
*/
char* getLCDCurrents(int index){
	pthread_mutex_lock(&lcd_currents_mutex);
	static char temp[LCD_CHAR_PER_LINE_NULL];
	switch(index){
		case 0:
			sprintf(temp, "%s%1.2f", LCD_Current_Text[0], MPPT[0]);		
			break;
		case 1:
			sprintf(temp, "%s%1.2f", LCD_Current_Text[1], MPPT[1]);		
			break;
		case 2:
			sprintf(temp, "%s%1.2f", LCD_Current_Text[2], MPPT[2]);
			break;
		case 3:
			sprintf(temp, "%s%1.2f", LCD_Current_Text[3], MPPT[3]);
			break;
		case 4:
			sprintf(temp, "%s%1.2f", LCD_Current_Text[4], MPPT[4]);
			break;
		case 5:
			sprintf(temp, "%s%1.2f", LCD_Current_Text[5], MPPT[5]);
			break;
		case 6:
			sprintf(temp, "%s%1.2f", LCD_Current_Text[6], MPPT[6]);
			break;	
	}
	pthread_mutex_unlock(&lcd_currents_mutex);
	return temp;
}

/**
@author Reid Kersey <reidkersey@gmail.com> 678-736-0899

@brief This function is used so that the variables can be kept in one place,
and mutexes are used so that race conditions do not occur

@return This funciton returns the current text and values for the LCD "temperatures page"
*/
char* getLCDTemps(int index){
	pthread_mutex_lock(&lcd_temps_mutex);
	static char temp[LCD_CHAR_PER_LINE_NULL];
	switch(index){
		case 0:
			sprintf(temp, "%s%1.2f", LCD_Temp_Text[0], BMS[0]);		
			break;
		case 1:
			sprintf(temp, "%s%1.2f", LCD_Temp_Text[1], BMS[1]);		
			break;
		case 2:
			sprintf(temp, "%s%1.2f", LCD_Temp_Text[2], BMS[2]);
			break;
		case 3:
			sprintf(temp, "%s%1.2f", LCD_Temp_Text[3], BMS[3]);
			break;
		case 4:
			sprintf(temp, "%s%1.2f", LCD_Temp_Text[4], BMS[4]);
			break;
		case 5:
			sprintf(temp, "%s%1.2f", LCD_Temp_Text[5], BMS[5]);
			break;
		case 6:
			sprintf(temp, "%s%1.2f", LCD_Temp_Text[6], BMS[6]);
			break;	
	}
	pthread_mutex_unlock(&lcd_temps_mutex);
	return temp;
}

//GPS
/**
@author Reid Kersey <reidkersey@gmail.com> 678-736-0899

@brief This function is used so that the variables can be kept in one place,
and mutexes are used so that race conditions do not occur

@return This funciton returns the current latitude from the last GPS update
*/
char * getLat(){
	pthread_mutex_lock(&lat_mutex);
	static char temp[GPS_LAT_CHARS];
	strcpy(temp, LAT);
	pthread_mutex_unlock(&lat_mutex);
	return temp;
}

/**
@author Reid Kersey <reidkersey@gmail.com> 678-736-0899

@brief This function is used so that the variables can be kept in one place,
and mutexes are used so that race conditions do not occur

@return This funciton returns the current longitude from the last GPS update
*/
char * getLong(){
	pthread_mutex_lock(&longitude_mutex);
	static char temp[GPS_LONG_CHARS];
	strcpy(temp, LONG);
	pthread_mutex_unlock(&longitude_mutex);
	return temp;
}

/**
@author Reid Kersey <reidkersey@gmail.com> 678-736-0899

@brief This function is used so that the variables can be kept in one place,
and mutexes are used so that race conditions do not occur

@return This funciton returns the current heading from the last GPS RMC update
*/
char * getHeading(){
	pthread_mutex_lock(&heading_mutex);
	static char temp[GPS_HEADING_CHARS];
	strcpy(temp, HEADING);
	pthread_mutex_unlock(&heading_mutex);
	return temp;
}

/**
@author Reid Kersey <reidkersey@gmail.com> 678-736-0899

@brief This function is used so that the variables can be kept in one place,
and mutexes are used so that race conditions do not occur

@return This funciton returns the current GPS signal quality from the last GPS update
*/
int getQuality(){
	pthread_mutex_lock(&gps_quality_mutex);
	int temp = GPS_QUALITY;
	pthread_mutex_unlock(&gps_quality_mutex);
	return temp;
}

/**
@author Reid Kersey <reidkersey@gmail.com> 678-736-0899

@brief This function is used so that the variables can be kept in one place,
and mutexes are used so that race conditions do not occur

@return This funciton returns the current number of satilites being tracked (but not
nessassairly used) from the last GPS update.
*/
int getNumSat(){
	pthread_mutex_lock(&gps_numsat_mutex);
	int temp = GPS_NUMSAT;
	pthread_mutex_unlock(&gps_numsat_mutex);
	return temp;
}

/**
@author Reid Kersey <reidkersey@gmail.com> 678-736-0899

@brief This function is used so that the variables can be kept in one place,
and mutexes are used so that race conditions do not occur

@return This funciton returns the current fix type form the last GPS update
*/
int getFixType(){
	pthread_mutex_lock(&gps_fix_type_mutex);
	int temp = GPS_FIX_TYPE;
	pthread_mutex_unlock(&gps_fix_type_mutex);
	return temp;
}

/**
@author Reid Kersey <reidkersey@gmail.com> 678-736-0899

@brief This function is used so that the variables can be kept in one place,
and mutexes are used so that race conditions do not occur

@return This funciton returns the current altitude from the last GPS update
*/
double getAltitude(){
	pthread_mutex_lock(&altitude_mutex);
	double temp = GPS_FIX_TYPE;
	pthread_mutex_unlock(&altitude_mutex);
	return temp;
}

/**
@author Reid Kersey <reidkersey@gmail.com> 678-736-0899

@brief This function is used so that the variables can be kept in one place,
and mutexes are used so that race conditions do not occur

@return This funciton returns the current speed in knots from the last GPS update
*/
double getSpeedGPSKnots(){
	pthread_mutex_lock(&gps_speed_knots_mutex);
	double temp = GPS_SPEED_KNOTS;
	pthread_mutex_unlock(&gps_speed_knots_mutex);
	return temp;
}

/**
@author Reid Kersey <reidkersey@gmail.com> 678-736-0899

@brief This function is used so that the variables can be kept in one place,
and mutexes are used so that race conditions do not occur

@return This funciton returns the dilution of precision from the last GPS update
*/
double getDOP(){
	pthread_mutex_lock(&dop_mutex);
	double temp = DOP;
	pthread_mutex_unlock(&dop_mutex);
	return temp;
}

/**
@author Reid Kersey <reidkersey@gmail.com> 678-736-0899

@brief This function is used so that the variables can be kept in one place,
and mutexes are used so that race conditions do not occur

@return This funciton returns the horizontal dilution of precision from the last GPS update
*/
double getHDOP(){
	pthread_mutex_lock(&hdop_mutex);
	double temp = HDOP;
	pthread_mutex_unlock(&hdop_mutex);
	return temp;
}

/**
@author Reid Kersey <reidkersey@gmail.com> 678-736-0899

@brief This function is used so that the variables can be kept in one place,
and mutexes are used so that race conditions do not occur

@return This funciton returns the vertical dilution of precision from the last GPS update
*/
double getVDOP(){
	pthread_mutex_lock(&vdop_mutex);
	double temp = VDOP;
	pthread_mutex_unlock(&vdop_mutex);
	return temp;
}

/**
@author Reid Kersey <reidkersey@gmail.com> 678-736-0899

@brief This function is used so that the variables can be kept in one place,
and mutexes are used so that race conditions do not occur

@return This funciton returns the current heading in degreese from the last GPS update
*/
double getAngle(){
	pthread_mutex_lock(&angle_mutex);
	double temp = ANGLE;
	pthread_mutex_unlock(&angle_mutex);
	return temp;
}

//USB
/**
@author Reid Kersey <reidkersey@gmail.com> 678-736-0899

@brief This function is used so that the variables can be kept in one place,
and mutexes are used so that race conditions do not occur

@note The log buffer should be cleared once it is logged

@return This funciton returns the current log buffer
*/
char * getLogBuff(){
	pthread_mutex_lock(&log_buffer_mutex);
	static char temp[LOG_BUFFER_SIZE];
	strcpy(temp, LOG_BUFFER);
	pthread_mutex_unlock(&log_buffer_mutex);
	return temp;
}

//sets//////////////////////////////////////////////////////////
//DATE AND TIME
/**
@author Reid Kersey <reidkersey@gmail.com> 678-736-0899

@brief This function is used so that the variables can be kept in one place,
and mutexes are used so that race conditions do not occur.

@param time the time.
*/
void setTime(char * time){
	pthread_mutex_lock(&time_mutex);
	strcpy(TIME, time);
	pthread_mutex_unlock(&time_mutex);
}
/**
@author Reid Kersey <reidkersey@gmail.com> 678-736-0899

@brief This function is used so that the variables can be kept in one place,
and mutexes are used so that race conditions do not occur.

@param date the date.
*/
void setDate(char* date){
	pthread_mutex_lock(&date_mutex);
	strcpy(DATE, date);
	pthread_mutex_unlock(&date_mutex);
}

//RS-485
/**
@author Reid Kersey <reidkersey@gmail.com> 678-736-0899

@brief This function is used so that the variables can be kept in one place,
and mutexes are used so that race conditions do not occur.

@param cruise the current cruise speed
*/
void setCruise(int cruise){
	pthread_mutex_lock(&cruise_mutex);
	CRUISE = cruise;
	pthread_mutex_unlock(&cruise_mutex);
}

/**
@author Reid Kersey <reidkersey@gmail.com> 678-736-0899

@brief This function is used so that the variables can be kept in one place,
and mutexes are used so that race conditions do not occur.

@param blinker the current value of the blinker as defined in lcd.h
*/
void setBlinker(int blinker){
	pthread_mutex_lock(&blinker_mutex);
	BLINKER = blinker;
	pthread_mutex_unlock(&blinker_mutex);
}

/**
@author Reid Kersey <reidkersey@gmail.com> 678-736-0899

@brief This function is used so that the variables can be kept in one place,
and mutexes are used so that race conditions do not occur.

@param rpm the current RPM
*/
void setRPM(int rpm){
	pthread_mutex_lock(&rpm_mutex);
	RPM = rpm;
	pthread_mutex_unlock(&rpm_mutex);
}

/**
@author Reid Kersey <reidkersey@gmail.com> 678-736-0899

@brief This function is used so that the variables can be kept in one place,
and mutexes are used so that race conditions do not occur.

@param regen the amount of regen
*/
void setRegen(int regen){
	pthread_mutex_lock(&regen_mutex);
	REGEN = regen;
	pthread_mutex_unlock(&regen_mutex);
}

/**
@author Reid Kersey <reidkersey@gmail.com> 678-736-0899

@brief This function is used so that the variables can be kept in one place,
and mutexes are used so that race conditions do not occur.

@param airgap the position of the airgap
*/
void setAirgap(int airgap){
	pthread_mutex_lock(&airgap_mutex);
	AIRGAP = airgap;
	pthread_mutex_unlock(&airgap_mutex);
}

/**
@author Reid Kersey <reidkersey@gmail.com> 678-736-0899

@brief This function is used so that the variables can be kept in one place,
and mutexes are used so that race conditions do not occur.

@param bms The values for the called BMS
@param BMSNum the number of the BMS
*/
void setBMS(double * bms, int BMSNum){
	pthread_mutex_lock(&bms_mutex);
	int i;
	#ifdef DEBUG
	printf("Datalog Received BMS info for BMS %d",BMSNum);
	#endif
	for(i = 0; i < BMS_NUM_VAR; i++){
		BMS[(BMSNum*BMS_NUM_VAR)+i] = *(bms + i);
		#ifdef DEBUG
			printf("Var at %d is %f\n",i, *(bms + i));
		#endif
	}
	pthread_mutex_unlock(&bms_mutex);
}

/**
@author Reid Kersey <reidkersey@gmail.com> 678-736-0899

@brief This function is used so that the variables can be kept in one place,
and mutexes are used so that race conditions do not occur.

@param mppt the values for the called MPPT
@param MPPTNum the number of the called MPPT
*/
void setMPPT(double * mppt, int MPPTNum){
	pthread_mutex_lock(&mppt_mutex);
	int i;
	for(i = 0; i < MPPT_NUM_VAR; i++){
		MPPT[(MPPTNum*MPPT_NUM_VAR)+i] = *(mppt + i);
	}
	pthread_mutex_unlock(&mppt_mutex);
}

//ADC
/**
@author Reid Kersey <reidkersey@gmail.com> 678-736-0899

@brief This function is used so that the variables can be kept in one place,
and mutexes are used so that race conditions do not occur.

@param ADCTemps The values of the temperatres from the ADC board
*/
void setADCTemps(double * ADCTemps){
	pthread_mutex_lock(&adc_temps_mutex);
	int i;
	for(i = 0; i < NUM_ADC_TEMP_SENSORS; i++){
		ADC_TEMPS[i] = *(ADCTemps + i);
	}
	pthread_mutex_unlock(&adc_temps_mutex);
}

/**
@author Reid Kersey <reidkersey@gmail.com> 678-736-0899

@brief This function is used so that the variables can be kept in one place,
and mutexes are used so that race conditions do not occur.

@param ADCVolts The values of the voltages from the ADC board
*/
void setADCVolts(double * ADCVolts){
	pthread_mutex_lock(&adc_volts_mutex);
	int i;
	for(i = 0; i < NUM_ADC_VOLT_SENSORS; i++){
		ADC_VOLTS[i] = *(ADCVolts + i);
	}
	pthread_mutex_unlock(&adc_volts_mutex);
}

/**
@author Reid Kersey <reidkersey@gmail.com> 678-736-0899

@brief This function is used so that the variables can be kept in one place,
and mutexes are used so that race conditions do not occur.

@param ADCCurrent The values of the currents from the ADC board
*/
void setADCCurrent(double * ADCCurrent){
	pthread_mutex_lock(&adc_current_mutex);
	int i;
	for(i = 0; i < NUM_ADC_CURRENT_SENSORS; i++){
		ADC_CURRENT[i] = *(ADCCurrent + i);
	}
	pthread_mutex_unlock(&adc_current_mutex);
}

//calculated
/**
@author Reid Kersey <reidkersey@gmail.com> 678-736-0899

@brief This function is used so that the variables can be kept in one place,
and mutexes are used so that race conditions do not occur.

@param useSpeed the boolean value of weather or not to use GPS or RPM for the speedometer
*/
void setUseGPSSpeed(bool useSpeed){
	pthread_mutex_lock(&use_gps_speed_mutex);
	USE_GPS_SPEED = useSpeed;
	pthread_mutex_unlock(&use_gps_speed_mutex);
}

//other Storage
/**
@author Reid Kersey <reidkersey@gmail.com> 678-736-0899

@brief This function is used so that the variables can be kept in one place,
and mutexes are used so that race conditions do not occur.

@param DB The current value of the button debounce
*/
void setButtonDB(int DB){
	pthread_mutex_lock(&button_db_mutex);
	BUTTON_DB = DB;
	pthread_mutex_unlock(&button_db_mutex);
}

//Errors
/**
@author Reid Kersey <reidkersey@gmail.com> 678-736-0899

@brief This function is used so that the variables can be kept in one place,
and mutexes are used so that race conditions do not occur.

@param error The error code that matches the error
*/
void setError(int error){
	pthread_mutex_lock(&errors_mutex);
	ERROR_NUMS[NUM_ERRORS] = error;
	NUM_ERRORS += 1;
	pthread_mutex_unlock(&errors_mutex);
}

//GPS
/**
@author Reid Kersey <reidkersey@gmail.com> 678-736-0899

@brief This function is used so that the variables can be kept in one place,
and mutexes are used so that race conditions do not occur.

@param lat The current latitude
*/
void setLat(char * lat){
	pthread_mutex_lock(&lat_mutex);
	strcpy(LAT, lat);
	pthread_mutex_unlock(&lat_mutex);
}

/**
@author Reid Kersey <reidkersey@gmail.com> 678-736-0899

@brief This function is used so that the variables can be kept in one place,
and mutexes are used so that race conditions do not occur.

@param lon The current longitude
*/
void setLong(char * lon){
	pthread_mutex_lock(&longitude_mutex);
	strcpy(LONG, lon);
	pthread_mutex_unlock(&longitude_mutex);
}

/**
@author Reid Kersey <reidkersey@gmail.com> 678-736-0899

@brief This function is used so that the variables can be kept in one place,
and mutexes are used so that race conditions do not occur.

@param heading the current heading in terms of cardinal direction
*/
void setHeading(char * heading){
	pthread_mutex_lock(&heading_mutex);
	strcpy(HEADING, heading);
	pthread_mutex_unlock(&heading_mutex);
}

/**
@author Reid Kersey <reidkersey@gmail.com> 678-736-0899

@brief This function is used so that the variables can be kept in one place,
and mutexes are used so that race conditions do not occur.

@param qual The current quality of the GPS signal
*/
void setGPSQuality(int qual){
	pthread_mutex_lock(&gps_quality_mutex);
	GPS_QUALITY = qual;
	pthread_mutex_unlock(&gps_quality_mutex);
}

/**
@author Reid Kersey <reidkersey@gmail.com> 678-736-0899

@brief This function is used so that the variables can be kept in one place,
and mutexes are used so that race conditions do not occur.

@param numsat The current number of satalites being tracked
*/
void setGPSNumSat(int numsat){
	pthread_mutex_lock(&gps_numsat_mutex);
	GPS_NUMSAT = numsat;
	pthread_mutex_unlock(&gps_numsat_mutex);
}

/**
@author Reid Kersey <reidkersey@gmail.com> 678-736-0899

@brief This function is used so that the variables can be kept in one place,
and mutexes are used so that race conditions do not occur.

@param type The current fix type of the GPS signal
*/
void setFixType(int type){
	pthread_mutex_lock(&gps_fix_type_mutex);
	GPS_FIX_TYPE = type;
	pthread_mutex_unlock(&gps_fix_type_mutex);
}

/**
@author Reid Kersey <reidkersey@gmail.com> 678-736-0899

@brief This function is used so that the variables can be kept in one place,
and mutexes are used so that race conditions do not occur.

@param alt The current altidue above sea level
*/
void setAltitude(double alt){
	pthread_mutex_lock(&altitude_mutex);
	ALTITUDE = alt;
	pthread_mutex_unlock(&altitude_mutex);
}

/**
@author Reid Kersey <reidkersey@gmail.com> 678-736-0899

@brief This function is used so that the variables can be kept in one place,
and mutexes are used so that race conditions do not occur.

@param speed the current speed in knots
*/
void setSpeedGPSKnots(double speed){
	pthread_mutex_lock(&gps_speed_knots_mutex);
	GPS_SPEED_KNOTS = speed;
	pthread_mutex_unlock(&gps_speed_knots_mutex);
}

/**
@author Reid Kersey <reidkersey@gmail.com> 678-736-0899

@brief This function is used so that the variables can be kept in one place,
and mutexes are used so that race conditions do not occur.

@param dop The current Dilution of Precision value from the last GPS update
*/
void setDOP(double dop){
	pthread_mutex_lock(&dop_mutex);
	DOP = dop;
	pthread_mutex_unlock(&dop_mutex);
}

/**
@author Reid Kersey <reidkersey@gmail.com> 678-736-0899

@brief This function is used so that the variables can be kept in one place,
and mutexes are used so that race conditions do not occur.

@param dop The current Horizontal Dilution of Precision value from the last GPS update
*/
void setHDOP(double dop){
	pthread_mutex_lock(&hdop_mutex);
	HDOP = dop;
	pthread_mutex_unlock(&hdop_mutex);
}

/**
@author Reid Kersey <reidkersey@gmail.com> 678-736-0899

@brief This function is used so that the variables can be kept in one place,
and mutexes are used so that race conditions do not occur.

@param dop The current Vertical Dilution of Precision value from the last GPS update
*/
void setVDOP(double dop){
	pthread_mutex_lock(&vdop_mutex);
	VDOP = dop;
	pthread_mutex_unlock(&vdop_mutex);
}

/**
@author Reid Kersey <reidkersey@gmail.com> 678-736-0899

@brief This function is used so that the variables can be kept in one place,
and mutexes are used so that race conditions do not occur.

@param angle The current heading in degreese
*/
void setAngle(double angle){
	pthread_mutex_lock(&angle_mutex);
	ANGLE = angle;
	pthread_mutex_unlock(&angle_mutex);
}

//USB
/**
@author Reid Kersey <reidkersey@gmail.com> 678-736-0899

@brief This function is used so that the variables can be kept in one place,
and mutexes are used so that race conditions do not occur.

@param message The message to get tacked onto the existing log file
@param severity The severity level of the log message (0-5) 5 being most severe, 0 being notice
*/
void logMessage(char * message, int severity){
	pthread_mutex_lock(&log_buffer_mutex);
	char severityStr[6];
	sprintf(severityStr, "%d, ", severity);
	strcat(LOG_BUFFER, severityStr);
	strcat(LOG_BUFFER, message);
	strcat(LOG_BUFFER, "\n");
	pthread_mutex_unlock(&log_buffer_mutex);
}

/**
@author Reid Kersey <reidkersey@gmail.com> 678-736-0899

@brief This function is used so that the variables can be kept in one place,
and mutexes are used so that race conditions do not occur.
*/
void clearLogBuffer(){
	pthread_mutex_lock(&log_buffer_mutex);
	LOG_BUFFER[0] = '\0';
	pthread_mutex_unlock(&log_buffer_mutex);
}

/**
* @}
*/
