/* 
 * File:   rs485.h
 * Author: SJ
 *
 * Created on April 9, 2013, 12:04 AM
 */

#ifndef RS485_H
#define	RS485_H

#ifdef	__cplusplus
extern "C" {
#endif

#define BAUDRATE (9600)

void UART1PutChar(char Ch);

#ifdef	__cplusplus
}
#endif

#endif	/* RS485_H */

