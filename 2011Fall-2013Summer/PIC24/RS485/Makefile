# MPLAB IDE generated this makefile for use with GNU make.
# Project: PIC_24H_UART.mcp
# Date: Mon Jan 09 23:13:51 2012

AS = pic30-as.exe
CC = pic30-gcc.exe
LD = pic30-ld.exe
AR = pic30-ar.exe
HX = pic30-bin2hex.exe
RM = rm

PIC_24H_UART.hex : PIC_24H_UART.cof
	$(HX) "PIC_24H_UART.cof"

PIC_24H_UART.cof : PIC_24H_UART_Test.o UART_Setup.o
	$(CC) -mcpu=24HJ64GP502 "PIC_24H_UART_Test.o" "UART_Setup.o" -o"PIC_24H_UART.cof" -Wl,--script="..\..\..\..\..\..\Program Files (x86)\Microchip\mplabc30\v3.30c\support\PIC24H\gld\p24HJ64GP502.gld",--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__MPLAB_DEBUGGER_SKDE=1,--defsym=__ICD2RAM=1,-Map="PIC_24H_UART.map",--report-mem

PIC_24H_UART_Test.o : ../../../../../../program\ files\ (x86)/microchip/mplabc30/v3.30c/support/PIC24H/h/p24HJ64GP502.h UART_Setup.h PIC_24H_UART_Test.c
	$(CC) -mcpu=24HJ64GP502 -x c -c "PIC_24H_UART_Test.c" -o"PIC_24H_UART_Test.o" -D__DEBUG -D__MPLAB_DEBUGGER_SKDE=1 -g -Wall

UART_Setup.o : ../../../../../../program\ files\ (x86)/microchip/mplabc30/v3.30c/support/PIC24H/h/p24HJ64GP502.h UART_Setup.c
	$(CC) -mcpu=24HJ64GP502 -x c -c "UART_Setup.c" -o"UART_Setup.o" -D__DEBUG -D__MPLAB_DEBUGGER_SKDE=1 -g -Wall

clean : 
	$(RM) "PIC_24H_UART_Test.o" "UART_Setup.o" "PIC_24H_UART.cof" "PIC_24H_UART.hex"

