#include <stdio.h>

// 2.81

unsigned int A(int k)
{
    return -1 << k;
}

unsigned int B(int k, int j)
{
    int w = sizeof(int) << 3;
    return (((unsigned) -1) >> (w - k)) << j;
}

int main()
{
    printf("%x\n", A(4));
    printf("%x\n", B(20, 10));

    return 0;
}

