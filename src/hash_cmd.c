#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hash_cmd.h"

int hashageCmd(char *cmdStr)
{
    int hasher = 0, i = 0;

    if(strlen(cmdStr) < 5) /* la commande ne doit pas faire plus de 3 caractères (4 si je compte le \0) */
    {
        while(cmdStr[i] != '\0')
        {
	    hasher = hasher*256 + cmdStr[i]; /* decalage de 2 bits hexa */
	    i++;
	}
    }

    return hasher;
}
