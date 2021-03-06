#ifndef _EXECUTE_H_
#define _EXECUTE_H_

#include <stdio.h>
#include <stdlib.h>

#include "mips.h"
#include "takeBits.h"

#include "executeADD.h"
#include "executeAND.h"
#include "executeADDI.h"
#include "executeBEQ.h"
#include "executeBGTZ.h"
#include "executeBLEZ.h"
#include "executeBNE.h"
#include "executeDIV.h"
#include "executeJ.h"
#include "executeJAL.h"
#include "executeJR.h"
#include "executeLUI.h"
#include "executeLW.h"
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
#include "executeSW.h"
#include "executeXOR.h"

int execute(mips * pMips);

#endif
