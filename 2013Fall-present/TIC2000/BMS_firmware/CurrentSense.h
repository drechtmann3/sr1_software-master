//DEFINES
//Typical conventions: charging produces a negative current, discharging produces a positive current
#define MAX_DISCHARGE_CUR 100.0f //Max discharge current
#define MAX_CHARGE_CUR (-49.6f) //Amperes, Max charging current = 16 batteries per pack * 3.1A max charging per battery

//PROTOTYPES

//__interrupt void getCurrent(void); //Fetch value from ADC and calculate current from battery pack

//GLOBAL VARIABLES

//extern volatile char batCurrentRead;
//extern volatile float32 batCurrent; //Instantaneous battery current readings
