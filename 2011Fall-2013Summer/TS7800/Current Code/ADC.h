#ifndef ADC_H
#define ADC_H

// Initial values for ADC SPI pins
#define ADC_SS_INIT     (1)
#define ADC_CLK_INIT    (1)
#define ADC_MOSI_INIT   (0)
#define AVG_SIZE		(1500)
#define MAX_RESET		(10)

// Function Definitions
void InitADC();
int ADCReadRaw(int channel);
int TempSensor(int channel);
void ADC_SPIclockCycle();
int ADCAverage(int channel, int numForAverage);
double sum(int num_array1[], int start, int end);
void averagePedal();
#endif

