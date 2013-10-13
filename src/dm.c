#include "dm.h"

// dm addr
int executeDmDirect( uint addr )
{
    printf( "%#x:\t%#x\n", addr, 0 );
    return 0;
}

// dm addr1~addr2
int executeDmRange( uint from, uint to )
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
	printf( "0x00" ); // display only 0s for now

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
int executeDmNb( uint from, uint nb )
{
    executeDmRange( from, from + nb - 1 );

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
	executeDmNb( v1, v2 );
    }
    // Then check for addr1~addr2
    else if( 2 == sscanf( paramStr, "%x~%x", &v1, &v2 ) )
    {
//	printf( "Format is addr1~addr2 : %#x~%#x\n", v1, v2 );
	executeDmRange( v1, v2 );
    }
    // Then only left is addr
    else if( 1 == sscanf( paramStr, "%x", &v1 ) )
    {
//	printf( "Format is addr : %#x\n", v1 );
	executeDmDirect( v1 );
    }
    // Not a good format
    else
    {
	WARNING_MSG( "Usage : dm <addr> | <addr>:<nyBytes> | <addr1>~<addr2> where addr, addr1 and addr2 are given in hexadecimal form and nyBytes in decimal form.\n" );
    }
    
    return 0;
}
