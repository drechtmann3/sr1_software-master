/*
 * I2CForDS2484.h
 *
 *  Created on: Apr 5, 2014
 *      Author: Alex
 */

#ifndef I2CFORDS2484_H_
#define I2CFORDS2484_H_

//PROTOTYPES
Uint16 i2c_read_data_byte(char NACKSTOPTreatment); //Read a data byte from the I2C line
char i2c_send_data_byte(Uint16 data); //Send a command/data byte over the I2C Line
char i2c_send_start_and_slave_address(Uint16 slave_address, int rwbit); //Send start condition over I2C Line
void i2c_status(void); //Prints out useful information about I2C state
void i2c_init(void); //Initialize I2C on microcontroller
char getBitFromByte(Uint16 byte, char bitnum); //Get the ith bit from the passed byte


#endif /* I2CFORDS2484_H_ */
