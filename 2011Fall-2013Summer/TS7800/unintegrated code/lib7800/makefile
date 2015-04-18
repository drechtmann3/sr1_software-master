CC=arm-linux-gcc

CFLAGS=-Wall -Werror
OUT=lib7800.a
SRC=ADC.c  DIO.c  RS232.c RS485.c 
OBJ=ADC.o  DIO.o  RS232.o RS485.o 

$(OUT): $(OBJ)
	$(CC) -c $(SRC)
	ar rcs $(OUT) $(OBJ)

clean:
	rm -f $(OBJ) $(OUT)
