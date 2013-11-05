#ifndef _MIPS_H_
#define _MIPS_H_

typedef unsigned int uint;

// Register data type
typedef uint reg;         // sizeof( unsigned int ) = 32

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
    unsigned char * memText;
    unsigned char * memBss;
    unsigned char * memData;

    // Sizes of segments in the MIPS (in multiples of 4096 bytes)
    int sizeText;
    int sizeBss;
    int sizeData;

} mips;

#endif
