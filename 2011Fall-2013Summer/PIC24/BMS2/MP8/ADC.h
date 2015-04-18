/* 
 * File:   ADC.h
 * Author: SJ
 *
 * Created on April 8, 2013, 11:59 PM
 */

#ifndef ADC_H
#define	ADC_H

#ifdef	__cplusplus
extern "C" {
#endif

int ADCReadAvg(int channel);
int ADCReadRaw (int channel);

double readTempSensor (int channel);
double readCurrentSensor (int channel);
int checkTemperature(int channel);
int checkCurrentSensor(int channel);

void ADC_setCS(int val);
void ADC_setMOSI(int val);
int ADC_getMOSI();
void ADC_clock();
int ADC_getMISO();
int initADC();
int checkADC();

#define ADC_AVG_CYCLE (8)
#define TEMP_MAX    (55)
#define TEMP_MIN    (1)
#define TEMP_YELLOW_MAX (40)
#define TEMP_YELLOW_MIN (0)
#define CURRENT_MAX     (23)
#define CURRENT_MIN     (-19.5)
#define CURR_YELLOW_MAX ( 19.5)
#define CURR_YELLOW_MIN (-16)
#define TEMP1_CHANNEL	(0)
#define TEMP2_CHANNEL	(1)
#define TEMP3_CHANNEL	(2)
#define TEMP4_CHANNEL	(3)
#define CURR_CHANNEL	(4)




#ifdef	__cplusplus
}
#endif

#endif	/* ADC_H */

