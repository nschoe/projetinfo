#ifndef _LR_H_
#define _LR_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "notify.h"
#include "mips.h"

int executeLr(int index, uint value, mips * pMips);
int parseLr(mips *, const char * paramStr );

#endif
