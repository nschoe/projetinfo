#include "si.h"

int executeSi(mips * pMips)
{
    execute(pMips);

    return 0;
}

int parseSi( mips * pMips, char * args )
{
    if(!strcmp(" ", args) || !strcmp("", args))
	executeSi(pMips);
    else
	WARNING_MSG( "Command si need no arguments\n" );

    return 0;
}

