//DEFINES
#define MAX_BATTERY_VOLTAGE 3.65 //Maximum recommended charging voltage of a cell
#define MIN_BATTERY_VOLTAGE 2.5 //Minimum recommended discharging voltage of a cell
#define FRAM_I2C_SLAVE_ADDRESS (0x50) //Slave ID = 0b1010000 for accessing page 0
#define FRAM_SOC_ADDRESS 0 //SoC value is stored in page 0, address 0

//PROTOTYPES

void calcSOC(float32 avg_current); //Calculate SOC

//GLOBAL VARIABLES

extern volatile float32 SoC; //Current state of charge
