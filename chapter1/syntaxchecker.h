#ifndef SYNTAXCHECKER_H
#define SYNTAXCHECKER_H

#include <stdio.h> /* Mainly used for size_t definition */
#include <stdbool.h>

/* Define a debugging macro for debug print outs when compile with -DDEBUG=1 */
#if defined(DEBUG) && DEBUG > 0
    #define DEBUG_PRINT(fmt, args...)\
        fprintf(stderr, "DEBUG: %s:%d:%s() " fmt, __FILE__,\
                __LINE__, __func__, ##args)
#else
    #define DEBUG_PRINT(fmt, args...)
#endif

/* The initial buffer size that should be used for the input */
#ifndef BUFFER_SIZE
#define BUFFER_SIZE 256
#endif

/* Gather all of the input string from stdin and allocate enough memory for it.
 * Memory is reallocated each time the buffer size is unable to fit any new
 * characters. The buffer size is initially init_buf in size. The buffer is
 * reallocated by init_buf each time it needs increasing. The whole string is
 * stored into the char** buf passed into the function. The size of the string
 * up to and including \0 is returned from the function. */
size_t get_input(size_t init_buf, char** buf);

/* Traverse the passed in string and run all of the syntax checks available.
 * If a single syntax check fails then this function will return false. It will
 * also print out errors to stdout. This function returns the number of syntax
 * errors that have been found in the string. */
int syntax_check(char* s, size_t len);

/* Checks whether the character literal is complete. The string passed in should
 * be at the start of the character literal. This function will check the next 4
 * characters in the string to make sure that are all valid. If a char literal
 * is incorrect then this function will return < 1. If the char literal is
 * correct then this function will return the length of the char literal. */
int check_char_literal(char* s, size_t len);

/* Checks the string literal to make sure that it has an ending character. Any
 * escaped characters in the string will be skipped. This means that if the
 * string contains \" inside of it then the '"' character will not be used as
 * the end character of the string. */
int check_string_literal(char* s, size_t len);

/* Return the matching for the char passed in. */
char get_matching_char(char c);

/* Find the location of the correctly matching char. This function takes into
 * account the number of matching opening and closing characters in between the
 * closing character needed. This function also ignores comments and strings.
 * It returns the position of the matched character in the string passed in. */
int find_matching_char(char* s, size_t len, char open, char close);

int swallow_comment(char* s, size_t len);

/* Swallow all characters until the match has been found. */
int swallow_until_matching(char* s, size_t len, char* match);

/* Return whether the string passed in has the prefix pre. */
bool has_prefix(char* s, char* pre);

#endif
