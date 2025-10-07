#include <stdio.h>

// 2.79

int mul3div4(int x)
{
    return (((x << 1) + x) >> 2) + (x < 0 && ((1 << 2) - 1) != 0);
}

int main()
{
    int x = 0x00AF1234;
    printf("%d == %d ? %d\n", mul3div4(x), (x * 3) / 4, mul3div4(x) == ((x * 3) / 4));
    x = 0x87654321;
    printf("%d == %d ? %d\n", mul3div4(x), (x * 3) / 4, mul3div4(x) == ((x * 3) / 4));

    return 0;
}

