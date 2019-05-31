#include <stdio.h>

int any(char*, char* s2);

int main() {
    printf("hello h -> 0 == %d\n", any("hello", "h"));
    printf("hello lh -> 0 == %d\n", any("hello", "lh"));
    printf("hello la -> 2 == %d\n", any("hello", "la"));
    printf("hello aaabbbo -> 4 == %d\n", any("hello", "aaabbbo"));
    printf("hello a -> -1 == %d\n", any("hello", "a"));
}

int any(char* s1, char* s2) {
    int i, j;
    char c1, c2;

    for (i = 0; (c1 = s1[i]) != '\0'; i++) {
        c1 = s1[i];
        for (j = 0; (c2 = s2[j]) != '\0'; j++) {
            if (c1 == c2)
                return i;
        }
    }
    return -1;
}
