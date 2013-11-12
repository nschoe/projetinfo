#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "executeAND.h"
#include "takeBits.h"

int executeAND( mips * pMips, const uint rawArgs )
{
    int rs, rd, rt, ret;

    rs = takeBits( rawArgs, 6, 5 );
    rt = takeBits( rawArgs, 11, 5 );
    rd = takeBits( rawArgs, 16, 5 );

    ret = 0;

    return ret;
}

