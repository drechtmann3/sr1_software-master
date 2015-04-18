/* ADC polling (via software SPI) of the MCP3004/8 10-bit ADC.
 * See the MCP3004 datasheet for more info.*/

#ifndef ADC_H
#define ADC_H

#define ADC_ABSOLUTE_MAX	(float)(1023)
#define ADC_ABSOLUTE_MIN	(float)(0)

#define MCP3008_NUMCHANNELS    (8)

struct ADCcalibInfo {
/* ADC channel calibration info for one channel */
	int max;
	int min;
} ;

struct ADC_device {
	/* Maps DIO pins to MCP3004/8 pins. One of these structs should
	   be set up per device. The row entries should be set using
	   row offsets as defined by the DIO module. */

	unsigned int ss;   // chip select
	unsigned int ss_row;
	unsigned int ss_dir;

	unsigned int clk;  // clock
	unsigned int clk_row;
	unsigned int clk_dir;

	unsigned int mosi; // master data out
	unsigned int mosi_row;
	unsigned int mosi_dir;

	unsigned int miso; // master data in
	unsigned int miso_row;
	unsigned int miso_dir;

	struct ADCcalibInfo calibration_values[8];
} ;

void InitADC(struct ADC_device *device); /* called once per device */
int ADCread(int channel, struct ADC_device *device);	/* uncalibrated reading */


#endif
