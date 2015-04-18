
#include <stdio.h>
#include <stdlib.h>

#include "ADC.h"
#include "DIO.h"

// Initial values for ADC SPI pins
#define SPI_SS_INIT		(1)
#define SPI_CLK_INIT	(1)
#define SPI_MOSI_INIT	(0)
#define ADCSAMPLES		(7)

static int ADCreadRaw(int channel, struct ADC_device *);	// raw reading
static int ADC_calibrate(int reading, struct ADCcalibInfo calib); // calibrate a reading
static void SPIclockCycle(struct ADC_device *);


/* An initialization function to be called once per device. */
void InitADC(struct ADC_device *device)
{

	// initialize pin directions 
	InitDIO_direction(device->ss, device->ss_dir, GPIO_OUTPUT);
	InitDIO_direction(device->mosi, device->mosi_dir, GPIO_OUTPUT);
	InitDIO_direction(device->miso, device->miso_dir, GPIO_INPUT );
	InitDIO_direction(device->clk, device->clk_dir, GPIO_OUTPUT);

	// initialize outputs
	SetPin(device->mosi, device->mosi_row, SPI_MOSI_INIT);
	SetPin(device->ss, device->ss_row, SPI_SS_INIT);
	SetPin(device->clk, device->clk_row, SPI_CLK_INIT);


}

int ADCread(int channel, struct ADC_device *device)
{	/*API function for reading from the ADC.
	Averages multiple samples. */
	int i, j, mean, min = ADC_ABSOLUTE_MAX, max = 0, sum = 0;
	int samples[ADCSAMPLES];
	for (i = 0; i < ADCSAMPLES; i++) {
		j = ADCreadRaw(channel, device);
#ifdef ADC_DEBUG
		printf("ADCreadRaw (%d) returned %d\n", i, j);
#endif /* #ifdef ADC_DEBUG */
		samples[i] = j;
		if (j < min)
			min = j;
		if (j > max)
			max = j;
		sum += j;
	}
	sum -= (max + min);	//remove max and min values
	mean = sum / (ADCSAMPLES - 2);	// Take average.
#ifdef ADC_DEBUG
		printf("Average: %d\n", mean);
#endif /* #ifdef ADC_DEBUG */

	// calibrate and return
	return ADC_calibrate(mean, device->calibration_values[channel]);
}

int ADCreadRaw(int channel, struct ADC_device *device)
{	/*Return raw output of one ADC sample.
	 *See MCP3004 datasheet (section on serial communication)
         *for more info. */

	int i;
	unsigned int ret = 0;

	if ( channel > 7 ) {
		perror("invalid ADC channel selection\n");
		return -1;
	}

	// start bit: set SS low to begin sequence
	SetPin(device->ss, device->ss_row, PIN_HIGH);
	SetPin(device->ss, device->ss_row, PIN_LOW); 
	SetPin(device->mosi, device->mosi_row, PIN_HIGH);
	SPIclockCycle(device);

	// select single-ended input
	SetPin(device->mosi, device->mosi_row, PIN_HIGH);
	SPIclockCycle(device);

	// channel request (three clock cycles)
	for ( i = 0; i < 3; i++ ) {
		SetPin(device->mosi, device->mosi_row, channel & (1<<(2-i)) );
		SPIclockCycle(device);
	}

	// ignore null bit
	SPIclockCycle(device);
	SPIclockCycle(device);

	// receive response
	for( i = 0; i < 10; i++ ) {
		SPIclockCycle(device);
		ret <<= 1;
		ret |= !CheckPinRaw(device->miso, device->miso_row);

	}

	// bring SS high again to finish sequence
	SetPin(device->ss, device->ss_row, PIN_HIGH);
	return ret;
}

static int ADC_calibrate(int reading, struct ADCcalibInfo calib)
{	/* Calibrate ADC reading based on calibration data. */
	float readingFl = (float)reading;
	return (int)(((readingFl - calib.min) * (ADC_ABSOLUTE_MAX - ADC_ABSOLUTE_MIN)
		/ (calib.max - calib.min)) + ADC_ABSOLUTE_MIN);
}

static void SPIclockCycle(struct ADC_device *device)
{	/* Single clock cycle. */
	SetPin(device->clk,	device->clk_row, PIN_LOW);
	SetPin(device->clk,	device->clk_row, PIN_HIGH);
}



