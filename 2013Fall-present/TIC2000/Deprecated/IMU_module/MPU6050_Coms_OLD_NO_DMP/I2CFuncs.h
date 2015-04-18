/*
 * I2CFuncs.h
 *
 *  Created on: Nov 11, 2013
 *      Author: Alex
 */



#ifndef I2CFUNCS_H_
#define I2CFUNCS_H_

// Function prototypes:
int i2c_write_byte(Uint16 Slave_address, Uint16 Start_address, Uint16 databyte);
void i2c_read(Uint16 Slave_address, Uint16 Start_address, Uint16 No_of_databytes, Uint16 Read_Array[]);
void I2CA_Init(void);

void puts_int(char *message, int num);
void puts_float(char *message, float num);

#endif /* I2CFUNCS_H_ */
