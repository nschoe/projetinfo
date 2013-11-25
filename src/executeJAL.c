#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "executeJAL.h"
#include "takeBits.h"

int executeJAL( mips * pMips, const uint rawArgs )
{
    int offset;

    offset = takeBits( rawArgs, 6, 26 );

    // Place return address 
    pMips->registers[31] = pMips->regPC + 8;

    offset = (takeBits(pMips->regPC, 0, 4 ) << 28 ) + (offset << 2);

    pMips->regPC = offset;

    return 0;
}

