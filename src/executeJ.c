#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "executeJ.h"
#include "takeBits.h"

int executeJ( mips * pMips, const uint rawArgs )
{
    int offset;

    offset = takeBits( rawArgs, 6, 26 );

    offset = (takeBits(pMips->regPC, 0, 4 ) << 28 ) + (offset << 2);

    pMips->regPC = offset;

    return 0;
}

