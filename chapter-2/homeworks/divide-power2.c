#include <stdio.h>
#include <limits.h>

// 2.78

int divide_power2(int x, int k)
{
    return (x >> k) + (x < 0 && ((1 << k) - 1) != 0);
}

int main()
{
    int x;

    x = 0x12345678;
    printf("%x == %x ? %d\n", divide_power2(x, 1), x / 2, divide_power2(x, 1) == x / 2);

    x = 0x87654321;
    printf("%x == %x ? %d\n", divide_power2(x, 2), x / 4, divide_power2(x, 2) == x / 4);

    x = 0xA0CDEF12;
    printf("%x == %x ? %d\n", divide_power2(x, 2), x / 4, divide_power2(x, 2) == x / 4);

    return 0;
}
