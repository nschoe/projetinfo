#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "notify.h"
#include "mips.h"
#include "mipself.h"
#include "readELF.h"

/* Use mipsloader to read and parse an ELF file and store its
   information in the mips data structure*/
int readELF( const char * filename, mips * uP )
{
    SectionELF * textSection;
    SectionELF * dataSection;
    SectionELF * bssSection;

    // Allocate space for the sections
    textSection = (SectionELF *) malloc( sizeof( SectionELF ) );
    dataSection = (SectionELF *) malloc( sizeof( SectionELF ) );
    bssSection = (SectionELF *) malloc( sizeof( SectionELF ) );
    textSection->data = NULL;
    dataSection->data = NULL;
    bssSection->data = NULL;

    // Parsing ELF file with mipsloader function
    if( mipsloader( filename, textSection, dataSection, bssSection ) )
    {
	ERROR_MSG( "Error while reading ELF file !\n" );
    }
    
    /* Making the links between their stucture (from mipsloader)
       to ours (mips.h)*/

    // Allocate space for the three sections
    uP->memText = (unsigned char *) malloc( textSection->size * sizeof( unsigned char ));
    uP->memData = (unsigned char *) malloc( dataSection->size * sizeof( unsigned char ));
    uP->memBss = (unsigned char *) malloc( bssSection->size * sizeof( unsigned char ));

    // Check for allocation error
    if( NULL == uP->memText )
	ERROR_MSG( "Error while allocating space for the text section (%d bytes)\n", textSection->size );

    if( NULL == uP->memData )
	ERROR_MSG( "Error while allocating space for the data section (%d bytes)\n", dataSection->size );

    if( NULL == uP->memBss )
	ERROR_MSG( "Error while allocating space for the bss section (%d bytes)\n", bssSection->size );

    // Actual data copy
    memcpy( uP->memText, textSection->data, textSection->size );
    memcpy( uP->memData, dataSection->data, dataSection->size );
    memcpy( uP->memBss, bssSection->data, bssSection->size );

    // Computes sizes (in multiple of 4096)    
    uP->sizeText = (int) ceil( textSection->size / 4096.0 );
    uP->sizeData = (int) ceil( dataSection->size / 4096.0 );
    uP->sizeBss = (int) ceil( bssSection->size / 4096.0 );

    uP->realSizeText = textSection->size;
    uP->realSizeData = dataSection->size;
    uP->realSizeBss = bssSection->size;

    // Clean up the sections returned by mips loader
    /*
    free( textSection->name );
    free( textSection->data );
    free( textSection );
    
    free( dataSection->name );
    free( dataSection->data );
    free( dataSection );

    free( bssSection->name );
    free( bssSection->data );
    free( bssSection );
    */
    return 0;
}
