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

    uP.startText = 0;
    uP.startData = 4096 * sizeText;
    uP.startBss = uP.startData + 4096 * sizeData;

    return uP;
}
