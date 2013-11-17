#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "executeXOR.h"
#include "takeBits.h"

int executeXOR( mips * pMips, const uint rawArgs )
{
    int rs, rd, rt;

    rs = takeBits( rawArgs, 6, 5 );
    rd = takeBits( rawArgs, 16, 5 );
    rt = takeBits( rawArgs, 11, 5 );

    pMips->registers[rd] = pMips->registers[rs] ^ pMips->registers[rt];

    // Update PC
    pMips->regPC = pMips->regPC + 4;

    return 0;
}

