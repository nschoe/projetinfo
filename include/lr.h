#ifndef _LR_H_
#define _LR_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "notify.h"
#include "mips.h"
#include "parseReg.h"

int executeLr(char * regName, char * regValue, mips micro);
int parseLr(char * paramStr, mips micro);

#endif
