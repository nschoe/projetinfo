#include "parseHexa.h"
#include "notify.h"

uint parseHexa( const char * str )
{
    uint v;

    // Hexadecimal value is written Oxhhh... so it's minimum 3 character long, excpet 0 that is accepted
    if( strlen( str ) == 0 || strlen( str ) == 2 )
	ERROR_MSG( "\"%s\" is not an hexadecimal value 1!\n", str );
    // the only 1 character long hexa value allowed is 0
    else if( 1 == strlen( str ) )
    {
	if( '0' == str[0] )
	    v = 0;
	else
	    ERROR_MSG( "\"%s\" is not an hexadecimal value 2!\n", str );
    }
    // we can attempt to parse an hexa value
    else if( '0' == str[0] && 'x' == str[1] )
    {
	if( 1 != sscanf( str, "%x", &v ) )
	{
	    // Parse failed
	    ERROR_MSG( "\"%s\" is not an hexadecimal value 3!\n", str );
	}
	    
    }
    else
	ERROR_MSG( "\"%s\" is not an hexadecimal value 4!\n", str );
    
    return v;
}
