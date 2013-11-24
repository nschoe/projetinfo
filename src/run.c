#include "run.h"

int executeRun( mips * pMips )
{
    uint endValue = pMips->sizeText*4096;

    if(pMips->memText)
    {
	endValue = minOver(pMips->bpList, pMips->regPC);
	while(pMips->regPC < endValue)
	    execute(pMips);

	return 0;
    }

    printf("No load program\n");

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
