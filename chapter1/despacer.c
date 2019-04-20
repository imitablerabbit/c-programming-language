#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/**
 * TODO:
 * This file could use a common function for finding the position of the first
 * character in a whitespace sequence. This would mean that all blank and the
 * trimwhitespace functions could use the same mechnism.
 */

bool iswhitespace(char c);
bool allblank(char* line, size_t bufsize);
int trimwhitespace(char* line, size_t bufsize);

int main() {
    // Args that getline will need.
    char* line = NULL; // Need to free as malloc or realloc will be used.
    size_t buffersize = 0;
    ssize_t len;

    // Apparently there is a getline implementation in stdio.h for POSIX
    while ((len = getline(&line, &buffersize, stdin)) != -1) {
        if (allblank(line, buffersize))
            continue;

        trimwhitespace(line, buffersize);
        printf("%s\n", line);
    }
    free(line);
}

bool iswhitespace(char c) {
    return c == ' ' || c == '\n' || c == '\t';
}

bool allblank(char* line, size_t bufsize) {
    int i;

    for (i = 0; (line[i] != '\0') && i < bufsize; i++) 
        if (!iswhitespace(line[i]))
            return false;
    return true;
}

int trimwhitespace(char* line, size_t bufsize) {
    int i, j;

    for (i = 0; (line[i] != '\0') && i < bufsize; i++);
    for (j = i-1; iswhitespace(line[j]) && j > 0; j--);
    line[j+1] = '\0';
    return i - j;
}

