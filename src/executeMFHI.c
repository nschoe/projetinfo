#include <stdlib.h>
#include <stdio.h>

#include "executeMFHI.h"
#include "takeBits.h"

int executeMFHI( mips * pMips, const uint rawArgs )
{   
    int rd;

    rd = takeBits( rawArgs, 16, 5 );

    pMips->registers[rd] = pMips->regHI;

    // Update PC
    pMips->regPC = pMips->regPC + 4;

    return 0;
}

