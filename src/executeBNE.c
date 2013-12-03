#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "executeBNE.h"
#include "takeBits.h"

int executeBNE( mips * pMips, const uint rawArgs )
{
    int rs, rt, offset;

    rs = takeBits( rawArgs, 6, 5 );
    rt = takeBits( rawArgs, 11, 5 );
    offset = takeBits( rawArgs, 16, 16 );
    if(offset > 32767)
	offset = offset - 65536;

    if( pMips->registers[rs] != pMips->registers[rt] )
    {
	pMips->regPC = pMips->regPC + 4 + offset*4;
    }
    else
    {
	pMips->regPC = pMips->regPC + 4;
    }

    return 0;
}

