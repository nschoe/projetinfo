#include <stdlib.h>
#include <stdio.h>

#include "executeNOP.h"
#include "takeBits.h"

int executeNOP( mips * pMips )
{   
    // Update PC
    pMips->regPC = pMips->regPC + 4;
    
    return 0;
}

