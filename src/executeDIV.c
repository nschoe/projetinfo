#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "executeDIV.h"
#include "takeBits.h"

int executeDIV( mips * pMips, const uint rawArgs )
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

