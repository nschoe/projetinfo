#ifndef _SI_H_
#define _SI_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "notify.h"
#include "mips.h"
#include "execute.h"

int executeSi( mips * );
int parseSi( mips *, char * );

#endif
