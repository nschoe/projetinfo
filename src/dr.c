#include "dr.h"
#include "nameRegisters.h"
#include "parseNumber.h"

/*
int executeDr( mips * pMips, int index, char * regName )
{
    int i;

    switch( index )
    {
        case -1 : // PC
	    printf("PC :\t%#x\n", pMips->regPC);
	    break;
        case -2 : // HI
	    printf("HI :\t%#x\n", pMips->regHI);
	    break;
        case -3 : // LO
	    printf("LO :\t%#x\n", pMips->regLO);
	    break;
        case -4 : // aucun parametre
	    for(i = 0; i < 32; i++)
		printf("$%d :\t%#x\n", i, pMips->registers[i]);

	    printf("PC :\t%#x\n", pMips->regPC);
	    printf("HI :\t%#x\n", pMips->regHI);
	    printf("LO :\t%#x\n", pMips->regLO);
	    break;

        default :
	    printf("%s :\t%#x\n", regName, pMips->registers[index]);
	    break;
    }

    return CMD_OK_RETURN_VALUE;
}
*/

int executeDr( mips * pMips, const int * toDisplay, const int len )
{
    int i;
    uint v;

    for( i = 1; i <= len; i++ )
    {
	// display register name: register value
	if( toDisplay[i-1] < 32 )
	    v = pMips->registers[toDisplay[i-1]];
	else if( 32 == toDisplay[i-1] )
	    v = pMips->regPC;
	else if( 33 == toDisplay[i-1] )
	    v = pMips->regHI;
	else if( 34 == toDisplay[i-1] )
	    v = pMips->regLO;
	else if( 35 == toDisplay[i-1] )
	    v = pMips->regSR;
	    
	printf( "%s:\t0x%08x", indexToName( toDisplay[i-1] ), v );

	// compute if '\n' must be displayed
	if( 0 == i % 4 )
	    printf( "\n" );
	else
	    printf( "\t\t" );
    }

    printf( "\n" );

    return 0;
}

int parseDr( mips * pMips, const char * paramStr )
{
    char * argCopy = NULL, * pch = NULL, * str = NULL;
    int toDisplay[100];
    int i, nb, parseNb, invalid;
    char parseName[100] = {'\0'};

    nb = 0;
    invalid = 0;

    // copy argument string for modifications
    argCopy = (char *) malloc( 1 + strlen( paramStr ) );
    argCopy = strcpy( argCopy, paramStr );

    pch = strtok( argCopy, " " );

    if( NULL == pch )
    {
	// no arguments given : display all registers
	for( i = 0; i < 36; i++ )
	    toDisplay[i] = i;

	nb = 36;
    }
    else
    {
        do
	{
	    if( '$' == pch[0] )
	    {
		// copy pch without the '$'
		str = (char *) malloc( strlen( pch ) );
		strcpy( str, pch+1 );
	    }
	    else
	    {
		// pch doesn't contain '$', copy it entirely
		str = (char *) malloc( 1 + strlen( pch ) );
		strcpy( str, pch );
	    }

	    // process 'str'
	    if( isDigit( str[0] ) )
	    {
		// $index form
		sscanf( str, "%d", &parseNb );
		if( parseNb >= 0 && parseNb <= 31 )
		{
		    toDisplay[nb] = parseNb;
		    nb++;
		}
		else
		    invalid++;
	    }
	    else
	    {
		// $name form
		sscanf( str, "%s", parseName );
		if( nameToIndex( parseName ) >= 0 )
		{
		    toDisplay[nb] = nameToIndex( parseName );
		    nb++;
		}
		else
		{
		    invalid++;
		}
	    }

	    pch = strtok( NULL, " " );
	} while( NULL != pch );
    }

    if( invalid )
    {
	WARNING_MSG( "invalid registers" );
	printf( "Warning : %d invalid registers names were ignored.\n", invalid );
    }

    return( executeDr( pMips, toDisplay, nb ) );
}

/*
int parseDr( mips * pMips, const char * paramStr )
{
    char * argCopy = NULL, * regName = NULL;
    char delim[] = " ";
    int index, i;
    char * paramStrCpy = NULL;
    char * regsNames[] = {"$zero", "$at", "$vo", "$v1", "$a0", "$a1", "$a2", "$a3", "$t0", "$t1", "$t2", "$t3", "$t4", "$t5", "$t6", "$t7", "$s0", "$s1", "$s2", "$s3", "$s4", "$s5", "$s6", "$s7", "$t8", "$t9", "$k0", "$k1", "$gp", "$sp", "$fp", "$ra"};

    argCopy = (char *) malloc( 1 + strlen( paramStr ) );
    strcpy(argCopy, paramStr); // copy of param allowing modifications

    regName = strtok(paramStrCpy, delim); // cut the first parameters : name of the register

    if( NULL == regName )
    {
	// display all registers
	executeDr(pMips, -4, "");
	return CMD_OK_RETURN_VALUE;
    }

    while( regName != NULL )
    {
	index = 32;

	if(regName[0] != '$')
	{
	    if(!strcmp(regName, "PC"))
		index = -1;
	    else if(!strcmp(regName, "HI"))
		index = -2;
	    else if(!strcmp(regName, "LO"))
		index = -3;
	    else
	    {
		WARNING_MSG( "invalid register name" );
		printf( "Invalid register name.\n" );
	    }
	}
	else if(regName[1] >= 0x30 && regName[1] <= 0x39)
	    sscanf(regName + 1, "%d", &index);
	else
	{
	    for(i = 0; i < 32; i++)
	    {
		if(!strcmp(regName, regsNames[i]))
		    index = i;
	    }
	}

	if(index > 31)
	{
	    WARNING_MSG("register doesn't exist");
	    printf( "Register $%d doesn't exist.\n", index );
	}
	else
	    executeDr(pMips, index, regName); // print register value
	regName = strtok(NULL, delim); // next parameter
    }

    return CMD_OK_RETURN_VALUE;
}
*/
