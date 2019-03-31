#include <stdio.h>

unsigned int setbits(unsigned int, int, int, unsigned int);

int main() {
    unsigned int x = 0xAA; // 10101010
    unsigned int y = 0xBD; // 10111101
    unsigned int correctout = 0xAC; // 10101100
    unsigned int out;

    out = setbits(x, 4, 3, y);
    printf("Required: %#08x, Actual: %#08x, Match: %d\n", correctout, out, correctout == out);
}

// Sets the bits in int x starting at position p for n places with the
// values found in the int y.
// Example:
//      x = 10101010
//      p = 4
//      n = 3
//      y = 10111101
//
//      returns 10101100
unsigned int setbits(unsigned int x, int p, int n, unsigned int y) {
    unsigned int mask, xmask, ymask;

    // Bit mask of 1's at position p through to n
    mask = (~(~0 << n)) << (p - n); // 00001110

    // Keep only the x bits we need
    xmask = x & ~mask; // 10100000

    // Keep only the y bits we need
    ymask = y & mask; // 00001100

    // Take the relevant bits from each masked int
    return xmask | ymask; 
}
