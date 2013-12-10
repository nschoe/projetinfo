#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "trimStr.h"

char * trimStr( char * str )
{
    size_t len = 0;
    char *frontP = str - 1;
    char *endP = NULL;

    // Check if an un-initialized string was given
    if( NULL == str )
	return( NULL );

    // Check if an empty string was given
    if( '\0' == str[0] )
	return( str );

    // Initialize pointers
    len = strlen( str );
    endP = str + len; // points to the \0 character

    /* Move the front and back pointers to address
     * the first non-whitespace characters from both
     * the beginning and the end of the string
     */
    while( isspace( *(++frontP) ) );
    while( isspace( *(--endP) ) && endP != frontP );

    // Add an end character if we trimmed trailing spaces
    if( str + len - 1 != endP )
	*(endP + 1) = '\0';
    else if( frontP != str && endP == frontP )
	*str = '\0';

    // Shift the string to make it begin at str pointer
    endP = str;

    if( frontP != str )
    {
	while( *frontP ) *endP++ = *frontP++;
	*endP = '\0';
    }

    return( str );
}
