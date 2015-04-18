#ifndef PTHREADS_H
#define PTHREADS_H
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <time.h>


void *buttons_thread(int *x);
void *wireless_thread(int *x);
void *RS485_thread(int *x);
void *USB_thread(int *x);
void *GPS_thread(int *x);
void *ADC_thread(int *x);
void *LCD_thread(int *x);

extern pthread_mutex_t date_mutex;
extern pthread_mutex_t time_mutex;
extern pthread_mutex_t cruise_mutex;
extern pthread_mutex_t blinker_mutex;
extern pthread_mutex_t rpm_mutex;
extern pthread_mutex_t regen_mutex;
extern pthread_mutex_t airgap_mutex;
extern pthread_mutex_t bms_mutex;
extern pthread_mutex_t mppt_mutex;
extern pthread_mutex_t adc_temps_mutex;
extern pthread_mutex_t adc_volts_mutex;
extern pthread_mutex_t adc_current_mutex;
extern pthread_mutex_t battery_mutex;
extern pthread_mutex_t use_gps_speed_mutex;
extern pthread_mutex_t button_db_mutex;
extern pthread_mutex_t errors_mutex;
extern pthread_mutex_t def_errors_mutex;
extern pthread_mutex_t lcd_errors_mutex;
extern pthread_mutex_t lcd_general_mutex;
extern pthread_mutex_t lcd_voltages_mutex;
extern pthread_mutex_t lcd_currents_mutex;
extern pthread_mutex_t lcd_temps_mutex;
extern pthread_mutex_t lat_mutex;
extern pthread_mutex_t longitude_mutex;
extern pthread_mutex_t heading_mutex;
extern pthread_mutex_t gps_quality_mutex;
extern pthread_mutex_t gps_numsat_mutex;
extern pthread_mutex_t gps_fix_type_mutex;
extern pthread_mutex_t altitude_mutex;
extern pthread_mutex_t gps_speed_knots_mutex;
extern pthread_mutex_t dop_mutex;
extern pthread_mutex_t hdop_mutex;
extern pthread_mutex_t vdop_mutex;
extern pthread_mutex_t angle_mutex;
extern pthread_mutex_t log_buffer_mutex;

extern pthread_mutex_t time_arr_mutex;
extern pthread_mutex_t date_arr_mutex;
extern pthread_mutex_t bms_arr_mutex;
extern pthread_mutex_t mppt_arr_mutex;
extern pthread_mutex_t adc_temps_arr_mutex;
extern pthread_mutex_t adc_volts_arr_mutex;
extern pthread_mutex_t adc_current_arr_mutex;
extern pthread_mutex_t errors_arr_mutex;
extern pthread_mutex_t def_errors_arr_mutex;
extern pthread_mutex_t lcd_errors_arr_mutex;
extern pthread_mutex_t lcd_general_arr_mutex;
extern pthread_mutex_t lcd_voltages_arr_mutex;
extern pthread_mutex_t lcd_currents_arr_mutex;
extern pthread_mutex_t lcd_temps_arr_mutex;
extern pthread_mutex_t lat_arr_mutex;
extern pthread_mutex_t long_arr_mutex;
extern pthread_mutex_t heading_arr_mutex;
extern pthread_mutex_t log_buff_arr_mutex;
#endif
