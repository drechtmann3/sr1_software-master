// #include "IMU.h"
// int lastMillis;
// clock_t lastClock;

// #define GPIO_ROW (4)
// #define SDO_PIN (0)
// #define SDI_PIN (1)
// #define SCL_PIN (2)
// #define CS_ACC_Pin (3)
// #define CS_Gyro_Pin (4)
// #define Int1_ACC_Pin (5)
// #define Int2_ACC_Pin (6)
// #define Int1_Gyro_Pin (7)
// #define Int2_Gyro_Pin (8)
// #define MILLIS_BETWEEN_READINGS (50)
// #define FILTER_ALPHA (0.2)

// float angles[];

// void init(){
	// InitDIO_direction(SDO_PIN,GPIO_ROW,GPIO_INTPUT);
	// InitDIO_direction(SDI_PIN,GPIO_ROW,GPIO_OUPUT);
	// InitDIO_direction(CS_ACC_Pin ,GPIO_ROW,GPIO_OUTPUT);
	// InitDIO_direction(CS_Gyro_Pin ,GPIO_ROW,GPIO_OUTPUT);
	// InitDIO_direction(SCL_PIN ,GPIO_ROW,GPIO_OUTPUT);
	// lastClock=clock();
// }


// int elapsedMillis(){
	// clock_t currentClock=clock();
	// return (currentClock-lastClock)/(CLOCKS_PER_SEC/100);	
// }

// void loop(){
	// float dt=MILLIS_BETWEEN_READINGS/1000.0f;
	// if(elapsedMillis>=MILLIS_BETWEEN_READINGS){
		// int gyroReadings[]=gyroRead();
		// int accReadings[]=accRead();
		// int i=0;
		// lastClock=clock();

		// for(i=0;i<3;i++)	
			// angles[i] = (1-FILTER_ALPHA)*(angles[i] + gyroReadings[i] * dt) + (FILTER_ALPHA)*(accReadings[i]);
		
	// }
// }


// /*
// The first bit (bit 0) starts at the first falling edge of SPC after the falling
// edge of CS while the last bit (bit 15, bit 23, ...) starts at the last falling edge of SPC just
// before the rising edge of CS.
// */
// void clockPulse(){
	// SetPin(SCL_PIN, GPIO_ROW, PIN_HIGH);
	// SetPin(SCL_PIN, GPIO_ROW, PIN_LOW);
// }


// int[] sensorRead(bool Gyro){
	// /*
	// CS is the Serial Port Enable and is controlled by the SPI master. It goes low at the start of
// the transmission and goes back high at the end.
	// */
	// if(Gyro){
		// SetPin(CS_Gyro_Pin ,GPIO_ROW,PIN_HIGH);
		// SetPin(CS_Gyro_Pin ,GPIO_ROW,PIN_LOW);
	// }else{
		// SetPin(CS_ACC_Pin ,GPIO_ROW,PIN_HIGH);
		// SetPin(CS_ACC_Pin ,GPIO_ROW,PIN_LOW);
	// }
	
	
	// //11010 1000 - Start read, set to address auto-increment, start at address 40 for first reading
	// int vals[]={PIN_HIGH,PIN_HIGH,PIN_LOW,PIN_HIGH,PIN_LOW,PIN_HIGH,PIN_LOW,PIN_LOW,PIN_LOW};
	// int i=0;
	// int currentRead=0; 
	// for(i=0;i<8;i++){
		// clockPulse();
		// SetPin(SDI_PIN,GPIO_ROW,vals[i]);
	// }
	// int readings[6];
	// int reading=0;
	// for(reading=0;reading<6;reading++){
		// for(i=0;i<8;i++){
			// clockPulse();
			// currentRead=SetPin(SDI_PIN,GPIO_ROW,vals[i]);	
		// }
		// readings[reading]=(1<<readings[reading])|CheckPin(SDO_PIN,GPIO_ROW);
	// }
	// if(Gyro)
		// SetPin(CS_Gyro_Pin ,GPIO_ROW,PIN_HIGH);
	// else
		// SetPin(CS_ACC_Pin ,GPIO_ROW,PIN_HIGH);	

	// return readings;
// }


// /*
// OUT_X_L 
// OUT_X_H
// OUT_Y_L
// OUT_Y_H
// OUT_Z_L
// OUT_Z_H 
// */
// int[] gyroRead(){
	// //TODO convert to real world values/3 values
	// return sensorRead(true);
// }

// int[] accRead(){
	// //TODO convert to real world values/3 values
	// return sensorRead(false);
// }

