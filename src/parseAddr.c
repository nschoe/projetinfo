#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "mips.h"
#include "notify.h"

#include "parseAddr.h"

// Tell us if a char is a digit or not
int isDigit( const char str )
{
    int b;

    if( str >= 48 && str <= 57 ) // 48 : '0' / 57 ; '9'
	b = 1;
    else
	b = 0;

    return b;
}

uint parseAddr( const char * str )
{
    uint parse;
    
    // TODO : strlen == 1 !!

    if( '0' == str[0] )
    {
	// May be hexa or octal
	if( 'x' == str[1] )
	{
	    // Hexa value
	    sscanf( str, "%x", &parse );
	}
	else
	{
	    // Octal value
	    sscanf( str, "%o", &parse );
	}
    }
    else
    {
	// Only left is decimal, so check for digit
	if( isDigit( str[0] ) )
	{
	    // Decimal value
	    sscanf( str, "%d", &parse );
	}
	else
	    WARNING_MSG( "\"%s\" is not a number !\n", str );
    }

    return parse;
}
