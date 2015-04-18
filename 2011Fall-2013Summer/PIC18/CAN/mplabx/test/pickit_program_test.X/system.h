/******************************************************************************/
/* System Level #define Macros                                                */
/******************************************************************************/

/* TODO Define system operating frequency */

/* Microcontroller MIPs (FCY) */
#define SYS_FREQ        8000000L
#define FCY             SYS_FREQ/4

//bit 6-4 IRCF2:IRCF0: Internal Oscillator Frequency Select bits
//(INTOSC drives clock directly)
#define EightMHz 0x70
#define FourMHz 0x60
#define TwoMHz 0x50
#define OneMHz 0x40
#define FiveHundkHz 0x30
#define TwoFiftykHz 0x20
#define OneTwentyFivekHz 0x10
//(from either INTOSC/256 or INTRC directly)(2)
#define ThirtyOnekHz 0x00

//bit 1-0 SCS1:SCS0: System Clock Select bits(4)
#define InternalOscillatorBlock 0x02
#define SecondaryOscillator 0x01
#define PrimaryOscillator   0x00


/******************************************************************************/
/* System Function Prototypes                                                 */
/******************************************************************************/

/* Custom oscillator configuration funtions, reset source evaluation
functions, and other non-peripheral microcontroller initialization functions
go here. */

void ConfigureOscillator(void); /* Handles clock switching/osc initialization */
