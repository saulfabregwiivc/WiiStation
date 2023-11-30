/***************************************************************************
                            spu.h  -  description
                             -------------------
    begin                : Wed May 15 2002
    copyright            : (C) 2002 by Pete Bernert
    email                : BlackDove@addcom.de
 ***************************************************************************/
/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version. See also the license.txt file for *
 *   additional informations.                                              *
 *                                                                         *
 ***************************************************************************/

#ifndef __P_SPU_H__
#define __P_SPU_H__

struct SPUFreeze;
struct xa_decode;

long CALLBACK DF_SPUopen(void);
long CALLBACK DF_SPUinit(void);
long CALLBACK DF_SPUshutdown(void);
long CALLBACK DF_SPUclose(void);
void CALLBACK DF_SPUwriteRegister(unsigned long, unsigned short, unsigned int);
unsigned short CALLBACK DF_SPUreadRegister(unsigned long, unsigned int);
void CALLBACK DF_SPUregisterCallback(void (*cb)(int));
void CALLBACK DF_SPUregisterScheduleCb(void (*cb)(unsigned int));
long CALLBACK DF_SPUfreeze(unsigned int, struct SPUFreeze *, unsigned int);
void CALLBACK DF_SPUasync(unsigned int cycle, unsigned int flags, unsigned int psxType);

void CALLBACK DF_SPUreadDMAMem(unsigned short * pusPSXMem,int iSize,unsigned int cycles);
void CALLBACK DF_SPUwriteDMAMem(unsigned short * pusPSXMem,int iSize,unsigned int cycles);

void CALLBACK DF_SPUplayADPCMchannel(struct xa_decode *xap, unsigned int cycle, int is_start);
int  CALLBACK DF_SPUplayCDDAchannel(short *pcm, int bytes, unsigned int cycle, int is_start);
void CALLBACK DF_SPUsetCDvol(unsigned char ll, unsigned char lr,
		unsigned char rl, unsigned char rr, unsigned int cycle);

// internal
void ClearWorkingState(void);

#endif /* __P_SPU_H__ */
