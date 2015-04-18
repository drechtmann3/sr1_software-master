/******************************************************************************/
/*Files to Include                                                            */
/******************************************************************************/

#include <GenericTypeDefs.h>       /* For true/false definition */

#include "p18f4321.h"
#include "system.h"
/* Refer to the device datasheet for information about available
oscillator configurations. */
void ConfigureOscillator(void)
{
    OSCCON = OneTwentyFivekHz&&InternalOscillatorBlock; 
}
