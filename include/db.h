#ifndef _DB_H_
#define _DB_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "notify.h"
#include "mips.h"
#include "list.h"

int executeDb( mips * );
int parseDb( mips *, char * );

#endif
