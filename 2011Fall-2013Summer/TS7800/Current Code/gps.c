// /**
// * @ingroup telemetry
// * @defgroup gps GPS
// * @brief GPS functions
// * 
// * @{
// */

// #include <termios.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <sys/mman.h>
// #include <fcntl.h>
// #include <err.h>
// #include <unistd.h>
// #include "gps.h"
// #include "errno.h"
// #include "sys/types.h"
// #include "sys/mman.h"
// #include "assert.h"
// #include "sys/stat.h"
// #include "fcntl.h"
// #include "sys/signal.h"
// #include "string.h"
// #include "stdbool.h"
// #include "datastore.h"
// #include "conversions.h"
// #include <time.h>
// #include <sys/time.h>
// #include "log.h"

// volatile int gpso;

// /**
// @author Reid Kersey <reidkersey@gmail.com> 678-736-0899

// @brief This function initializes the GPS reciver on the top usb port

// @note The GPS receiver must be plugged into USB0 (top USB port on 7800)

// @details This function initializes the GPS receiver.

// @todo increase the baud rate. The codes to do this can be found here:http://gpsd.googlecode.com/files/SiRF-SiRF-v2_4.pdf
// @todo write errors to logfile
// */

// int GPS_Init(){
	// //initialize the port configuration settings
	// struct termios config;
	
	// //Connect to the GPS device
	// gpso = open(GPSDEVICE, O_RDWR | O_NOCTTY); //gps device is the directory name of the device (usb0)
	
	// //if Not Connected
	// if(gpso < 0)
	// {
		// writeLog(CRITICAL, "GPS not initialized properly");
		// printf("ERROR\n"); 
		// //Throw Error
		// perror(GPSDEVICE);
		// return 0;
	// }

	// //allow process to receive SIGIO
	// fcntl(gpso, F_SETOWN, getpid());

	// //clear, for new port settings
	// bzero(&config, sizeof(config)); 
	
	// //configure the I/O channel for intial GPS setup
	// config.c_cflag = B4800 | CRTSCTS | CS8 | CLOCAL | CREAD | IXON;
	// config.c_iflag = IGNPAR | ICRNL;
	// config.c_oflag = 0;
	// config.c_lflag = ICANON;

	// //get rid of any remaining data
	// tcflush(gpso, TCIFLUSH);

	// //set the I/O line to the new config atributes
	// tcsetattr(gpso, TCSANOW, &config);
	// writeLog(NOTICE, "GPS device initialized successfully");
	// return 1;
// }


// /**
// @author Reid Kersey <reidkersey@gmail.com> 678-736-0899

// @brief This function gets the GPS string, and then distributes it to
// the appropriate function

// @note Currenly supported functions are RMC, GGA, and GSA
// @note Information on the NEMA strings are available here: http://www.gpsinformation.org/dale/nmea.htm#GGA

// @todo line by line comments
// */
  
// void parseGPS(){
	// //intialize the variables
	// char *segment = NULL;
	// int size;
	// char GPSstring[256] = {};
	// char GPSstringCpy[256] = {};
	
	// //read in the data
	// size = read(gpso, GPSstring, 100);
	
	// //terminate the GPS strng with an null character
	// GPSstring[size] = '\0';	
	// printf(GPSstring,"\n");
	
	// //make a copy of the string to figgure out the type of string
	// strcpy(GPSstringCpy, GPSstring);
	// segment = strtok(GPSstringCpy, GPSDELIM);
	
	// //disrubute the type string to the appropriate funciton
	// if(!strcmp(segment, GGA)){
		// parseGGA(GPSstring);
	// }else if(!strcmp(segment, RMC)){
		// parseRMC(GPSstring);
	// }
	
	// debugGPS();
// }


// /**
// @author Reid Kersey <reidkersey@gmail.com> 678-736-0899

// @brief This function takes in the heading angle, and then converts that to a cardinal direction.

// @details This function takes in the heading angle, and then converts that to a cardinal direction.
// The output will allways be two characters, to prevent the problem of having to clear the screen
// when the direction changes.

// @param angle This takes in an angle that represents the heading direction

// @return This function returns the cardinal, and ordinal directions. If the angle is not within range,
// it will return a "? ". Otherwise it will return a two character abreviation for the direction.
// */
// char* calculateHeading(double angle){
	// if((angle >= 0 && angle < 22.5) || (angle >= 337.5)){
		// return "N ";
	// }else if(angle >= 22.5 && angle < 67.5){
		// return "NE";
	// }else if(angle >= 67.5 && angle < 112.5){
		// return "E ";
	// }else if(angle >= 112.5 && angle < 157.5){
		// return "SE";
	// }else if(angle >= 157.5 && angle < 202.5){
		// return "S ";
	// }else if(angle >= 202.5 && angle < 247.5){
		// return "SW";
	// }else if(angle >= 247.5 && angle < 292.5){
		// return "W ";
	// }else if(angle >= 292.5 && angle < 337.5){
		// return "NW";
	// }
	// writeLog(ERROR, "GPS angle is out of range");
	// return "? ";
// }

// /**
// @author Reid Kersey <reidkersey@gmail.com> 678-736-0899

// @brief This function gets a RMC character string from the GPS, and then parses it

// @details This function takes in an RMC character string. From that it parses and sets
// the time, latitude longitude, speed in knots, angle, heading, and the date. If the
// data is not appropriate, the Speed indicator is set to use rpm

// @note Information on the NEMA strings are available here: http://www.gpsinformation.org/dale/nmea.htm#GGA

// @param RMC The NEMA RMC string from the GPS device.

// @todo line by line comments
// */
// void parseRMC(char * RMC){
	// //setup a way to combine latitude, and longitude with direction
	// char *segment = NULL;
	
	// //get time
	// setString("time", strtok(NULL, GPSDELIM));
	
	// //if the status is active (has a GPS fix)
	// if(!strcmp(strtok(NULL, GPSDELIM), "A")){
		// //get and set the latitude and longitude
		// char lat[254] = {}; //TODO how long do these actually need to be?
		// char lon[254] = {};
		// segment = strtok(NULL, GPSDELIM);
		// strcat(lat, segment);
		// strcat(lat, ";");
		// strcat(lat, strtok(NULL, GPSDELIM));
		// setString("latitude", lat);
		// segment = strtok(NULL, GPSDELIM);
		// strcat(lon, segment);
		// strcat(lon, ";");
		// strcat(lon, strtok(NULL, GPSDELIM));
		// setString("longitude", lon);
		
		// //get the speed
		// setFloat("speedKnots", atof(strtok(NULL, GPSDELIM)));
		// setFloat("speedMPH", getFloat("speedKnots")*1.15078);
		// //get the heading angle
		// setFloat("angle", atof(strtok(NULL, GPSDELIM)));
		
		// //set the heading in cardinal directions
		// //set the heading direction
		// setString("Heading", calculateHeading((double)getFloat("angle")));		//To do. calculateHeading function is in datalog
		
		// //set the date
		// setString("date", strtok(NULL, GPSDELIM));
		
		// //set the date and time
		// setDateTime(getString("date"), getString("time"));
	// }else
	// {
		// setTime(getString("time"));
		// setInt("useGPSData", 0);
		// //if the status is void make the speedometer use RPM TODO
		// //setUseGPSSpeed(false);
	// }
// }

// /**
// @author Reid Kersey <reidkersey@gmail.com> 678-736-0899

// @brief This function gets a GGA character string from the GPS, and then parses it.

// @details This function takes in an GGA character string. From that it parses and sets
// the time, latitude, longitude, quality, number of satilite fixes, and the altitude.
// This function will set the speedometer to RPM if the GPS fix is invalid. 

// @param GGA The NEMA GGA string from the GPS device.

// @note Information on the NEMA strings are available here: http://www.gpsinformation.org/dale/nmea.htm#GGA

// @todo line by line comments
// @todo protect the GPS quality, and GPS NumSat against overreading strtok
// */
// void parseGGA(char * GGA){
	// //initialize the variables
	// char *segment;
	// char lat[254] = {};
	// char lon[254] = {};
	
	// //set the time
	// setString("time", strtok(NULL, GPSDELIM));
	// setTime(getString("time"));
	
	// //set the latitudes and longitudes
	// segment = strtok(NULL, GPSDELIM);
	// strcat(lat, segment);
	// strcat(lat, ",");
	// strcat(lat, strtok(NULL, GPSDELIM));
	// setString("latitude", lat);
	// segment = strtok(NULL, GPSDELIM);
	// strcat(lon, segment);
	// strcat(lon, ",");
	// strcat(lon, strtok(NULL, GPSDELIM));
	// //if the longitude seems wrong (i.e. strtok was overread)
	// //make it right
	// if(!strcmp(lon, "M,0.0")){
		// setString("logintude", "0,0");
	// }else{
		// setString("longitude", lon);
	// }
	
	// //set the quality of the GPS signal (will be wrong if strtok is over read)
	// setInt("quality", atoi(strtok(NULL, GPSDELIM)));
	// //set the Number of Satalites of the GPS signal (will be wrong if strtok is over read)
	// setInt("numSats", atoi(strtok(NULL, GPSDELIM)));
	// //if the quality of the GPS signal is within range get the altitude
	// //else make the speedometer use RPM
	// if(getInt("quality") > 0){
		// //ignore the HDOP
		// strtok(NULL, GPSDELIM);
		// //set the altitude
		// setString("altitude", strtok(NULL, GPSDELIM));
	// }else
	// {
		// setInt("useGPSData", 0);
	// }
// }

// void debugGPS(){
	// printf("time: %s\n", getTime());
	// printf("date: %s\n", getDate());
	// printf("speed: %f\n", getFloat("speedKnots")*1.15078);
	// printf("lat: %s\n", getString("latitude"));
	// printf("lon: %s\n", getString("longitude"));
	// printf("alt: %f\n", getDouble("altitude"));
	// printf("angle: %f\n", getFloat("angle"));
	// printf("Heading: %s\n", getString("Heading"));
// }

// /**
// * @}
// */

