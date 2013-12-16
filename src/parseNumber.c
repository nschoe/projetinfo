#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "mips.h"
#include "notify.h"

#include "parseNumber.h"

// Tell us if a char is a digit or not
int isDigit( const char str )
{
    int b;

    if( str >= 48 && str <= 57 ) // 48 : '0' / 57 : '9'
	b = 1;
    else
	b = 0;

    return b;
}

/* Parse a number from a string and puts the result in the result pointer.
 * Returns the correct value, whether the number is provided in hexadecimal, decimal or octal form.
 * Return code indicate parsing success or fail. On fail parsing, the pointer value is left unchanged.
 */
int parseNumber( const char * str, uint * result )
{
    int errCode;
    char *strCopy = NULL;
    char * pch = NULL;

    strCopy = (char *) malloc( 1 + strlen( str ) );
    strcpy( strCopy, str );

    // Remove leading spaces
    pch = strtok( strCopy, " " );

    // Empty string
    if( NULL == pch )
    {
	errCode = 2;
	WARNING_MSG( "Empty or only-space string" );
	//printf( "An empty (or space-only) string was given as a number.\n" );
    }
    else if( 1 == strlen( pch ) )
    {
	if( isDigit( pch[0] ) )
	{
	    sscanf( pch, "%d", result );
	    errCode = 0;
	}
	else
	{
	    errCode = 2;
	    WARNING_MSG( "\"%s\" is not a number ! (single digit check)\n", str );
	    //printf( "\"%s\" is not a number.\n", str );
	}
    }
    else if( '0' == pch[0] )
    {
	// May be hexa or octal
	if( 'x' == pch[1] )
	{
	    // Hexa value
	    sscanf( pch, "%x", result );
	    errCode = 0;
	}
	else if( isDigit( pch[1] ) )
	{
	    // Octal value
	    sscanf( pch, "%o", result );
	    errCode = 0;
	}
	else if( ':' == pch[1] || '~' == pch )
	{
	    // In the form 0:xxx or 0~xxx with no spaces
	    *result = 0;
	    errCode = 0;
	}
	else
	{
	    WARNING_MSG( "\"%s\" is not a number ! (hexa or octal possible)\n", str );
	    //printf( "\"%s\" is not a number.\n", str );
	    errCode = 2;
	}
    }
    else
    {
	// Only left is decimal, so check for digit
	if( isDigit( pch[0] ) )
	{
	    // Decimal value
	    sscanf( pch, "%d", result );
	    errCode = 0;
	}
	else
	{
	    errCode = 2;
	    WARNING_MSG( "\"%s\" is not a number !\n (decimal fail)", str );
	    //printf( "\"%s\" is not a number.\n", str );
	}
    }

    free( strCopy );

    return( errCode );
}
