#ifndef _MIPS_H_
#define _MPIS_H_

// Register data type
typedef struct
{
    char v[4];           // 4 char is 4*8 = 32 bits
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
