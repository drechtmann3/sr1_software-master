/* 
 * File:   main.h
 * Author: SJ
 *
 * Created on April 8, 2013, 11:59 PM
 */

#ifndef MAIN_H
#define	MAIN_H

#ifdef	__cplusplus
extern "C" {
#endif

#define GREEN_STATUS        (1)
#define OVERTEMP_STATUS     (2)
#define OVERCURRENT_STATUS  (4)
#define YELLOW_STATUS       (6)
#define RED_STATUS          (8)

void configPins();
void configSPI1();
void configClock();

#ifdef	__cplusplus
}
#endif

#endif	/* MAIN_H */

