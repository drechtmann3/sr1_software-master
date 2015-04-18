/* 
 * File:   LED.h
 * Author: SJ
 *
 * Created on April 8, 2013, 11:59 PM
 */

#ifndef LED_H
#define	LED_H

#ifdef	__cplusplus
extern "C" {
#endif



void red(int in);
void yellow1(int in);
void yellow2(int in);
void green(int in);
void setStatusLEDs(int status);

#ifdef	__cplusplus
}
#endif

#endif	/* LED_H */

