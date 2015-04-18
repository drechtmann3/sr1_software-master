/**
* @defgroup telemetry Telemetry
* @author Reid Kersey <reidkersey@gmail.com> 678-736-0899 4/23/12-Current
* @author Andrey Kurenkov <akurenkov3@gatech.edu> 
* @brief HMI/Telemetry code
* @details
* The HMI/Telemetry code is created for use on the GT Solar Car.
* The code will contain methods for use on the telemetry system, and for
* updating the lcd screens. The code should interface with an Xtend wireless
* radio, simple push buttons, RS-485 based on the Solar Jackets RS-485
* protocol, and numerous sensors interfacing through the Solar Jackets
* ADC Board. This codes purpose will be to log and report data to the 
* appropriate systems. 
* 
* @todo RS-485
* @todo USB-logging
* @todo lcd based on data
* @todo make the project description on more readable
* 
* @{
*/

#include <stdio.h>
#include <pthread.h>
#include "pthreads.h"
#include "ADC.h"
#include "DIO.h"
#include "lcd.h"
#include "gps.h"
#include "wireless.h"
#include "usb.h"
#include "buttons.h"
#include "datalog.h"
#include "main.h"

int main()
{
	/* Initialization */
	InitDIO(TOTALPINS);
	//InitLCD();
	/* End initialization */
	pthread_mutex_init(&data_mutex, NULL);
	pthread_mutex_init(&ADC_mutex, NULL);
	
	pthread_t pthread_RS485, pthread_ADC, pthread_LCD, pthread_GPS, pthread_buttons, pthread_wireless, pthread_USB;
	int i1 = 1; //an arguement
	initDataLog();
	pthread_create(&pthread_ADC, NULL, (void *) &ADC_thread, &i1);
	pthread_create(&pthread_RS485, NULL, (void *) &RS485_thread, &i1);
	pthread_create(&pthread_LCD, NULL, (void *) &LCD_thread, &i1);
	pthread_create(&pthread_GPS, NULL, (void *) &GPS_thread, &i1);
	pthread_create(&pthread_buttons, NULL, (void *) &buttons_thread, &i1);
	pthread_create(&pthread_wireless, NULL, (void *) &wireless_thread, &i1);
	pthread_create(&pthread_USB, NULL, (void *) &USB_thread, &i1);

	pthread_join(pthread_RS485, NULL);
	pthread_join(pthread_ADC, NULL);
	pthread_join(pthread_LCD, NULL);
	pthread_join(pthread_GPS, NULL);
	pthread_join(pthread_buttons, NULL);
	pthread_join(pthread_wireless, NULL);
	pthread_join(pthread_USB, NULL);
	return 1;
}


/**
* @}
*/
