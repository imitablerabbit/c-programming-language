/* C Syntax Checker.
 *
 * This program is able to check for basic syntax errors in c programs.
 * Examples include missing paratensis, braces or quotes.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "syntaxchecker.h"

int main() {
    char c;
    char* input = NULL;
    size_t len;
    unsigned int ecount;

    len = get_input(BUFFER_SIZE, &input);
    ecount = syntax_check(input, len); 
    free(input);
    return ecount;
}

size_t get_input(const size_t init_buf, char** buf) {
    char* buffer = NULL;
    size_t buf_size = init_buf;
    char c;
    unsigned int index = 0;

    buffer = (char*) malloc(buf_size); 
    while ((c = getchar()) != EOF) {
        if (index >= buf_size - 2) { /* Accounting for null terminator */
            buf_size += init_buf;
            buffer = (char*) realloc(buffer, buf_size); 
            DEBUG_PRINT("Reallocated buffer size to %d\n", buf_size);
        }
        buffer[index] = c;
        index++;
    }
    buffer[index] = '\0';
    *buf = buffer;
    return index;
}

/* Traverse the passed in string and run all of the syntax checks available.
 * If a single syntax check fails then this function will return false. It will
 * also print out errors to stdout. This function returns the number of syntax
 * errors that have been found in the string. */
int syntax_check(char* s, size_t len) {
    unsigned int i;
    unsigned int error_count;
    char c, matching_c;
    int check_resp;
    unsigned int line, cpos;

    line = 1, cpos = 0;
    for (i = 0; i < len && (c = s[i]) != '\0'; i++) {
        switch (c) {
            case '\n':
                line++;
                cpos = 0;
                break;
            case '"':
                DEBUG_PRINT("Checking string literal at %d\n", i);
                check_resp = check_string(s + i, len - i);
                if (check_resp < 0) {
                    printf("%d-%d: Missing \" (apostrophe) at the end of string literal\n", line, cpos);
                    error_count++;
                } else {
                    DEBUG_PRINT("Char literal check passed at %d\n", i);
                    i += check_resp;
                }
                break;
            case '\'':
                DEBUG_PRINT("Checking char literal at %d\n", i);
                check_resp = check_char_literal(s + i, len - i);
                if (check_resp < 0) {
                    printf("%d-%d: Missing ' (quote) at the end of char literal\n", line, cpos);
                    error_count++;
                } else {
                    DEBUG_PRINT("Char literal check passed at %d\n", i);
                    i += check_resp;
                }
                break;
            case '{':
            case '[':
            case '(':
                /* Check forward matching characters. */
                matching_c = get_matching_char(c);
                DEBUG_PRINT("Checking for matching chars %c and %c\n", c, matching_c);
                check_resp = find_matching_char(s + i, len - i, c, matching_c);
                if (check_resp < 0) {
                    printf("%d-%d: No matching char %c found for %c\n", line, cpos, matching_c, c);
                    error_count++;
                } else {
                    DEBUG_PRINT("Matching char %c found at %d\n", matching_c, i + check_resp);
                }
                break;
            default:
                break;
        }
        cpos++;
    }
    return error_count;
}

/* Checks whether the character literal is complete. The string passed in should
 * be at the start of the character literal. This function will check the next 4
 * characters in the string to make sure that are all valid. If a char literal
 * is incorrect then this function will return < 1. If the char literal is
 * correct then this function will return the length of the char literal. */
int check_char_literal(char* s, size_t len) {
    unsigned int i = 0;
    char c;

    /* If less than 4 then it cannot be correct. The minimum it cold be is
     * open, character, close and a null terminator. Anything less must
     * contain an error. */
    if (len < 4) {
        return -1;
    }
    c = s[i];
    if (c != '\'')
        return -1;
    i++;
    c = s[i];
    if (c == '\\') { /* Skip the escaped char */
        i++;
        c = s[i];
    }
    i++;
    c = s[i];
    if (c != '\'')
        return -1;
    return i;
}

int check_string(char* s, size_t len) {
    int i = 0;
    bool skip = false;

    if (s[i] != '"')
        return -1;
    for (i = 1; i < len && s[i] != '\0'; i++) {
        if (skip) {
            skip = false;
            continue;
        }
        if (s[i] == '\\') {
            skip = true;
            continue;
        }
        if (s[i] == '"')
            return i;
    }
    return -1;
}

char get_matching_char(char c) {
    switch (c) {
        case '[': return ']';
        case ']': return '[';
        case '{': return '}';
        case '}': return '{';
        case '(': return ')';
        case ')': return '(';
    }
}

/* Find the location of the correctly matching char. This function takes into
 * account the number of matching opening and closing characters in between the
 * closing character needed. This function also ignores comments and strings.
 * It returns the position of the matched character in the string passed in. */
int find_matching_char(char* s, size_t len, char open, char closing) {
    unsigned int needed = 1;
    unsigned int i;
    int skip;
    char c;

    for (i = 1; i < len && (c = s[i]) != '\0'; i++) {

        /* Remove strings as long as we are not looking for quote */
        if (c == '"' && closing != '"') {
            skip = check_string(s + i, len);
            if (skip > 0) {
                i += skip;
            }
            c = s[i];
        }

        /* Remove character literals */
        if (c == '\'' && closing != '\'') {
            skip = check_char_literal(s + i, len);
            if (skip > 0) {
                i += skip;
            }
            c = s[i];
        }

        /* Skip any comments if possible */
        if (c == '/' && s[i + 1] == '*') {
            skip = swallow_comment(s + i, len);
            if (skip > 0) {
                i += skip;
            }
            c = s[i];
        }

        if (c == open && open != closing) {
            needed++;
        }
        if (c == closing) {
            needed--;
            if (needed == 0) {
                return i;
            }
        }
    }
    return -1;
}

int swallow_comment(char* s, size_t len) {
    return swallow_until_matching(s, len, "*/");
}

int swallow_until_matching(char* s, size_t len, char* match) {
    int i;
    char c;

    for (i = 1; i < len && (c = s[i]) != '\0'; i++) {
        if (has_prefix(s + i, match)) {
            return i + strlen(match);
        }
    }
    return -1;
}

bool has_prefix(char* s, char* pre) {
    int len;
    int i;

    len = strlen(pre);
    for (i = 0; i < len; i++) {
        if (pre[i] != s[i]) {
            return false;
        }
    }
    return true;
}

