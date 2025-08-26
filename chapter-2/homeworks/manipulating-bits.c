#include <assert.h>
#include <stdbool.h>
#include <stdio.h>

unsigned replace_byte(unsigned x, int i, unsigned char b);

int main()
{
    // 2.59
    int x = 0x89ABCDEF;
    int y = 0x76543210;
    int op_result = (y & 0xFFFFFF00) + (x & 0x000000FF);

    printf("5.59: result is %x\n", op_result);
    printf("5.59: result is right? %d\n", op_result == 0x765432EF);

    // 2.60
    printf("2.60: replacing bytes 0...3 with 0xAB, for 0x12345678:\n");
    replace_byte(0x12345678, 0, 0xAB);
    replace_byte(0x12345678, 1, 0xAB);
    replace_byte(0x12345678, 2, 0xAB);
    replace_byte(0x12345678, 3, 0xAB);

    return 0;
}

unsigned replace_byte(unsigned x, int i, unsigned char b)
{
    assert(i > -1 && i < 4);

    unsigned int byte_mask = (unsigned int) b << (8 * i);
    unsigned int left_mask = i == 3 ? 0x00 : x & ((unsigned int) -1 << (8 * (i + 1)));
    unsigned int right_mask = x & ~((unsigned int) -1 << (8 * i));
    unsigned int result = left_mask + byte_mask + right_mask;

    printf("%x\n", result);

    return result;
}

