#include "initMips.h"
#include "notify.h"
#include "dico.h"

int initMips( mips * puP, const char * name, const char * dicoFile )
{
    // TODO : add the possibility to change dictionnary based on its name
    int i;

    // Name our puP (emotional moment !)
    puP->name = (char *) malloc( 1 + strlen( name ) );
    strcpy( puP->name, name );

    // Registers initialization
    puP->regPC = 0;
    puP->regHI = 0;
    puP->regLO = 0;
    puP->regSR = 0;
    for( i = 0; i < 32; i++ )
	puP->registers[i] = 0;

    // Initialize break points list
    puP->bpList = NULL;

    // Initializing memory
    puP->memText = NULL;
    puP->memBss = NULL;
    puP->memData = NULL;
    puP->dicoR = NULL;
    puP->dicoI = NULL;
    puP->dicoJ = NULL;

    // Init sizes
    puP->sizeText = 0;
    puP->sizeBss = 0;
    puP->sizeData = 0;
    puP->realSizeText = 0;
    puP->realSizeBss = 0;
    puP->realSizeData = 0;

    // Dictionnary loading
    return( loadDico( puP ) );
}

/*
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
*/
