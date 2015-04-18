#ifndef CAN_H_
#define CAN_H_

typedef enum{
        PRECHARGE,
        MOTOR_CONTROLLER,
        PEDALS,
        BMS,
        GPS,
        IMU,
        MPPT,
        AIRGAP,
        LIGHTS,
        STEERING_WHEEL,
        WIFI,
        HORN
        //Number of CAN nodes must be less than 2^29! Not going to be a problem...ever
} CAN_ID;



typedef struct{
        CAN_ID ID;
        void (*upon_sent_isr)();
        void (*upon_receive_isr)(CAN_ID ID, int dataH, int dataL, int mbox_num);
}CAN_INFO;

__interrupt void ecan_isr(void);
void CAN_send(Uint32* data, Uint32 length, CAN_ID ID, int);
void CAN_receive(CAN_ID ID, int length, int mbox_num);
void CAN_request(CAN_ID ID, int length, int mbox_num);
void CAN_autoreply(Uint32* data, Uint32 length, CAN_ID ID, int mbox_num);
void CAN_init();


#endif /* CAN_H_ */
