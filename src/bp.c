#include "bp.h"

int executeBp(mips * pMips, uint addr)
{
    pMips->bpList = addToList(pMips->bpList, addr);

    return 0;
}

int parseBp( mips * pMips, char * args )
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
	executeBp(pMips, addr);
	return 0;
    }

    WARNING_MSG("This address is not in text part");

    return 1;
}
