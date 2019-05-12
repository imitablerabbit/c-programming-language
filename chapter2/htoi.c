#include <stdio.h>

int main() {

    printf("%s = %d -> %d\n", "0x00", 0x00, htoi("0x00", 5));
    printf("%s = %d -> %d\n", "0x01", 0x01, htoi("0x01", 5));
    printf("%s = %d -> %d\n", "0x02", 0x02, htoi("0x02", 5));
    printf("%s = %d -> %d\n", "0x0A", 0x0A, htoi("0x0A", 5));
    printf("%s = %d -> %d\n", "0x10", 0x10, htoi("0x10", 5));
    printf("%s = %d -> %d\n", "0xFF", 0xFF, htoi("0xFF", 5));
    printf("%s = %d -> %d\n", "0xAB", 0xAB, htoi("0xAB", 5));
    printf("%s = %d -> %d\n", "0xAC", 0xAC, htoi("0xAC", 5));
    printf("%s = %d -> %d\n", "0xFAB", 0xFAB, htoi("0xFAB", 6));
    printf("%s = %d -> %d\n", "0xDEAD", 0xDEAD, htoi("0xDEAD", 7));
    printf("%s = %d -> %d\n", "0xBEEF", 0xBEEF, htoi("0xBEEF", 7));
    printf("%s = %d -> %d\n", "0xdead", 0xdead, htoi("0xdead", 7));
}

int htoi(char* s, size_t len) {
    int num = 0;
    int i = 0;
    int x = 0;

    /* Remove the optional 0x from the start of the string */
    if (len > 2)
        if (s[0] == '0' && (s[1] == 'x' || s[1] == 'X'))
            i += 2;
    for (; i < len && s[i] != '\0'; i++) {

        /* Convert the char to a number */
        if (s[i] >= '0' && s[i] <= '9') {
            x = s[i] - '0';
        } else if (s[i] >= 'a' && s[i] <= 'f') {
            x = s[i] - 'a' + 10;
        } else if (s[i] >= 'A' && s[i] <= 'F') {
            x = s[i] - 'A' + 10;
        }

        /* Add the number to the running total */
        num = (num * 16) + x;
    }
    return num;
}

