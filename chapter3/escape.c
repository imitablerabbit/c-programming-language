#include <stdio.h>

#define BUFFER_SIZE 1000

int escape(char* s, char* t);

int main() {
    char* t = "hello world\nI am a new sting\tThis is the rest";
    char s[BUFFER_SIZE];

    escape(s, t);
    printf("%s\n", s);
}

int escape(char* s, char* t) {
    while(*t) {
        switch (*t) {
            case '\n':
                *s = '\\'; s++; *s = 'n';
                break;
            case '\t':
                *s = '\\'; s++; *s = 't';
                break;
            /* Repeat the pattern above for all escape sequences */
            default:
                *s = *t;
        }
        t++;
        s++;
    }
    return 0
}
