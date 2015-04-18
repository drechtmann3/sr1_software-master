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
void clock();
double readTempSensor (int channel);
double readCurrentSensor (int channel);
int checkTemperature(int channel);
int checkCurrentSensor(int channel);


#define ADC_AVG_CYCLE (8)
#define TEMP_MAX    (55)
#define TEMP_MIN    (-18)
#define TEMP_YELLOW_MAX (40)
#define TEMP_YELLOW_MIN (0)
#define CURRENT_MAX     (25)
#define CURRENT_MIN     (-19.5)
#define CURR_YELLOW_MAX ( 19.5)
#define CURR_YELLOW_MIN (-16)
#



#ifdef	__cplusplus
}
#endif

#endif	/* ADC_H */

