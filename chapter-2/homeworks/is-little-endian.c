#include <stdbool.h>
#include <stdio.h>

#define TEST_VAL 1

typedef unsigned char *byte_pointer;

static bool is_little_endian();

int main()
{
    printf("Is little endian? %d\n", is_little_endian());
    return 0;
}

static bool is_little_endian()
{
    unsigned int i = TEST_VAL;
    byte_pointer ptr = (byte_pointer) &i;

    return ptr[0] > 0;
}

