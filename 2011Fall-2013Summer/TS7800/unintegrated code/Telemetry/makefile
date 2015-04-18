CC= arm-linux-gcc

LDLIBS= -lpthread
CFLAGS=-Wall -mcpu=arm9 -I../lib7800 -L../lib7800 -pthread
LIB7800=-l7800 #links the file lib7800.a
SOURCES= main.c lcd.c buttons.c datalog.c gps.c usb.c wireless.c pthreads.c conversions.c RS485BMSCom.c
OBJECTS= main.o lcd.o buttons.o datalog.o gps.o usb.o wireless.o pthreads.o conversions.o RS485BMSCom.o
WTSOURCES= wirelessTest.c
WTOBJECTS= wirelessTest.o
RS485SOURCES = RS485BMSCom.c RS485test.c
RS485OBJECTS = RS485BMSCom.c RS485test.o


all: $(OBJECTS)
	$(CC) $(CFLAGS) -o main $(SOURCES) $(LIB7800) $(LDLIBS)
	
wtest: $(WTOBJECTS)
	$(CC) $(CFLAGS) -o wTest $(WTSOURCES) $(LIB7800)
	
RS485test: $(RS485OBJECTS)
	$(CC) $(CFLAGS) -o RS485test $(RS485SOURCES) $(LIB7800)


.c.o:	$*.c
	$(CC) $(CFLAGS) -c $*.c

clean:
	rm -f *.o
	rm -f *~
	

	

