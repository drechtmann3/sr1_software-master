/*
 * MPUFunc.c
 *
 *  Created on: Nov 18, 2013
 *      Author: Alex
 */
#include "PeripheralHeaderIncludes.h"
#include "MPUFuncs.h"
#include "I2CFuncs.h"
#include "MPU6050_Constants.h"

// These values store the calibrated gyroscope offsets:
float32 gyro_x_offset;
float32 gyro_y_offset;
float32 gyro_z_offset;

// This function returns the linear acceleration of the MPU-6050, in g's.
void get_linear_acceleration(float32 lin_acc[]) {
	Uint16 ACCEL_OUT[6]; // 3 axis, and 2 bytes per axis = 6 bytes total.
	i2c_read(MPU6050_ADDRESS, MPU6050_RA_ACCEL_XOUT_H, 6, ACCEL_OUT);

	// LSB sensitivity for full scale range (LSB per g) (CURRENTLY +/-2g)
	float32 lsbpg = 16384;

	float32 *temp_pointer = lin_acc;
	temp_pointer[0] = (int)((ACCEL_OUT[0]<<8)|ACCEL_OUT[1]) / lsbpg;
	temp_pointer[1] = (int)((ACCEL_OUT[2]<<8)|ACCEL_OUT[3]) / lsbpg;
	temp_pointer[2] = (int)((ACCEL_OUT[4]<<8)|ACCEL_OUT[5]) / lsbpg;
}

// This function returns the angular velocity of the MPU-6050, in degrees/s.
void get_angular_velocity(float32 ang_vel[]) {
	Uint16 VEL_OUT[6]; // 3 axis, and 2 bytes per axis = 6 bytes total.
	i2c_read(MPU6050_ADDRESS, MPU6050_RA_GYRO_XOUT_H, 6, VEL_OUT);

	// LSB sensitivity for full scale range (LSB/degree) (CURRENTLY +/-250 deg/sec)
	float32 lsbpd = 131;

	float32 *temp_pointer = ang_vel;
	temp_pointer[0] = (int)((VEL_OUT[0]<<8)|VEL_OUT[1]) / lsbpd - gyro_x_offset;
	temp_pointer[1] = (int)((VEL_OUT[2]<<8)|VEL_OUT[3]) / lsbpd - gyro_y_offset;
	temp_pointer[2] = (int)((VEL_OUT[4]<<8)|VEL_OUT[5]) / lsbpd - gyro_z_offset;
}

// Calibrate the MPU-6050 by recording the values it currently reads.
// ASSUMING: MPU is PARALLEL to the ground and STATIONARY.
void calibrate_MPU6050() {
	gyro_x_offset = 0;
	gyro_y_offset = 0;
	gyro_z_offset = 0;
	float32 gyro_xout_sum = 0;
	float32 gyro_yout_sum = 0;
	float32 gyro_zout_sum = 0;

	int n;
	for (n = 0; n < 1000; n++) {
		float32 ang_vel[3];
		get_angular_velocity(ang_vel);
		gyro_xout_sum += ang_vel[0];
		gyro_yout_sum += ang_vel[1];
		gyro_zout_sum += ang_vel[2];

		int t;
		for (t = 0; t < 10000; t++); // Wait a bit between samples.
	}

	gyro_x_offset = gyro_xout_sum / 1000.0;
	gyro_y_offset = gyro_yout_sum / 1000.0;
	gyro_z_offset = gyro_zout_sum / 1000.0;
	puts_float("x offset: %f deg/s", gyro_x_offset);
	puts_float("y offset: %f deg/s", gyro_y_offset);
	puts_float("z offset: %f deg/s", gyro_z_offset);
}

// This function sets up the MPU-6050, and returns 1 if setup was successful.
int setup_MPU6050() {
	int sops_completed =
	//Sets sample rate to 8000/1+7 = 1000Hz
	i2c_write_byte(MPU6050_ADDRESS, MPU6050_RA_SMPLRT_DIV, 0x07) +
	//Disable FSync, 256Hz DLPF
	i2c_write_byte(MPU6050_ADDRESS, MPU6050_RA_CONFIG, 0x00) +
	//Disable gyro self tests, scale of 500 degrees/s full scale range
	i2c_write_byte(MPU6050_ADDRESS, MPU6050_RA_GYRO_CONFIG, 0x08) +
	//Disable accel self tests, scale of +-2g, no DHPF
	i2c_write_byte(MPU6050_ADDRESS, MPU6050_RA_ACCEL_CONFIG, 0x00) +
	//Freefall threshold of |0mg|
	i2c_write_byte(MPU6050_ADDRESS, MPU6050_RA_FF_THR, 0x00) +
	//Freefall duration limit of 0
	i2c_write_byte(MPU6050_ADDRESS, MPU6050_RA_FF_DUR, 0x00) +
	//Motion threshold of 0mg
	i2c_write_byte(MPU6050_ADDRESS, MPU6050_RA_MOT_THR, 0x00) +
	//Motion duration of 0s
	i2c_write_byte(MPU6050_ADDRESS, MPU6050_RA_MOT_DUR, 0x00) +
	//Zero motion threshold
	i2c_write_byte(MPU6050_ADDRESS, MPU6050_RA_ZRMOT_THR, 0x00) +
	//Zero motion duration threshold
	i2c_write_byte(MPU6050_ADDRESS, MPU6050_RA_ZRMOT_DUR, 0x00) +
	//Disable sensor output to FIFO buffer
	i2c_write_byte(MPU6050_ADDRESS, MPU6050_RA_FIFO_EN, 0x00);
	puts_int("Completed %i setup operations", sops_completed);
	if (sops_completed != 11) return 0;

	//AUX I2C setup
	sops_completed =
	//Sets AUX I2C to single master control, plus other config
	i2c_write_byte(MPU6050_ADDRESS, MPU6050_RA_I2C_MST_CTRL, 0x00) +
	//Setup AUX I2C slaves
	i2c_write_byte(MPU6050_ADDRESS, MPU6050_RA_I2C_SLV0_ADDR, 0x00) +
	i2c_write_byte(MPU6050_ADDRESS, MPU6050_RA_I2C_SLV0_REG, 0x00) +
	i2c_write_byte(MPU6050_ADDRESS, MPU6050_RA_I2C_SLV0_CTRL, 0x00) +
	i2c_write_byte(MPU6050_ADDRESS, MPU6050_RA_I2C_SLV1_ADDR, 0x00) +
	i2c_write_byte(MPU6050_ADDRESS, MPU6050_RA_I2C_SLV1_REG, 0x00) +
	i2c_write_byte(MPU6050_ADDRESS, MPU6050_RA_I2C_SLV1_CTRL, 0x00) +
	i2c_write_byte(MPU6050_ADDRESS, MPU6050_RA_I2C_SLV2_ADDR, 0x00) +
	i2c_write_byte(MPU6050_ADDRESS, MPU6050_RA_I2C_SLV2_REG, 0x00) +
	i2c_write_byte(MPU6050_ADDRESS, MPU6050_RA_I2C_SLV2_CTRL, 0x00) +
	i2c_write_byte(MPU6050_ADDRESS, MPU6050_RA_I2C_SLV3_ADDR, 0x00) +
	i2c_write_byte(MPU6050_ADDRESS, MPU6050_RA_I2C_SLV3_REG, 0x00) +
	i2c_write_byte(MPU6050_ADDRESS, MPU6050_RA_I2C_SLV3_CTRL, 0x00) +
	i2c_write_byte(MPU6050_ADDRESS, MPU6050_RA_I2C_SLV4_ADDR, 0x00) +
	i2c_write_byte(MPU6050_ADDRESS, MPU6050_RA_I2C_SLV4_REG, 0x00) +
	i2c_write_byte(MPU6050_ADDRESS, MPU6050_RA_I2C_SLV4_DO, 0x00) +
	i2c_write_byte(MPU6050_ADDRESS, MPU6050_RA_I2C_SLV4_CTRL, 0x00) +
	i2c_write_byte(MPU6050_ADDRESS, MPU6050_RA_I2C_SLV4_DI, 0x00);
	puts_int("Completed %i setup operations", sops_completed);
	if (sops_completed != 18) return 0;

	sops_completed =
	//Setup INT pin and AUX I2C pass through
	i2c_write_byte(MPU6050_ADDRESS, MPU6050_RA_INT_PIN_CFG, 0x00) +
	//Enable data ready interrupt
	i2c_write_byte(MPU6050_ADDRESS, MPU6050_RA_INT_ENABLE, 0x00) +

	//Slave out, dont care
	i2c_write_byte(MPU6050_ADDRESS, MPU6050_RA_I2C_SLV0_DO, 0x00) +
	i2c_write_byte(MPU6050_ADDRESS, MPU6050_RA_I2C_SLV1_DO, 0x00) +
	i2c_write_byte(MPU6050_ADDRESS, MPU6050_RA_I2C_SLV2_DO, 0x00) +
	i2c_write_byte(MPU6050_ADDRESS, MPU6050_RA_I2C_SLV3_DO, 0x00) +
	//More slave config
	i2c_write_byte(MPU6050_ADDRESS, MPU6050_RA_I2C_MST_DELAY_CTRL, 0x00) +
	//Reset sensor signal paths
	i2c_write_byte(MPU6050_ADDRESS, MPU6050_RA_SIGNAL_PATH_RESET, 0x00) +
	//Motion detection control
	i2c_write_byte(MPU6050_ADDRESS, MPU6050_RA_MOT_DETECT_CTRL, 0x00) +
	//Disables FIFO, AUX I2C, FIFO and I2C reset bits to 0
	i2c_write_byte(MPU6050_ADDRESS, MPU6050_RA_USER_CTRL, 0x00) +
	//Sets clock source to gyro reference w/ PLL
	i2c_write_byte(MPU6050_ADDRESS, MPU6050_RA_PWR_MGMT_1, 0x02) +
	//Controls frequency of wakeups in accel low power mode plus the sensor standby modes
	i2c_write_byte(MPU6050_ADDRESS, MPU6050_RA_PWR_MGMT_2, 0x00) +

	//Data transfer to and from the FIFO buffer
	i2c_write_byte(MPU6050_ADDRESS, MPU6050_RA_FIFO_R_W, 0x00);
	puts_int("Completed %i setup operations", sops_completed);
	if (sops_completed != 13) return 0;

	return 1; // MPU6050 setup complete.
}

// This function returns the status of the MPU-6050 IMU:
// 0: Not connected/connection problems
// 1: Connected & ready
int get_MPU6050_status() {
	// To check if the MPU6050 is working, attempt to read the byte
	// at memory register 0x75 (MPU6050_RA_WHO_AM_I) on the IMU. This should
	// give 0x68, if all is working correctly.

	Uint16 received_data[1];
	received_data[0] = 0x00;
	// We are now sending a read query to the MPU address, to the WHO_AM_I register (0x75), which should contain 0x68.
	puts_int("Sending out to I2C address 0x%x", MPU6050_ADDRESS);
	puts_int("Sending read query on I2C line for register 0x%x on MPU...", MPU6050_RA_WHO_AM_I);
	i2c_read(MPU6050_ADDRESS, MPU6050_RA_WHO_AM_I, 1, received_data);
	puts_int("Received from I2C: %x", received_data[0]);

	if (received_data[0] == 0x68) {
		return 1;
	}
	return 0;
}



