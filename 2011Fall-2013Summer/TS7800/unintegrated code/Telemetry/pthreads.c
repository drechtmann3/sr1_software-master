/**
* @ingroup telemetry
* @defgroup pthread PThread
* @brief PThread functions
* 
* @{
*/

#include "pthreads.h"
#include "datalog.h"
#include <unistd.h>
#include <stdio.h>
#include "lcd.h"
#include "gps.h"
#include "usb.h"
#include "RS485BMSCom.h"
#include "ADC.h"
#include "wireless.h"


static struct LCD_screen LCD_speed = {  
		.ss = LCD_SPEED_SS,
		.ss_row = GPIO_DAT_A,

		.clk = LCD_SPEED_CLK,
		.clk_row = GPIO_DAT_A,

		.mosi = LCD_SPEED_MOSI,
		.mosi_row = GPIO_DAT_A,

		.A0 = LCD_SPEED_A0,
		.A0_row = GPIO_DAT_A,

		.page = SPEED_PAGE,
		.errorPage = 0,
		.pageSwitch = 1,
		.clear = 1,
		.reset = 0,

		.speed = 0,
		.cruise = 0,
		.blinker = 0,
		.battery = 0,
		.speedType = RPM_TYPE
};
static struct LCD_screen LCD_error = {  
		.ss = LCD_ERROR_SS,
		.ss_row = GPIO_DAT_A,

		.clk = LCD_ERROR_CLK,
		.clk_row = GPIO_DAT_A,

		.mosi = LCD_ERROR_MOSI,
		.mosi_row = GPIO_DAT_A,

		.A0 = LCD_ERROR_A0,
		.A0_row = GPIO_DAT_A,

		.page = 1,
		.errorPage = 0,
		.pageSwitch = 1,
		.clear = 1,
		.reset = 0,

		.speed = 0,
		.cruise = 0,
		.blinker = 0,
		.battery = 0,
		.speedType = RPM_TYPE
};
static struct ADC_device ADCPinz = {
		.ss = 3,
		.ss_row = GPIO_DAT_A,

		.clk = 0,
		.clk_row = GPIO_DAT_A,

		.mosi = 2,
		.mosi_row = GPIO_DAT_A,

		.miso = 1,
		.miso_row = GPIO_DAT_A
};
static struct WirelessPins wireless = {
		.uart = "/dev/ttts6",
		.baud = B115200,
		.cmd = 15,
		.cmd_row = GPIO_DAT_A
};

pthread_mutex_t date_mutex;
pthread_mutex_t time_mutex;
pthread_mutex_t cruise_mutex;
pthread_mutex_t blinker_mutex;
pthread_mutex_t rpm_mutex;
pthread_mutex_t regen_mutex;
pthread_mutex_t airgap_mutex;
pthread_mutex_t bms_mutex;
pthread_mutex_t mppt_mutex;
pthread_mutex_t adc_temps_mutex;
pthread_mutex_t adc_volts_mutex;
pthread_mutex_t adc_current_mutex;
pthread_mutex_t battery_mutex;
pthread_mutex_t use_gps_speed_mutex;
pthread_mutex_t button_db_mutex;
pthread_mutex_t errors_mutex;
pthread_mutex_t def_errors_mutex;
pthread_mutex_t lcd_errors_mutex;
pthread_mutex_t lcd_general_mutex;
pthread_mutex_t lcd_voltages_mutex;
pthread_mutex_t lcd_currents_mutex;
pthread_mutex_t lcd_temps_mutex;
pthread_mutex_t lat_mutex;
pthread_mutex_t longitude_mutex;
pthread_mutex_t heading_mutex;
pthread_mutex_t gps_quality_mutex;
pthread_mutex_t gps_numsat_mutex;
pthread_mutex_t gps_fix_type_mutex;
pthread_mutex_t altitude_mutex;
pthread_mutex_t gps_speed_knots_mutex;
pthread_mutex_t dop_mutex;
pthread_mutex_t hdop_mutex;
pthread_mutex_t vdop_mutex;
pthread_mutex_t angle_mutex;
pthread_mutex_t log_buffer_mutex;
pthread_mutex_t time_arr_mutex;
pthread_mutex_t date_arr_mutex;
pthread_mutex_t bms_arr_mutex;
pthread_mutex_t mppt_arr_mutex;
pthread_mutex_t adc_temps_arr_mutex;
pthread_mutex_t adc_volts_arr_mutex;
pthread_mutex_t adc_current_arr_mutex;
pthread_mutex_t errors_arr_mutex;
pthread_mutex_t def_errors_arr_mutex;
pthread_mutex_t lcd_errors_arr_mutex;
pthread_mutex_t lcd_general_arr_mutex;
pthread_mutex_t lcd_voltages_arr_mutex;
pthread_mutex_t lcd_currents_arr_mutex;
pthread_mutex_t lcd_temps_arr_mutex;
pthread_mutex_t lat_arr_mutex;
pthread_mutex_t long_arr_mutex;
pthread_mutex_t heading_arr_mutex;
pthread_mutex_t log_buff_arr_mutex;

/**
@author Reid Kersey <reidkersey@gmail.com> 678-736-0899

@brief This function initializes the mutexes for use by the pthread

@details The only purpose of this function is to initialize the mutexes.
The mutexes are defined in pthreads.h, as externals, and they are "initialized"
at the top of pthreads.c.

@warning This function must be called before starting any thread that uses mutexes
 */
void initMutex(){
	pthread_mutex_init(&date_mutex, NULL);
	pthread_mutex_init(&time_mutex, NULL);
	pthread_mutex_init(&cruise_mutex, NULL);
	pthread_mutex_init(&blinker_mutex, NULL);
	pthread_mutex_init(&rpm_mutex, NULL);
	pthread_mutex_init(&regen_mutex, NULL);
	pthread_mutex_init(&airgap_mutex, NULL);
	pthread_mutex_init(&bms_mutex, NULL);
	pthread_mutex_init(&mppt_mutex, NULL);
	pthread_mutex_init(&adc_temps_mutex, NULL);
	pthread_mutex_init(&adc_volts_mutex, NULL);
	pthread_mutex_init(&adc_current_mutex, NULL);
	pthread_mutex_init(&battery_mutex, NULL);
	pthread_mutex_init(&use_gps_speed_mutex, NULL);
	pthread_mutex_init(&button_db_mutex, NULL);
	pthread_mutex_init(&errors_mutex, NULL);
	pthread_mutex_init(&def_errors_mutex, NULL);
	pthread_mutex_init(&lcd_errors_mutex, NULL);
	pthread_mutex_init(&lcd_general_mutex, NULL);
	pthread_mutex_init(&lcd_voltages_mutex, NULL);
	pthread_mutex_init(&lcd_currents_mutex, NULL);
	pthread_mutex_init(&lcd_temps_mutex, NULL);
	pthread_mutex_init(&lat_mutex, NULL);
	pthread_mutex_init(&longitude_mutex, NULL);
	pthread_mutex_init(&heading_mutex, NULL);
	pthread_mutex_init(&gps_quality_mutex, NULL);
	pthread_mutex_init(&gps_numsat_mutex, NULL);
	pthread_mutex_init(&gps_fix_type_mutex, NULL);
	pthread_mutex_init(&altitude_mutex, NULL);
	pthread_mutex_init(&gps_speed_knots_mutex, NULL);
	pthread_mutex_init(&dop_mutex, NULL);
	pthread_mutex_init(&hdop_mutex, NULL);
	pthread_mutex_init(&vdop_mutex, NULL);
	pthread_mutex_init(&angle_mutex, NULL);
	pthread_mutex_init(&log_buffer_mutex, NULL);
	pthread_mutex_init(&time_arr_mutex, NULL);
	pthread_mutex_init(&date_arr_mutex, NULL);
	pthread_mutex_init(&bms_arr_mutex, NULL);
	pthread_mutex_init(&mppt_arr_mutex, NULL);
	pthread_mutex_init(&adc_temps_arr_mutex, NULL);
	pthread_mutex_init(&adc_volts_arr_mutex, NULL);
	pthread_mutex_init(&adc_current_arr_mutex, NULL);
	pthread_mutex_init(&errors_arr_mutex, NULL);
	pthread_mutex_init(&def_errors_arr_mutex, NULL);
	pthread_mutex_init(&lcd_errors_arr_mutex, NULL);
	pthread_mutex_init(&lcd_general_arr_mutex, NULL);
	pthread_mutex_init(&lcd_voltages_arr_mutex, NULL);
	pthread_mutex_init(&lcd_currents_arr_mutex, NULL);
	pthread_mutex_init(&lcd_temps_arr_mutex, NULL);
	pthread_mutex_init(&lat_arr_mutex, NULL);
	pthread_mutex_init(&long_arr_mutex, NULL);
	pthread_mutex_init(&heading_arr_mutex, NULL);
	pthread_mutex_init(&log_buff_arr_mutex, NULL);
}

/**
@author Reid Kersey <reidkersey@gmail.com> 678-736-0899

@brief This thread continously checks for button presses.

@details This thread continously checks for button presses. If one is found,
it waits .1 seconds then continues checking

@todo only change page once button has been released
@todo test with lcd screens
 */
void *buttons_thread(int *x){
	while(1){
		LCDButtonPush(&LCD_error);
		if(getButtonDB()){
			usleep(500000);
			setButtonDB(0);
		}
		usleep(100);
	}
}

/**
@author Reid Kersey <reidkersey@gmail.com> 678-736-0899

@brief This thread will send data over the xtend radio to the
telemetry computer.

@details This thread will send data over the xtend radio to the
telemetry computer.

@todo everything
 */
void *wireless_thread(int *x){
	if(initWireless(&wireless)){
		while(1){

		}
	}
	printf("WIRELESS ERROR\n");
	return "okay";
}

/**
@author Reid Kersey <reidkersey@gmail.com> 678-736-0899

@brief This thread logs data to the usb stick

@details This thread first initailizes the usb sitck, and 
then at intervals of .1 seconds logs relevent data that is
stored in the datalog.c file. This thread will not execute
if the usb stick can not be mounted

@todo write error when usb stick can not be mounted
 */
void *USB_thread(int *x){
	if(initUSB()){
		usleep(100000);
		while(1){
			writeEssentials();
			writeCVT();
			writeGPS();
			writeLog();
			usleep(100000);
		}
	}
	printf("USB ERROR\n");
	return "okay";
}

/**
@author Reid Kersey <reidkersey@gmail.com> 678-736-0899

@brief This thread logs gps data into datalog.c

@details This thread will initialize the GPS, and then
it will write data to datalog.c when the data comes in.
The information gathered is used to set time and date
stamps on log files, and for race logistics/diagnostic
purposes

@todo write error if the gps fails to initialize
 */
void *GPS_thread(int *x){
	if(initGPS())
	{
		while(1){
			parseGPS();
			usleep(100000);
		}
	}
	return "okay";
}

/**
@author Reid Kersey <reidkersey@gmail.com> 678-736-0899

@brief This thread logs ADC data into datalog.c

@details This thread will initialize the ADC spi bus, 
and then it will write data to datalog.c when the data comes in.
The information gathered is used as diagnostic information.

@todo write error if the ADC fails to initialize
@todo write error for out of range values
 * @todo make it work?
 */
void *ADC_thread(int *x){
	int i;
	while(1){
		InitADC(&ADCPinz);
		for(i = 0; i < 8; i++){
			//printf("ADC CH: %d = %d\n", i, ADCread(i, &ADCPinz));
		}
	}
	return NULL;
}

/**
@author Andrey Kurenkov <akurenkov3@gatech.edu> 

@brief Sends pings and collects data from the RS-485 line

@details This data will send infomation pings to pic 
and then it will write data to datalog.c when the data comes in.
The information gathered is used as diagnostic information.
 */
void *RS485_thread(int *x){
	initPicCom();
	int i;
	while(1) {
		char device;
		char addressNum;
		char response[RS_485_BMS_STATUS_RESPONSE_LENGTH-3];

		pingPics(&device,&addressNum,response);
		if(device=='B') {//if BMS
			int deviceNum=addressNum;
			double vars[RS_485_BMS_DATA_VARS];
			for(i=0;i<20;i+=4) {//First vars need to be handled specially as doubles
				char asciiVal[5]={response[i],response[i+1],response[i+2],response[i+3], 0 };
				vars[i/4]=((double)ASCIIToHex(asciiVal))/10;
			}
			for(i=20;i<(RS_485_BMS_STATUS_RESPONSE_LENGTH-CMD_LENGTH);i+=4){
				char asciiVal[5]={response[i],response[i+1],response[i+2],response[i+3], 0 };
				vars[i/4]=(double)ASCIIToHex(asciiVal);
			}
			setBMS(vars,deviceNum);
		} else {//otherwise Control computer
			double* vars;
			for(i=0;i>(RS_485_MC_STATUS_RESPONSE_LENGTH-CMD_LENGTH);i+=8){
				char asciiVal[8];
				snprintf(asciiVal,9,"%s",response+i);
				vars[i/8]=ASCIIToHex(asciiVal);
			}
			void setCruise(int cruise);
			//void setBlinker(int blinker); no state for blinker?
			setRPM(vars[0]);
			//void setRegen(int regen);
			setAirgap(vars[1]);

		}

	}
	endPicCom();
	return 0;
}


/**
@author Reid Kersey <reidkersey@gmail.com> 678-736-0899

@brief This thread updates the lcd screens

@details This thread will initialize the LCD screens, and
then it will start writing to them data from datalog.c.


 */
void *LCD_thread(int *x){
	InitLCD(&LCD_speed);
	InitLCD(&LCD_error);
	InitSpeed(&LCD_speed);
	while(1){
		updateLCD(&LCD_speed);
		updateLCD(&LCD_error);
		if(LCD_error.reset == 1 || LCD_speed.reset == 1){
			displayReset(&LCD_error);
			displayReset(&LCD_speed);
			InitSpeed(&LCD_speed);
		}
		usleep(100);
	} 

}

/**
* @}
*/
