#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "executeADD.h"
#include "takeBits.h"

int executeADD( mips * pMips, const uint rawArgs )
{
    long result;
    int truncatedResult;
    int rs, rd, rt, ret;

    rs = takeBits( rawArgs, 6, 5 );
    rt = takeBits( rawArgs, 11, 5 );
    rd = takeBits( rawArgs, 16, 5 );

    // compute result in 64 bits
    result = (long)pMips->registers[rs] + (long)pMips->registers[rt];
    // truncate result on 32 bits
    truncatedResult = (int)result;

    // check if the two results are the same or not (overflow)
    if( result == truncatedResult )
    {
	// No overflow : proceed
	pMips->registers[rd] = (int)truncatedResult;

	// Update PC
	pMips->regPC = pMips->regPC + 4;

	// happened okay
	ret = 0;
    }
    else
    {
	// overflow : raise flag and do not update
	pMips->regSR = (pMips->SR) || 0x800; // 2^11

	// happened okay
	ret = 0;
    }

    return ret;
}

