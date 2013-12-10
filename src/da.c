#include <string.h>

#include "da.h"
#include "notify.h"
#include "delSpaces.h"

int printAssembler( mips * pMips, uint value )
{
    int i, j, cpyOrder;
    uint cpyValue = value >> 26, param[4];

    if(!cpyValue)
    {
	cpyValue = value;
	param[0] = cpyValue >> 21; // 21-25 bits correspond to the first parameter
	cpyValue = cpyValue - (param[0] << 21);
	param[1] = cpyValue >> 16; // 16-20 bits correspond to the second parameter
	cpyValue = cpyValue - (param[1] << 16);
	param[2] = cpyValue >> 11; // 11-15 bits correspond to the third parameter
	cpyValue = cpyValue - (param[2] << 11);
	param[3] = cpyValue >> 6; // 6-10 bits correspond to the last parameter
	cpyValue = cpyValue - (param[3] << 6); // 0-5 coding the op_code

	if(!cpyValue)
	{
	    if(!param[0] && !param[1] && !param[2] && !param[3])
	    {
		printf("NOP\n");
		return 0;
	    }
	    printf("SLL %d %d %d\n", param[2], param[1], param[3]);
	    return 0;
	}

	if(cpyValue == 0x2)
	{
	    if(param[0] == 0x1)
	    {
		printf("ROTR %d %d %d\n", param[2], param[1], param[3]);
		return 0;
	    }
	    printf("SRL %d %d %d\n", param[2], param[1], param[3]);
	    return 0;
	}

	for(i = 0; i < pMips->sizeR; i++)
	{
	    if(pMips->dicoR[i].op_code == cpyValue)
	    {
		printf("%s", pMips->dicoR[i].name);
		cpyOrder = pMips->dicoR[i].order;
		while(cpyOrder != 0)
		{		
		    j = cpyOrder - (cpyOrder/10)*10;
		    cpyOrder /= 10;
		    printf(" %d", param[j - 1]);
		}
		printf("\n");
		return 0;
	    }
	}
    }
    else
    {
	cpyValue = value - (cpyValue << 26);
	for(i = 0; i < pMips->sizeJ; i++)
	{
	    if(pMips->dicoJ[i].op_code == cpyValue)
	    {
		printf("%s %#x\n", pMips->dicoJ[i].name, cpyValue);
		return 0;
	    }
	}

	param[0] = cpyValue >> 21; // 21-25 bits correspond to the first parameter
	cpyValue = cpyValue - (param[0] << 21);
	param[1] = cpyValue >> 16;  // 16-20 bits correspond to the second parameter
	cpyValue = cpyValue - (param[1] << 16);
	param[2] = cpyValue;  // 0-15 bits correspond to offset
	cpyValue = value >> 26;

	if(cpyValue == 0x2B)
	{
	    printf("SW %d %d(%d)\n", param[1], param[2], param[0]);
	    return 0;
	}

	for(i = 0; i < pMips->sizeI; i++)
	{
	    if(pMips->dicoI[i].op_code == cpyValue)
	    {
		printf("%s", pMips->dicoI[i].name);
		cpyOrder = pMips->dicoI[i].order;
		while(cpyOrder != 0)
		{		
		    j = cpyOrder - (cpyOrder/10)*10;
		    cpyOrder /= 10;
		    printf(" %d", param[j - 1]);
		}
		printf("\n");

		return 0;
	    }
	}
    }

    return 0;
}

int executeDa( mips * pMips, uint addr, uint nb )
{
    uint i;
    int overflow = 0;
    InstructionCode instruc;

    for( i = 0; !overflow && (i < 4*nb); i += 4 )
    {
	if( addr + i < pMips->realSizeText )
	{
	    //printf( "%#x:\t%#x\t", addr+i, *(pMips->memText + i) );
	    instruc.c[0] = *(pMips->memText + addr + i);
	    instruc.c[1] = *(pMips->memText + addr + i + 1);
	    instruc.c[2] = *(pMips->memText + addr + i + 2);
	    instruc.c[3] = *(pMips->memText + addr + i + 3);

	    switchEndian( &instruc );

	    printf( "%#x:\t%#x\t", addr+i, instruc.i );
	    printAssembler(pMips, instruc.i);
	}
	else
	{
	    overflow = 1;
	}
    }

    if( overflow )
    {
	WARNING_MSG( "overflow" );
	printf( "Reached end of .text segment at address %#x\n", pMips->realSizeText );
    }

    return CMD_OK_RETURN_VALUE;
}

int parseDa( mips * pMips, char * args )
{
    char * argCopy = NULL, * pch = NULL;
    uint v1, v2;

    if( 0 == pMips->realSizeText )
    {
	WARNING_MSG( "No program loaded" );
	printf( "No program was loaded into memory : no assembly to display.\n" );
	return 0;
    }

    argCopy = (char *) malloc( 1 + strlen( args ) );
    strcpy( argCopy, args );

    delSpaces( argCopy );

    if( parseNumber( argCopy, &v1 ) )
    {
	WARNING_MSG( "Bad form usage" );
	printf( "Usage : da <addr> : <nb_instr> where <addr> is aligned on a multiple of 4. If <nb_instr> is ommited, assumed as 1.\n" );
    }

    // Checks that the address is aligned over 4
    if( 0 != (v1 % 4) )
    {
	WARNING_MSG( "address not aligned over 4" );
	printf( "Addresses must be aligend on a multiple of 4.\n" );
	return 2;
    }

    // Check form addr:nb
    pch = strstr( argCopy, ":" );

    if( NULL != pch )
    {
	// then addr : nb
	if( parseNumber( pch+1, &v2 ) )
	{
	    WARNING_MSG( "Bad second argument" );
	    printf( "Usage : da <addr> : <nb_instr> where <addr> is aligned on a multiple of 4. If <nb_instr> is ommited, assumed as 1.\n" );
	}
	else
	{	 
	    executeDa( pMips, v1, v2 );
	}
    }
    else
    {
	// then only addr
	executeDa( pMips, v1, 1 );
    }

    return 0;
}

/*
int parseDa( mips * pMips, char * args )
{
    uint addr;
    uint nbInstructions;
    
    /* Check the format of the parameter :
       addr     -- assume display only 1 instruction
       addr:nb  -- display nb instructions
    */
/*
    //da addr:nb
    if( 2 == sscanf( args, "%x:%d", &addr, &nbInstructions ) )
    {
	if( 0 != addr % 4 )
	{
	    WARNING_MSG( "Careful : instructions are aligned on addresses that are multiple of 4, %#x is not.\n", addr );
	}
	else
	    executeDa( pMips, addr, nbInstructions );
    }
    // da addr
    else if( 1 == sscanf( args, "%x", &addr ) )
    {
	if( 0 != addr % 4 )
	{
	    WARNING_MSG( "Careful : instructions are aligned on addresses that are multiple of 4, %#x is not.\n", addr );
	}
	else
	    executeDa( pMips, addr, 1 );
    }
    else
    {
	WARNING_MSG( "Usage : da addr | da addr:nb where addr is a hexadecimal memory address and nb is a decimal number of instructions.\n" );
    }
    

    return 0;
}
*/

void switchEndian( InstructionCode * ins )
{
    unsigned char temp;

    temp = ins->c[0];
    ins->c[0] = ins->c[3];
    ins->c[3] = temp;

    temp = ins->c[1];
    ins->c[1] = ins->c[2];
    ins->c[2] = temp;
}
