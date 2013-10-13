#ifndef _DR_H_
#define _DR_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "notify.h"
#include "mips.h"

int executeDr(char ** regNameArray, int nbParam, mips * pMips);
int parseDr( mips *, char * paramStr );

#endif
