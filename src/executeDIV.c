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

    if( pMips->registers[rt] != 0 )
    {
	// no division by zero : proceed
	pMips->regLO = pMips->registers[rs] / pMips->registers[rt];
	pMips->regHI = pMips->registers[rs] % pMips->registers[rt];
    }
    else
    {
	// division by zero : flag
	pMips->regSR = (pMips->regSR) || 0x40; // 2^6
    }

    // Update PC
    pMips->regPC = pMips->regPC + 4;

    return 0;
}

