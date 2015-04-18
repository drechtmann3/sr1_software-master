/* 
 * File:   relay.h
 * Author: SJ
 *
 * Created on April 9, 2013, 12:04 AM
 */

#ifndef RELAY_H
#define	RELAY_H

#ifdef	__cplusplus
extern "C" {
#endif

void setRelay(int status);
#define RELAY_ON (1)
#define RELAY_OFF (0)

#ifdef	__cplusplus
}
#endif

#endif	/* RELAY_H */

