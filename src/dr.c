#include "dr.h"

int showReg(char * regName, mips * pMips)
{
    int i;

    if(regName[0] != '$')
    {
	if(!strcmp(regName, "PC"))
	    printf("PC = %x", pMips->regPC);
	else if(!strcmp(regName, "HI"))
	    printf("HI = %x", pMips->regHI);
	else if(!strcmp(regName, "LO"))
	    printf("LO = %x", pMips->regLO);
	else
	{    
	    WARNING_MSG("First parameter must be a register name (PC, HI and LO or begin with $)\n");
	    return 2;
	}
	return 0;
    }

    i = parseReg(regName);

    if(i == -1)
    {
	WARNING_MSG("This register does not exist.\n");
	return 3;
    }
    micro.registers[i] = value;


    return 0;
}

int executeDr(char ** regNamesArray, int nbParam, mips * pMips)
{
    return 0;
}

int parseDr(char * paramStr, mips * pMips)
{
    return 0;
}
