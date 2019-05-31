#include <stdio.h>

unsigned int invert(unsigned int x, unsigned int p, unsigned int n);

int main() {
    unsigned int x = 0xAA; // 10101010
    unsigned int correctout = 0x92; // 10010010
    unsigned int out;

    out = invert(0xAA, 6, 3);
    printf("Required: %#08x, Actual: %#08x, Match: %d\n", correctout, out, correctout == out);
}

/* 0x4A = 01001010 3, 6 = 01010110 */
unsigned int invert(unsigned int x, unsigned int p, unsigned int n) {
    unsigned int mask, new, keep;

    /* Bit mask of 1's at position p through to n */
    mask = (~(~0 << n)) << (p - n);

    /* Keep only the x bits we need */
    keep = x & ~mask;
    new = ~x & mask;

    /* Take the relevant bits from each masked int */
    return keep | new;
}
