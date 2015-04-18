#ifndef SCI_FUNCS_H_
#define SCI_FUNCS_H_

#include "PeripheralHeaderIncludes.h"
#include <stdio.h>
#include <string.h>

signed char scia_transmit_string(char *transmit_string);
signed char scia_xmit(char sendChar);

void scia_init(void);
void scia_fifo_init(void);

#endif /* SCI_FUNCS_H_ */
