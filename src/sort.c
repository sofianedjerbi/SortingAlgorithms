#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <time.h>


// Swap two values
void swap(uint32_t *a, uint32_t *b){
    uint32_t c = *b;
    *b = *a;
    *a = c;
}


/* c native qsort */
//void qsortc(size_t len, uint32_t *t);

/* Sort an array t via quicksort
 * len: len(T)
 * We use aliasing and len instead of f and d. */
void qsortu(size_t len, uint32_t *t) {
    if (len <= 1)
        return;
    uint32_t x = t[len-1];
    size_t n = len-1;
    for (size_t i=len-1; i < len; --i){
        if (t[i-1]>x){
            t[n] = t[i-1];
            t[i-1] = t[n-1];
            n = n-1;
        }
    }
    t[n] = x;
    qsortu(n, t);
    qsortu(len-n-1, t + n + 1);
}

/* Sort an array t via quicksort and HEURISTICS
 * len: len(T)
 * We use aliasing and len instead of f and d. */
void qsorth(size_t len, uint32_t *t) {
    if (len <= 1)
        return;
    size_t n = rand() % len;
    uint32_t x = t[n];
    swap(t + n, t + len - 1);
    for (size_t i=len-1; i < len; --i){
        if (t[i-1]>x){
            t[n] = t[i-1];
            t[i-1] = t[n-1];
            n = n-1;
        }
    }
    t[n] = x;
    qsortu(n, t);
    qsortu(len-n-1, t + n + 1);
}

void qsortg(void *t, size_t elementCount, size_t elementSize,
           int (*compareFunction)(const void*, const void*)) {
    if (len <= 1)
        return;
    qsortu(t, n, len);
    qsortu(len-n-1, t + n + 1);                                                                           
}
