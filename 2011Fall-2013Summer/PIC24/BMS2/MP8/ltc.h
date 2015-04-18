/* 
 * File:   ltc.h
 * Author: SJ
 *
 * Created on April 9, 2013, 12:21 AM
 */

#ifndef LTC_H
#define	LTC_H

#ifdef	__cplusplus
extern "C" {
#endif
#define CFGR0 (0b01111100)  // old was 0b10010010
#define CFGR1 (0b00000000)
#define CFGR2 (0b00000000)
#define CFGR3 (0b00000000)
#define CFGR4 (135) // for running
#define CFGR5 (182) // for running
#define WRCFG (0x01)
#define RDCV (0x04) // All cells
#define RDCVA (0x06) // Just cells 1-4
#define STCVAD (0x10)
#define STCVDC (0x60)
#define RDTMP (0x0E)
#define LTC_CS_SELECT (0)
#define LTC_CS_DESELECT (1)
#define LTC1 (0)
#define LTC2 (1)
#define LTC3 (2)
#define LTC_ALL (3)
#define LTC_CLOCK_LOW (0)
#define LTC_CLOCK_HI (1)
#define CELL_CUTOFF_HI (3650)
#define CELL_CUTOFF_LOW (2000)
#define CELL_WARN_HI (3400)
#define CELL_WARN_LOW (2500)


int LTC_readVoltages(int LTC);
void LTC_sendCommand(char command);
char PEC(char cmd);
char continuePEC(char cmd, char PEC);
void LTC_writeConfig(int LTC, int discharge);
void LTC_CS(int LTC, int CS);
int LTC_getMISO(int ltcNum);
void LTC_setMOSI(int mosi);
void LTC_setClock(int clock);
int initLTC();

#ifdef	__cplusplus
}
#endif

#endif	/* LTC_H */

