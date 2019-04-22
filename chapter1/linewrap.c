/** @file */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_LENGTH 80

// Add new lines in appropriate places so that the line becomes
// less than max_length.
void wrapline(char** line, size_t* buffer, unsigned int max_length);

int main() {
    char* line = NULL;
    size_t buffer = 0;
    ssize_t len;

    while ((len = getline(&line, &buffer, stdin)) != -1) {
        if (len > 80) {
            wrapline(&line, &buffer, MAX_LENGTH);
        }
        printf("%s", line);
    }
    free(line);
}

/** 
 * wrapline will wrap a line via newline characters. The newlines will be
 * used in place of the previous space character before the line exceeds the
 * max_length. If there is no space before the line should wrap, then a hard
 * word wrap will be used and the newline character will be added before the
 * max_length.
 *
 * This function may cause mem allocations if the buffer is not big enough to
 * hold the new line characters. Its is therefore required to call `free' on
 * the line variable after this function has been called.
 *
 * @param line - The input line that will have the newline characters inserted
 * into it. This is a pointer to a character array.
 *
 * @param buffer - The initial buffer size of the input text. This is a pointer
 * to a size_t var as it can be changed if the input string gets reallocated.
 *
 * @param max_length - The maximum length that the line should have before a
 * new line character is added.
 *
 * @return void
 * */
void wrapline(char** line, size_t* buffer, unsigned int max_length) {
    int i, j;           // Generic indexes
    int line_length;    // The actual line length of the string
    int approx_lines;   // The approximate number of newlines
    int since_last;     // The number of characters since the last new line
    bool space_found;   // Whether we could find a space to replace

    int new_i;              // The current position in the new_line array.
    char* new_line = NULL;  // The new string that will be returned as line
    size_t new_buffer;      // The new size of the buffer

    // Get the length of the line
    for (i = 0; i < *buffer && (*line)[i] != '\0'; i++);
    line_length = i;
    if (line_length-1 <= max_length) // Compensate for null terminator
        return;

    // Allocate a big enough char array assuming worst case scenario of the new
    // lines being added to the middle.
    // TODO: check for whether the buffer size is already ample
    approx_lines = (line_length / max_length) * 2;
    new_buffer = *buffer + approx_lines;
    if (line_length + approx_lines < *buffer) {
        new_line = (char*) malloc(new_buffer);
    }
    
    // Loop over all characters and add the newlines.
    since_last = 0;
    for (i = 0, new_i = 0; i < *buffer && (*line)[i] != '\0'; i++, new_i++) {
        if (since_last >= max_length) {

            // Replace any space with a new line.
            space_found = false;
            for (j = 0; j < since_last; j++) {
                if ((*line)[i - j] == ' ') {
                    new_line[new_i - j] = '\n';
                    i -= j-1; // Move back to where we just added the newline
                    new_i -= j-1;
                    space_found = true;
                    break;
                }
            }

            // Add a newline before the current character if we couldnt add a
            // new line in a polite way.
            if (!space_found) {
                new_line[new_i] = '\n';
                new_i++;
            }
            since_last = 0;
        }

        // Add the current character
        new_line[new_i] = (*line)[i];
        since_last++; 
    }
    free(*line);
    *line = new_line;
    *buffer = new_buffer;
}

