#include <stdlib.h>
#include <stdio.h>

#include "executeROTR.h"
#include "takeBits.h"

int executeROTR( mips * pMips, const uint rawArgs )
{   
    int sa, rd, rt, temp;

    sa = takeBits( rawArgs, 21, 5 );
    rt = takeBits( rawArgs, 11, 5 );
    rd = takeBits( rawArgs, 16, 5 );

    temp = takeBits( pMips->registers[rt], 31 - (sa - 1), sa ) << (32 - sa);
    temp += takeBits( pMips->registers[rt], 0, 32 - sa);
    
    pMips->registers[rd] = temp;

    // Update PC
    pMips->regPC = pMips->regPC + 4;

    return 0;
}

