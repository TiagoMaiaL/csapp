#include <assert.h>
#include <stdbool.h>
#include <stdio.h>

unsigned replace_byte(unsigned x, int i, unsigned char b);
bool int_shifts_are_arithmetic();
unsigned srl(unsigned x, int k);
int sra(int x, int k);

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

    // 2.61
    printf("2.61 a: 0x72 -> %x\n", 0x72 != 0);
    printf("2.61 a: 0x00 -> %x\n", 0x00 != 0);

    printf("2.61 b: 0xFFFFFFFF -> %x\n", 0xFFFFFFFF != -1);
    printf("2.61 b: 0x00 -> %x\n", 0x00 != -1);
    printf("2.61 b: 0xCADF14EE -> %x\n", 0xCADF14EE != -1);

    printf("2.61 c: 0xFEDD0174 -> %x\n", (0xFEDD0174 & 0x000000FF) != 0x00);
    printf("2.61 c: 0xFEDD0100 -> %x\n", (0xFEDD0100 & 0x000000FF) != 0x00);

    printf("2.61 d: 0xFEDD0174 -> %x\n", (0xFEDD0174 >> ((sizeof(int) - 1) << 3)) != 0xFF);
    printf("2.61 d: 0xFFDD0174 -> %x\n", (0xFFDD0174 >> ((sizeof(int) - 1) << 3)) != 0xFF);

    // 2.62
    printf("2.62: uses arithmetic? %d\n", int_shifts_are_arithmetic());

    // 2.63
    unsigned int j = 0xF0F1D2C3;
    printf("2.63: before shift = %x, after srl = %x, native srl = %x\n", j, srl(j, 8), j >> 8);
    printf("2.63: before shift = %x, after sra = %x, native sra = %x\n", j, sra(j, 8), (int) j >> 8);

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

bool int_shifts_are_arithmetic()
{
    // Obs: after researching, here's a simpler way:
    // return (-1 >> 1) == -1;

    size_t w = (sizeof(int) << 3);
    short shift = w - 1;

    return (((0x01 << shift) >> (w - 4)) & 0xFF) == 0xF8;
}

unsigned srl(unsigned x, int k)
{
    if (k == 0)
        return x;

    size_t w;
    int result;
    unsigned mask;

    w = sizeof(int) << 3;
    result = (int) x >> k;
    
    mask = 1;
    for (int j = 0; j < (w - k - 1); j++) {
        mask = mask << 1;
        mask++;
    }

    return mask & result;
}

int sra(int x, int k)
{
    if (k == 0)
        return x;

    size_t w;
    int result;
    unsigned mask;

    w = sizeof(int) << 3;
    result = (unsigned) x >> k;

    mask = 1;
    for (int j = 0; j < k - 1; j++) {
        mask = mask << 1;
        mask++;
    }
    mask = mask << (w - k);

    return mask + result;
}

