#include "s.h"

int executeS(mips * pMips)
{
    uint value, addr;

    addr = pMips->regPC + 8;
    value = pMips->memText[pMips->regPC] >> 26;
    execute(pMips);
    if(value == 0x03)
    {
	while(pMips->regPC != addr)
	    execute(pMips);
    }

    return 0;
}

int parseS( mips * pMips, char * args )
{
    if(!strcmp(" ", args) || !strcmp("", args))
	executeS(pMips);
    else
	WARNING_MSG( "Command s need no arguments\n" );

    return 0;
}
