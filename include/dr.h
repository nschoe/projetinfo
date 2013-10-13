#ifndef _DR_H_
#define _DR_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "notify.h"
#include "mips.h"
#include "parseReg.h"

int showReg(char * regName, mips * pMips);
int executeDr(char ** regNameArray, int nbParam, mips * pMips);
int parseDr(char * paramStr, mips * pMips);

#endif
