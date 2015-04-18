//INCLUDES
#include "DS2484_Coms.h"
#include "I2CForDS2484.h"

//DEFINES
#define NUM_TEMP_SENSORS 31 //The number of temperature sensors to use
#define BAT_TEMP_LIMIT_C 59.5f // Max battery temperature before shutdown, in C

//PROTOTYPES
signed char readTempSensor(char indx); //Read temperature sensors
signed char initializeTempSensors(void); //Initialize temp sensors
float32 getHighestTempSensorReading(void); //Get the highest temp sensor reading
void sendTempSensorReadingsViaCAN(void); //Send readings via CAN

//GLOBAL VARIABLES
extern volatile float32 tempSensorReadings[NUM_TEMP_SENSORS]; //Readings, in degrees C
extern volatile unsigned char tempSensorStatuses[NUM_TEMP_SENSORS]; //Status of temp sensors
extern volatile char tempSensorsRead; //Only use temp sensor readings if this is ==+1!
extern volatile unsigned int tempSensorTimers[NUM_TEMP_SENSORS];
extern volatile unsigned char tempSensorReadCommandSent[NUM_TEMP_SENSORS];

