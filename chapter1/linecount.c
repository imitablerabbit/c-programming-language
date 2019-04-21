#include <stdio.h>
#include <stdlib.h>

int main() {
    int len;
    char* line = NULL;
    size_t buffer = 0;

    /*
     * getline from POSIX stdio will malloc/realloc char array so editing
     * the program is trivial. If I were to do something like this from scratch
     * I would have revised how the getline function works in the example so
     * that it will either realloc a bigger array. As the book doesnt talk
     * about malloc/realloc until later on, I would probably return the full
     * word length but populate a set size array instead.
     * */
    while ((len = getline(&line, &buffer, stdin)) != -1) {
        printf("%d - %s", len, line);
    }
    free(line);
    return 0;
}
