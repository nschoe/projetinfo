#include "execute.h"

int execute(mips * pMips)
{
    InstructionCode raw;
    int op_code;

    raw.c[0] = pMips->memText[pMips->regPC];
    raw.c[1] = pMips->memText[pMips->regPC + 1];
    raw.c[2] = pMips->memText[pMips->regPC + 2];
    raw.c[3] = pMips->memText[pMips->regPC + 3];
    op_code = takeBits(raw.i, 0, 6);
    switch(op_code)
    {
    case 0 : // instruction type R
	op_code = takeBits(raw.i, 25, 6);
	switch(op_code)
	{
	case 0x20 : // ADD
	    executeADD(pMips, takeBits(raw.i, 5, 20));
	    break;
	case 0x24 : // AND
	    executeAND(pMips, takeBits(raw.i, 5, 20));
	    break;
	case 0x1A : // DIV
	    executeDIV(pMips, takeBits(raw.i, 5, 20));
	    break;
	case 0x08 : // JR
	    executeJR(pMips, takeBits(raw.i, 5, 20));
	    break;
	case 0x10 : // MFHI
	    executeMFHI(pMips, takeBits(raw.i, 5, 20));
	    break;
	case 0x12 : // MFLO
	    executeMFLO(pMips, takeBits(raw.i, 5, 20));
	    break;
	case 0x00 :
	    if(raw.i == 0)
		executeNOP(pMips); // NOP
	    else
		executeSLL(pMips, takeBits(raw.i, 5, 20)); // SLL
	    break;
	case 0x25 : // OR
	    executeOR(pMips, takeBits(raw.i, 5, 20));
	    break;
	case 0x02 :
	    if(takeBits(raw.i, 10, 1))
		executeROTR(pMips, takeBits(raw.i, 5, 20)); // ROTR
	    else
		executeSRL(pMips, takeBits(raw.i, 5, 20)); // SRL
	    break;
	case 0x2A : // SLT
	    executeADD(pMips, takeBits(raw.i, 5, 20));
	    break;
	case 0x22 : // SUB
	    executeSUB(pMips, takeBits(raw.i, 5, 20));
	    break;
/*	case 0x0C : // SYSCALL
	    executeSYSCALL(pMips, takeBits(raw.i, 5, 20));
	    break;
*/	case 0x26 : // XOR
	    executeXOR(pMips, takeBits(raw.i, 5, 20));
	    break;
	default :
	    return 1;
	}
	break;
/*    case 0x08 : // ADDI
	executeADDI(pMips, takeBits(raw.i, 5, 26));
	break;
    case 0x04 : // BEQ
	executeBEQ(pMips, takeBits(raw.i, 5, 26));
	break;
    case 0x07 : // BGTZ
	executeBGTZ(pMips, takeBits(raw.i, 5, 26));
	break;
    case 0x06 : // BLEZ
	executeBLEZ(pMips, takeBits(raw.i, 5, 26));
	break;
    case 0x05 : // BNE
	executeBNE(pMips, takeBits(raw.i, 5, 26));
	break;
    case 0x0F : // LUI
	executeLUI(pMips, takeBits(raw.i, 5, 26));
	break;
    case 0x23 : // LW
	executeLW(pMips, takeBits(raw.i, 5, 26));
	break;
    case 0x2B : // SW
	executeSW(pMips, takeBits(raw.i, 5, 26));
	break;
    case 0x02 : // J
	executeJ(pMips, takeBits(raw.i, 5, 26));
	break;
    case 0x03 : // JAL
	executeJAL(pMips, takeBits(raw.i, 5, 26));
	break;
*/    default :
	return 1;
    }

    return 0;
}
