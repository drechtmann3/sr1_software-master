#ifndef BMSHEADER_H_GUARD
#define BMSHEADER_H_GUARD

#include <math.h>
#include <stdio.h>
#include "28069Common.h"
#include "CAN.h"
#include "LTC_Interface.h"
#include "Init_Funcs.h"
#include "SPI_Funcs.h"
#include "SOC.h"
#include "Temp.h"
#include "CurrentSense.h"
#include "Flash2806x_API.h"
#include "BMS_CAN.h"


void readSPIVoltages();
void turnOffCar();

#endif
