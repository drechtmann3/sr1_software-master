# MPLAB IDE generated this makefile for use with GNU make.
# Project: BMSv1.mcp
# Date: Thu Jul 05 01:59:10 2012

AS = pic30-as.exe
CC = pic30-gcc.exe
LD = pic30-ld.exe
AR = pic30-ar.exe
HX = pic30-bin2hex.exe
RM = rm

BMSv1.hex : BMSv1.cof
	$(HX) "BMSv1.cof"

BMSv1.cof : bms.o PIC24_RS485.o Init.o
	$(CC) -mcpu=24HJ64GP502 "bms.o" "PIC24_RS485.o" "Init.o" -o"BMSv1.cof" -Wl,-Tp24HJ64GP502.gld,--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__MPLAB_DEBUGGER_SKDE=1,--defsym=__ICD2RAM=1,-Map="BMSv1.map",--report-mem

bms.o : ../../../../../program\ files\ (x86)/microchip/mplabc30/v3.30c/support/PIC24H/h/p24HJ64GP502.h PIC24_RS485.h ../../../../../program\ files\ (x86)/microchip/mplabc30/v3.30c/include/stddef.h ../../../../../program\ files\ (x86)/microchip/mplabc30/v3.30c/include/string.h ltc6802-1.h bms.h ../../../../../program\ files\ (x86)/microchip/mplabc30/v3.30c/support/PIC24H/h/p24HJ64GP502.h ../../../../../program\ files\ (x86)/microchip/mplabc30/v3.30c/support/PIC24H/h/p24Hxxxx.h bms.c
	$(CC) -mcpu=24HJ64GP502 -x c -c "bms.c" -o"bms.o" -D__DEBUG -D__MPLAB_DEBUGGER_SKDE=1 -g -Wall

PIC24_RS485.o : ../../../../../program\ files\ (x86)/microchip/mplabc30/v3.30c/include/stdlib.h ../../../../../program\ files\ (x86)/microchip/mplabc30/v3.30c/include/string.h ../../../../../program\ files\ (x86)/microchip/mplabc30/v3.30c/include/stdarg.h ../../../../../program\ files\ (x86)/microchip/mplabc30/v3.30c/include/stddef.h ../../../../../program\ files\ (x86)/microchip/mplabc30/v3.30c/include/stdio.h ../../../../../program\ files\ (x86)/microchip/mplabc30/v3.30c/support/PIC24H/h/p24HJ64GP502.h PIC24_RS485.h PIC24_RS485.c
	$(CC) -mcpu=24HJ64GP502 -x c -c "PIC24_RS485.c" -o"PIC24_RS485.o" -D__DEBUG -D__MPLAB_DEBUGGER_SKDE=1 -g -Wall

Init.o : ../../../../../program\ files\ (x86)/microchip/mplabc30/v3.30c/support/PIC24H/h/p24HJ64GP502.h Init.c
	$(CC) -mcpu=24HJ64GP502 -x c -c "Init.c" -o"Init.o" -D__DEBUG -D__MPLAB_DEBUGGER_SKDE=1 -g -Wall

clean : 
	$(RM) "bms.o" "PIC24_RS485.o" "Init.o" "BMSv1.cof" "BMSv1.hex"

