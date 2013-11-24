#ifndef _ER_H_
#define _ER_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "notify.h"
#include "mips.h"
#include "list.h"
#include "parseHexa.h"

int executeEr( mips * pMips, uint addr );
int parseEr( mips *, char * );

#endif
