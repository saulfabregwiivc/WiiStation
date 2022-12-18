/***************************************************************************
 *   Copyright (C) 2007 Ryan Schultz, PCSX-df Team, PCSX team              *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Street, Fifth Floor, Boston, MA 02111-1307 USA.           *
 ***************************************************************************/

#ifndef __CDROM_H__
#define __CDROM_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "psxcommon.h"
#include "decode_xa.h"
#include "r3000a.h"
#include "plugins.h"
#include "psxmem.h"
#include "psxhw.h"

//#define btoi(b)     ((b) / 16 * 10 + (b) % 16) /* BCD to u_char */
//#define btoi(b)		(((b) >> 4) * 10 + ((b) & 15)) /* BCD to u_char */
#define btoi(b)		(btoiBuf[b]) /* BCD to u_char */
//#define itob(i)     ((i) / 10 * 16 + (i) % 10) /* u_char to BCD */
//#define itob(i)		((((i) / 10) << 4) + (i) % 10)  /* u_char to BCD */
#define itob(i)		(itobBuf[i])  /* u_char to BCD */

#define ABS_CD(x) ((x >= 0) ? x : -x)
#define MIN_VALUE(a,b) ({ __typeof__ (a) _a = (a); __typeof__ (b) _b = (b); _a < _b ? _a : _b; })
#define MAX_VALUE(a,b) ({ __typeof__ (a) _a = (a); __typeof__ (b) _b = (b); _a > _b ? _a : _b; })

//#define MSF2SECT(m, s, f)		(((m) * 60 + (s) - 2) * 75 + (f))
#define MSF2SECT(m, s, f)		(msf2SectM[(m)] + msf2SectS[(s)] - 150 + (f))

#define CD_FRAMESIZE_RAW		2352
#define DATA_SIZE				(CD_FRAMESIZE_RAW - 12)

#define SUB_FRAMESIZE			96

typedef struct {
	// unused members maintain savesate compatibility
	unsigned char unused0;
	unsigned char unused1;
	unsigned char Reg2;
	unsigned char unused2;
	unsigned char Ctrl;
	unsigned char Stat;

	unsigned char StatP;

	unsigned char Transfer[DATA_SIZE];
	struct {
		unsigned char Track;
		unsigned char Index;
		unsigned char Relative[3];
		unsigned char Absolute[3];
	} subq;
	unsigned char TrackChanged;
	unsigned char unused3[3];
	unsigned int  freeze_ver;

	unsigned char Prev[4];
	unsigned char Param[8];
	unsigned char Result[16];

	unsigned char ParamC;
	unsigned char ParamP;
	unsigned char ResultC;
	unsigned char ResultP;
	unsigned char ResultReady;
	unsigned char Cmd;
	unsigned char SubqForwardSectors;
	unsigned char SetlocPending;
	u32 Reading;

	unsigned char ResultTN[6];
	unsigned char ResultTD[4];
	union {
        unsigned char SetSectorPlay[4];
        u32           SetSectorPlayU32;
    };
	union {
        unsigned char SetSectorEnd[4];
        u32           SetSectorEndU32;
    };
	union {
        unsigned char SetSector[4];
        u32           SetSectorU32;
    };
	unsigned char Track;
	bool Play, Muted;
	int CurTrack;
	int Mode, File, Channel;
	unsigned char LocL[8];
	int FirstSector;

	xa_decode_t Xa;

	u16 FifoOffset;
	u16 FifoSize;

	u16 CmdInProgress;
	u8 Irq1Pending;
	u8 unused5;
	u32 unused6;

	u8 unused7;

	u8 DriveState;
	u8 FastForward;
	u8 FastBackward;
	u8 unused8;

	u8 AttenuatorLeftToLeft, AttenuatorLeftToRight;
	u8 AttenuatorRightToRight, AttenuatorRightToLeft;
	u8 AttenuatorLeftToLeftT, AttenuatorLeftToRightT;
	u8 AttenuatorRightToRightT, AttenuatorRightToLeftT;
} cdrStruct;

extern cdrStruct cdr;
extern unsigned char btoiBuf[];
extern unsigned char itobBuf[];
extern int msf2SectM[];
extern int msf2SectS[];
extern int msf2SectMNoItob[];
extern int msf2SectSNoItob[];

void cdrReset();

void cdrInterrupt(void);
void cdrPlayReadInterrupt(void);
void cdrLidSeekInterrupt(void);
void cdrDmaInterrupt(void);
void LidInterrupt(void);
unsigned char cdrRead0(void);
unsigned char cdrRead1(void);
unsigned char cdrRead2(void);
unsigned char cdrRead3(void);
void cdrWrite0(unsigned char rt);
void cdrWrite1(unsigned char rt);
void cdrWrite2(unsigned char rt);
void cdrWrite3(unsigned char rt);
int cdrFreeze(gzFile f, int Mode);

bool swapIso;
void (*p_cdrPlayCddaData)(int timePlus, int isEnd, s16* cddaBuf);
void (*p_cdrAttenuate)(s16 *buf, int samples, int stereo);

#ifdef __cplusplus
}
#endif
#endif
