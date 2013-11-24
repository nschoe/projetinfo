#ifndef _S_H_
#define _S_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "notify.h"
#include "mips.h"
#include "execute.h"

int executeS(mips *);
int parseS( mips *, char * );

#endif
