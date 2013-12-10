#include "lm.h"
#include "parseNumber.h"
#include "mips.h"
#include "da.h"

int executeLm( mips * pMips, const uint addr, const uint value )
{
    char seg[10];
    InstructionCode v;
    int wrote = 1;\

    v.i = value;
    switchEndian( &v );

    if( addr < pMips->sizeText*4096 )
    {
	// addr in Text
	memcpy( pMips->memText + addr, &(v.i), sizeof( v.i ) );
	strcpy( seg, ".text" );
    }
    else if( addr < (pMips->sizeText + pMips->sizeData)*4096 )
    {
	// addr in data
	memcpy( pMips->memData + (addr - pMips->sizeText*4096), &(v.i), sizeof( v.i ) );
	strcpy( seg, ".data" );
    }
    else if( addr < (pMips->sizeText + pMips->sizeData + pMips->sizeBss)*4096 )
    {
	// addr in Bss
	memcpy( pMips->memBss + (addr - (pMips->sizeText + pMips->sizeData)*4096), &(v.i), sizeof( v.i ) );
	strcpy( seg, ".bss" );
    }
    else
    {
	WARNING_MSG( "out of memory" );
	printf( "Address %#x is out of memory.\n", addr );
	wrote = 0;
    }

    if( wrote )
	printf( "Wrote %#x at location %#x (segment %s).\n", value, addr, seg );

    return CMD_OK_RETURN_VALUE;
}

int parseLm( mips * pMips, const char * args )
{
    char * argsCopy = NULL, *pch = NULL;
    uint addr, value;

    argsCopy = (char *) malloc( 1 + strlen( args ) );
    if( NULL == argsCopy )
	ERROR_MSG( "Failed to allocate memory for argsCopy.\n" );

    strcpy( argsCopy, args );

    // First cut : get the address
    if( parseNumber( argsCopy, &addr ) )
    {
	WARNING_MSG( "no address given" );
	printf( "Usage : lm <addr> <value> where <addr> is the address in memory to load, expressed in hexa, decimal or octal base and <value> is a 32-bit value, expressed in hexa, decimal or octal base.\n" );
	return 2;
    }

    pch = strtok( argsCopy, " " ); // consumes space (is now addr)
    pch = strtok( NULL, " " ); // consumes addr and is now value

    if( NULL == pch || parseNumber( pch, &value ) )
    {
	WARNING_MSG( "no value given" );
	printf( "Usage : lm <addr> <value> where <addr> is the address in memory to load, expressed in hexa, decimal or octal base and <value> is a 32-bit value, expressed in hexa, decimal or octal base.\n" );
    }

    return( executeLm( pMips, addr, value ) );
}
