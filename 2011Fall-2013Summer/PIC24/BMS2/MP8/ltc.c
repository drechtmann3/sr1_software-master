#include "ltc.h"
#include "datastore.h"
#include "relay.h"
#include "LED.h"
#include <stdio.h>
#include <p24HJ128GP202.h>

void LTC_setClock(int clock){
	LATBbits.LATB3 = clock;
}

void LTC_setMOSI(int mosi){
	LATBbits.LATB2 = mosi;
}
int LTC_getMISO(int ltcNum){
	if(ltcNum == LTC1){
		return PORTBbits.RB5;
	}else if(ltcNum == LTC2){
		return PORTBbits.RB6;
	}else{
		return PORTBbits.RB7;
	}
}

void LTC_CS(int LTC, int CS){
	switch(LTC){
		case LTC1:
			LATBbits.LATB12 = CS;
			break;
		case LTC2:
			LATBbits.LATB13 = CS;
			break;
		case LTC3:
			LATBbits.LATB14 = CS;
			break;
		case LTC_ALL:
			LATBbits.LATB12 = CS;
			LATBbits.LATB13 = CS;
			LATBbits.LATB14 = CS;
			break;
		default:
			break;
	}
}

void LTC_writeConfig(int LTC, int discharge){
	int config_pec = 0;
	
	LTC_setClock(LTC_CLOCK_LOW); //Init clock

	//start the write config procedure
	LTC_CS(LTC, LTC_CS_SELECT);
	LTC_sendCommand(WRCFG);
	LTC_sendCommand(PEC(WRCFG));

	//send the user bits
	LTC_sendCommand(CFGR0); //operation settings
	config_pec = PEC(CFGR0);

	LTC_sendCommand((discharge & 0xFF)|CFGR1); //discharge settings
	config_pec = continuePEC((discharge & 0xFF)|CFGR1, config_pec);

	LTC_sendCommand((discharge>>8)|CFGR2); //discharge and mask settings
	config_pec = continuePEC((discharge>>8)|CFGR2, config_pec);

	LTC_sendCommand(CFGR3); //mask settings
	config_pec = continuePEC(CFGR3, config_pec);

	LTC_sendCommand(CFGR4); //under voltage settings
	config_pec = continuePEC(CFGR4, config_pec);

	LTC_sendCommand(CFGR5); //over voltage settings
	config_pec = continuePEC(CFGR5, config_pec);

	LTC_sendCommand(config_pec); //send the error check code

	LTC_CS(LTC, LTC_CS_DESELECT); //stop write config procedure
}

int LTC_readVoltages(int LTC){

	unsigned int voltbits[19];
	long voltages[12];
	int voltout[12];
	int i;
	int j;
	int k = 0;
	int bits = 0;
	char buffer [8];

	//start ADC conversions
	LTC_CS(LTC, LTC_CS_SELECT);
	LTC_sendCommand(0x10); //TODO take in status to do STCVDC when in yellow
	LTC_sendCommand(PEC(0x10));
	
	//wait til conversion finishes
	while(LTC_getMISO(LTC) == 0){
		k++;
		k--;
	}
	LTC_CS(LTC, LTC_CS_DESELECT);
	
	//Read the cell voltages
	LTC_CS(LTC, LTC_CS_SELECT);
	LTC_sendCommand(RDCV);
	LTC_sendCommand(PEC(RDCV));
	
	//read in raw bits
	for(i = 0; i < 19; i++){
		voltbits[i] = 0; //initialize the value
		for(j = 0; j < 8; j++){
			//clock in the data
			LTC_setClock(LTC_CLOCK_HI); 
			//save the data to voltbits
			voltbits[i] = voltbits[i] << 1;
			voltbits[i] |= LTC_getMISO(LTC);
			//clock out
			LTC_setClock(LTC_CLOCK_LOW);
		}
	}	

	//convert raw bits into usable decimal values
	for(i = 0; i < 12; i++){
		if(i % 2 == 0){
			voltages[i] = voltbits[bits] | ((voltbits[bits+1]&0x0F)<<8);
			bits++;
		}else{
			voltages[i] = (voltbits[bits]>>4)|(voltbits[bits+1]<<4);
			bits += 2;
		}
		if(i < 10){
			voltout[i] = (voltages[i]-512)*1.5;
		}else{
			voltout[i] = 3200;
		}
		sprintf(buffer, "%dCell%d", LTC, i+1);
		//setInt(buffer, voltout[i]);

		int warn = 0;
		char buffer [8];
		//sprintf(buffer, "%dCell%d",LTC, i+1);
		//cellV = getInt(buffer);
		if(voltout[i] > CELL_CUTOFF_HI || voltout[i] < CELL_CUTOFF_LOW){
			setRelay(RELAY_OFF);
			setCritical(LED_ON);
			setWarn1(LED_ON);
			//setInt("critical", 1);
			LTC_CS(LTC, LTC_CS_DESELECT);
			//return 0;
		}else if(voltout[i] > CELL_WARN_HI || voltout[i] < CELL_WARN_LOW){
			warn++;
		}
		setWarn1(warn);
	}
	//stop read cell voltage procedure
	LTC_CS(LTC, LTC_CS_DESELECT);
	LTC_CS(LTC, LTC_CS_DESELECT);
	/*static int z = 0;
	if(z > 1){
		int x = 10;
	}
	z++;*/
	return 1;
}

int LTC_analyzeVolts(int LTC){
	int i;
	int cellV;
	int warn = 0;
	for(i = 1; i <= 10; i++)
	{
		char buffer [8];
		sprintf(buffer, "%dCell%d",LTC, i+1);
		cellV = getInt(buffer);
		if(cellV > CELL_CUTOFF_HI || cellV < CELL_CUTOFF_LOW){
			setRelay(RELAY_OFF);
			setCritical(LED_ON);
			setWarn1(LED_ON);
			//setInt("critical", 1);
			return 0;
		}else if(cellV > CELL_WARN_HI || cellV < CELL_WARN_LOW){
			warn++;
		}
		setWarn1(warn);
	}
	return 1;
}

int initLTC(){
	LTC_writeConfig(LTC_ALL, 0);
	int i;
	for(i = LTC1; i < LTC_ALL; i++){
		if(LTC_readVoltages(i) == 0){
			return 0;
		}
	}
	return 1;
}

void LTC_sendCommand(char command){
	int i;
	int sendBit;

	//send 8 bits (one byte)
	for(i = 0; i < 8; i++){
		sendBit = (command>>(7-i)) & 1; //calcuate the binary bit value to be sent
		LTC_setMOSI(sendBit); //set mosi to the value
		LTC_setClock(LTC_CLOCK_HI); //clock the data in
		LTC_setClock(LTC_CLOCK_LOW); //clock the data out
	}
}

char PEC(char cmd) {
	//magic taken straight from LTC manual 
    char in0;
    char in1;
    char in2;
    char PEC = 0b01000001;
    int i;
    for(i = 0; i < 8; i++){
        in0 = ((cmd >> (7-i)) & 1) ^ ((PEC >> 7) & 1);
        in1 = (PEC & 1) ^ in0;
        in2 = ((PEC >> 1) & 1) ^ in0;
        in1 = in1 << 1;
        in2 = in2 << 2;
        PEC = ((PEC << 1) & 0b11111000) | (((0 | in2) | in1) | in0);
    }
    return PEC;
}

char continuePEC(char cmd, char PEC) {
	//pec code using old pec value
    char in0;
    char in1;
    char in2;
    int i;
    for(i = 0; i < 8; i++){
        in0 = ((cmd >> (7-i)) & 1) ^ ((PEC >> 7) & 1);
        in1 = (PEC & 1) ^ in0;
        in2 = ((PEC >> 1) & 1) ^ in0;
        in1 = in1 << 1;
        in2 = in2 << 2;
        PEC = ((PEC << 1) & 0b11111000) | (((0 | in2) | in1) | in0);
    }
    return PEC;
}
