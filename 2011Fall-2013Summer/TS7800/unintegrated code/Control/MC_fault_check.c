
#include <stdio.h>
#include "MotorController.h"
#include "RS232.h"
#include "MC_commands.h"

int main()
{

	printf("Running MCsetup...\n");
	MC_Setup();
	printf("Polling for motor faults...\n");
	
	printf("Fault type 1:  %x\n", MC_Query(Q_FAULT1LATCH));
	printf("Fault type 2:  %x\n", MC_Query(Q_FAULT2));
	printf("Fault type 3:  %x\n", MC_Query(Q_FAULT3));
	printf("Fault type 4:  %x\n", MC_Query(Q_FAULT4));


	MC_CloseConnection();
	return 0;
}
