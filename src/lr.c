#include "lr.h"

int executeLr(int index, uint value, mips * pMips)
{
    switch(index)
    {
        case -1 :
	    pMips->regPC = value;
	    break;
        case -2 :
	    pMips->regHI = value;
	    break;
        case -3 :
	    pMips->regLO = value;
	    break;
        default :
	    pMips->registers[index] = value;
	    break;
    }

    return CMD_OK_RETURN_VALUE;
}

int parseLr( mips * pMips,  char * paramStr )
{
    char * paramStrCpy = malloc(strlen(paramStr)*sizeof(char));
    char * regName = NULL;
    char * regValue = NULL;
    char delim[] = " ";

    int index = 32, i;
    uint value;
    char * regsNames[] = {"$zero", "$at", "$vo", "$v1", "$a0", "$a1", "$a2", "$a3", "$t0", "$t1", "$t2", "$t3", "$t4", "$t5", "$t6", "$t7", "$s0", "$s1", "$s2", "$s3", "$s4", "$s5", "$s6", "$s7", "$t8", "$t9", "$k0", "$k1", "$gp", "$sp", "$fp", "$ra"};

    strcpy(paramStrCpy, paramStr); // copy of param allowing modifications

    regName = strtok(paramStrCpy, delim); // cut the first parameters : name of the register
    if(regName == NULL)
    {
	WARNING_MSG("A number or a name of register must be given to the function 'lr'\n");
	return 2;
    }

    regValue = strtok(NULL, delim); // cut the second parameters : value of the register
    if(regValue == NULL)
    {
	WARNING_MSG("A value for the register must be given to the function 'lr'\n");
	return 2;
    }

    if(strtok(NULL, delim) != NULL)
    {
	WARNING_MSG("Too much parameters, lr only takes two arguments\n");
	return 2;
    }

    if(regValue[0] != '0' || regValue[1] != 'x' || !sscanf(regValue, "%x", &value))
    {
	WARNING_MSG("Second parameter must be a hexadecimal number (starting with 0x)\n");
	return 2;
    }

    if(regName[0] != '$')
    {
	if(!strcmp(regName, "PC"))
	    index = -1;
	else if(!strcmp(regName, "HI"))
	    index = -2;
	else if(!strcmp(regName, "LO"))
	    index = -3;
    }

    if(regName[1] > 0x30 && regName[1] < 0x39)
	sscanf(regName + 1, "%d", &index);
    for(i = 0; i < 32; i++)
    {
	if(!strcmp(regName, regsNames[i]))
	    index = i;
    }

    if(index > 31)
    {
	WARNING_MSG("This register does not exist");
	return 2;
    }

    fprintf(stdout, "CMD LOAD REGISTER %s WITH %#x\n", regName, value);

    return executeLr(index, value, pMips); // change register value
}
