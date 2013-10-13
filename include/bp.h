#ifndef _BP_H_
#define _BP_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "notify.h"
#include "mips.h"

int executeBp(char * paramStr);
int parseBp( mips *, char * );

#endif
