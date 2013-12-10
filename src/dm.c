#include "dm.h"
#include "notify.h"
#include "parseNumber.h"
#include "delSpaces.h"

// dm addr
int executeDmDirect( mips * pMips, const uint addr )
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
int executeDmRange( mips * pMips, const uint from, const uint to )
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
	executeDmDirect( pMips, v1 );
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

/*
int parseDm( mips * pMips, const char * paramStr )
{
    uint v1 = 0;
    uint v2 = 0;
    char * argCopy = NULL;
    char * pch = NULL;
    char * pch2 = NULL;

    // Copy input string
    argCopy = (char *) malloc( 1 + strlen( paramStr ) );
    strcpy( argCopy, paramStr );

    // First of all : trim leading spaces
    pch = strtok( argCopy, " " );

    printf( "first parse : [%s]\n", pch );

    // Check for empty string
    if( NULL == pch )
    {
	WARNING_MSG( "Empty string given to DM" );
	printf( "Usage : dm <addr> | <addr>:<nyBytes> | <addr1>~<addr2> where addr, addr1 and addr2 are given in hexadecimal form and nyBytes in decimal form.\n" );
	return 2;
    }

    // Acquire address
    if( parseNumber( pch, &v1 ) )
    {
	printf( "Address could not be parsed.\n" );
    }

    // Acquire symbol (:, ~ or nothing)
    pch = strtok( NULL, " " );
    printf( "Second parse : [%s]\n", pch );


    return 0;

    /* First check the format of the param : 
       addr
       addr:nbBytes
       addr1~addr2
    */
    // First check for addr:nbBytes
/*    if( 2 == sscanf( paramStr, "%x:%d", &v1, &v2 ) )
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
*/
