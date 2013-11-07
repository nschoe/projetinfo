#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "notify.h"

#include "lp.h"
#include "readELF.h"

/* Check that one and exactly one file argument has been given
   and that it exists and is readable
*/
int parseLp( mips * pMips, char * args )
{
    char * argsCopy = malloc( strlen( args ) * sizeof( char ) );
    char * pch = NULL;
    char delim[] = " ";
    FILE * h = NULL;

    // Copy the string argument to use strtok on it
    strcpy( argsCopy, args );

    // First cut
    pch = strtok (argsCopy, delim);
    
    // Check if we have one argument given
    if( NULL == pch )
    {
	WARNING_MSG( "Usage: lp filename\nwhere filename is an MIPS 32 ELF file.\n" );
	return 2;
    }
    else
    {
	// Check if the file exists and is readable
	h = fopen( pch, "r" );
	if( NULL == h )
	{
	    WARNING_MSG( "The file \"%s\" doesn't exists or you don't have the permissions to read it.\n", pch );
	    return 3;
	}
	else
	{	    
	    fclose( h );
	    executeLp( pMips, pch );
	}

	// Do a second cut to check that only one file was given
	pch = strtok (NULL, delim);

	if( NULL != pch )
	{
	    WARNING_MSG( "The function lp only takes the first argument into account and will ignore the others.\n" );
	}

    }
    
    return CMD_OK_RETURN_VALUE;
}

int executeLp( mips * uP, const char * filename )
{

    readELF( filename, uP );

    printf( "File \"%s\" successfully loaded.\n", filename );

    return 0;
}
