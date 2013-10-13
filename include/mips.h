#ifndef _MIPS_H_
#define _MIPS_H_

typedef unsigned int uint;

// Register data type
typedef struct
{
    uint v;             // sizeof( unsigned int ) = 32
} reg;

// Architecture of the MIPS
typedef struct
{
    // MIPS' name
    char* name;

    // Registers definition
    reg registers[32];   // 32 general-purpose registers
    reg regPC;           // the PC register
    reg regHI;           // the higher HI register
    reg regLO;           // the lower LO register

    // Memory definition (size allocated dynamically)
    void * memText;
    void * memBss;
    void * memData;
} mips;

#endif
