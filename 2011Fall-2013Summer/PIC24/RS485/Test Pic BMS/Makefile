# MPLAB IDE generated this makefile for use with GNU make.
# Project: Test Pic BMS.mcp
# Date: Sat Jun 16 13:55:26 2012

AS = pic30-as.exe
CC = pic30-gcc.exe
LD = pic30-ld.exe
AR = pic30-ar.exe
HX = pic30-bin2hex.exe
RM = rm

Test\ Pic\ BMS.hex : Test\ Pic\ BMS.cof
	$(HX) "Test Pic BMS.cof"

Test\ Pic\ BMS.cof : Init.o PIC24_RS485.o
	$(CC) -mcpu=24HJ64GP502 "Init.o" "PIC24_RS485.o" -o"Test Pic BMS.cof" -Wl,-Tp24HJ64GP502.gld,--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__MPLAB_DEBUGGER_SKDE=1,--defsym=__ICD2RAM=1,-Map="Test Pic BMS.map",--report-mem

Init.o : ../../../../../../../program\ files\ (x86)/microchip/mplabc30/v3.30c/support/PIC24H/h/p24HJ64GP502.h Init.c
	$(CC) -mcpu=24HJ64GP502 -x c -c "Init.c" -o"Init.o" -D__DEBUG -D__MPLAB_DEBUGGER_SKDE=1 -g -Wall

PIC24_RS485.o : ../../../../../../../program\ files\ (x86)/microchip/mplabc30/v3.30c/include/stdarg.h ../../../../../../../program\ files\ (x86)/microchip/mplabc30/v3.30c/include/stddef.h ../../../../../../../program\ files\ (x86)/microchip/mplabc30/v3.30c/include/stdio.h ../../../../../../../program\ files\ (x86)/microchip/mplabc30/v3.30c/support/PIC24H/h/p24HJ64GP502.h PIC24_RS485.h PIC24_RS485.c
	$(CC) -mcpu=24HJ64GP502 -x c -c "PIC24_RS485.c" -o"PIC24_RS485.o" -D__DEBUG -D__MPLAB_DEBUGGER_SKDE=1 -g -Wall

clean : 
	$(RM) "Init.o" "PIC24_RS485.o" "Test Pic BMS.cof" "Test Pic BMS.hex"

