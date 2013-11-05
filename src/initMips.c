#include "initMips.h"
#include "notify.h"

mips initMips( const char * name, const int sizeText, const int sizeData, const int sizeBss )
{
    mips uP;

    // Initialize mips name
    uP.name = malloc( strlen( name ) * sizeof( char ) );
    if( NULL == uP.name )
    {
	ERROR_MSG( "Failed allocating space for mips name !\n" );
    }
    else
    {
	strcpy( uP.name, name );
    }

    // Memory initialization (random for now)
    uP.memText = (unsigned char *) malloc( sizeText * 4096 * sizeof( char ) );
    if( NULL == uP.memText )
	ERROR_MSG( "Failed allocating space for text segment !\n" );

    uP.memData = (unsigned char *) malloc( sizeData * 4096 * sizeof( char ) );
    if( NULL == uP.memData )
	ERROR_MSG( "Failed allocating space for data segment !\n" );

    uP.memBss = (unsigned char *) malloc( sizeBss * 4096 * sizeof( char ) );
    if( NULL == uP.memBss )
	ERROR_MSG( "Failed allocating space for bss segment !\n" );

    uP.sizeText = sizeText;
    uP.sizeData = sizeData;
    uP.sizeBss = sizeBss;

    return uP;
}
