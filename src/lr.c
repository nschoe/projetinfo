#include "lr.h"

int executeLr(char * regName, char * regValue, mips micro)
{
    int i;
    int value;

    if(regValue[0] != '0' || regValue[1] != 'x')
    {
	WARNING_MSG("Second parameter must be a hexadecimel number (starting with 0x)");
	return 1;
    }
    sscanf(regValue, "%x", value);

    if(regName[0] != '$')
    {
	if(!strcmp(regName, "PC"))
	    micro.regPC = value;
	else if(!strcmp(regName, "HI"))
	    micro.regHI = value;
	else if(!strcmp(regName, "LO"))
	    micro.regLO = value;
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

int parseLr(char * paramStr, mips micro)
{
    char * paramStrCpy = malloc(strlen(paramStr)*sizeof(char));
    char * regName = NULL;
    char * regValue = NULL;
    char delim[] = " ";

    strcpy(paramStrCpy, paramStr); // copy of param allowing modifications

    regName = strtok(paramStrCpy, delim); // cut the first parameters : name of the register
    if(regName == NULL)
    {
	WARNING_MSG("A number or a name of register must be given to the function 'lr'\n");
	return 1;
    }

    regValue = strtok(paramStrCpy, delim); // cut the second parameters : value of the register
    if(regValue == NULL)
    {
	WARNING_MSG("A value for the register must be given to the function 'lr'\n");
	return 2;
    }

    if(strtok(paramStrCpy, delim) != NULL)
    {
	WARNING_MSG("too much parameters, lr only takes two arguments");
	return 3;
    }

    executeLr(regName, regValue, micro); // rendition of parameters

    return 0;
}
