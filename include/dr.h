#ifndef _DR_H_
#define _DR_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "notify.h"
#include "mips.h"

//int executeDr(mips * pMips, int index, char * regName);
int executeDr( mips *, const int *, const int );
int parseDr( mips *, const char * paramStr );

#endif
