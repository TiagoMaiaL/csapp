#include <stdio.h>

typedef unsigned char *byte_pointer;

void show_bytes(byte_pointer start, size_t len)
{
    int i;
    for (i = 0; i < len; i++) {
        printf(" %.2x", start[i]);
    }
    printf("\n");
}

void show_int(int n)
{
    show_bytes((byte_pointer) &n, sizeof(int));
}

void show_short(short n)
{
    show_bytes((byte_pointer) &n, sizeof(short));
}

void show_long(long n)
{
    show_bytes((byte_pointer) &n, sizeof(long));
}

void show_float(float n)
{
    show_bytes((byte_pointer) &n, sizeof(float));
}

void show_pointer(void *x)
{
    show_bytes((byte_pointer) &x, sizeof(void *));
}

int main(int argc, char **argv)
{
    show_int(7);
    show_int(15);
    show_int(255);
    show_int(2500489);

    show_short(231);
    show_long(19847325);

    show_float(12.44f);
    show_float(11232.44f);
    show_float(5123.24497f);

    int a = 10;
    show_pointer(&a);
}

