#ifndef SCI_FUNCS_H_
#define SCI_FUNCS_H_

#include "PeripheralHeaderIncludes.h"
#include <stdio.h>
#include <string.h>

extern char scia_receive_buffer[17]; // Allocate 17 bytes max for received message string in data section.



signed char scia_transmit_string_echo(char *transmit_string);
signed char scia_send_eol_cr_echo();
signed char scia_send_char_wait_for_echo(char sendChar);

signed char scia_transmit_string(char *transmit_string);
signed char scia_send_char(char sendChar);

signed char scia_receive_string();

void scia_init(void);
void scia_fifo_init(void);

#endif /* SCI_FUNCS_H_ */
