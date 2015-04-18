typedef enum{
	SEND_VOLTAGES,
	SEND_TEMPS,
	SEND_CURRENT,
	SEND_CHARGE,
	SEND_VOLTAGEMAXandMI
} BMS_CAN_REQUEST;
//defines

void BMSCAN_sendVoltages();
void BMSCAN_sendCurrent();
//__interrupt void CANSendAllBatteryInfo();

//GLOBAL VARIABLES
void BMA_CAN_init();

