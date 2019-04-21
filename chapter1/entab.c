#include <stdio.h>
#include <stdlib.h>

#define TAB_STOP 8

void replacespaces(char[], char[], int);

int main() {
    ssize_t len;
    char* line = NULL;
    size_t buffer = 0;

    while ((len = getline(&line, &buffer, stdin)) != -1) {
        char expandedline[len];
        replacespaces(line, expandedline, TAB_STOP);
        printf("%s", expandedline);
    }
    free(line);
    return 0;
}

// Replace the spaces in the string with the number of
// tabs needed to meet the tab stop
void replacespaces(char from[], char to[], int tabstop) {
    int i;
    char c;
    int spacestart;
    int toindex = 0;
    int spaces = 0;

    // Loop over the array and fill in the new array when a
    // non space character is met.
    for (i = 0; (c = from[i]) != '\0'; i++) {
        if (c == ' ') {
            spaces++;
            continue;
        }

        // Add the tab characters from run of spaces
        while (spaces > 0) {
            spacestart = i - spaces; // start of spaces
            if ((spacestart % tabstop) + spaces >= tabstop) { // Fill in tabs
                spaces -= tabstop - (spacestart % tabstop);
                to[toindex] = '\t';
                toindex++;
            } else { // Add remaining spaces
                to[toindex] = ' ';
                toindex++;
                spaces--;
            }
        }

        // Add the normal character
        to[toindex] = c;
        toindex++;
    }
    to[toindex] = '\0';
}
