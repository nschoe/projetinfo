#include <stdlib.h>
#include <stdio.h>

#include "executeSRL.h"
#include "takeBits.h"

int executeSRL( mips * pMips, const uint rawArgs )
{   
    int sa, rd, rt;

    sa = takeBits( rawArgs, 21, 5 );
    rt = takeBits( rawArgs, 11, 5 );
    rd = takeBits( rawArgs, 16, 5 );
    
    pMips->registers[rd] = pMips->registers[rt] >> sa;

    // Update PC
    pMips->regPC = pMips->regPC + 4;

    return 0;
}

