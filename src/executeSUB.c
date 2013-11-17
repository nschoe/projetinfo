#include <stdlib.h>
#include <stdio.h>

#include "executeSUB.h"
#include "takeBits.h"

int executeSUB( mips * pMips, const uint rawArgs )
{   
    int sa, rd, rt, temp;

    rs = takeBits( rawArgs, 6, 5 );
    rt = takeBits( rawArgs, 11, 5 );
    rd = takeBits( rawArgs, 16, 5 );
    
    temp = pMips->registers[rs] - pMips->registers[rt];
    
    // Check for overflow
    if( temp < 0 )
    {
	// overflow : raise flag and do not update register
	pMips->regSR = (pMips->regSR) || 0x800; // 2^11
    }
    else
    {
	// no overflow : proceed
	pMips->registers[rd] = temp;
    }

    // Update PC
    pMips->regPC = pMips->regPC + 4;

    return 0;
}

