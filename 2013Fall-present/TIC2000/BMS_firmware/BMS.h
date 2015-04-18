#ifndef BMSHEADER_H_GUARD
#define BMSHEADER_H_GUARD

#include <math.h>
#include <stdio.h>
#include "main.h"
#include "28069Common.h"
#include "LTC_Interface.h"
#include "SPI_Funcs.h"
#include "SOC.h"
#include "Temp.h"
#include "CurrentSense.h"

void readSPIVoltages();
void turnOffCar();

extern volatile float32 batCurrent;
#endif
