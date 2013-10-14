#ifndef _DM_H_
#define _DM_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "notify.h"
#include "mips.h"

int executeDmDirect( mips *, uint );
int executeDmRange( mips *, uint, uint );
int executeDmNb( mips *, uint, uint );
int parseDm( mips *, char * );

#endif
