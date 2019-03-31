#include <stdio.h>

int main() {
    char c;

    printf("EOF: %d\n", EOF);
    c = getc(stdin); /// ^D to create EOF 
    printf("Char: %d\n", c);
    printf("Equal: %d\n", c == EOF);
}
