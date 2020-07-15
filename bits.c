#include <stdio.h>
#include <string.h>
#include "toolkit.h"

//计算一个bitset 中有多少个bit 1
int countOf1(unsigned long bitset)
{
    int count = 0;
    while (bitset)
    {
        bitset &= bitset - 1;
        count++;
    }
    return count;
}

void count_test()
{
    FUNC_HEAD();
    unsigned long l = 0;
    for (int i = 0; i < 8; i++)
    {
        l += 1 << i;
        printf("0x%lx has %d of bits 1\n", l, countOf1(l));
    }
}

//对整数取反
int reversal(int a)
{
    return ~a + 1;
}

void reversal_test()
{
    FUNC_HEAD();
    int i;
    i = 100;
    printf("reversal of  %d = %d \n", i, reversal(i));
    i = -88;
    printf("reversal of  %d = %d \n", i, reversal(i));
}

int main()
{
    count_test();
    reversal_test();
    return 0;
}
