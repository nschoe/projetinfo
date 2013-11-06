#include "da.h"
#include "parseAddr.h"
#include "notify.h"
#include <string.h>

int printAssembler( mips * pMips, uint value )
{
    int i, j, cpyOrder;
    uint cpyValue = value >> 26, param[4];

    if(!cpyValue)
    {
	cpyValue = value - (cpyValue << 26);
	param[0] = cpyValue >> 21;
	cpyValue = cpyValue - (param[0] << 21);
	param[1] = cpyValue >> 16;
	cpyValue = cpyValue - (param[1] << 16);
	param[2] = cpyValue >> 11;
	cpyValue = cpyValue - (param[2] << 11);
	param[3] = cpyValue >> 6;
	cpyValue = cpyValue - (param[3] << 6);

	if(!param[0] && !param[1] && !param[2] && !param[3] && cpyValue)
	{
	    printf("NOP\n");
	    return 0;
	}

	for(i = 0; i < pMips->sizeR; i++)
	{
	    if(pMips->dicoR[i].op_code == cpyValue)
	    {
		if(cpyValue == 000010 && (value >> 22) == 0)
		{
		    printf("SRL %d, %d, %d,\n", param[3], param[2], param[4]);
		    return 0;
		}
		if(cpyValue == 000010 && (value >> 22) == 1)
		{
		    printf("ROTR %d, %d, %d,\n", param[3], param[2], param[4]);
		    return 0;
		}
		printf("%s", pMips->dicoR[i].name);
		cpyOrder = pMips->dicoR[i].order;
		while(cpyOrder != 0)
		{		
		    j = cpyOrder - cpyOrder/10;
		    cpyOrder /= 10;
		    printf("%d", param[j]);
		}
		printf("\n");
		return 0;
	    }
	}
    }
    else
    {
	for(i = 0; i < pMips->sizeJ; i++)
	{
	}

	cpyValue = cpyValue - (param[0] << 26);
	param[1] = cpyValue >> 21;
	cpyValue = cpyValue - (param[1] << 21);
	param[1] = cpyValue >> 16;
	cpyValue = cpyValue - (param[0] << 16);

	for(i = 0; i < pMips->sizeI; i++)
	{
	}
    }

    return 0;
}

int executeDa( mips * pMips, uint addr, uint nb )
{
    uint i;
    int overflow = 0;

    for( i = 0; i < nb; i++ )
    {
	if( !overflow && addr + i < pMips->sizeText*4096 )
	{
	    printf( "%#x:\t%08x\t", addr+i, *(pMips->memText + i) );
	    printAssembler(pMips, *(pMips->memText + i));
	    printf("\n");
	}
	else if( !overflow )
	{
	    overflow = 1;
	    WARNING_MSG( "%#x not in text segment (no assembly code to display !\n", addr + i );
	    break;
	}
    }

    return CMD_OK_RETURN_VALUE;
}

int parseDa( mips * pMips, char * args )
{
    uint addr;
    uint nbInstructions;
    
    /* Check the format of the parameter :
       addr     -- assume display only 1 instruction
       addr:nb  -- display nb instructions
    */

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
