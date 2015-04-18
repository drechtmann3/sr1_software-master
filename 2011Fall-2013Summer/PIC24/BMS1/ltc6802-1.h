#ifndef ltc68021_h
#define ltc68021_h

/* ----- Command Codes -----
The LTC is hardcoded to respond to these. Refer to LTC datasheet for more info.
------------------------- */

// Basic commands
#define WRCFG (0x01) // Write configuration register group 
#define RDCFG (0x02) // Read configuration register group
#define RDCV  (0x04) // Read cell voltage register group
#define RDFLG (0x06) // Read flag register group 
#define RDTMP (0x08) // Read temperature register group

// Start cell voltage A/D conversions and poll status
#define STCVAD (0x10)       // All cell voltage inputs.
#define STCVADTEST1 (0x1E)  // Self test 1; all CV = 0x555
#define STCVADTEST2 (0x1F)  // Self test 2; all CV = 0xAAA

// Start open wire A/D conversions and poll status
#define STOWAD (0x20)       // All cell voltage inputs
#define STOWADTEST1 (0x2E)  // Self test 1; all CV = 0x555
#define STOWADTEST2 (0x2F)  // Self test 2; all CV = 0xAAA

// Start temperature A/D conversions and poll status
#define STTMPAD (0x30)      // All temperature inputs
#define STTMPADTEST1 (0x3E) // Self test 1; all CV = 0x555
#define STTMPADTEST2 (0x3F) // Self test 2; all CV = 0xAAA

#define PLADC (0x40)        // Poll A/D converter status
#define PLINT (0x50)        // Poll interrupt status

// Start cell voltage A/D conversions and poll status w/ discharge permitted
#define STCVDC (0x60)       // All cell voltage inputs
#define STCVDCTEST1 (0x6E)  // Self test 1; all CV = 0x555
#define STCVDCTEST2 (0x6F)  // Self test 2; all CV = 0xAAA

// Start open wire A/D conversions and poll status w/ discharge permitted
#define STOWDC (0x70)       // All cell voll voltage inputs
#define STOWDCTEST1 (0x7E)  // Self test 1; all CV = 0x555
#define STOWDCTEST2 (0x7F)  // Self test 2; all CV = 0xAAA

typedef struct LTC{
	unsigned char CFGRbytes[6];
}LTCcontrol;

//unsigned char setCFGR0(unsigned char CDC,unsigned char CELL10,unsigned char LVLPL,unsigned char GPIO1,unsigned char GPIO2,usigned char WDT) 
//typedef LTCcontrol unsigned char[6]; // LTC control corresponds to the 6 bytes of CFGR needed to modify LTC control state
/* ----- Configuration Bits ----- EDIT: Depreciated to aviod compiler dependancy
Make the LTC configuration bits (refer to manual) easily accessible by putting them into bit field unions.
Google to find out more about this trick. This method is not portable, since the order of fields
in a structure is compiler dependent, thus corrent endianness is not guaranteed for a different compiler.
For the Microchip C30 toolsuite, the least significant bit is defined first in the structure.
A very similar method is used in the p24x.h files to make bitfields for the PIC24 SFRs, so I figured
the correct endianness is preserved at least across PIC compilers.
-------------------------------*/
//
//volatile union CFGR0_union {
//	struct { //Allows access to individual bits in the SFR
//		unsigned CDC:3;
//		unsigned CELL10:1;
//		unsigned LVLPL:1;
//		unsigned GPIO1:1;
//		unsigned GPIO2:1;
//		unsigned WDT:1;
//	
//	} bits;
//	unsigned char byte; //Allows access to the entire byte
//	
//} CFGR0;
//
//volatile union CFGR1_union {
//	struct {
//		unsigned DCC1:1;
//		unsigned DCC2:1;
//		unsigned DCC3:1;
//		unsigned DCC4:1;
//		unsigned DCC5:1;
//		unsigned DCC6:1;
//		unsigned DCC7:1;
//		unsigned DCC8:1;
//	
//	} bits;
//	unsigned char byte;
//	
//} CFGR1;
//
//volatile union CFGR2_union {
//	struct {
//		unsigned DCC9:1;
//		unsigned DCC10:1;
//		unsigned DCC11:1;
//		unsigned DCC12:1;
//		unsigned MC1I:1;
//		unsigned MC2I:1;
//		unsigned MC3I:1;
//		unsigned MC4I:1;
//	
//	} bits;
//	unsigned char byte;
//	
//} CFGR2;
//
//volatile union CFGR3_union {
//	struct {
//		unsigned MC5I:1;
//		unsigned MC6I:1;
//		unsigned MC7I:1;
//		unsigned MC8I:1;
//		unsigned MC9I:1;
//		unsigned MC10I:1;
//		unsigned MC11I:1;
//		unsigned MC12I:1;
//	
//	} bits;
//	unsigned char byte;
//	
//} CFGR3;
//
//volatile union CFGR4_union {
//	struct {
//		unsigned VUV:8;
//	
//	} bits;
//	unsigned char byte;
//	
//} CFGR4;
//
//volatile union CFGR5_union {
//	struct {
//		unsigned VOV:8;
//	
//	} bits;
//	unsigned char byte;
//	
//} CFGR5;

#endif
