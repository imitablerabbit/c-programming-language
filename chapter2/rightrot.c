#include <stdio.h>

unsigned char rightrot(unsigned char x, unsigned char n);

int main() {
    unsigned int x = 0xF; // 00001111 
    unsigned int correctout = 0xF0; // 11110000 
    unsigned int out;

    out = rightrot(0xF, 4);
    printf("Required: %#08x, Actual: %#08x, Match: %d\n", correctout, out, correctout == out);
}

unsigned char rightrot(unsigned char x, unsigned char n) {
    int i;
    unsigned discarded, rotated;

    for (i = 0; i < n; i++) {
        discarded = x & 1;
        rotated = discarded << (sizeof(x) * 8) - 1;
        x = (x >> 1) | rotated;
    }
    return x;
}
