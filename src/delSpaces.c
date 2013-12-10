#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "delSpaces.h"

void delSpaces( char * str )
{
    int modified, len, i, j;

    len = strlen( str );

    do
    {
	modified = 0;
	for( i = 0; i < len; i++ )
	{
	    // Search the whole string for a space
	    if( ' ' == str[i] )
	    {
		// When a space is detected, shift remaining chars
		modified = 1;

		for( j = i; j < len; j ++ )
		{
		    str[j] = str[j+1];
		}
	    }
	}
    } while( modified );
}
