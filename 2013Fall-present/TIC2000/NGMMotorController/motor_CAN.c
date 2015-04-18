#include "CAN_formatting.h"
#include "motor_CAN.h"

// These interrupt functions are not actually called ever, since I have disabled interrupts for the motor controller.
void motor_CAN_send_isr(CAN_ID ID, Uint32 dataH, Uint32 dataL, Uint16 length, int mbox_num) {
	//puts("Can sent!");
}
void motor_CAN_receive_isr(CAN_ID ID, Uint32 dataH, Uint32 dataL, Uint16 length, int mbox_num) {
	//puts("Can received");
}

// This array describes what ID CAN sends, and send and receive callbacks
CAN_INFO motor_CAN_info_array[] = {
		{
				MOTOR_CONTROLLER,
				&motor_CAN_send_isr,
				&motor_CAN_receive_isr // Interrupts are not actually called
		}
};


void initialize_CAN() {
	CAN_init(motor_CAN_info_array, 1, 0); // Initialize CAN with the number of CAN ID's we intend to be sending/receiving from, in this case, just "MOTOR_CONTROLLER" Don't use interrupts.
}

/**
 * \brief Send CAN: [SPEED_H][SPEED_L][ID], where SPEED is in mph
 * \note This speed function will have to be calibrated!
 */
#define NGMSCM150_MOTOR_POLES 12.0f
#define M_PI 3.141592f
#define WHEEL_DIAMETER_INCHES 18.5f
#define INCHES_IN_A_MILE 63360.0f
void CAN_send_speed_msg(Uint16 deciHz_speed) {
	int mph;
	Uint32 CAN_buffer[2];
	mph = (float32)deciHz_speed * 12.0f / NGMSCM150_MOTOR_POLES * 60.0f * M_PI * WHEEL_DIAMETER_INCHES / INCHES_IN_A_MILE; // Our motor has 12 poles, so AM_SPEED = RPM
	CAN_buffer[0] = (Uint32)CAN_SPEED_MSG | (((Uint32)mph)<<8);
	CAN_buffer[1] = 0; // Nothing in upper byte
	CAN_send(CAN_buffer, 8, MOTOR_CONTROLLER, 10, 0); // Put 8 bytes of data in Mailbox 10
	//ECanaRegs.CANTA.bit.TA10 = 1; // Aknowledge transmit
}

/**
 * \brief Send CAN: [F4][F3][F2][F1][ID]
 * \note faults must be an array of 4 faults.
 */
void CAN_send_faults_msg(unsigned char* faults) {
	Uint32 CAN_buffer[2];
	CAN_buffer[0] = (Uint32)CAN_MOTOR_FAULT_MSG | (Uint32)faults[0]<<8 | (Uint32)faults[1]<<16 | (Uint32)faults[2]<<24;
	CAN_buffer[1] = (Uint32)faults[3];
	CAN_send(CAN_buffer, 8, MOTOR_CONTROLLER, 0, 0); // Put 8 bytes of data in Mailbox 0
	//ECanaRegs.CANTA.bit.TA0 = 1; // Aknowledge transmit
}

/**
 * \brief Send CAN: [Drivestate][ID]
 */
void CAN_send_drivestate_msg(unsigned char drivestate) {
	Uint32 CAN_buffer[2];
	CAN_buffer[0] = (Uint32)CAN_MOTOR_STATUS_MSG | (Uint32)drivestate<<8;
	CAN_buffer[1] = 0;
	CAN_send(CAN_buffer, 8, MOTOR_CONTROLLER, 1, 0); // Put 8 bytes of data in Mailbox 1
	ECanaRegs.CANTA.bit.TA1 = 1; // Aknowledge transmit
}

/**
 * \brief Send CAN: [Temperature (C) (2 bytes)][Heatsink Temperature (C) (2 bytes)][Supply voltage (2 bytes)][ID]
 */
void CAN_send_temperature_voltage_msg(Uint16 temp, Uint16 h_temp, Uint16 voltage) {
	Uint32 CAN_buffer[2];
	CAN_buffer[0] = (Uint32)CAN_TEMPERATURE_VOLTAGE_MSG | ((Uint32)voltage)<<8 | ((Uint32)h_temp)<<24;
	CAN_buffer[1] = ((Uint32)h_temp)>>8 | ((Uint32)temp)<<8;
	CAN_send(CAN_buffer, 8, MOTOR_CONTROLLER, 8, 0); // Put 8 bytes of data in Mailbox 8
	ECanaRegs.CANTA.bit.TA8 = 1; // Aknowledge transmit
}

/**
 * \brief Send CAN: [Error Code][ID]
 *        Error Codes:
 *        0x02 Bad program state
 *        0x05 Error sending/receiving RS-232 data from the motor
 *        0x07 Motor was not in the correct state for the operation to continue. (Called when failed to enter cruise control).
 */
void CAN_send_error_msg(char error_code) {
	Uint32 CAN_buffer[2];
	CAN_buffer[0] = (Uint32)CAN_MOTOR_ERROR_MSG | (Uint32)error_code<<8;
	CAN_buffer[1] = 0;
	CAN_send(CAN_buffer, 8, MOTOR_CONTROLLER, 3, 0); // Put 8 bytes of data in Mailbox 3
	ECanaRegs.CANTA.bit.TA3 = 1; // Aknowledge transmit
}

/**
 * \brief Send CAN: [Throttle/Regen Phase Current (deci-A) (2 bytes)][ID] (negative if regen, positive for throttle)
 */
void CAN_send_throttle_regen_msg(int16 throttle) {
	Uint32 CAN_buffer[2];
	CAN_buffer[0] = (Uint32)CAN_THROTTLE_REGEN_VALUE_MSG | (Uint32)throttle<<8;
	CAN_buffer[1] = 0;
	CAN_send(CAN_buffer, 8, MOTOR_CONTROLLER, 5, 0); // Put 8 bytes of data in Mailbox 5
	ECanaRegs.CANTA.bit.TA5 = 1; // Aknowledge transmit
}

/**
 * \brief Send CAN: [Cruise control enabled][ID]
 */
void CAN_send_cruise_control_enabled_msg(char cc_en) {
	Uint32 CAN_buffer[2];
	CAN_buffer[0] = (Uint32)CAN_MOTOR_CC_EN_MSG | (Uint32)cc_en<<8;
	CAN_buffer[1] = 0;
	CAN_send(CAN_buffer, 8, MOTOR_CONTROLLER, 12, 0); // Put 8 bytes of data in Mailbox 12
	ECanaRegs.CANTA.bit.TA12 = 1; // Aknowledge transmit
}

/**
 * \brief Send CAN: [Reverse motor direction enabled][ID]
 */
void CAN_send_reverse_direction_enabled_msg(char rev_en) {
	Uint32 CAN_buffer[2];
	CAN_buffer[0] = (Uint32)CAN_MOTOR_REV_EN_MSG | (Uint32)rev_en<<8;
	CAN_buffer[1] = 0;
	CAN_send(CAN_buffer, 8, MOTOR_CONTROLLER, 13, 0); // Put 8 bytes of data in Mailbox 13
	ECanaRegs.CANTA.bit.TA13 = 1; // Aknowledge transmit
}

/**
 * \brief Send CAN [Left blinker EN][Right blinker EN][ID]
 */
void CAN_send_blinker_status_msg(char left_blinker_en, char right_blinker_en) {
	Uint32 CAN_buffer[2];
	CAN_buffer[0] = ((Uint32)CAN_BLINKER_EN_MSG) | ((Uint32)right_blinker_en<<8) | ((Uint32)left_blinker_en<<16);
	CAN_buffer[1] = 0;
	CAN_send(CAN_buffer, 8, MOTOR_CONTROLLER, 4, 0); // Put 8 bytes of data in Mailbox 4
	ECanaRegs.CANTA.bit.TA4 = 1; // Aknowledge transmit

}
