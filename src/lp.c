#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "notify.h"

#include "lp.h"
#include "readELF.h"

/* Check that one and exactly one file argument has been given
   and that it exists and is readable
*/
int parseLp( mips * pMips, const char * args )
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
	WARNING_MSG( "usage : lp filename" );
	printf( "Usage: lp filename\nwhere filename is an MIPS 32 ELF file.\n" );
	return 2;
    }
    else
    {
	// Check if the file exists and is readable
	h = fopen( pch, "r" );
	if( NULL == h )
	{
	    WARNING_MSG( "File doesn't exist" );
	    printf( "The file \"%s\" doesn't exist or you don't have the permissions to read it.\n", pch );
	    return 3;
	}
	else
	{	    
	    fclose( h );
	    return( executeLp( pMips, pch ) );
	}
    }
}

int executeLp( mips * uP, const char * filename )
{
    readELF( uP, filename );

    printf( "File \"%s\" successfully loaded.\n", filename );

//    printf( "realSizeText = %d\nrealSizeData = %d\nrealSizeBss = %d\n", uP->realSizeText, uP->realSizeData, uP->realSizeBss );

    return 0;
}
