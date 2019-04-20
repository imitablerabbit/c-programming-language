#include <stdio.h>
#include <stdlib.h>

#define MAX_LENGTH 500

int getindex(char*, char);
int inccount(char*, int*, char);
int appendchar(char*, char);
void drawhistogram(char*, int*);
char* escapechar(char);

int main() {
    unsigned int i;
    unsigned int freq[MAX_LENGTH]; // The frequency of the chars
    unsigned char chars[MAX_LENGTH]; // Char pos in the freq
    char c;

    for (i = 0; i < MAX_LENGTH; i++)
        freq[i] = 0;
    chars[0] = '\0';

    while ((c = getchar()) != EOF)
        inccount(chars, freq, c);
    printf("chars: %s\n", chars);
    drawhistogram(chars, freq);
}

// Increment the frequency of the character passed in. Returns
// the index of the character.
int inccount(char* chars, int* freq, char c) {
    int index;
    index = getindex(chars, c);
    if (index < 0)
        index = appendchar(chars, c);
    freq[index]++;
    return index;
}

int getindex(char* chars, char c) {
    unsigned int i;
    char c2;
    for (i = 0; (c2 = chars[i]); i++)
        if (c == c2)
            return i;
    return -1;
}

int appendchar(char* chars, char c) {
    int i;
    for (i = 0; chars[i] != '\0'; i++);
    chars[i] = c;
    chars[i + 1] = '\0';
    return i;
}

// The character used to draw the histogram bars.
#define BAR_CHAR '-'

// The max length of the histogram bars. Only hit if 100% of the data fits
// in a single bin.
#define HIST_LENGTH 50 

/* function: drawhistogram
 * chars: The chars that the freq represents.
 * freq: The word length frequencies that need to be plotted.
 * s: Size of the histogram array passed in.
 *
 * Plots the histogram data passed into the function on stdout.
 */
void drawhistogram(char* chars, int* freq) {
    int totalchars;
    int i, j, nbarchars;
    char barchars[HIST_LENGTH+1];
    float ratio;

    for (i = 0, totalchars = 0; chars[i] != '\0'; i++)
        totalchars++;
    
    printf("Char\t|Freq\n");
    printf("====\t|====\n");
    for (i = 0; i < totalchars; i++) {
        ratio = (float) freq[i] / (float) totalchars;
        nbarchars = (int) (ratio * HIST_LENGTH);
        for (j = 0; j < nbarchars && j < HIST_LENGTH; j++)
            barchars[j] = BAR_CHAR;
        barchars[j] = '\0';
        printf("%s\t|%s\n", escapechar(chars[i]), barchars);
    }
}

char* escapechar(char c) {
    char* s;
    switch (c) {
        case '\n': return "\\n";
        case ' ': return "' '";
        case '\b': return "\\b";
    }
    s = (char*) malloc(2);
    sprintf(s, "%c", c);
    return s;
}
