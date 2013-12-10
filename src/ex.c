#include "ex.h"

int executeEx( mips * pMips )
{
    // Free memory
    free( pMips->name );
    free( pMips->memText );
    free( pMips->memBss );
    free( pMips->memData );
    free( pMips->dicoR );
    free( pMips->dicoI );
    free( pMips->dicoJ );
    free( pMips->bpList );

    INFO_MSG("Exiting simulator...");
    return CMD_EXIT_RETURN_VALUE;
}

int parseEx( mips * pMips, char * args )
{
    return executeEx( pMips );
}
