#include "da.h"
#include "parseAddr.h"
#include "notify.h"
#include <string.h>

int executeDa( mips * pMips, uint addr, uint nb )
{
    uint i;
    int overflow = 0;

    for( i = 0; i < nb; i++ )
    {
	if( !overflow && addr + i < pMips->sizeText*4096 )
	    printf( "%#x:\t%08x\n", addr+i, *(pMips->memText + i) );
	else if( !overflow )
	{
	    overflow = 1;
	    WARNING_MSG( "%#x not in text segment (no assembly code to display !\n", addr + i );
	    break;
	}
    }

    return CMD_OK_RETURN_VALUE;
}

int parseDa( mips * pMips, char * args )
{
    uint addr;
    uint nbInstructions;
    
    /* Check the format of the parameter :
       addr     -- assume display only 1 instruction
       addr:nb  -- display nb instructions
    */

    //da addr:nb
    if( 2 == sscanf( args, "%x:%d", &addr, &nbInstructions ) )
    {
	if( 0 != addr % 4 )
	{
	    WARNING_MSG( "Careful : instructions are aligned on addresses that are multiple of 4, %#x is not.\n", addr );
	}
	else
	    executeDa( pMips, addr, nbInstructions );
    }
    // da addr
    else if( 1 == sscanf( args, "%x", &addr ) )
    {
	if( 0 != addr % 4 )
	{
	    WARNING_MSG( "Careful : instructions are aligned on addresses that are multiple of 4, %#x is not.\n", addr );
	}
	else
	    executeDa( pMips, addr, 1 );
    }
    else
    {
	WARNING_MSG( "Usage : da addr | da addr:nb where addr is a hexadecimal memory address and nb is a decimal number of instructions.\n" );
    }
    

    return 0;
}
