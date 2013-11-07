#include "dico.h"

int loadDico(mips * pMips)
{
    FILE * dictionnary = NULL;
    int i, j, order = 0;
    char command[15];
    char ligne[256];

    dictionnary = fopen("src/dico.txt", "r");
    if(!dictionnary)
	return 1;

    fscanf(dictionnary, "%d", &(pMips->sizeR));
    pMips->dicoR = calloc(pMips->sizeR, sizeof(instr));

    fscanf(dictionnary, "%d", &(pMips->sizeI));
    pMips->dicoI = calloc(pMips->sizeI, sizeof(instr));

    fscanf(dictionnary, "%d", &(pMips->sizeJ));
    pMips->dicoJ = calloc(pMips->sizeJ, sizeof(instr));

    fgets(ligne, 256, dictionnary);

    for(i = 0; i < pMips->sizeR; i++)
    {
	fscanf(dictionnary, "%x %c %s", &(pMips->dicoR[i].op_code), &(pMips->dicoR[i].type), command);
	pMips->dicoR[i].name = calloc(strlen(command) + 1, sizeof(char));
	strcpy(pMips->dicoR[i].name, command);

	order = 0;
	j = 0;
	fgets(ligne, 256, dictionnary);
	while(ligne[j] != '\n')
	{
	    if(ligne[j] == 'r')
	    {
		if(ligne[j+1] == 's')
		    order = order*10 + 1;
		if(ligne[j+1] == 't')
		    order = order*10 + 2;
		if(ligne[j+1] == 'd')
		    order = order*10 + 3;
		j++;
	    }
	    if(ligne[j] == 's' && ligne[j+1] == 'a')
	    {
		order = order*10 + 4;
		j++;
	    }
	    j++;
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
	fscanf(dictionnary, "%x %c %s", &(pMips->dicoI[i].op_code), &(pMips->dicoI[i].type), command);
	pMips->dicoI[i].name = calloc(strlen(command) + 1, sizeof(char));
	strcpy(pMips->dicoI[i].name, command);

	order = 0;
	j = 0;
	fgets(ligne, 256, dictionnary);
	while(ligne[j] != '\n')
	{
	    if(ligne[j] == 'r')
	    {
		if(ligne[j+1] == 's')
		    order = order*10 + 1;
		if(ligne[j+1] == 't')
		    order = order*10 + 2;
		j++;
	    }
	    if(!strcmp("offset\n", ligne + j) || !strcmp("immediate\n", ligne + j) || !strcmp("offset(base)\n", ligne + j))
	    {
		order = order*10 + 3;
		j++;
	    }
	    if(ligne[j] == 's' && ligne[j+1] == 'a')
	    {
		order = order*10 + 4;
		j++;
	    }
	    j++;
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
	fscanf(dictionnary, "%x %c %s", &(pMips->dicoJ[i].op_code), &(pMips->dicoJ[i].type), command);
	pMips->dicoJ[i].name = calloc(strlen(command) + 1, sizeof(char));
	strcpy(pMips->dicoJ[i].name, command);

	pMips->dicoJ[i].order = 0;
	fgets(ligne, 256, dictionnary);
	if(!strcmp(" target\n", ligne))
	    pMips->dicoJ[i].order = 1;
    }

    fclose(dictionnary);

    return 0;
}
