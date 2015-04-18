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
#define CFGR0 (0b10010010)
#define LTC_UNDERVOLT (0x5B0)
#define LTC_OVERVOLT (0xB10)
#define WRCFG (0x01)
#define RDCV (0x04)
#define STCVAD (0x10)

void writeConfig(int address, int discharge);
int calcPEC(int cmd);
void sendSPI(int cmd);
void cycleClock();
int calcPECMult(int cmd, char PEC);
void readCellVolts(int address, int voltarray[]);
int receiveSPI(int address, int bits);
int checkCellVolts(int voltArray[]);
#ifdef	__cplusplus
}
#endif

#endif	/* LTC_H */

