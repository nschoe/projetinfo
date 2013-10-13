#ifndef _ER_H_
#define _ER_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "notify.h"
#include "mips.h"

int executeEr(char * paramStr);
int parseEr( mips *, char * );

#endif
