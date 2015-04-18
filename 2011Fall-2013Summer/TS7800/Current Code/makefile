CC=arm-linux-gcc



LDLIBS= -lpthread

CFLAGS=-Wall -mcpu=arm9 -I../lib7800 -L../lib7800 -pthread



SOURCES= ADC.c airgap.c comm.c datastore.c DIO.c main.c motor.c threads.c

OBJECTS= ADC.o airgap.o comm.o datastore.o DIO.o main.o motor.o threads.o





all: $(OBJECTS)

	$(CC) $(CFLAGS) -o main $(SOURCES) $(LDLIBS)



.c.o:	$*.c

	$(CC) $(CFLAGS) -c $*.c



clean:

	rm -f *.o

	rm -f *~
	
	make

	

