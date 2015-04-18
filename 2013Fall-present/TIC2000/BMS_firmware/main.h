#ifndef MAIN_H_
#define MAIN_H_

#define NOP asm(" NOP");
#define getTempSlope() (*(int (*)(void))0x3D7E82)()
#define getTempOffset() (*(int (*)(void))0x3D7E85)()

void SysClkInit(); //Initialize system clock
void TimerInit(); //Initialize CPU Timer 0
void InterruptInit(); //Initialize PIE/CPU interrupts
void GpioInit(); //Initialize GPIOs
void AdcInit(); //Initialize ADC block
void SpiInit(); //Initialize SPI block
void TimerISR(); //Interrupt subroutine for CPU Timer 0
void AdcISR(); //Interrupt subroutine for ADC
void WaitLoop(float time_ms);
void writeConfig();
void startCellConversions();
int pollVoltages();
void readVoltages();
void convertTemps();
void readTemps();
//void checkEverything();

#endif /* MAIN_H_ */
