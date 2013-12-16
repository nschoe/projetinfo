#include "bp.h"
#include "parseNumber.h"

int executeBp(mips * pMips, uint addr)
{
    pMips->bpList = addToList(pMips->bpList, addr);
    printf("Adress %#x added to breakpoint list\n", addr); 

    return 0;
}

int parseBp( mips * pMips, char * args )
{
    uint addr;

    if(!parseNumber(args + 1, &addr))
    {
	printf("Usage : bp <addr>\n");
    }
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
