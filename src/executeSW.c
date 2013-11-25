#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "executeSW.h"
#include "takeBits.h"

int executeSW( mips * pMips, const uint rawArgs )
{
    int base, rt, offset, addr;

    base = takeBits( rawArgs, 6, 5 );
    rt = takeBits( rawArgs, 11, 5 );
    offset = takeBits( rawArgs, 16, 16 );

    addr = offset + pMips->registers[base];

    // Check natural alignment
    if((addr / 2) != 0 || ((addr >> 1) / 2) != 0 )
    {
	fprintf( stderr, "Error in SW : %#x is not naturally aligned !\n", addr );
    }
    else
    {
	// Load from the right memory location
	if( addr < pMips->sizeText * 4096 )
	{
	    // Data is in text segment
	    *(pMips->memText + addr) = pMips->registers[rt];
	}
	else if( addr < (pMips->sizeText + pMips->sizeData) * 4096 )
	{
	    // Data is in data segment
	    *(pMips->memData + addr - (pMips->sizeText * 4096) ) = pMips->registers[rt];
	}
	else if( addr < (pMips->sizeText + pMips->sizeData + pMips->sizeBss) * 4096 )
	    // Data is in bss segment
	{
	    *(pMips->memBss + addr - ((pMips->sizeText + pMips->sizeData) * 4096) ) = pMips->registers[rt];
	}
	else
	{
	    fprintf( "Address %#x is out of memory!\n", addr );
	}

	// Update PC
	pMips->regPC = pMips->regPC + 4;
    }

    return 0;
}

