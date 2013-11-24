#include "db.h"

int executeDb(mips * pMips)
{
    printf("Break point list\n");
    printList(pMips->bpList);
    return 0;
}

int parseDb( mips * pMips, char * args )
{
    executeDb(pMips);

    return 0;
}
