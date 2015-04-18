/**
* @ingroup telemetry
* @defgroup conversions Conversions
* @brief Unit conversion functions
* 
* @{
*/

#include "wrapper.h"

double knotsToMPH(int speed){
	return (speed * 1.15077945); 
}

double knotsToKMH(int speed){
	return (speed * 1.852);
}

double RPMToMPH(int rpm){
	return (2*3.14159265*WHEEL_RADIUS*rpm*(60.0/5280.0));
}

/**
* @}
*/
