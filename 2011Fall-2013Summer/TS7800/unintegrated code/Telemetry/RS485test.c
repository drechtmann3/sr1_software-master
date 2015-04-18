/* testing of RS485 functionality */
/*For Andrey only: scp andrey@192.168.0.1:/home/andrey/School/SJ/pp/SBC/src/HMI+Telem/RS485test ./RS485test*/
#include "stdio.h"
#include "RS485BMSCom.h"

int main()
{	
	initPicCom();	
	while(1){
		char device;
		char deviceNum;
		char response[200];
		pingPics(&device,&deviceNum,response);

	}
	endPicCom();
	return 0;
}

