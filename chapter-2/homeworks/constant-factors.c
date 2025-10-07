#include <stdio.h>

// 2.77

int A(int x)
{
    return (x << 4) + x;
}

int B(int x)
{
    // x - 8x = -7x = kx, k being -7
    return x - (x << 3);
}

int C(int x)
{
    // (64x) - (4x) = 60x, k being 60
    return (x << 6) - (x << 2);
}

int D(int x)
{
    // (16x) - (128x) = -112x
    return (x << 4) - (x << 7);
}

int main()
{
    int x = 0x12345678;

    printf("%d == %d? %d\n", A(x), x * 17, A(x) == (x * 17));
    printf("%d == %d? %d\n", B(x), x * -7, B(x) == (x * -7));
    printf("%d == %d? %d\n", C(x), x * 60, C(x) == (x * 60));
    printf("%d == %d? %d\n", D(x), x * -112, D(x) == (x * -112));

    return 0;
}
