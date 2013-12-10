#ifndef _DM_H_
#define _DM_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "notify.h"
#include "mips.h"

int executeDmDirect( mips *, const uint );
int executeDmRange( mips *, const uint, const uint );
int executeDmNb( mips *, const uint, const uint );
int parseDm( mips *, const char * );

#endif
