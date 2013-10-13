#include "dr.h"

int executeDr(mips * pMips, int index, char * regName)
{
    int i;

    switch(index)
    {
        case -1 :
	    printf("%s\t:\t%#x\n", regName, pMips->regPC);
	    break;
        case -2 :
	    printf("%s\t:\t%#x\n", regName, pMips->regHI);
	    break;
        case -3 :
	    printf("%s\t:\t%#x\n", regName, pMips->regLO);
	    break;
        case -4 :
	    for(i = 0; i < 32; i++)
		printf("$%d\t:\t%#x\n", i, pMips->registers[i]);
	    printf("PC\t:\t%#x\n", i, pMips->regPC);
	    printf("HI\t:\t%#x\n", i, pMips->regHI);
	    printf("LO\t:\t%#x\n", i, pMips->regLO);
	    break;
        default :
	    printf("%s\t:\t%#x\n", regName, pMips->registers[index]);
	    break;
    }

    return 0;
}

int parseDr( mips * pMips, char * paramStr )
{
    char * paramStrCpy = malloc(strlen(paramStr)*sizeof(char));
    char * regName = NULL;
    char delim[] = " ";

    int index = 32, i;
    char * regsNames[] = {"$zero", "$at", "$vo", "$v1", "$a0", "$a1", "$a2", "$a3", "$t0", "$t1", "$t2", "$t3", "$t4", "$t5", "$t6", "$t7", "$s0", "$s1", "$s2", "$s3", "$s4", "$s5", "$s6", "$s7", "$t8", "$t9", "$k0", "$k1", "$gp", "$sp", "$fp", "$ra"};

    strcpy(paramStrCpy, paramStr); // copy of param allowing modifications

    regName = strtok(paramStrCpy, delim); // cut the first parameters : name of the register

    if(regName == NULL)
    {
	executeDr(pMips, -4, "");
	
	return 0;
    }

    while(regName != NULL)
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
	}
	else if(regName[1] > 0x30 && regName[1] < 0x39)
	{
	    sscanf(regName + 1, "%d", &index);
	    for(i = 0; i < 32; i++)
	    {
		if(!strcmp(regName, regsNames[i]))
		    index = i;
	    }
	}

	if(index > 31)
	    WARNING_MSG("This register does not exist\n");
	else
	    executeDr(pMips, index, regName); // print register value
	regName = strtok(NULL, delim); // next parameter
    }

    return 0;
}
