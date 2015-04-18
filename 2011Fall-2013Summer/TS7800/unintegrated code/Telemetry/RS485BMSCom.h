char initPicCom();
void pingPics(char* deviceType, char* deviceNum, char* asciiArr);
void endPicCom();
char sendPing();
unsigned int expectedResponseLength();
int ASCIIToHex(unsigned char convert[]);

#define TRUE 1
#define FALSE 0

#define CMD_LENGTH (13)
#define MSG_LENGTH (16)
#define RS_485_ACK_RESPONSE_LENGTH (13)
#define RS_485_BMS_STATUS_RESPONSE_LENGTH (153)
#define RS_485_BMS_DATA_VARS (35)
#define RS_485_MC_STATUS_RESPONSE_LENGTH (141)
#define RS_485_BMS_STATUS_LENGTH (86)

