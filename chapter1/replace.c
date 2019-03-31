#include <stdio.h>

int main() {
    char c;

    while ((c = getchar()) != EOF) {
        if (c == '\n')
            printf("\\n"); 
        else if (c == '\b')
            printf("\\b");
        else
            putchar(c);
    }
}
