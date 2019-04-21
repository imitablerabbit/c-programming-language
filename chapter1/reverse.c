#include <stdio.h>
#include <stdlib.h>

void reverse(char s[]);

int main() {
    ssize_t len;
    char* line = NULL;
    size_t buffer = 0;

    while((len = getline(&line, &buffer, stdin)) != -1) {
        reverse(line);
        printf("%s", line);
    }
    free(line);
}

void reverse(char s[]) {
    int i, j;
    int strlen;
    int halfway;
    char temp;
    
    for (i = 0; s[i] != '\0'; i++);
    strlen = i;
    halfway = strlen / 2;
    for (i = 0, j = strlen - 2; i <= j; i++, j--) { // skip \0 and \n
        temp = s[i];
        s[i] = s[j];
        s[j] = temp;
    }
}
