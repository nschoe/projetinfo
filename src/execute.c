#include "execute.h"

int execute(mips * pMips)
{
    InstructionCode raw;
    int op_code;
    unsigned char temp;

    raw.c[0] = pMips->memText[pMips->regPC];
    raw.c[1] = pMips->memText[pMips->regPC + 1];
    raw.c[2] = pMips->memText[pMips->regPC + 2];
    raw.c[3] = pMips->memText[pMips->regPC + 3];
    temp = raw.c[0];
    raw.c[0] = raw.c[3];
    raw.c[3] = temp;
    temp = raw.c[1];
    raw.c[1] = raw.c[2];
    raw.c[2] = temp;
    op_code = takeBits(raw.i, 0, 6);
    switch(op_code)
    {
    case 0 : // instruction type R
	op_code = takeBits(raw.i, 26, 6);
	switch(op_code)
	{
	case 0x20 : // ADD
	    executeADD(pMips, raw.i);
	    break;
	case 0x24 : // AND
	    executeAND(pMips, raw.i);
	    break;
	case 0x1A : // DIV
	    executeDIV(pMips, raw.i);
	    break;
	case 0x08 : // JR
	    executeJR(pMips, raw.i);
	    break;
	case 0x10 : // MFHI
	    executeMFHI(pMips, raw.i);
	    break;
	case 0x12 : // MFLO
	    executeMFLO(pMips, raw.i);
	    break;
	case 0x00 :
	    if(raw.i == 0)
		executeNOP(pMips); // NOP
	    else
		executeSLL(pMips, raw.i); // SLL
	    break;
	case 0x25 : // OR
	    executeOR(pMips, raw.i);
	    break;
	case 0x02 :
	    if(takeBits(raw.i, 10, 1))
		executeROTR(pMips, raw.i); // ROTR
	    else
		executeSRL(pMips, raw.i); // SRL
	    break;
	case 0x2A : // SLT
	    executeADD(pMips, raw.i);
	    break;
	case 0x22 : // SUB
	    executeSUB(pMips, raw.i);
	    break;
	case 0x0C : // SYSCALL
	    return 1;
	    break;
	case 0x26 : // XOR
	    executeXOR(pMips, raw.i);
	    break;
	default :
	    return 2;
	}
	break;
    case 0x08 : // ADDI
	executeADDI(pMips, raw.i);
	break;
    case 0x04 : // BEQ
	executeBEQ(pMips, raw.i);
	break;
    case 0x07 : // BGTZ
	executeBGTZ(pMips, raw.i);
	break;
    case 0x06 : // BLEZ
	executeBLEZ(pMips, raw.i);
	break;
    case 0x05 : // BNE
	executeBNE(pMips, raw.i);
	break;
    case 0x0F : // LUI
	executeLUI(pMips, raw.i);
	break;
    case 0x23 : // LW
	executeLW(pMips, raw.i);
	break;
    case 0x2B : // SW
	executeSW(pMips, raw.i);
	break;
    case 0x02 : // J
	executeJ(pMips, raw.i);
	break;
    case 0x03 : // JAL
	executeJAL(pMips, raw.i);
	break;
    default :
	return 2;
    }

    return 0;
}
