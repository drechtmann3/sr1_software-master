#define RS_485_MAX_RX_DATA_BYTES (12)
#define RS_485_NUM_MSGTYPE_BYTES (4)
typedef struct message{
	char address[2]; 
	char messageType[RS_485_NUM_MSGTYPE_BYTES];
	char dataAsciiArr[RS_485_MAX_RX_DATA_BYTES];
	int length;
}Message;

char initPicCom();
Message checkRS485();
void endPicCom();
void *RS485_Control(void *thread_id); //the main thread routine

#define TRUE 0
#define FALSE 1
