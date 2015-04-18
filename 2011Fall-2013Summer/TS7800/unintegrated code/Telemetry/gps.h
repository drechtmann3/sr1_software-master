#ifndef GPS_H
#define GPS_H

	#define GPSDEVICE 		"/dev/ttyUSB0" 	//The USB tty (top port)
	#define MAX_DOP			(3)				//The maximum amount of acceptiable dilution of precision
	#define MIN_GPS_SPEED	(10)			//The lowest speed for acurate GPS speed calculations
	
	//The begining of each string
	static const char GGA[7] = "$GPGGA";
	static const char RMC[7] = "$GPRMC";
	static const char GSA[7] = "$GPGSA";
	static const char GPSDELIM[] = ",*";
	
	//Funciton initilaizations
	int initGPS();
	char* calculateHeading(double angle);
	void parseGPS();
	void parseGGA(char * GGA);
	void parseRMC(char * RMC);
	void parseGSA(char * GSA);
	
#endif
