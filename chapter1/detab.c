#include <stdio.h>

#define TAB_STOP 8
#define MAX_LINE_LENGTH 1000

int getLine(char[], int);
void replaceTabs(char[], int, char[], int);

int main() {
    char line[MAX_LINE_LENGTH];
    int len;
    while ((len = getLine(line, MAX_LINE_LENGTH)) > 0) {
        printf("Line: %s", line);
        char expandedLine[len * TAB_STOP];
        replaceTabs(line, len, expandedLine, TAB_STOP);
        printf("Expanded Line: %s", expandedLine);
    }
    return 0;
}

int getLine(char a[], int lim) {
    int c, i;
    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; i++) {
        a[i] = c;
    }
    if (c == '\n') {
        a[i] = c;
        i++;
    }
    a[i] = '\0';
    return i;
}

// Replace the tabs in the string with the number of
// spaces needed to meet the tab stop
void replaceTabs(char from[], int size, char to[], int tabStop) {
    int c, i, j;
    int spaces; // Number of spaces to replace the tab with
    int offset = 0; // The current offset from the original

    for (i = 0; i < size && (c = from[i]) != '\0'; i++) {
        if (c != '\t') {
            to[i + offset] = c;
            continue;
        }
        spaces = tabStop - ((i + offset) % tabStop);
        for (j = i + offset; j < i + offset + spaces; j++)
            to[j] = ' ';
        offset += spaces - 1;
    }
    to[i + offset] = '\0';
}

