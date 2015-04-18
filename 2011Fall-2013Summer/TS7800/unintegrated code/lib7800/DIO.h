#ifndef DIOPOLL_H
#define DIOPOLL_H

/* GPIO functions for the PC/104 header, rows A, B, C, D, on the TS-7800.*/

/* GPIO PC/104 row offsets */
#define	 GPIO_ROW_A		(4)
#define	 GPIO_ROW_B		(5)
#define	 GPIO_ROW_C		(6)
#define GPIO_ROW_D		(7)

/* GPIO PC/104 pin mode address offsets */
/* (ISA versus GPIO) */
#define GPIO_MODE_A		(12)
#define GPIO_MODE_B		(13)
#define GPIO_MODE_C		(14)
#define GPIO_MODE_D		(15)

/* Pin direction values */
#define GPIO_OUTPUT		(1)
#define GPIO_INPUT		(0)

/* Pin output values */
#define PIN_HIGH		(1)
#define PIN_LOW			(0)

//Base address in memmoryfor the DIO pins
#define DIO_BASE (0xE8000000)



/* Set up DIO; initialize pins as inputs or outputs. */
void InitDIO();
/* Initialize pin direction (either GPIO_OUTPUT or GPIO_INPUT) */
void InitDIO_direction(int pinNum, int RowOffset, int direction);

/* Set a pin output. */
void SetPin(unsigned int pinNumber, unsigned int pageOffset, int val);
/* Check whether pin is tied to ground. */
int CheckPin(int pinNum, int rowOffset);
//Check wether the pin is connected to ground or not
int IsGroundRaw(int row, int pinNum);

#endif
