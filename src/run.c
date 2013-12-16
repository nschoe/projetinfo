#include "run.h"

int executeRun( mips * pMips )
{
    uint i, endValue = pMips->realSizeText;
    if(pMips->memText)
    {
	i = minOver(pMips->bpList, pMips->regPC);
	if(i != 0)
	    endValue = i;
	while(pMips->regPC < endValue)
	{
	    executeDa(pMips, pMips->regPC, 1);
	    i = execute(pMips);
	    if(i == 1)
		return 0;
	    else if(i == 2)
		return 1;
	}
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
	if(addr < pMips->realSizeText)
	{
	    if(!(addr % 4))
		pMips->regPC = addr;
	    else
	    {
		printf("This adress not multiple of 4\n");
		return 1;
	    }
	}
	else
	{
	    printf("This address does not contain assembler command\n");
	    return 1;
	}
    }
    executeRun(pMips);

    return 0;
}
