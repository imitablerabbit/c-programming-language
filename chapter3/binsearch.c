#include <stdio.h>

#define NUM_ELEMENTS 1000000

#ifndef BINSEARCH_TYPE
    #define BINSEARCH_TYPE 1
#endif

#if BINSEARCH_TYPE == 1
    #define BINSEARCH binsearch
#elif BINSEARCH_TYPE == 2
    #define BINSEARCH binsearch2
#endif

int binsearch(int x, int v[], int n);

int main() {
    int x, n, i;
    int v[NUM_ELEMENTS];

    n = NUM_ELEMENTS;
    x = 1000;
    for (i = 0; i < NUM_ELEMENTS; i++) {
        v[i] = i;
    }
    printf("Pos %d\n", BINSEARCH(x, v, n));
}

int binsearch(int x, int v[], int n) {
    int low, mid, high;

    low = 0;
    high = n - 1;
    while (low <= high) {
        mid = (low + high) / 2;
        if (x < v[mid]) {
            high = mid - 1;
        } else if (x > v[mid]) {
            low = mid + 1;
        } else {
            return mid;
        }
    }
    return -1;
}

int binsearch2(int x, int v[], int n) {
    int low, mid, high;

    low = 0;
    high = n;
    while (low < high) {
        mid = low + ((high - low) / 2);
        if (v[mid] < x) {
            low = mid + 1;
        } else {
            high = mid;            
        }
    }
    if ((low < n) && v[low] == x) {
        return low;
    }
    return -1;
}
