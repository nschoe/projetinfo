#ifndef _DM_H_
#define _DM_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "notify.h"
#include "mips.h"

int executeDmDirect( uint addr);
int executeDmRange( uint from, uint to );
int executeDmNb( uint from, uint nb );
int parseDm( char * paramStr );

#endif
