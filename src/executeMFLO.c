#include <stdlib.h>
#include <stdio.h>

#include "executeMFLO.h"
#include "takeBits.h"

int executeMFLO( mips * pMips, const uint rawArgs )
{   
    int rd;

    rd = takeBits( rawArgs, 16, 5 );

    pMips->registers[rd] = pMips->regLO;

    return 0;
}

