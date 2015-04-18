#include "DIO.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <err.h>

#define DIO_BASE (0xE8000000)
#define DEBOUNCE_THRESHOLD (7)

static int IsGroundRaw(int row, int pinNum);
static int IsGround(int row, int pinNum, int *db);

/* PinRecord stores previous pin states; bit n
stores the previous value of pin n. So,
PinRecord>>pinNum & 1 is true if pin pinNum was
previously set. */
typedef unsigned int PinRecord;
PinRecord pinRecord;

volatile unsigned int *dio; // memory-mapped pin registers
int *dbInteg; // debounce integrator array

//totalPins -- TOTAL_GPIO
void InitDIO(int totalPins)
{
	int memfd;
	// Open onboard shared memory
	memfd = open("/dev/mem", O_SYNC | O_RDWR);
	if(memfd == -1) {
		printf("error opening /dev/mem");
		return;
	}
	// Map DIO section of shared memory
	dio = (unsigned int*)(mmap(0, getpagesize(),
			PROT_READ | PROT_WRITE, MAP_SHARED, memfd, DIO_BASE));
	if(dio == MAP_FAILED) {
		printf("error mapping /dev/mem");
		return;
	}

	//initialize integrator array
	dbInteg = (int *)calloc(totalPins, sizeof(int));

	/* Set PC/104 header to GPIO mode (TS7800 manual claims
	   that the PC/104 header starts up in GPIO mode by default
	   but this doesn't seem to be strictly true,
	   so the mode is set explicitly) */
	dio[GPIO_MODE_A] = 0;
	dio[GPIO_MODE_B] = 0;
	dio[GPIO_MODE_C] = 0;
	dio[GPIO_MODE_D] = 0;

	/* Initialize pin record. Note that the "Nintendo bug" is 
		possible, i.e. no buttons should be pressed at startup.*/
	pinRecord = 0;
}

void InitDIO_direction(int pinNum, int RowOffset, int direction)
{
	SetPin(pinNum, RowOffset, direction);
}

int CheckPin(int pinNum, int rowOffset)
{ //Generic pin-checking. Assumes debounced pin inputs.
	// Returns true if pin is grounded.

	//dbInteg+pinNum; want pointer, not value in array!
	int currentState = IsGround(dio[rowOffset], pinNum, dbInteg+pinNum);
	int previousState = (pinRecord>>pinNum) & 1;
	if (currentState) {
		pinRecord |= (1<<pinNum);
		if (currentState != previousState)
			return 1; //pin is pressed and wasn't previously.
	} else
		pinRecord &= !(1<<pinNum);
	return 0; //default return.
}

int CheckPinRaw(int pinNum, int rowOffset)
{ // Non-debounced GPIO pin read, for use on clean signals.
	// Returns true if pin is grounded.
	if (IsGroundRaw(dio[rowOffset], pinNum))
		return 1;
	else
		return 0;
}

int IsGround(int row, int pinNum, int *db)
{ //check whether pin is grounded, using integrator-style software debounce.
	if (IsGroundRaw(row, pinNum) && *db < 2*DEBOUNCE_THRESHOLD)
		(*db)++;
	else if (!IsGroundRaw(row, pinNum) && *db > 0)
		(*db)--;

	return (*db >= DEBOUNCE_THRESHOLD);
}

int IsGroundRaw(int row, int pinNum)
{ //raw pin checking without debounce
	return (~(row) & (1 << pinNum));
}

void SetPin(unsigned int pinNumber, unsigned int pageOffset, int val)
{ //Set the pin [pinNumber] on row [pageOffset] to [val].
	if (val)
		dio[pageOffset] |= (1<<pinNumber);  //set
	else
		dio[pageOffset] &= ~(1<<pinNumber); //unset
}

/* Some info about pin interrupts, 
   from http://bioacoustics.cse.unsw.edu.au/archives/html/ts-7000/2010-12/msg00080.html
   and from http://tech.groups.yahoo.com/group/ts-7000/message/19683:



   The TS-7800 is capable of having user-space interrupts.  This will allows you 
   to write a generic C application that can tell the kernel that you are waiting 
   on an actual real-world interrupt.  In essence your application becomes the 
   bottom half of an ISR once the IRQ triggers as the interrupt driver tells the 
   scheduler that your application is now ready to run.  Your response time is 
   then dependent on the kernel scheduler and your application's scheduling 
   algorithm and priority.

   See the man page for select() for information on how to set up your application 
   to deal with user-space IRQs.  You will want to use select() to try to read 
   /proc/irq/78/irq until it no longer blocks for IRQ 14.  Real IRQ number == 
   PC/104 IRQ number + 64.

   See the man page for sched_setscheduler() for information on setting the 
   algorithm and priority for your process.




   For more information on this (if anybody is interested) I got it to work as
follows:


fd = open("/proc/irq/69/irq", O_RDONLY, S_IREAD); // (1)
//............................................................. while
(1) {
read(fd, (int *)buffer, sizeof(int)); // (2)
set( GPIOFEOI , 1<<3); // (3)
// process interrupt here
}
//.............................................................
close(fd); // (4)

Notes:

(1) Various other web posts on this topic have fd = open("/proc/irq/69/irq",
O_RDONLY|O_NONBCLOCK); which causes read() to return always without blocking!
i.e. remove O_NONBLOCK.

(2) The thread will block here until the IRQ pin has gone high. The return value
in 'buffer' is the number of interrupts missed, which can be useful!

(3) Interrupts are level sensitive, not edge sensitive, so read() will block
when the IRQ pin is low and return continuously when the IRQ pin is high! Extra
facilities should be added here to make the hardware return the IRQ pin level
back to zero. (the code shown is for the EP9302 chip).

(4) Important! The file "/proc/irq/78" must be programatically closed somehow
(not shown here) when the program ends. I found that if the application exits
unexpectedly (easily done under development), the handle for this file will hang
and the program will fail if it is called again, necessitating a full power
reboot. It is possible to dislodge the handle from the shell with 'fuser -k
/proc/irq/69/irq' but I haven't found a way to do this programmatically. (any
ideas?)

Hope this is of use.

Tom

*/
