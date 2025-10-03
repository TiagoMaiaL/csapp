#include <assert.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned replace_byte(unsigned x, int i, unsigned char b);
bool int_shifts_are_arithmetic();
unsigned srl(unsigned x, int k);
int sra(int x, int k);
int any_odd_one(unsigned x);
int odd_ones(unsigned x);
int leftmost_one(unsigned x);
int int_size_is_32();
int lower_one_mask(int n);
unsigned rotate_left(unsigned x, int n);
int fits_bits(int x, int n);
void copy_int(int val, void *buf, int maxbytes);

typedef unsigned packed_t;
int xbyte(packed_t word, int bytenum);

int saturating_add(int x, int y);
int tsub_ok(int x, int y);

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

    // 2.64
    printf("2.64: any odd one of 0xAAAAAAAA = %d\n", any_odd_one(0xAAAAAAAA));
    printf("2.64: any odd one of 0x50450010 = %d\n", any_odd_one(0x50450010));

    // 2.65
    printf("2.65: odd ones of 0xAF12AF12 = %x\n", (unsigned) odd_ones(0xAF12AF12));
    printf("2.65: odd ones of 0xAF2431FF = %x\n", (unsigned) odd_ones(0xAF2431FF));

    // 2.66
    printf("2.66: leftmost_one of 0x08000011 = %x\n", (unsigned) leftmost_one(0x08000011));
    printf("2.66: leftmost_one of 0x0003AFD5 = %x\n", (unsigned) leftmost_one(0x0003AFD5));
    printf("2.66: leftmost_one of 0x00007A11 = %x\n", (unsigned) leftmost_one(0x00007A11));

    // 2.67
    printf("2.67 a: shifting to an amount greater than the type size is undefined behavior.\n");
    printf("2.67 b, c: int size is 32? %d\n", (unsigned) int_size_is_32());

    // 2.68
    printf("2.68: lower_one_mask(6) = %x\n", lower_one_mask(6));
    printf("2.68: lower_one_mask(17) = %x\n", lower_one_mask(17));
    printf("2.68: lower_one_mask(30) = %x\n", lower_one_mask(30));

    // 2.69
    printf("2.69: rotate_left 0x12345678 by 4  (should be 0x23456781) = %x\n", rotate_left(0x12345678, 4));
    printf("2.69: rotate_left 0x12345678 by 20 (should be 0x67812345) = %x\n", rotate_left(0x12345678, 20));

    // 2.70
    printf("2.70: fits_bits(0x00004567, 16) ? %d\n", fits_bits(0x00004567, 16));
    printf("2.70: fits_bits(0x00008567, 16) ? %d\n", fits_bits(0x00008567, 16));
    printf("2.70: fits_bits(0xFFFF4567, 20) ? %d\n", fits_bits(0xFFFF4567, 20));
    printf("2.70: fits_bits(0xFFF80007, 20) ? %d\n", fits_bits(0xFFF80007, 20));

    // 2.71
    printf("2.71: xbyte(0xDDCCBB7A, 0) == %x\n", xbyte(0xDDCCBB7A, 0));
    printf("2.71: xbyte(0xDDCCABAA, 1) == %x\n", xbyte(0xDDCCABAA, 1));
    printf("2.71: xbyte(0xDDCCBBAA, 2) == %x\n", xbyte(0xDDCCBBAA, 2));
    printf("2.71: xbyte(0x3FCCBBAA, 3) == %x\n", xbyte(0x3FCCBBAA, 3));

    // 2.72
    int a = 0x87654321;
    int b = 0xFEDCBA98;
    void *buf = malloc(sizeof(int) * 2);

    copy_int(a, buf, 8);
    printf("2.72: copy_int result for a = %x\n", (int)((int *)buf)[0]);
    copy_int(b, (void *)((int *)buf + 1), 4);
    printf("2.72: copy_int result for b = %x\n", (int)((int *)buf)[1]);

    free(buf);

    // 2.73
    printf("2.73: saturating_add(tmax, 10) = %x\n", saturating_add(INT_MAX, 10));
    printf("2.73: saturating_add(tmin, -10) = %x\n", saturating_add(INT_MIN, -10));
    printf("2.73: saturating_add(101, 23) = %x\n", saturating_add(101, 23));

    // 2.74
    printf("2.74: tsub_ok(10, 10) = %x\n", tsub_ok(10, 10));
    printf("2.74: tsub_ok(TMIN, 1) = %x\n", tsub_ok(INT_MIN, 1));
    printf("2.74: tsub_ok(2, -8) = %x\n", tsub_ok(2, -8));

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

int any_odd_one(unsigned x)
{
    unsigned mask = 0x55555555;
    return ((unsigned) (x & mask)) != 0;
}

int odd_ones(unsigned x)
{
    x = x ^ (x >> 16);
    x = x ^ (x >> 8);
    x = x ^ (x >> 4);
    x = x ^ (x >> 2);
    x = x ^ (x >> 1);
    x = x & 0x1;
    return x;
}

int leftmost_one(unsigned x)
{
    x = x | x >> 1;
    x = x | x >> 2;
    x = x | x >> 4;
    x = x | x >> 8;
    x = x | x >> 16;
    x = x + 1;
    x = x >> 1;

    return x;
}

int int_size_is_32()
{
    unsigned int x;

    x = (unsigned int) 0x8000000000000000U;

    if (x != 0) {
        return 0;
    }

    x = 0x80000000U;

    if (x != 0) {
        return 1;
    } else {
        return 0;
    }
}

int lower_one_mask(int n)
{
    unsigned x;
    short w = sizeof(int) << 3;

    if (n < 1 || n > w)
        return 0;

    x = (unsigned) -1;
    x = x >> (w - n);

    return x;
}

unsigned rotate_left(unsigned x, int n)
{
    int w = sizeof(int) << 3;

    unsigned mask = (unsigned) -1;
    mask = mask >> n;
    mask = ~mask;

    unsigned right_bits = x & mask;
    right_bits = right_bits >> (w - n);

    x = x << n;
    x = x + right_bits;

    return x;
}

int fits_bits(int x, int n)
{
    short w = sizeof(int) << 3;

    int max = -1;
    max = (unsigned) max >> 1;
    max = (unsigned) max >> (w - n);

    int min = (n == w) ? (max + 1) : -(1 << (n - 1));

    if (n < 1 || n > w)
        return 0;

    if (x <= max && x >= min)
        return 1;

    return 0;
}

#define MAX_BYTE 3
int xbyte(packed_t word, int bytenum)
{
    return ((int)(word << ((MAX_BYTE - bytenum) << 3))) >> (MAX_BYTE << 3);
}

void copy_int(int val, void *buf, int maxbytes)
{
    if (maxbytes <= 0)
        return;

    if ((size_t)maxbytes >= sizeof(val))
        memcpy(buf, (void *)&val, sizeof(val));
}

int saturating_add(int x, int y)
{
    bool can_overflow_pos = x > 0 && y > 0;
    bool can_overflow_neg = x < 0 && y < 0;
    int result = x + y;

    ((can_overflow_pos && result < 0) && (result = INT_MAX)) || 
    ((can_overflow_neg && result > 0) && (result = INT_MIN));

    return result;
}

int tsub_ok(int x, int y)
{
    int res = 1;
    (x < 0) && ((x - y) > 0) && (res = 0);
    return res;
}
