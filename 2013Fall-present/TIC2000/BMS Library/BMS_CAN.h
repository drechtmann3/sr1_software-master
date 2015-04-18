
//PROTOTYPES
#include "CAN.h"

void BMS_send_isr(CAN_ID ID, Uint32 dataH, Uint32 dataL, Uint16 length, int mbox_num);
void BMS_receive_isr(CAN_ID ID, Uint32 dataH, Uint32 dataL, Uint16 length, int mbox_num);

void BMSCAN_sendVoltages();
void BMSCAN_sendSOCAndCurrent();
//__interrupt void CANSendAllBatteryInfo();

//GLOBAL VARIABLES

extern CAN_INFO BMS_CAN_INFO_ARRAY[4];

