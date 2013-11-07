#include "dico.h"

int loadDico(mips * pMips)
{
    FILE * dictionnary = fopen("dico.txt", "r");
    int i, order = 0;
    char command[15];

    fscanf(dictionnary, "%d", &(pMips->sizeR));
    pMips->dicoR = calloc(pMips->sizeR, sizeof(instr));

    fscanf(dictionnary, "%d", &(pMips->sizeI));
    pMips->dicoI = calloc(pMips->sizeI, sizeof(instr));

    fscanf(dictionnary, "%d", &(pMips->sizeJ));
    pMips->dicoJ = calloc(pMips->sizeJ, sizeof(instr));

    fgets(NULL, 256, dictionnary);

    for(i = 0; i < pMips->sizeR; i++)
    {
	fscanf(dictionnary, "%x", &(pMips->dicoR[i].op_code));
	fscanf(dictionnary, "%c", &(pMips->dicoR[i].type));
	fscanf(dictionnary, "%s", command);
	pMips->dicoR[i].name = calloc(strlen(command), sizeof(char));
	strcpy(command, pMips->dicoR[i].name);

	order = 0;
	while(fscanf(dictionnary, "%s", command))
	{
	    if(command[0] == 'r' && command[1] == 'd')
		order = order*10 + 3;
	    if(command[0] == 'r' && command[1] == 's')
		order = order*10 + 2;
	    if(command[0] == 'r' && command[1] == 't')
		order = order*10 + 1;
	    if(command[0] == 's' && command[1] == 'a')
		order = order*10 + 4;
	}

	pMips->dicoR[i].order = 0;
	while(order != 0)
	{
	    pMips->dicoR[i].order *= 10;
	    pMips->dicoR[i].order += order - (order/10)*10;
	    order /= 10;
	}
    }

    for(i = 0; i < pMips->sizeI; i++)
    {
	fscanf(dictionnary, "%x", &(pMips->dicoI[i].op_code));
	fscanf(dictionnary, "%c", &(pMips->dicoI[i].type));
	fscanf(dictionnary, "%s", command);
	pMips->dicoI[i].name = calloc(strlen(command), sizeof(char));
	strcpy(command, pMips->dicoI[i].name);

	order = 0;
	while(fscanf(dictionnary, "%s", command))
	{
	    if(command[0] == 'r' && command[1] == 's')
		order = order*10 + 2;
	    if(command[0] == 'r' && command[1] == 't')
		order = order*10 + 1;
	    if(command[0] == 's' && command[1] == 'a')
		order = order*10 + 4;
	    if(strcmp("offset", command) || strcmp("immediate", command) || strcmp("offset(base)", command))
		order = order*10 + 3;
	}

	pMips->dicoI[i].order = 0;
	while(order != 0) // inverting order
	{
	    pMips->dicoI[i].order *= 10;
	    pMips->dicoI[i].order += order - (order/10)*10;
	    order /= 10;
	}
    }

    for(i = 0; i < pMips->sizeJ; i++)
    {
	fscanf(dictionnary, "%x", &(pMips->dicoJ[i].op_code));
	fscanf(dictionnary, "%c", &(pMips->dicoJ[i].type));
	fscanf(dictionnary, "%s", command);
	pMips->dicoJ[i].name = calloc(strlen(command), sizeof(char));
	strcpy(command, pMips->dicoJ[i].name);

	order = 0;
	while(fscanf(dictionnary, "%s", command))
	{
	    if(strcmp("target", command))
		order = 1;
	}

	pMips->dicoJ[i].order = 0;
	while(order != 0)
	{
	    pMips->dicoJ[i].order *= 10;
	    pMips->dicoJ[i].order += order - (order/10)*10;
	    order /= 10;
	}
    }

    return 0;
}
