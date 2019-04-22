#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>


int main() {
    char prev_c, c, next_c;
    bool in_single_line = false;
    bool in_multi_line = false;
    bool in_string = false;

    c = getchar();
    if (c == EOF)
        exit(0);
    while ((prev_c = c, c = getchar()) != EOF) {
        // Handle removing the string and comment blocks
        if (in_string) {
            if (c == '"') {
                in_string = false;
            }
            putchar(c);
            continue;
        } else if (in_single_line) {
            if (c == '\n') {
                in_single_line = false;    
                putchar(c);
            }
            continue;
        } else if (in_multi_line) {
            if (prev_c == '*' && c == '/') {
                in_multi_line = false;
            }
            continue;
        }

        // Handle entering the blocks
        if (c == '"') {
            in_string = true;
        } else if (prev_c == '/' && c == '/') {
            in_single_line = true;
            continue;
        } else if (prev_c == '/' && c == '*') {
            in_multi_line = true;
            continue;
        }

        // Handle printing of the char
        next_c = getchar();
        ungetc(next_c, stdin);
        if (c == '/' && (next_c == '/' || next_c == '*'))
            continue;
        putchar(c);
    }
}
