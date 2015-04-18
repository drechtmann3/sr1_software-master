/* Testing of RS232 serial communication with the motor controller. */
#include <stdio.h>
#include "MotorController.h"
#include "RS232.h"


int main()
{
	printf("Testing RS232 functionality...\n");

	MC_Setup();
	MC_CloseConnection();

		/* MCsetup() uses the 232 connection after setting it up, so success
		 * indicates that everything is working properly. */
	printf("RS232 working properly.\n");


	return 0;
}
