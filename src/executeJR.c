#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "executeJR.h"
#include "takeBits.h"

int executeJR( mips * pMips, const uint rawArgs )
{
    int rs, rt;

    rs = takeBits( rawArgs, 6, 5 );
    rt = takeBits( rawArgs, 11, 5 );

    if( pMips->regisers[rt] != 0 )
    {
	pMips->regLO = pMips->registers[rs] / pMips->registers[rt];
	pMips->regHI = pMips->registers[rs] % pMips->registers[rt];
    }

    return 0;
}

