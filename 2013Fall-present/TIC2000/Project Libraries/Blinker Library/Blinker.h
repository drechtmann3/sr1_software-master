/*
 * Blinker.h
 *
 *  Created on: May 7, 2014
 *      Author: rliou
 */

#ifndef BLINKER_H_
#define BLINKER_H_

//Function prototypes
__interrupt void cpu_timer0_isr(void);
__interrupt void xint1_isr(void);
void InitBlinker(void);

#endif /* BLINKER_H_ */
