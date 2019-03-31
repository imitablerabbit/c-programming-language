#include <stdio.h>

int main() {
    char p, c;

    p = getchar();
    putchar(p);
    while ((c = getchar()) != EOF) {
        if (p != ' ' || c != ' ')
            putchar(c);
        p = c;
    }
}
