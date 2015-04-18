/**
* @ingroup telemetry
* @defgroup gps GPS
* @brief GPS functions
* 
* @{
*/

#include <termios.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <err.h>
#include <unistd.h>
#include "gps.h"
#include "errno.h"
#include "sys/types.h"
#include "sys/mman.h"
#include "assert.h"
#include "sys/stat.h"
#include "fcntl.h"
#include "sys/signal.h"
#include "string.h"
#include "datalog.h"
#include "stdbool.h"
#include "conversions.h"

volatile int gpso;

/**
@author Reid Kersey <reidkersey@gmail.com> 678-736-0899

@brief This function initializes the GPS reciver on the top usb port

@note The GPS receiver must be plugged into USB0 (top USB port on 7800)

@details This function initializes the GPS receiver.

@todo increase the baud rate. The codes to do this can be found here:http://gpsd.googlecode.com/files/SiRF-SiRF-v2_4.pdf
@todo write errors to logfile
*/
int initGPS(){
	//initialize the port configuration settings
	struct termios config;
	
	//Connect to the GPS device
	gpso = open(GPSDEVICE, O_RDWR | O_NOCTTY); //gps device is the directory name of the device (usb0)
	
	//if Not Connected
	if(gpso < 0)
	{
		printf("ERROR\n");
		//Throw Error
		perror(GPSDEVICE);
		return 0;
	}

	//allow process to receive SIGIO
	fcntl(gpso, F_SETOWN, getpid());

	//clear, for new port settings
	bzero(&config, sizeof(config)); 
	
	//configure the I/O channel for intial GPS setup
	config.c_cflag = B4800 | CRTSCTS | CS8 | CLOCAL | CREAD | IXON;
	config.c_iflag = IGNPAR | ICRNL;
	config.c_oflag = 0;
	config.c_lflag = ICANON;

	//get rid of any remaining data
	tcflush(gpso, TCIFLUSH);

	//set the I/O line to the new config atributes
	tcsetattr(gpso, TCSANOW, &config);
	logMessage("GPS device initialized successfully", 0);
	return 1;
}

/**
@author Reid Kersey <reidkersey@gmail.com> 678-736-0899

@brief This function gets the GPS string, and then distributes it to
the appropriate function

@note Currenly supported functions are RMC, GGA, and GSA
@note Information on the NEMA strings are available here: http://www.gpsinformation.org/dale/nmea.htm#GGA

@todo line by line comments
*/
void parseGPS(){
	//intialize the variables
	char *segment = NULL;
	int size;
	char GPSstring[256];
	char GPSstringCpy[256];
	
	//read in the data
	size = read(gpso, GPSstring, 100);
	
	//terminate the GPS stirng with an null character
	GPSstring[size] = '\0';	
	
	//make a copy of the string to figgure out the type of string
	strcpy(GPSstringCpy, GPSstring);
	segment = strtok(GPSstringCpy, GPSDELIM);
	
	//disrubute the type string to the appropriate funciton
	if(!strcmp(segment, GGA)){
		parseGGA(GPSstring);
	}else if(!strcmp(segment, GSA)){
		parseGSA(GPSstring);
	}else if(!strcmp(segment, RMC)){
		parseRMC(GPSstring);
	}
}

/**
@author Reid Kersey <reidkersey@gmail.com> 678-736-0899

@brief This function takes in the heading angle, and then converts that to a cardinal direction.

@details This function takes in the heading angle, and then converts that to a cardinal direction.
The output will allways be two characters, to prevent the problem of having to clear the screen
when the direction changes.

@param angle This takes in an angle that represents the heading direction

@return This function returns the cardinal, and ordinal directions. If the angle is not within range,
it will return a "? ". Otherwise it will return a two character abreviation for the direction.
*/
char* calculateHeading(double angle){
	if((angle >= 0 && angle < 22.5) || (angle >= 337.5)){
		return "N ";
	}else if(angle >= 22.5 && angle < 67.5){
		return "NE";
	}else if(angle >= 67.5 && angle < 112.5){
		return "E ";
	}else if(angle >= 112.5 && angle < 157.5){
		return "SE";
	}else if(angle >= 157.5 && angle < 202.5){
		return "S ";
	}else if(angle >= 202.5 && angle < 247.5){
		return "SW";
	}else if(angle >= 247.5 && angle < 292.5){
		return "W ";
	}else if(angle >= 292.5 && angle < 337.5){
		return "NW";
	}
	return "? ";
}

/**
@author Reid Kersey <reidkersey@gmail.com> 678-736-0899

@brief This function gets a RMC character string from the GPS, and then parses it

@details This function takes in an RMC character string. From that it parses and sets
the time, latitude longitude, speed in knots, angle, heading, and the date. If the
data is not appropriate, the Speed indicator is set to use rpm

@note Information on the NEMA strings are available here: http://www.gpsinformation.org/dale/nmea.htm#GGA

@param RMC The NEMA RMC string from the GPS device.

@todo line by line comments
*/
void parseRMC(char * RMC){
	//setup a way to combine latitude, and longitude with direction
	char *segment = NULL;
	
	//get and set the time
	setTime(strtok(NULL, GPSDELIM));
	
	//if the status is active (has a GPS fix)
	if(!strcmp(strtok(NULL, GPSDELIM), "A")){
		//get and set the latitude and longitude
		char lat[254];
		char lon[254];
		segment = strtok(NULL, GPSDELIM);
		strcat(lat, segment);
		strcat(lat, ";");
		strcat(lat, strtok(NULL, GPSDELIM));
		setLat(lat);
		segment = strtok(NULL, GPSDELIM);
		strcat(lon, segment);
		strcat(lon, ";");
		strcat(lon, strtok(NULL, GPSDELIM));
		setLong(lon);
		
		//get the speed
		setSpeedGPSKnots(strtod(strtok(NULL, GPSDELIM), NULL));
		
		//get the heading angle
		setAngle(strtod(strtok(NULL, GPSDELIM), NULL));
		
		//set the heading direction
		setHeading(calculateHeading(getAngle()));
		
		//set the date
		setDate(strtok(NULL, GPSDELIM));
	}else
	{
		//if the status is void make the speedometer use RPM
		setUseGPSSpeed(false);
	}
}

/**
@author Reid Kersey <reidkersey@gmail.com> 678-736-0899

@brief This function gets a GSA character string from the GPS, and then parses it.

@details This function takes in an GSA character string. From that it parses and sets the
FixType, and the dilution of precisions. If everything is within range, it will have
the speedometer use GPS instead of RPM. This function ignores the satilite prns and
the auto selecton of 2d/3d fix

@note Information on the NEMA strings are available here: http://www.gpsinformation.org/dale/nmea.htm#GGA
@note Information on dilution of precision is available here: http://en.wikipedia.org/wiki/Dilution_of_precision_(GPS)#Meaning_of_DOP_Values
@param GSA The NEMA GSA string from the GPS device.

@todo line by line comments
*/
void parseGSA(char * GSA){
	//initialize the variables
	int i;
	
	//ignore the auto selecton type
	strtok(NULL, GPSDELIM);
	
	//set the type of fix (1 = no fix, 2 = 2D fix, 3 = 3D fix)
	setFixType(atoi(strtok(NULL, GPSDELIM)));
	
	//if the fix is at least 2D
	if(getFixType() > 1) 
	{
		char * prnTok = GSA;
		for(i = 0; i < 14; i++)
		{ 
			//ignore the PRNs
			prnTok = strchr(prnTok+1, (int)',');
		}
		
		//set the dilution of precisions
		setDOP(strtod(strtok(prnTok, GPSDELIM), NULL));
		setHDOP(strtod(strtok(NULL, GPSDELIM), NULL));
		setVDOP(strtod(strtok(NULL, GPSDELIM), NULL));
		
		//if the fix type is 3D, and the dilution of precision is within range set the
		//speedometer to use GPS else set it to use RPM
		if(getFixType() == 3 && getDOP() < MAX_DOP && knotsToMPH(getSpeedGPSKnots()) >= MIN_GPS_SPEED){
			setUseGPSSpeed(true);
		}
		else
		{
			setUseGPSSpeed(false);
		}
	}
}

/**
@author Reid Kersey <reidkersey@gmail.com> 678-736-0899

@brief This function gets a GGA character string from the GPS, and then parses it.

@details This function takes in an GGA character string. From that it parses and sets
the time, latitude, longitude, quality, number of satilite fixes, and the altitude.
This function will set the speedometer to RPM if the GPS fix is invalid. 

@param GGA The NEMA GGA string from the GPS device.

@note Information on the NEMA strings are available here: http://www.gpsinformation.org/dale/nmea.htm#GGA

@todo line by line comments
@todo protect the GPS quality, and GPS NumSat against overreading strtok
*/
void parseGGA(char * GGA){
	//initialize the variables
	char *segment;
	char lat[254] = {};
	char lon[254] = {};
	
	//set the time
	setTime(strtok(NULL, GPSDELIM));
	
	//set the latitudes and longitudes
	segment = strtok(NULL, GPSDELIM);
	strcat(lat, segment);
	strcat(lat, ",");
	strcat(lat, strtok(NULL, GPSDELIM));
	setLat(lat);
	segment = strtok(NULL, GPSDELIM);
	strcat(lon, segment);
	strcat(lon, ",");
	strcat(lon, strtok(NULL, GPSDELIM));

	//if the longitude seems wrong (i.e. strtok was overread)
	//make it right
	if(!strcmp(lon, "M,0.0")){
		setLong("0,0");
	}else{
		setLong(lon);
	}
	
	//set the quality of the GPS signal (will be wrong if strtok is over read)
	setGPSQuality(atoi(strtok(NULL, GPSDELIM)));
	
	//set the Number of Satalites of the GPS signal (will be wrong if strtok is over read)
	setGPSNumSat(atoi(strtok(NULL, GPSDELIM)));
	
	//if the quality of the GPS signal is within range get the altitude
	//else make the speedometer use RPM
	if(getQuality() > 0){
		//ignore the HDOP
		strtok(NULL, GPSDELIM);
		
		//set the altitude
		setAltitude(strtod(strtok(NULL, GPSDELIM), NULL));
	}else
	{
		//make the speedometer use RPM
		setUseGPSSpeed(false);
	}
}

/**
* @}
*/

