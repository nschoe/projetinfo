#include <stdlib.h>
#include <stdio.h>

#include "executeMULT.h"
#include "takeBits.h"

int executeMULT( mips * pMips, const uint rawArgs )
{   
    int rs, rt;
    long prod;

    rs = takeBits( rawArgs, 6, 5 );
    rt = takeBits( rawArgs, 11, 5 );

    prod = (long) ((pMips->registers[rs]) * (pMips->registers[rt]));

    pMips->regLO = (int) (prod << 32) >> 32;
    pMips->regHI = (int) (prod >> 32);

    // Update PC
    pMips->regPC = pMips->regPC + 4;

    return 0;
}

