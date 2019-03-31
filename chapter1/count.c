#include <stdio.h>

int main() {
    int newlines = 0;
    int blanks = 0;
    int other = 0;
    char c;

    while ((c = getchar()) != EOF) {
        if (c == '\n') {
            newlines++;
        } else if (c == ' ') {
            blanks++;
        } else {
            other++;
        }
    }
    printf("New Lines: %d\n", newlines);
    printf("Blanks: %d\n", blanks);
    printf("Other: %d\n", other);
}
