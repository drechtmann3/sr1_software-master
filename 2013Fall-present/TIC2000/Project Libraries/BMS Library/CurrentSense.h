//DEFINES
//May have to change signs (+ or -) depending on which direction the current sensor is installed
#define MAX_DISCHARGE_CUR 100.0f //Max discharge current
#define MAX_CHARGE_CUR (-49.6f) //Ampheres, Max charging current = 16 batteries per pack * 3.1A max charging per battery

//PROTOTYPES

__interrupt void getCurrent(void); //Fetch value from ADC and calculate current from battery pack

//GLOBAL VARIABLES

extern volatile char batCurrentRead;
extern volatile float32 batCurrent; //Instantaneous battery current readings
