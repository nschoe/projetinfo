#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "nameRegisters.h"

// general purpose registers
static char * gprNames[36] = {"zero", "at", "vo", "v1", "a0", "a1", "a2", "a3", "t0", "t1", "t2", "t3", "t4", "t5", "t6", "t7", "s0", "s1", "s2", "s3", "s4", "s5", "s6", "s7", "t8", "t9", "k0", "k1", "gp", "sp", "fp", "ra", "pc", "hi", "lo", "sr"};

char * indexToName( const int index )
{
    char * reg = NULL;

    if( index >= 0 && index <= 35 )
    {
	reg = (char *) malloc( 1 + strlen( gprNames[index] ) );
	strcpy( reg, gprNames[index] );
    }

    return reg ;
}

int nameToIndex( const char * name )
{
    char * regName = NULL;
    int i, answer;

    answer = -1;

    // Copy argument to allow modifications
    regName = (char *) malloc( 1 + strlen( name ) );
    strcpy( regName, name );
    
    // normalize string : to lowercase (for comparison)
    for( i = 0; i < strlen( regName ); i++ )
    {
	regName[i] = tolower( regName[i] );
    }

    // check string
    for (i = 0; i < 36; i++ )
    {
	if( !strcmp( regName, gprNames[i] ) )
	{
	    answer = i;
	    break;
	}
    }

    return answer;
}
