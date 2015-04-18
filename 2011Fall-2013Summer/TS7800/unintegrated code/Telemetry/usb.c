/**
* @ingroup telemetry
* @defgroup usb USB
* @brief USB functions
* 
* @{
*/
#include <stdio.h>
#include <sys/mount.h>
#include "string.h"
#include "wrapper.h"
#include "datalog.h"
#include "usb.h"

int initUSB(){
	int i;
	for(i = 0; i < 26; i++) {
		char usbMountFromPathTry[256];
		char sdanum[5];
		strcpy(usbMountFromPathTry, usbMountFromPath);
		sprintf(sdanum, "%c1", i+'a');
		strcat(usbMountFromPathTry, sdanum);
		if(!mount(usbMountFromPathTry, usbMountToPath, "vfat", (long)NULL, NULL)){
			printf("Mount successful");
			logMessage("USB drive was mounted sucessfully", 0);
			return 1;
		} else if(!mount(usbMountFromPathTry, usbMountToPath, "vfat", MS_REMOUNT, NULL)){
			printf("Mount successful\n");
			logMessage("USB drive was remounted sucessfully", 0);
			return 1;
		}
		printf("Mount error: ");
		printf("%s\n", usbMountFromPathTry);
	}
	printf("Mount ERROR\n");
	return 0;
}

void writeEssentials(){
	FILE * file = fopen(usbMountEssentials, "a+");
	fflush(file);
	if(file == NULL){
		initUSB();
		printf("null file\n");
		logMessage("File pointer was null, check dmesg for file panic errors, if errors exist run 'fsck -r /dev/sda1'", 2);
		return;
	}
	fprintf(file, "\n%s, ", getDate());
	fprintf(file, "%s, ", getTime());
	fprintf(file, "%1.2f, ", getSpeed());
	fprintf(file, "%d, ", getRPM());
	fprintf(file, "%d, ", getRegen());
	fprintf(file, "%d, ", getAirgap());
	fprintf(file, "%d, ", getBattery());
	fprintf(file, "%.2f, ", *(getADCTemps()+COMPUTER_BOX_TEMP_INDEX));
	fprintf(file, "%.2f, ", *(getBMS()+BMS_TEMP_INDEX+(BMS_NUM_VAR*0)));
	fprintf(file, "%.2f, ", *(getBMS()+BMS_TEMP_INDEX+(BMS_NUM_VAR*1)));
	fprintf(file, "%.2f, ", *(getBMS()+BMS_TEMP_INDEX+(BMS_NUM_VAR*2)));
	fprintf(file, "%.2f, ", *(getMPPT()+MPPT_TEMP_INDEX+(MPPT_NUM_VAR*0)));
	fprintf(file, "%.2f, ", *(getMPPT()+MPPT_TEMP_INDEX+(MPPT_NUM_VAR*1)));
	fprintf(file, "%.2f, ", *(getMPPT()+MPPT_TEMP_INDEX+(MPPT_NUM_VAR*2)));
	fprintf(file, "%.2f, ", *(getMPPT()+MPPT_TEMP_INDEX+(MPPT_NUM_VAR*3)));
	fprintf(file, "%s, ", getLat());
	fprintf(file, "%s, ", getLong());
	int i;
	for(i = 0; i < getNumErrors(); i++){
		//fprintf(file, "%s, ", getErrorText(*(getErrors()+i)));
	}
	fclose(file);
}

void writeCVT(){
	FILE * file = fopen(usbMountCVT, "a");
	fflush(file);
	if(file == NULL){
		initUSB();
		printf("null file\n");
		logMessage("File pointer was null, check dmesg for file panic errors, if errors exist run 'fsck -r /dev/sda1'\n", 2);
		return;
	}
	fprintf(file, "\n%s, ", getDate());
	fprintf(file, "%s, ", getTime());
	
	int i;
	for(i = 0; i < NUM_ADC_CURRENT_SENSORS; i++){
		fprintf(file, "%.2f, ", *(getADCCurrent()+i));
	}
	for(i = 0; i < NUM_BMS_CURRENTS; i++){
		fprintf(file, "%.2f, ", *(getBMS()+BMS_CURRENT_INDEX+i));
	}
	for(i = 0; i < NUM_BMS_CURRENTS; i++){
		fprintf(file, "%.2f, ", *(getBMS()+BMS_CURRENT_INDEX+BMS_NUM_VAR+i));
	}
	for(i = 0; i < NUM_BMS_CURRENTS; i++){
		fprintf(file, "%.2f, ", *(getBMS()+BMS_CURRENT_INDEX+(BMS_NUM_VAR*2)+i));
	}
	for(i = 0; i < NUM_MPPT_CURRENTS; i++){
		fprintf(file, "%.2f, ", *(getMPPT()+MPPT_CURRENT_INDEX+i));
	}
	for(i = 0; i < NUM_MPPT_CURRENTS; i++){
		fprintf(file, "%.2f, ", *(getMPPT()+MPPT_CURRENT_INDEX+MPPT_NUM_VAR+i));
	}
	for(i = 0; i < NUM_MPPT_CURRENTS; i++){
		fprintf(file, "%.2f, ", *(getMPPT()+MPPT_CURRENT_INDEX+(MPPT_NUM_VAR*2)+i));
	}
	for(i = 0; i < NUM_MPPT_CURRENTS; i++){
		fprintf(file, "%.2f, ", *(getMPPT()+MPPT_CURRENT_INDEX+(MPPT_NUM_VAR*3)+i));
	}
	for(i = 0; i < NUM_ADC_VOLT_SENSORS; i++){
		fprintf(file, "%.2f, ", *(getADCVolts()+i));
	}
	for(i = 0; i < NUM_BMS_VOLTS; i++){
		fprintf(file, "%.2f, ", *(getBMS()+BMS_VOLT_INDEX+i));
	}
	for(i = 0; i < NUM_BMS_VOLTS; i++){
		fprintf(file, "%.2f, ", *(getBMS()+BMS_VOLT_INDEX+BMS_NUM_VAR+i));
	}
	for(i = 0; i < NUM_BMS_VOLTS; i++){
		fprintf(file, "%.2f, ", *(getBMS()+BMS_VOLT_INDEX+(BMS_NUM_VAR*2)+i));
	}
	for(i = 0; i < NUM_MPPT_VOLTS; i++){
		fprintf(file, "%.2f, ", *(getMPPT()+MPPT_VOLT_INDEX+i));
	}
	for(i = 0; i < NUM_MPPT_VOLTS; i++){
		fprintf(file, "%.2f, ", *(getMPPT()+MPPT_VOLT_INDEX+MPPT_NUM_VAR+i));
	}
	for(i = 0; i < NUM_MPPT_VOLTS; i++){
		fprintf(file, "%.2f, ", *(getMPPT()+MPPT_VOLT_INDEX+(MPPT_NUM_VAR*2)+i));
	}
	for(i = 0; i < NUM_MPPT_VOLTS; i++){
		fprintf(file, "%.2f, ", *(getMPPT()+MPPT_VOLT_INDEX+(MPPT_NUM_VAR*3)+i));
	}
	for(i = 0; i < NUM_ADC_TEMP_SENSORS; i++){
		fprintf(file, "%.2f, ", *(getADCTemps()+i));
	}
	for(i = 0; i < NUM_BMS_TEMPS; i++){
		fprintf(file, "%.2f, ", *(getBMS()+BMS_TEMP_INDEX+i));
	}
	for(i = 0; i < NUM_BMS_TEMPS; i++){
		fprintf(file, "%.2f, ", *(getBMS()+BMS_TEMP_INDEX+BMS_NUM_VAR+i));
	}
	for(i = 0; i < NUM_BMS_TEMPS; i++){
		fprintf(file, "%.2f, ", *(getBMS()+BMS_TEMP_INDEX+(BMS_NUM_VAR*2)+i));
	}
	for(i = 0; i < NUM_MPPT_TEMPS; i++){
		fprintf(file, "%.2f, ", *(getMPPT()+MPPT_TEMP_INDEX+i));
	}
	for(i = 0; i < NUM_MPPT_TEMPS; i++){
		fprintf(file, "%.2f, ", *(getMPPT()+MPPT_TEMP_INDEX+MPPT_NUM_VAR+i));
	}
	for(i = 0; i < NUM_MPPT_TEMPS; i++){
		fprintf(file, "%.2f, ", *(getMPPT()+MPPT_TEMP_INDEX+(MPPT_NUM_VAR*2)+i));
	}
	for(i = 0; i < NUM_MPPT_TEMPS; i++){
		fprintf(file, "%.2f, ", *(getMPPT()+MPPT_TEMP_INDEX+(MPPT_NUM_VAR*3)+i));
	}
	
	fclose(file);
}

void writeGPS(){
	FILE * file = fopen(usbMountGPS, "a");
	fflush(file);
	if(file == NULL){
		initUSB();
		printf("null file\n");
		logMessage("File pointer was null, check dmesg for file panic errors, if errors exist run 'fsck -r /dev/sda1'\n", 2);
		return;
	}
	fprintf(file, "\n%s, ", getDate());
	fprintf(file, "%s, ", getTime());
	fprintf(file, "%s, ", getLat());
	fprintf(file, "%s, ", getLong());
	fprintf(file, "%s, ", getHeading());
	fprintf(file, "%.2f, ", getSpeedGPSKnots());
	fprintf(file, "%.2f, ", getAltitude());
	fprintf(file, "%.2f, ", getAngle());
	fprintf(file, "%d, ", getFixType());
	fprintf(file, "%d, ", getQuality());
	fprintf(file, "%d, ", getNumSat());
	fprintf(file, "%.2f, ", getDOP());
	fprintf(file, "%.2f, ", getHDOP());
	fprintf(file, "%.2f, ", getVDOP());
	fclose(file);
}

void writeLog(){
	if(strlen(getLogBuff())>0){
		FILE * file = fopen(usbMountLog, "a");
		fflush(file);
		if(file == NULL){
			initUSB();
			printf("null file\n");
			logMessage("File pointer was null, check dmesg for file panic errors, if errors exist run 'fsck -r /dev/sda1'\n", 2);
			return;
		}
		fprintf(file, "%s, ", getDate());
		fprintf(file, "%s, ", getTime());
		fprintf(file, "%s", getLogBuff());
		fclose(file);
		clearLogBuffer();
	}
}

/**
* @}
*/
