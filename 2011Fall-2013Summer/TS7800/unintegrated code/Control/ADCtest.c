#include <stdlib.h>
#include <stdio.h>
#include "wrapper.h"
#include "DIO.h"
#include "ADC.h"

/**
@author Matt Olson <matt.a.olson@gmail.com> 404-680-0566

@brief testing of ADC functionality. Use the pin assignments in wrapper. to connect the MCP3008 ADC.

@return 0 if good
*/
int main(int argc, char *argv[])
{
	static struct ADC_device adc0 = {
		.ss = SPI_SS,
		.ss_row = GPIO_DAT_A,
		.ss_dir = GPIO_DIR_A,

		.clk = SPI_CLK,
		.clk_row = GPIO_DAT_A,
		.clk_dir = GPIO_DIR_A,

		.mosi = SPI_MOSI,
		.mosi_row = GPIO_DAT_A,
		.mosi_dir = GPIO_DIR_A,

		.miso = SPI_MISO,
		.miso_row = GPIO_DAT_A,
		.miso_dir = GPIO_DIR_A,

		/* Leave these values at full range; this program is to
		 * be used to find the proper calibration values for
		 * the production build.
		 */
		.calibration_values[0] = {
				.min = ADC_ABSOLUTE_MIN,
				.max = ADC_ABSOLUTE_MAX
		},
		.calibration_values[1] = {
				.min = ADC_ABSOLUTE_MIN,
				.max = ADC_ABSOLUTE_MAX
		},
		.calibration_values[2] = {
				.min = ADC_ABSOLUTE_MIN,
				.max = ADC_ABSOLUTE_MAX
		}
	};

	int channel;
	if (argc != 2) {
		printf("Defaulting on channel 0\n");
		channel = 0;
	} else {
		channel = atoi(argv[1]);
	}

	InitDIO(TOTAL_GPIO);
	InitADC(&adc0);

	ADCread(channel, &adc0);

	return 0;
}
