#include "dm.h"

int executeDm()
{
    return 0;
}

int parseDm( char * paramStr )
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
	printf( "Format is addr:nyBytes : %#x:%d\n", v1, v2 );
    }
    // Then check for addr1~addr2
    else if( 2 == sscanf( paramStr, "%x~%x", &v1, &v2 ) )
    {
	printf( "Format is addr1~addr2 : %#x~%#x\n", v1, v2 );
    }
    // Then only left is addr
    else if( 1 == sscanf( paramStr, "%x", &v1 ) )
    {
	printf( "Format is addr : %#x\n", v1 );
    }
    // Not a good format
    else
    {
	WARNING_MSG( "Usage : dm <addr> | <addr>:<nyBytes> | <addr1>~<addr2> where addr, addr1 and addr2 are given in hexadecimal form and nyBytes in decimal form.\n" );
    }
    
    return 0;
}
