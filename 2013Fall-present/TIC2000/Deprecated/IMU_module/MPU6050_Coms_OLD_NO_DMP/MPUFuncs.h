/*
 * MPUFuncs.h
 *
 *  Created on: Nov 18, 2013
 *      Author: Alex
 */

#ifndef MPUFUNCS_H_
#define MPUFUNCS_H_

void get_linear_acceleration(float32 lin_acc[]);
void get_angular_velocity(float32 ang_vel[]);

void calibrate_MPU6050();
int setup_MPU6050();
int get_MPU6050_status();



#endif /* MPUFUNCS_H_ */
