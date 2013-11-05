#include "dm.h"
#include "notify.h"

// dm addr
int executeDmDirect( mips * pMips, uint addr )
{    
    if( addr < pMips->sizeText*4096 )
    {
	// addr in Text
	printf( "%#x:\t%02x\n", addr, *(pMips->memText + addr) );
    }
    else if( addr < (pMips->sizeText + pMips->sizeData)*4096 )
    {
	// addr in data
	printf( "%#x:\t%02x\n", addr, *(pMips->memData + (addr - pMips->sizeText*4096)) );
    }
    else if( addr < (pMips->sizeText + pMips->sizeData + pMips->sizeBss)*4096)
    {
	// addr in Bss
	printf( "%#x:\t%02x\n", addr, *(pMips->memBss + (addr - (pMips->sizeText + pMips->sizeData)*4096)) );
    }
    else
    {
	WARNING_MSG( "Address %#x is out of memory !\n", addr );
    }
    
    return CMD_OK_RETURN_VALUE;
}

// dm addr1~addr2
int executeDmRange( mips * pMips, uint from, uint to )
{
    int l = 0;
    uint c;

    // Display memory from 'from' to 'to'
    for( c = from; c <= to; c++ )
    {
	// We want to display 16 bytes per line

	// Display first byte address at the beginnning of a line
	if( 0 == l )
	    printf( "%#x:\t", c );

	// Display memory content
	if( c < pMips->sizeText*4096 )
	{
	    // addr in Text
	    printf( "%02x", *(pMips->memText + c) );
	}
	else if( c < (pMips->sizeText + pMips->sizeData)*4096 )
	{
	    // addr in data
	    printf( "%02x", *(pMips->memData + (c - pMips->sizeText*4096)) );
	}
	else if( (pMips->sizeText + pMips->sizeData + pMips->sizeBss)*4096 )
	{
	    // addr in Bss
	    printf( "%02x", *(pMips->memBss + *(pMips->memBss + (c - (pMips->sizeText + pMips->sizeData)*4096))) );
	}
	else
	{
	    WARNING_MSG( "Address %#x is out of memory !\n", c );
	}
	
	// Decide whether to display a space or a newline
	15 == l ? printf( "\n" ) : printf( " " );

	// Increase the column indice
	l = (l+1) % 16;
    }
    
    // Clear the last line
    printf( "\n" );

    return 0;
}

// dm addr:nbBytes
int executeDmNb( mips * pMips, uint from, uint nb )
{
    executeDmRange( pMips, from, from + nb - 1 );

    return 0;
}

int parseDm( mips * pMips, char * paramStr )
{
    uint v1 = 0;
    uint v2 = 0;

    /* First check the format of the param : 
       addr
       addr:nbBytes
       addr1~addr2
    */
    // First check for addr:nbBytes
    if( 2 == sscanf( paramStr, "%x:%d", &v1, &v2 ) )
    {
//	printf( "Format is addr:nyBytes : %#x:%d\n", v1, v2 );
	executeDmNb( pMips, v1, v2 );
    }
    // Then check for addr1~addr2
    else if( 2 == sscanf( paramStr, "%x~%x", &v1, &v2 ) )
    {
//	printf( "Format is addr1~addr2 : %#x~%#x\n", v1, v2 );
	executeDmRange( pMips, v1, v2 );
    }
    // Then only left is addr
    else if( 1 == sscanf( paramStr, "%x", &v1 ) )
    {
//	printf( "Format is addr : %#x\n", v1 );
	executeDmDirect( pMips, v1 );
    }
    // Not a good format
    else
    {
	WARNING_MSG( "Usage : dm <addr> | <addr>:<nyBytes> | <addr1>~<addr2> where addr, addr1 and addr2 are given in hexadecimal form and nyBytes in decimal form.\n" );
    }
    
    return 0;
}
