#include "takeBits.c"

uint takeBits(const uint value, const int from, const int nb)
{
    uint newValue;

    newValue = value << from;
    newValue = newValue >> (32 - nb);

    return newValue;
}
