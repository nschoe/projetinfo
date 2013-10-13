#ifndef _RUN_H_
#define _RUN_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "notify.h"
#include "mips.h"

int executeRun(char * paramStr);
int parseRun( mips *, char * );

#endif
