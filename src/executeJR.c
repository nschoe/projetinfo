#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "executeJR.h"
#include "takeBits.h"

int executeJR( mips * pMips, const uint rawArgs )
{
    int rs;

    rs = takeBits( rawArgs, 6, 5 );

    pMips->regPC = pMips->registers[rs];

    return 0;
}

