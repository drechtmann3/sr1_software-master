/*
 * I2CForDS2484.h
 *
 *  Created on: Apr 5, 2014
 *      Author: Alex
 */

#include "PeripheralHeaderIncludes.h"
#include <stdio.h>
#include "F2806x_Device.h"

#ifndef I2CFORDS2484_H_
#define I2CFORDS2484_H_

Uint16 i2c_read_data_byte(char NACKSTOPTreatment);
char i2c_send_data_byte(Uint16 data);
char i2c_send_start_and_slave_address(Uint16 slave_address, int rwbit);
void i2c_status(void);
void i2c_init(void);
char getBitFromByte(Uint16 byte, char bitnum);


#endif /* I2CFORDS2484_H_ */
