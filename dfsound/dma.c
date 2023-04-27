/***************************************************************************
                            dma.c  -  description
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

#include "stdafx.h"

#define _IN_DMA

#include "externals.h"

bool readFromCdData = false;

////////////////////////////////////////////////////////////////////////
// READ DMA (one value)
////////////////////////////////////////////////////////////////////////

unsigned short DF_SPUreadDMA(void)
{
 unsigned short s = *(unsigned short *)(spu.spuMemC + spu.spuAddr);
 spu.spuAddr += 2;
 spu.spuAddr &= 0x7fffe;

 return s;
}

////////////////////////////////////////////////////////////////////////
// READ DMA (many values)
////////////////////////////////////////////////////////////////////////

void DF_SPUreadDMAMem(unsigned short *pusPSXMem, int iSize,
    unsigned int cycles)
{
    int i;

    //do_samples_if_needed(cycles, 1);

    for (i = 0; i < iSize; i++)
    {
        if (spu.spuAddr <= 0x07ff) // CD audio
        {
            // For Vib Ribbon
            *pusPSXMem = LOAD_SWAP16p(spu.spuMemC + spu.spuAddr);
            readFromCdData = true;
        }
        else
        {
            *pusPSXMem = *(unsigned short *)(spu.spuMemC + spu.spuAddr);
            readFromCdData = false;
        }
        pusPSXMem++;
        spu.spuAddr += 2;
        spu.spuAddr &= 0x7fffe;
    }
}

////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

// to investigate: do sound data updates by writedma affect spu
// irqs? Will an irq be triggered, if new data is written to
// the memory irq address?

////////////////////////////////////////////////////////////////////////
// WRITE DMA (one value)
////////////////////////////////////////////////////////////////////////

void DF_SPUwriteDMA(unsigned short val)
{
 *(unsigned short *)(spu.spuMemC + spu.spuAddr) = val;

 spu.spuAddr += 2;
 spu.spuAddr &= 0x7fffe;
 spu.bMemDirty = 1;
}

////////////////////////////////////////////////////////////////////////
// WRITE DMA (many values)
////////////////////////////////////////////////////////////////////////

void DF_SPUwriteDMAMem(unsigned short *pusPSXMem, int iSize,
    unsigned int cycles)
{
    int i;

    //do_samples_if_needed(cycles, 1);
    spu.bMemDirty = 1;

    for (i = 0; i < iSize; i++)
    {
        if (readFromCdData && spu.rvb->StartAddr > 0 &&  spu.spuAddr >= spu.rvb->StartAddr * 2)
        {
            // For Vib Ribbon
            STORE_SWAP16p(spu.spuMemC + spu.spuAddr, *pusPSXMem++);
        }
        else
        {
            *(unsigned short *)(spu.spuMemC + spu.spuAddr) = *pusPSXMem++;
        }
        spu.spuAddr += 2;
        spu.spuAddr &= 0x7fffe;
    }
}

////////////////////////////////////////////////////////////////////////
