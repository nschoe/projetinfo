#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "executeLUI.h"
#include "takeBits.h"

int executeLUI( mips * pMips, const uint rawArgs )
{
    int rt, immediate;

    rt = takeBits( rawArgs, 11, 5 );
    immediate = takeBits( rawArgs, 16, 16 );

    pMips->registers[rt] = (immediate << 16);

    return 0;
}

