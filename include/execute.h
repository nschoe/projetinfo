#ifndef _EXECUTE_H_
#define _EXECUTE_H_

#include <stdio.h>
#include <stdlib.h>

#include "mips.h"
#include "takeBits.h"

#include "executeADD.h"
#include "executeAND.h"
#include "executeDIV.h"
#include "executeJR.h"
#include "executeMFHI.h"
#include "executeMFLO.h"
#include "executeMULT.h"
#include "executeNOP.h"
#include "executeOR.h"
#include "executeROTR.h"
#include "executeSLL.h"
#include "executeSLT.h"
#include "executeSRL.h"
#include "executeSUB.h"
#include "executeXOR.h"

int execute(mips * pMips);

#endif
