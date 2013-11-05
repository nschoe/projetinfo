#include "lm.h"
#include "parseHexa.h"
#include "mips.h"

int executeLm( mips * pMips, uint addr, uint value )
{
    char seg[10];

    if( addr < pMips->sizeText*4096 )
    {
	// addr in Text
	*(pMips->memText + addr) = value;
	strcpy(seg, ".text");
    }
    else if( addr < (pMips->sizeText + pMips->sizeData)*4096 )
    {
	// addr in data
	*(pMips->memData + (addr - pMips->sizeText*4096)) = value;
	strcpy( seg, ".data" );
    }
    else if( addr < (pMips->sizeText + pMips->sizeData + pMips->sizeBss)*4096 )
    {
	// addr in Bss
	*(pMips->memBss + (addr - (pMips->sizeText + pMips->sizeData)*4096)) = value;
	strcpy( seg, ".bss" );
    }
    
    printf( "Wrote %#x at location %#x (segment %s).\n", value, addr, seg );

    return CMD_OK_RETURN_VALUE;
}

int parseLm( mips * pMips, char * args )
{
    char * argsCopy = NULL, *pch = NULL;
    uint addr, value;

    argsCopy = malloc( strlen( args ) * sizeof( char ) );
    if( NULL == argsCopy )
	ERROR_MSG( "Failed to allocate memory for argsCopy.\n" );

    strcpy( argsCopy, args );

    // First cut : get the address
    pch = strtok( argsCopy, " " );
    if( NULL != pch )
	addr = parseHexa( pch );
    else
	WARNING_MSG( "Usage : dm addr value where addr and value are hexadecimal value (0xhhhh).\n" );

    // Second cut : get the value
    pch = strtok( NULL, " " );
    if( NULL != pch )
	value = parseHexa( pch );
    else
	WARNING_MSG( "Usage : dm addr value where addr and value are hexadecimal value (0xhhhh).\n" );

    return( executeLm( pMips, addr, value ) );
}
