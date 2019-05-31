/* Twos Compliment:
 *
 * x &= (x - 1) deletes the rightmost bit, explain why.
 *
 * Positive number (ending in 10):
 * x = b00000110
 * x - 1 = b00000101
 * x & (x - 1) = b00000110 & b00000101 = b00000100
 *
 * Positive number (ending in 1):
 * x = b00000001
 * x - 1 = b00000000
 * x & (x - 1) = b00000001 & b00000000 = b00000000
 *
 * Zeroed number:
 * x = b00000000
 * x - 1 = b11111111
 * x & (x - 1) = b00000000 & b11111111 = b00000000
 *
 * Negative number (ending in 1):
 * x = b11111111
 * x - 1 = b11111110
 * x & (x - 1) = b11111111 & b11111110 = b11111110
 *
 * Negative number (ending in 01):
 * x = b11111010
 * x - 1 = b11111001
 * x & (x - 1) = b11111010 & b11111001 = b11111000
 *
 * In a 2's complement system subtracting 1 off any number will always yield a
 * 0 in place of the last 1 bit in the bitstring. This means that when those 
 * numbers are '&' together the right most bit is set to 0.
 *
 * */
#include <stdio.h>

int main() {
    char x = 0xAA; /* b10101010 */
    int count = 0;

    printf("Number: 0x%02hhX\n", x); /* hh forces 8 bit print out */
    while (x != 0) {
        x &= x - 1;
        count++;
    }
    printf("Count: %d\n", count);
}
