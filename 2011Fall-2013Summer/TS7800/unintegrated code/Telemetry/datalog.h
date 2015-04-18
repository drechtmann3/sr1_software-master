#ifndef DATALOG_H
#define DATALOG_H
#include <stdbool.h>
#define NUMBATS					(3)
#define BMS_NUM_VAR				(35)
#define NUMMPPT					(4)
#define MPPT_NUM_VAR			(10)
#define SPEEDUNIT				("MPH")
#define NUM_ADC_TEMP_SENSORS	(5)
#define NUM_ADC_VOLT_SENSORS	(7)
#define NUM_ADC_CURRENT_SENSORS	(5)
#define NUM_DEF_ERRORS			(10)
#define LCD_CHAR_PER_LINE_NULL	(22)
#define GPS_TIME_CHARS			(6)
#define GPS_LAT_CHARS			(10)
#define GPS_LONG_CHARS			(11)
#define GPS_HEADING_CHARS		(3)
#define GPS_DATE_CHARS			(7)
#define DATE_CHARS				(9)
#define TIME_CHARS				(13)
#define MAX_ERROR_LENGTH		(50)
#define LOG_BUFFER_SIZE			(512)

void initDataLog();

//gets/////////////////////////////////////////////////////////////////
//date & time
char * getTime();
char * getDate();

//rs-485
int getCruise();
int getBlinker();
int getRPM();
int getRegen();
int getAirgap();
double* getBMS();
double* getMPPT();

//adc
double* getADCTemps();
double* getADCVolts();
double* getADCCurrent();

//calculated
double getSpeed();
int getBattery();
bool getUseGPSSpeed();

//OTHER STORAGE
int getButtonDB();


//ERRORS
char* getErrors(int index);
int getNumErrors();

//LCD
char* getLCDErrors();
char* getLCDGeneral();
char* getLCDVoltages();
char* getLCDCurrents();
char* getLCDTemps();

//GPS
char * getLat();
char * getLong();
char * getHeading();
int getQuality();
int getNumSat();
int getFixType();
double getAltitude();
double getSpeedGPSKnots();
double getDOP();
double getHDOP();
double getVDOP();
double getAngle();

//USB
void logMessage(char * message, int severity);
char * getLogBuff();

//sets/////////////////////////////////////////////
//DATE AND TIME
void setTime(char * time);
void setDate(char* date);

//RS-485
void setCruise(int cruise);
void setBlinker(int blinker);
void setRPM(int rpm);
void setRegen(int regen);
void setAirgap(int airgap);
void setBMS(double * bms, int BMSNum);
void setMPPT(double * mppt, int MPPTNum);

//ADC
void setADCTemps(double * ADCTemps);
void setADCVolts(double * ADCVolts);
void setADCCurrent(double * ADCCurrent);

//calculated
void setUseGPSSpeed(bool useSpeed);

//other Storage
void setButtonDB(int DB);

//Errors
void setError(int error);

//GPS
void setLat(char * lat);
void setLong(char * lon);
void setHeading(char * heading);
void setGPSQuality(int qual);
void setGPSNumSat(int numsat);
void setFixType(int type);
void setAltitude(double alt);
void setSpeedGPSKnots(double speed);
void setDOP(double dop);
void setHDOP(double dop);
void setVDOP(double dop);
void setAngle(double angle);

//USB
void clearLogBuffer();
#endif
