#include <stdio.h>

int get_line(char* s, int lim);

int main() {
    char line[1000];

    get_line(line, 1000);
    printf("%s", line);
}

int get_line(char* s, int lim) {
    int c, i;

    for (i = 0; i < lim - 1; i++) {
        c = getchar();
        if (c == '\n') break;
        if (c == EOF) break;
        s[i] = c;
    }
    if (c == '\n') {
        s[i] = c;
        i++;
    }
    s[i] = '\0';
    return i;

}
