#include "parseReg.h"

// Tell us if a char is a digit or not
int isDigit( const char str )
{
    int b;

    if( str >= 48 && str <= 57 ) // 48 : '0' / 57 ; '9'
	b = 1;
    else
	b = 0;

    return b;
}

// Tell us which element of the array is concern by regName
int parseReg(const char * regName)
{
    if(isDigit(regName[1])) // if number is directly give
    {
	sscanf(regName + 1,"%d", &i);
	if(i > 31 || i < 0)
	    return -1;
    }
    else if(!strcmp(regName, "$zero"))
	i = 0;
    else if(regName[3] == '\0') // all register excepting $zero have only 3 characters
    {
	switch(regName[1])
	{
	    case 0x61 : // corresponding to a
	        if(regName[2] == 't') // $at
		    i = 1;
		else if(regName[2] >= 0x30 && regName[2] <= 0x33) // $a[0..3] 
		{
		    i = regName[2] - 0x30; // i = [0..3]
		    i += 4; // offset to be in right position $a[0..3] -> $[4..7]
		}
		else
		    return -1;
		break;
	    case 0x76 : // corresponding to v
		if(regName[2] < 0x30 && regName[2] > 0x31) // $v[0..1]
		    return -1;
		i = regName[2] - 0x30;
		i += 2; // $v[0..1] -> $[2..3]
		break;
	    case 0x74 : // corresponding to t
		if(regName[2] < 0x30 || regName[2] > 0x39) // $t[0..9]
		    return -1;
		i = regName[2] - 0x30;
		if(i < 8)
		    i += 8; // $t[0..7] -> $[8..15]
		else
		    i += 16; // $t[8..9] -> $[24..25]
		break;
	    case 0x73 : // corresponding to s
		if(regName[2] == 'p') // $sp
		    i = 29;
		else if(regName[2] >= 0x30 && regName[2] <= 0x37) // $s[0..7] 
		{
		    i = regName[2] - 0x30;
		    i += 16; // $s[0..7] -> $[16..23]
		}
		else
		    return -1;
		break;
	    case 0x6b : // corresponding to k
		if(regName[2] < 0x30 && regName[2] > 0x31) // $k[0..1]
		    return -1;
		i = regName[2] - 0x30;
		i += 26; // $k[0..1] -> $[26..27]
		break;
	    case 0x67 : // corresponding to g
		if(regName[2] != 'p') // $gp
		    return -1;
		i = 28;
		break;
	    case 0x66 : // corresponding to f
		if(regName[2] != 'p') // $fp
		    return -1;
		i = 30;
		break;
	    case 0x72 : // corresponding to r
		if(regName[2] != 'a') // $ra
		    return -1;
		i = 31;
		break;
	    default :
		return -1;
		break;
	}
    }
    else
	return -1;
}
