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

    if( pMips->registers[rs] != pMips->registers[rt] )
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

