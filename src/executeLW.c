#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "executeLW.h"
#include "takeBits.h"

int executeLW( mips * pMips, const uint rawArgs )
{
    int base, rt, offset, addr, memContent;

    base = takeBits( rawArgs, 6, 5 );
    rt = takeBits( rawArgs, 11, 5 );
    offset = takeBits( rawArgs, 16, 16 );

    addr = offset + pMips->registers[base];

    // Check natural alignment
    if((addr / 2) != 0 || ((addr >> 1) / 2) != 0 )
    {
	fprintf( stderr, "Error in LW : %#x is not naturally aligned !\n", addr );
    }
    else
    {
	// Load from the right memory location
	if( addr < pMips->sizeText * 4096 )
	{
	    // Data is in text segment
	    memContent = *(pMips->memText + addr);
	}
	else if( addr < (pMips->sizeText + pMips->sizeData) * 4096 )
	{
	    // Data is in data segment
	    memContent = *(pMips->memData + addr - (pMips->sizeText * 4096) );
	}
	else if( addr < (pMips->sizeText + pMips->sizeData + pMips->sizeBss) * 4096 )
	    // Data is in bss segment
	{
	    memContent = *(pMips->memBss + addr - ((pMips->sizeText + pMips->sizeData) * 4096) );
	}
	else
	{
	    fprintf( "Address %#x is out of memory!\n", addr );
	}

	// Load into register
	pMips->registers[rt] = memContent;

	// Update PC
	pMips->regPC = pMips->regPC + 4;
    }

    return 0;
}

