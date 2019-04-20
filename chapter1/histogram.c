#include <stdio.h>
#include <stdlib.h>

#define MAX_LENGTH 15

void drawhistogram(int, int*, int);

int main() {
    unsigned int i, count, words;
    unsigned freq[MAX_LENGTH]; // Char pos in the freq
    char c;

    count = 0, words = 0;
    for (i = 0; i < MAX_LENGTH; i++)
        freq[i] = 0;

    while ((c = getchar()) != EOF) {
        if (c == ' ' || c == '\n') {
            printf("%d\n", count);
            freq[count]++;
            words++;
            count = 0;
        } else {
            count++;
        }
    }
    drawhistogram(words, freq, MAX_LENGTH);
}

// The character used to draw the histogram bars.
#define BAR_CHAR '-'

// The max length of the histogram bars. Only hit if 100% of the data fits
// in a single bin.
#define HIST_LENGTH 50 

/* function: drawhistogram
 * freq: The word length frequencies that need to be plotted.
 * s: Size of the histogram array passed in.
 *
 * Plots the histogram data passed into the function on stdout.
 */
void drawhistogram(int words, int* freq, int freqlen) {
    int i, j, nbarchars;
    char barchars[HIST_LENGTH+1];
    float ratio;

    printf("Len\t|Freq\n");
    printf("===\t|====\n");
    for (i = 0; i < freqlen; i++) {
        ratio = (float) freq[i] / (float) words;
        nbarchars = (int) (ratio * HIST_LENGTH);
        for (j = 0; j < nbarchars && j < HIST_LENGTH; j++)
            barchars[j] = BAR_CHAR;
        barchars[j] = '\0';
        printf("%d\t|%s %d\n", i, barchars, freq[i]);
    }
}
