/* Interface module to more easily use lib7800. */

#ifndef WRAPPER_H
#define WRAPPER_H
#include "datalog.h"
#include "lcd.h"
// Pin assignments (GPIO row A)
#define LCD_ERROR_CLK			(0)	/*Goes to con 53*/
#define LCD_ERROR_MOSI 			(1)   /*Goes to con 54*/
#define LCD_ERROR_A0	 			(2)	/*Should be 55*/
#define LCD_ERROR_SS				(3)	/*Should 56*/
#define LCD_SPEED_CLK			(0)	/*Goes to con 53*/
#define LCD_SPEED_MOSI 			(1)   /*Goes to con 54*/
#define LCD_SPEED_A0	 			(2)	/*Should be 55*/
#define LCD_SPEED_SS				(4)	/*Should be 57*/
#define BUTTON_LEFT_PIN			(5)   /*Goes to con 50*/
#define BUTTON_CENTER_PIN		(6)   /*Goes to con 51*/
#define BUTTON_RIGHT_PIN		(7)   /*Goes to con 52*/

//SPI - 1 through 6 is left to right
#define SPI1						(8)
#define SPI2						(9)
#define SPI3						(10)
#define SPI4						(11)
#define SPI5						(12)
#define SPI6						(13)

#define Blinker1						(14)
#define Blinker2						(15)
#define Blinker3	 	 				(16)

#define Blinker1						(14)
#define Blinker2						(15)
#define Blinker3	 	 				(16)

#define WIFI_GPO2_RXLed			   (17)
#define WIFI_DI			   		(18)
#define WIFI_DO			   		(19)
#define WIFI_GPI1_RTS_CMD   		(20)

#define COMPUTER_BOX_TEMP_INDEX	(0)
#define BMS_TEMP_INDEX			(0)
#define MPPT_TEMP_INDEX			(0)
#define BMS_CURRENT_INDEX		(0)
#define MPPT_CURRENT_INDEX		(0)
#define BMS_VOLT_INDEX			(0)
#define MPPT_VOLT_INDEX			(0)
#define NUM_MPPT_CURRENTS		(0)
#define NUM_MPPT_VOLTS			(0)
#define NUM_MPPT_TEMPS			(0)
#define NUM_BMS_CURRENTS		(0)
#define NUM_BMS_VOLTS			(0)
#define NUM_BMS_TEMPS			(0)
#define WHEEL_RADIUS			(.77083)

/* input/output values */
#define GPIO_OUTPUT (1)
#define GPIO_INPUT (0)





#endif
