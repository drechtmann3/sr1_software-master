/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

#include <GenericTypeDefs.h>       /* For true/false definition */


#include "user.h"
#include "cancom.h"
/******************************************************************************/
/* User Functions                                                             */
/******************************************************************************/

/* <Initialize variables in user.h and insert code for user algorithms.> */

void InitApp(void)
{
    initCan();

    /* Setup analog functionality and port direction */

    /* Initialize peripherals */

    /* Configure the IPEN bit (1=on) in RCON to turn on/off int priorities */

    /* Enable interrupts */
}
