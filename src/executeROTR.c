#include <stdlib.h>
#include <stdio.h>

#include "executeROTR.h"
#include "takeBits.h"

int executeROTR( mips * pMips, const uint rawArgs )
{   
    /* TO FIX
       It is not implemented the right way : make the effective rotation
    */

    int sa, rd, rt, i, temp;

    sa = takeBits( rawArgs, 21, 5 );
    rt = takeBits( rawArgs, 11, 5 );
    rd = takeBits( rawArgs, 16, 5 );

    temp = pMips->registers[rt];

    // Shift bytes
    for( i = 0; i < sa; i++ )
    {
	temp = temp / 2;
    }
    
    pMips->registers[rd] = temp;

    // Update PC
    pMips->regPC = pMips->regPC + 4;

    return 0;
}

