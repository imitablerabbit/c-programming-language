#include <stdio.h>

char lower(char);

int main() {
    printf("%c -> %c\n", 'H', lower('H'));
}

/* convert char c to lower case */
char lower(char c) {
    return (c >= 'A' && c <= 'Z') ? c + 'a' - 'A' : c;
}
