//PROTOTYPES

void SysClkInit(void); //Initialize system clock frequency to 90 MHz using PLL
void GpioInit(void); //Configure GPIOs
void SpiInit(void); //Initialize SPI module to use GPIOs 16,17,18,19
void TmrInit(void); //Initialize timer
void AdcInit(void); //Initializes ADC
void InterruptInit(void); //Initializes system interrupts
