#include "dm.h"
#include "notify.h"
#include "parseNumber.h"
#include "delSpaces.h"

// Displays a data at a memory address, display the header (address) if header is set, set wrote when targeted address could be read
int executeDmDirect( mips * pMips, const uint addr, const int header, int * wrote )
{

    if( addr < pMips->sizeText*4096 ) // check that addr is in text segment
    {
	if( addr < pMips->realSizeText ) // check that addr is real data in text segment
	{
	    if( header )
		printf( "0x%x:\t", addr );
	    printf( "%02x", *(pMips->memText + addr) );
	    
	    if( NULL != wrote )
		*wrote = 1;
	}
	else if( NULL != wrote )
	{
	    *wrote = 0;
	}
    }
    else if( addr < (pMips->sizeText + pMips->sizeData )*4096 ) // check that addr is in data segment
    {
	if( addr < (pMips->sizeText)*4096 + pMips->realSizeData ) // check that addr is real data in data segment
	{
	    if( header )
		printf( "0x%x:\t", addr );
	    printf( "%02x", *(pMips->memData + (addr - pMips->sizeText*4096)) );
	    
	    if( NULL != wrote )
		*wrote = 1;
	}
	else if( NULL != wrote )
	{
	    *wrote = 0;
	}
    }
    else if( addr < (pMips->sizeText + pMips->sizeData + pMips->sizeBss)*4096) // check that addr is in bss segment
    {
	if( addr < (pMips->sizeText + pMips->sizeData)*4096 + pMips->realSizeBss ) // check that addr is real data in bss segment
	{
	    if( header )
		printf( "0x%x:\t", addr );
	    printf( "%02x", *(pMips->memBss + (addr - (pMips->sizeText + pMips->sizeData)*4096)) );
	    
	    if( NULL != wrote )
		*wrote = 1;
	}
	else if( NULL != wrote )
	{
	    *wrote = 0;
	}
    }
    else
    {
	if( NULL != wrote )
		*wrote = 0;

	WARNING_MSG( "out of memory (dm)" );
	printf( "Address %#x is out of memory.\n", addr );
    }
    
    return CMD_OK_RETURN_VALUE;
}

// dm addr1~addr2
int executeDmRange( mips * pMips, const uint from, const uint to )
{
    int l = 0, wrote = 0;
    uint c;

    // Display memory from 'from' to 'to'
    for( c = from; c <= to; c++ )
    {
	// We want to display 16 bytes per line
	executeDmDirect( pMips, c, (l == 0), &wrote );
	
	// Decide whether to display a space or a newline	
	if( wrote )
	    15 == l ? printf( "\n" ) : printf( " " );

	// Increase the column indice
	l = (l+1) % 16;
    }
    
    // Clear the last line
    printf( "\n" );

    return CMD_OK_RETURN_VALUE;
}

// dm addr:nbBytes
int executeDmNb( mips * pMips, const uint from, const uint nb )
{
    executeDmRange( pMips, from, from + nb - 1 );

    return 0;
}

int parseDm( mips * pMips, const char * paramStr )
{
    char * argCopy = NULL, * pch = NULL;
    uint v1, v2;
    int type = 0;

    // Copy input string
    argCopy = (char *) malloc( 1 + strlen( paramStr ) );
    strcpy( argCopy, paramStr );

    // Remove interspaced spaces
    delSpaces( argCopy );

    // Acquire address
    if( parseNumber( argCopy, &v1 ) )
    {
	WARNING_MSG( "No address given  to dm" );
	printf( "Usage : dm <addr> | <addr>:<nyBytes> | <addr1>~<addr2> where addr, addr1 and addr2 are given in hexadecimal form and nyBytes in decimal form.\n" );
    }

    // Check form addr1:addr2
    pch = strstr( argCopy, ":" );
    if( NULL != pch )
    {
	type = 10;
	if( parseNumber( pch+1, &v2 ) )
	{
	    WARNING_MSG( "Bad form" );
	    printf( "Usage : dm <addr> | <addr>:<nyBytes> | <addr1>~<addr2> where addr, addr1 and addr2 are given in hexadecimal form and nyBytes in decimal form.\n" );
	}
    }
    else
    {
	pch = strstr( argCopy, "~" );
	if( NULL != pch )
	{
	    type = 20;
	    if( parseNumber( pch+1, &v2 ) )
	    {
		WARNING_MSG( "Bad form" );
		printf( "Usage : dm <addr> | <addr>:<nyBytes> | <addr1>~<addr2> where addr, addr1 and addr2 are given in hexadecimal form and nyBytes in decimal form.\n" );
	    }
	}
    }

    if( 0 == type )
    {
	executeDmDirect( pMips, v1, 1, NULL );
    }
    else if( 10 == type )
    {
	executeDmNb( pMips, v1, v2 );
    }
    else if( 20 == type )
    {
	executeDmRange( pMips, v1, v2 );
    }
    else
    {
	WARNING_MSG( "Wrong format" );
	printf( "Usage : dm <addr> | <addr>:<nyBytes> | <addr1>~<addr2> where addr, addr1 and addr2 are given in hexadecimal form and nyBytes in decimal form.\n" );
    }
    
    free( argCopy );
    return 0;
}
