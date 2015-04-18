#include <SPI.h>

// Define LTC commands
const byte WRCFG = 0x01;
const byte RDCV = 0x04;
const byte STCVAD = 0x10;
const byte RDCFG = 0x02;
const byte TEST1 = 0x1E;
const byte TEST2 = 0x1F;
const byte RDTMP = 0x0E;

// Define LTC configuration
const byte CFGR0 = B01100001;
const byte CFGR1 = B00000000;
const byte CFGR2 = B00000000;
const byte CFGR3 = B00000000;
const byte CFGR4 = 0;
const byte CFGR5 = 254;

// Pin configuration
const int chipSelectPin = 7;

// Declare other variables
byte configBytes[] = {CFGR0, CFGR1, CFGR2, CFGR3, CFGR4, CFGR5};
byte cellVoltages[18];
byte test[5];
int status;

// Initialization of Arduino and LTC
void setup() {
  
  // start the SPI library and config SPI
  SPI.begin();
  SPI.setBitOrder(MSBFIRST);
  SPI.setClockDivider(SPI_CLOCK_DIV16);
  SPI.setDataMode(SPI_MODE3);

  // Initialize pins
  pinMode(chipSelectPin, OUTPUT);
  
  // Start serial port for debug output
  Serial.begin(9600);
  
}

void loop() {
  
  // Configure the LTC
  digitalWrite(chipSelectPin, LOW);
  spiWriteByte(WRCFG);
  spiWriteBytes(configBytes, sizeof(configBytes));
  digitalWrite(chipSelectPin, HIGH);
  
  // Request ADC self test
  digitalWrite(chipSelectPin, LOW);
  spiWriteByte(TEST1);
  digitalWrite(chipSelectPin, HIGH);
  
  delay(20);
  
  // Read voltage registers
  digitalWrite(chipSelectPin, LOW);
  spiWriteByte(RDCV);
  status = spiReadBytes(cellVoltages, sizeof(cellVoltages));
  digitalWrite(chipSelectPin, HIGH);
  
  delay(40);
  
}

// Read a cluster of bytes. The PEC is not returned. nBytes does not include the PEC.
// This function compares calculated and received PEC values and returns 0 if data valid, 1 if invalid.
// byteArray[0] corresponds to first byte received.
int spiReadBytes(byte byteArray[], int nBytes) {
  
  int i;
  byte pecRead;
  byte pecCalculated = B01000001;   // init the calculated PEC
  
  // read the data bytes and calculate running PEC
  for(i = 0; i < nBytes; i++) {
    byteArray[i] = SPI.transfer(0x00);
    pecCalculated = continuePEC(byteArray[i], pecCalculated);
    
  }
  
  // read the PEC byte
  pecRead = SPI.transfer(0x00);
  
  // compare PECs
  if(pecCalculated == pecRead) {
    return 0;
    
  } else {
    return 1;
    
  }

}

// Write a cluster of bytes. The PEC is automatically calculated and written. nBytes does not include the PEC.
// byteArray[0] corresponds to first byte written.
void spiWriteBytes(byte byteArray[], int nBytes) {
  
  int i;
  byte pecCalculated = B01000001;   // init the calculated PEC

  // write the data bytes and calculate running PEC
  for(i = 0; i < nBytes; i++) {
    SPI.transfer(byteArray[i]);
    pecCalculated = continuePEC(byteArray[i], pecCalculated);
    
  }
  
  // write the PEC byte
  SPI.transfer(pecCalculated);

}

// Write a byte. The PEC is automatically calculated and written.
void spiWriteByte(byte theByte) {

  byte pecCalculated = B01000001;   // init the calculated PEC

  // write the data bytes and calculate running PEC
  SPI.transfer(theByte);
  pecCalculated = continuePEC(theByte, pecCalculated);
  
  // write the PEC byte
  SPI.transfer(pecCalculated);

}

byte continuePEC(byte cmd, byte PEC) {
    byte in0;
    byte in1;
    byte in2;
    int i;
    
    for(i = 0; i < 8; i++) {
        in0 = ((cmd >> (7-i)) & 1) ^ ((PEC >> 7) & 1);
        in1 = (PEC & 1) ^ in0;
        in2 = ((PEC >> 1) & 1) ^ in0;
        in1 = in1 << 1;
        in2 = in2 << 2;
        PEC = ((PEC << 1) & B11111000) | (((0 | in2) | in1) | in0);
    }
    
    return PEC;
    
}
