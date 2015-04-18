CC=arm-linux-gcc

#deployment
CFLAGS=-Wall -pthread -I../lib7800 -DUSE_MOTOR_THREAD \
	-DUSE_AIRGAP_THREAD -DENABLE_MOTOR_KILLSWITCH -DENABLE_AIRGAP_KILLSWITCH\
	-L../lib7800
DEBUGFLAGS=-Wall -pthread -DDEBUG -DENABLE_MOTOR_KILLSWITCH -I../lib7800 -DENABLE_AIRGAP_KILLSWITCH \
	-L../lib7800
LIB7800=-l7800  #links the file lib7800.a
SRC=Main.c Motor.c RS485ControlCom.c MotorController.c 
OBJ=Main.o Motor.o RS485ControlCom.o MotorController.o 


###
# motortest:
# Manual motor test
###
MOTORTEST_SRC=Main.c Motor.c MotorController.c 
MOTORTEST_OBJ=Main.o Motor.o MotorController.o 
MOTORTEST_FLAGS=$(DEBUGFLAGS) -DUSE_MOTOR_THREAD -DMOTORTEST_DEBUG_OUTPUT -DMC_DEBUG -DDEBUG

###
# TODO automated motor test 
###
UNMANNED_MOTORTEST_SRC=UnmannedMotorTest.c Motor.c MotorController.c 
UNMANNED_MOTORTEST_OBJ=UnmannedMotorTest.o Motor.o MotorController.o 
UNMANNED_MOTORTEST_FLAGS=$(DEBUGFLAGS) -DMC_DEBUG -DUSE_SPEED_CONTROL

###
# DIOtest:
# Put out square waves on all GPIO pins
###
DIOTEST_SRC=DIOtest.c 
DIOTEST_OBJ=DIOtest.o 
DIOTEST_FLAGS=$(DEBUGFLAGS)

###
# ADCtest:
# Single reading from arbitrary ADC channel
###
ADCTEST_SRC=ADCtest.c 
ADCTEST_OBJ=ADCtest.o 
ADCTEST_FLAGS=$(DEBUGFLAGS) -DADC_DEBUG

RS232TEST_SRC=RS232test.c MotorController.c 
RS232TEST_OBJ=RS232test.o MotorController.o 
RS232TEST_FLAGS=$(DEBUGFLAGS) -DRS232_DEBUG

RS485TEST_SRC=RS485test.c RS485ControlCom.c 
RS485TEST_OBJ=RS485test.o RS485ControlCom.o 
RS485TEST_FLAGS=$(DEBUGFLAGS) -DUSE_RS485_THREAD

AIRGAPTEST_SRC=Main.c Motor.c MotorController.c 
AIRGAPTEST_OBJ=Main.o Motor.o MotorController.o 
AIRGAPTEST_FLAGS=$(DEBUGFLAGS) -DUSE_AIRGAP_THREAD -DENABLE_AIRGAP_KILLSWITCH

MC_FAULT_SRC=MC_fault_check.c MotorController.c
MC_FAULT_OBJ=MC_fault_check.o MotorController.o
MC_FAULT_FLAGS=$(DEBUGFLAGS)



all: Main ADCtest DIOtest RS232test RS485test Airgaptest \
	MC_fault_check motortest unmanned_motortest

Main: $(OBJ) #deployment
	$(CC) $(CFLAGS) -o Main $(SRC) $(LIB7800)
motortest: $(MOTORTEST_OBJ)
	$(CC) $(MOTORTEST_FLAGS) -o motortest $(MOTORTEST_SRC) $(LIB7800)
unmanned_motortest: $(UNMANNED_MOTORTEST_OBJ)
	$(CC) $(UNMANNED_MOTORTEST_FLAGS) -o unmanned_motortest $(UNMANNED_MOTORTEST_SRC) $(LIB7800)
DIOtest: $(DIOTEST_OBJ)
	$(CC) $(DIOTEST_FLAGS) -o DIOtest $(DIOTEST_SRC) $(LIB7800)
ADCtest: $(ADCTEST_OBJ)
	$(CC) $(ADCTEST_FLAGS) -o ADCtest $(ADCTEST_SRC) $(LIB7800)
RS232test: $(RS232TEST_OBJ)
	$(CC) $(RS232TEST_FLAGS) -o RS232test $(RS232TEST_SRC) $(LIB7800)
RS485test: $(RS485TEST_OBJ)
	$(CC) $(RS485TEST_FLAGS) -o RS485test $(RS485TEST_SRC) $(LIB7800)
Airgaptest: $(AIRGAPTEST_OBJ)
	$(CC) $(AIRGAPTEST_FLAGS) -o Airgaptest $(AIRGAPTEST_SRC) $(LIB7800)
MC_fault_check: $(MC_FAULT_OBJ)
	$(CC) $(MC_FAULT_FLAGS) -o MC_fault_check $(MC_FAULT_SRC) $(LIB7800)
	

BINARIES=motortest unmanned_motortest DIOtest ADCtest RS232test RS485test Airgaptest MC_fault_check Main
clean:
	rm -f *.o
	rm -f $(BINARIES)