/* Interface module to more easily use lib7800. */

#ifndef WRAPPER_H
#define WRAPPER_H

/* DIO pin assigments for the control computer. */
// GPIO row A
	//ADC
#define SPI_CLK 			(0)
#define SPI_MISO 			(1)
#define SPI_MOSI 			(2)
#define SPI_SS				(3)
	//Motor state control - Go to button connectors
#define COMMAND_SPEED_UP 	(4)		/*Goes to con 43*/
#define COMMAND_SPEED_DOWN (5)		/*Goes to con 44*/
#define COMMAND_BRAKE 		(6)		/*Brake indicator. Goes to con 45*/
#define COMMAND_CRUISE 		(7)		/*Goes to con 46*/
	//Airgap state control
#define GAP_MOTOR_PWR		(8)	/*Goes to con 62*/
#define GAP_MOTOR_DIR		(9)	/*Goes to con 63*/
//Go to button connectors
#define COMMAND_AIRGAP_OPEN 	(10)  /*Goes to con 47*/
#define COMMAND_AIRGAP_CLOSE 	(11)  /*Goes to con 48*/
	//Software killswitch
#define KILLSWITCH			(12)        /*Goes to con 49*/
#define Blinker1			(13)
#define Blinker2			(14)
#define Blinker3			(15)
#define AIRGAP_KILLSWITCH	(16)	   /*Not wired to outside enclosure*/
	//total number of GPIO pins used
#define TOTAL_GPIO			(17)
	//Control-specific GPIO pin assignments
#define CONTROL_GPIO_DAT_ROW	GPIO_DAT_A
#define CONTROL_GPIO_DIR_ROW	GPIO_DIR_A
/* input/output values */
#define GPIO_OUTPUT (1)
#define GPIO_INPUT (0)



/* ADC Channel assignments */
#define CHAN_THR			(0)
#define CHAN_REGEN			(1)
#define CHAN_GAP			(2)
#define TOTAL_ADC_CHANNELS 	(3)

// ADC channel-specific calibration values
	/*  TODO set up calibration values here. The calibration values are
	 * to be determined using the ADCtest program.
	 */
#define CHAN_THR_MAX	(1024)
#define CHAN_THR_MIN	(0)
#define CHAN_REGEN_MAX	(1024)
#define CHAN_REGEN_MIN	(0)
#define CHAN_GAP_MAX	(1024)
#define CHAN_GAP_MIN	(0)

#endif /* #ifndef WRAPPER_H */
