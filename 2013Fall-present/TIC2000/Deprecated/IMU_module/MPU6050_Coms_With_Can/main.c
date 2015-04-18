#include "IMU_Interface.h"
#include "CAN.h"

// Function prototype for Piccolo initialization routine:
void DeviceInit(void);

//USER DEFINED CAN_INFO ARRAY
void imu_send_isr(){
	char string[] = "Sent";
	puts(string);
}

void imu_receive_isr(CAN_ID ID, Uint32 dataH, Uint32 dataL,Uint16 length, int mbox_num){
	char string[32];
	sprintf(string, "Received %d %d", dataH, dataL);
	puts(string);
}

CAN_INFO IMU_CAN_ARRAY[] = {
		{
				IMU,
				&imu_send_isr,
				&imu_receive_isr
		}
};


typedef union ufloat {
  float32 f;
  Uint32 u;
}ufloat;

int main(void) {
	DeviceInit(); // Initialize ports and modules on microcontroller.
	// Set up the IMU subsystem, and check that it went OK:
	if (imu_subsystem_setup() != 1)
		puts("Error setting up IMU!");
	// Set up the CAN system:
	CAN_init(IMU_CAN_ARRAY, 1);
	CAN_receive(IMU, 8, 31, 0);

	while (1) {
		 imu_read_data read_data = imu_subsystem_get_data_samples( 2 );

		 /*char string[32];
		 sprintf(string, "Temp: %d F", (int)read_data.temp);
		 sprintf(string, "roll:%d pitch:%d yaw:%d  x:%d y:%d z:%d  norm:%d  temp:%d", (int)(read_data.roll), (int)(read_data.pitch), (int)(read_data.yaw),
				 (int)(read_data.x_acc*1000), (int)(read_data.y_acc*1000), (int)(read_data.z_acc*1000), (int)(read_data.lin_acc*1000), (int)(read_data.temp));
		 puts(string);*/

		 // Send data via can:
		 ufloat roll; roll.f = read_data.roll; // degrees
		 ufloat pitch; pitch.f = read_data.pitch; // degrees
		 ufloat yaw; yaw.f = read_data.yaw; // degrees
		 ufloat roll_ang_vel; roll_ang_vel.f = read_data.roll_ang_vel; // degrees/sec
		 ufloat pitch_ang_vel; pitch_ang_vel.f = read_data.pitch_ang_vel; // degrees/sec
		 ufloat yaw_ang_vel; yaw_ang_vel.f = read_data.yaw_ang_vel; // degrees/sec
		 ufloat lin_acc; lin_acc.f = read_data.lin_acc; // g
		 ufloat z_acc; z_acc.f = read_data.z_acc; // g
		 ufloat x_acc; x_acc.f = read_data.x_acc; // g
		 ufloat y_acc; y_acc.f = read_data.y_acc; // g
		 ufloat temp; temp.f = read_data.temp; // degrees F

		 Uint32 imu_can_format[11];
		 imu_can_format[0] = roll.u;
		 imu_can_format[1] = pitch.u;
		 imu_can_format[2] = yaw.u;
		 imu_can_format[3] = roll_ang_vel.u;
		 imu_can_format[4] = pitch_ang_vel.u;
		 imu_can_format[5] = yaw_ang_vel.u;
		 imu_can_format[6] = lin_acc.u;
		 imu_can_format[7] = z_acc.u;
		 imu_can_format[8] = x_acc.u;
		 imu_can_format[9] = y_acc.u;
		 imu_can_format[10] = temp.u;

		 //if(!sent)
		 CAN_send(imu_can_format, 44, IMU, 0,0);
	}

	 return 0;
}


