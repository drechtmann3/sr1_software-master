// #include "log.h"
// #include "DIO.h"
// #include <stdio.h>
// #include <sys/mount.h>
// #include <string.h>
// #include "datastore.h"

// /**
// * @ingroup telemetry
// * @defgroup usb USB
// * @brief USB functions
// * 
// * @{
// */


// /**@author Michelle Van Enige <mave3@gatech.edu> 727-433-2927
// @brief attempts to mount the drive by trying sdanum a-z
// @todo what happens on the 27th try?
// */
// int initUSB(){
	// int i;
	// for(i = 0; i < 26; i++) {
		// char usbMountFromPathTry[256]; 
		// char sdanum[5];
		// strcpy(usbMountFromPathTry, usbMountFromPath);
		// sprintf(sdanum, "%c1", i+'a');
		// strcat(usbMountFromPathTry, sdanum);
		// if(!mount(usbMountFromPathTry, usbMountToPath, "vfat", (long)NULL, NULL)){ 
			// printf("Mount successful\n");
			// return 1;
		// } else if(!mount(usbMountFromPathTry, usbMountToPath, "vfat", MS_REMOUNT, NULL)){
			// printf("Mount successful\n");
			// return 1;
		// }
		// printf("Mount error: ");
		// printf("%s\n", usbMountFromPathTry);
	// }
	// printf("Mount ERROR\n");
	// return 0;
// }


// void writeLog(int level, char * message){
	// FILE * file = fopen(usbMountLog, "a");
	// fflush(file);
	// if(file == NULL){
		// if(!initUSB()){
			// printf("null file\n");
			// printf("File pointer was null, check dmesg for file panic errors, if errors exist run 'fsck -r /dev/sda1'\n");
			// return;
		// }
	// }
	// static int writeHeader = 0;
	// if(writeHeader == 0){
		// writeHeader = 1;
		// fprintf(file, "Date, Time, Error Level, message\n");
	// }
	// fprintf(file, "%s, ", getDate());
	// fprintf(file, "%s, ", getTime());
	// fprintf(file, "%d, ", level);
	// fprintf(file, "%s", message);
	// fprintf(file, "\n");
	// fclose(file);
	// printf("LOG %d: %s\n", level, message);
	 
// }

