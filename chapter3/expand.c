#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

/* TODO: Fix '-' characters getting dropped.
 * TODO: Move array appending into new function.
 * */

int expand(char* expansion_chars, char** expanded);

int main() {
    char* s = "az";
    char* expanded;
    expand(s, &expanded);
    printf("%s\n", expanded);
    free(expanded);

    expand_string("a-z1-3-5-9g-m", 11, &expanded);
    printf("%s\n", expanded);
    free(expanded);
}

/* Parse the string and expand when we need to. */
int expand_string(char* expansion_string, int len, char** expanded) {
    int has_expanded;
    
    char* buffer;
    char* buffer_temp;
    int buffer_size;

    char prev, prev2;
    int i;
    int char_count;
    char expansion_chars[1000];
    char* expanded_temp;
    int expansion_count;

    /* Check that there are enough chars to expand. */
    has_expanded = 0;
    if (len < 4)
        return has_expanded;

    /* Initialise with a default allocation. */
    buffer = (char*) malloc(len);
    buffer_size = len;

    /* Loop through the characters and expand them either side of
     * the '-' chars. */
    char_count = 0;
    prev = *expansion_string++;
    while (*expansion_string) {
        if (*expansion_string == '-') {
            /* Loop until we reach 2 characters which are not '-'. */
            i = 0;
            expansion_chars[i] = prev;
            i++;
            while (*expansion_string) {
                if (prev != '-' && *expansion_string != '-') {
                    break;
                }
                if (*expansion_string != '-') {
                    expansion_chars[i] = *expansion_string;
                    i++;
                }
                prev2 = prev;
                prev = *expansion_string++;
            }
            expansion_chars[i] = '\0';
            expansion_count = expand(expansion_chars, &expanded_temp);
            has_expanded = 1;

            /* Add the expanded chars to current character list. Memory is
             * reallocated on each expansion to encompass only the amount of
             * characters needed. */
            buffer_size = buffer_size + expansion_count;
            buffer_temp = malloc(buffer_size);
            buffer_temp = strcat(buffer_temp, buffer);
            buffer_temp = strcat(buffer_temp, expanded_temp);
            buffer = buffer_temp;
            free(expanded_temp);
        } else {
            *buffer = *expansion_string;
            char_count++;
        }
        prev = *expansion_string++;
    }
    *expanded = buffer;
    return has_expanded;
}

/* Expand the differences between the chars.
 *
 * The number of characters that were expanded is returned from the function.
 * The expansion is applied to the passing in character array using the `exp'
 * characters. */
int expand(char* expansion_chars, char** expanded) {
    char* expansion_chars_start = expansion_chars;
    size_t buffer_size;
    char* buffer;
    char* buffer_start;
    char prev;
    char c;

    /* Calculate the size of the string buffer needed to expand
     * the characters. */
    buffer_size = 1;
    prev = *expansion_chars++;
    while (*expansion_chars) {
        buffer_size += *expansion_chars - prev;
        prev = *expansion_chars;
        expansion_chars++; 
    }
    buffer_size++; /* Need space for null ending. */
    buffer = (char*) malloc(buffer_size);
    buffer_start = buffer;

    /* Expand the characters into the buffer. We only add the end expansion
     * character when at the very end so as to avoid duplicating some of
     * the characters. */
    expansion_chars = expansion_chars_start;
    prev = *expansion_chars++;
    while (*expansion_chars) {
        for (c = prev; c < *expansion_chars; c++) {
            *buffer++ = c;
        }
        prev = *expansion_chars;
        expansion_chars++;
    }
    *buffer++ = prev;
    *buffer = 0;
    *expanded = buffer_start;
    return buffer_size;
}
