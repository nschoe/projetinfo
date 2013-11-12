#include <stdlib.h>
#include <stdio.h>

#include "executeOR.h"
#include "takeBits.h"

int executeOR( mips * pMips, const uint rawArgs )
{   
    int rs, rd, rt;

    rs = takeBits( rawArgs, 6, 5 );
    rt = takeBits( rawArgs, 11, 5 );
    rd = takeBits( rawArgs, 16, 5 );

    pMips->registers[rd] = (pMips->registers[rs]) | (pMips->registers[rt]);

    return 0;
}

