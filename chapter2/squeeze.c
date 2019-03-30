#include <stdio.h>
#include <stdbool.h>

void squeeze(char[], int);
void squeezestr(char[], char[]);
bool match(char, char[]);

int main() {
    char s[] = "Hello world!";
    char s2[] = "Hello world!";

    squeeze(s, 'l');
    printf("%s\n", s);

    squeezestr(s2, "el");
    printf("%s\n", s2);
}

void squeeze(char s[], int c) {
    int i, j;

    for (i = j = 0; s[i] != '\0'; i++)
        if (s[i] != c)
            s[j++] = s[i];
    s[j] = '\0';
}

void squeezestr(char s[], char t[]) {
    int i, j, k;

    for (i = j = 0; s[i] != '\0'; i++)
        if (!match(s[i], t))
            s[j++] = s[i];
    s[j] = '\0';
}

bool match(char c, char t[]) {
    int i;

    for (i = 0; t[i] != '\0'; i++)
       if (c == t[i])
           return true;
    return false;
}
