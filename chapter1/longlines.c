#include <stdio.h>
#include <stdlib.h>

int main() {
    // Args that getline will need.
    char* line = NULL; // Need to free as malloc or realloc will be used.
    size_t buffersize = 0;
    ssize_t len;

    // Apparently there is a getline implementation in stdio.h for POSIX
    while ((len = getline(&line, &buffersize, stdin)) != -1)
        if (len > 80)
            printf("%s", line);

    free(line);
}
