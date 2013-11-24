#include "run.h"

int executeRun( mips * pMips )
{
    if(pMips->memText)
    {
	while(pMips->regPC < pMips->sizeText*4096) 
	    execute(pMips);

	return 0;
    }

    printf("no load program\n");

    return 1;
}

int parseRun( mips * pMips, char * args )
{
    uint addr;

    if(strcmp(" ", args) != 0 && strcmp("", args) != 0)
    {
	addr = parseHexa(args + 1);
	if(addr < pMips->sizeText*4096)
	    pMips->regPC = addr;
    }
    executeRun(pMips);

    return 0;
}
