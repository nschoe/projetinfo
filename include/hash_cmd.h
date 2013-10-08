#ifndef _HASH_CMD_
#define _HASH_CMD_

// Hash codes of all the functions
#define HASH_BP 0x6270
#define HASH_DA 0x6461
#define HASH_DB 0x6462
#define HASH_DM 0x646d
#define HASH_DR 0x6472
#define HASH_ER 0x6572
#define HASH_EX 0x6578
#define HASH_LM 0x6c6d
#define HASH_LP 0x6c70
#define HASH_LR 0x6c72
#define HASH_RUN 0x72756e
#define HASH_S 0x73
#define HASH_SI 0x7369

// Hash function to speed up strcmp
int hashageCmd(char *cmdStr);

#endif
