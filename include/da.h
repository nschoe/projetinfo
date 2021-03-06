#ifndef _DA_H_
#define _DA_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "notify.h"
#include "mips.h"

int printAssembler( mips *, uint );
int executeDa( mips *, uint, uint );
int parseDa( mips *, char * );

void switchEndian( InstructionCode * );
int signAlign( const int );

#endif
