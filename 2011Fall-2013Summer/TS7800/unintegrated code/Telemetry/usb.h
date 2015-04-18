#ifndef USB_H
#define USB_H

static const char usbMountFromPath[] = "/dev/sd";
static const char usbMountToPath[] = "/home/eclipse/flashdrive";
static const char usbMountEssentials[] = "/home/eclipse/flashdrive/Essentials.csv";
static const char usbMountCVT[] = "/home/eclipse/flashdrive/CVT.csv";
static const char usbMountGPS[] = "/home/eclipse/flashdrive/GPS.csv";
static const char usbMountLog[] = "/home/eclipse/flashdrive/Log.csv";
static const char HMITelemCheckFile[] = "/home/eclipse/flashdrive/DONOTREMOVE.TXT";

int initUSB();
void writeEssentials();
void writeCVT();
void writeGPS();
void writeLog();


#endif
