#ifndef _RUN_H_
#define _RUN_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "notify.h"
#include "mips.h"
#include "parseHexa.h"
#include "execute.h"
#include "list.h"

int executeRun( mips * );
int parseRun( mips *, char * );

#endif
