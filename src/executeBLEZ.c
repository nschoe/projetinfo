#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "executeBLEZ.h"
#include "takeBits.h"

int executeBLEZ( mips * pMips, const uint rawArgs )
{
    int rs, offset;

    rs = takeBits( rawArgs, 6, 5 );
    offset = takeBits( rawArgs, 16, 16 );

    if( pMips->registers[rs] <= 0x0 )
    {
	    // TO CHECK : is it PC + 4 + offset or just PC + offset ?
	pMips->regPC = pMips->regPC + (offset << 2);
    }
    else
    {
	pMips->regPC = pMips->regPC + 4;
    }

    return 0;
}

