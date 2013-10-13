#ifndef _LM_H_
#define _LM_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "notify.h"
#include "mips.h"

int executeLm( mips *, uint, uint );
int parseLm( mips *, char * );

#endif
