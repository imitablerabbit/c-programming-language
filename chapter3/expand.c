#include <stdio.h>
#include <ctype.h>

#define BUFFER_SIZE 1000

/* TODO: Fix the duplicate characters when chaining expansions. 
 * TODO: Fix dropped alnum when they are not followed by a '-'*/

int expand(char* s1, char* s2);

int main() {
    char* s1 = "aa-z\n0-3-4\n5-7-910-\ng-n\n";
    char s2[BUFFER_SIZE];

    expand(s1, s2);
    printf("%s\n", s2);
}

int expand(char* s1, char* s2) {
    int pos; /* The current position of the new string */
    int i; 

    /* The current and ending characters of the expansion. */
    char current, end; 

    pos = 0;
    for (i = 0; s1[i] != '\0'; i++) {
        if (isalnum(s1[i])) {
            
            /* Keep expanding until we no longer match the chars */
            while (s1[i+1] == '-' && isalnum(s1[i+2])) {
                current = s1[i];
                end = s1[i+2];

                /* Perform the character expanding. */
                while (current <= end) {
                    s2[pos] = current;
                    current++;
                    pos++;
                }
                i += 2;
            }
        } else {
            s2[pos] = s1[i];
            pos++;
        }
    }
    return 0;
}


