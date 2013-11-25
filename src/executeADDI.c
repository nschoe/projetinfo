#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "executeADDI.h"
#include "takeBits.h"

int executeADDI( mips * pMips, const uint rawArgs )
{
    long result;
    int truncatedResult;
    int rs, rt, ret, constant;

    rs = takeBits( rawArgs, 6, 5 );
    rt = takeBits( rawArgs, 11, 5 );
    constant = takeBits( rawArgs, 16, 16 );

    // compute result in 64 bits
    result = (long)pMips->registers[rs] + (long) constant;
    // truncate result on 32 bits
    truncatedResult = (int)result;

    // check if the two results are the same or not (overflow)
    if( result == truncatedResult )
    {
	// No overflow : proceed
	pMips->registers[rt] = (int)truncatedResult;

	// Update PC
	pMips->regPC = pMips->regPC + 4;

	// happened okay
	ret = 0;
    }
    else
    {
	// overflow : raise flag and do not update
	pMips->regSR = (pMips->regSR) || 0x800; // 2^11

	// happened okay
	ret = 0;
    }

    return ret;
}

