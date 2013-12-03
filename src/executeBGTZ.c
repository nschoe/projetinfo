#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "executeBGTZ.h"
#include "takeBits.h"

int executeBGTZ( mips * pMips, const uint rawArgs )
{
    int rs, offset;

    rs = takeBits( rawArgs, 6, 5 );
    offset = takeBits( rawArgs, 16, 16 );
    if(offset > 32767)
	offset = offset - 65536;

    if( pMips->registers[rs] > 0x0 )
    {
	pMips->regPC = pMips->regPC + 4 + offset*4;
    }
    else
    {
	pMips->regPC = pMips->regPC + 4;
    }

    return 0;
}

