#include "er.h"

int executeEr(mips * pMips, uint addr)
{
    pMips->bpList = rmFromList(pMips->bpList, addr);

    return 0;
}

int parseEr( mips * pMips, char * args )
{
    uint addr;

    addr = parseHexa(args + 1);
    if(addr < pMips->sizeText*4096)
    {
	if(addr != (addr >> 2) << 2)
	{
	    WARNING_MSG("This address is not a 4 multiple number");
	    return 1;
	}
	executeEr(pMips, addr);
	return 0;
    }

    WARNING_MSG("This address is not in text part");

    return 1;
}
