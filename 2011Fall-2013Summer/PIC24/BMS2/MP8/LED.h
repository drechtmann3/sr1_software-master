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



void setCritical(int in);
void setWarn1(int in);
void setWarn2(int in);

#define LED_ON	(1)
#define LED_OFF	(0)

#ifdef	__cplusplus
}
#endif

#endif	/* LED_H */

