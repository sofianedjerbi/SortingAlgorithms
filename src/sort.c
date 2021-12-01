#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <time.h>


// Swap two values
void swap(uint32_t *a, uint32_t *b) {
    uint32_t c = *b;
    *b = *a;
    *a = c;
}


// cpyswap: Swap any values
void cpyswap(void *a, void *b, size_t size) {
    void *temp = malloc(size); // Variable temporaire pour échanger les valeurs
    memcpy(temp, a, size);
    memcpy(a, b, size);
    memcpy(b, temp, size);
    free(temp);
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
    for (size_t i=len; i >= 1; --i) {
        if (t[i-1]>x){
            t[n] = t[i-1];
            t[i-1] = t[n-1];
            n--;
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
    size_t r = rand() % len;
    uint32_t x = t[r];
    size_t n = len-1;
    swap(t + r, t + n);
    for (size_t i=len; i >= 1; --i) {
        if (t[i-1]>x){
            t[n] = t[i-1];
            t[i-1] = t[n-1];
            n--;
        }
    }
    t[n] = x;
    qsorth(n, t);
    qsorth(len-n-1, t + n + 1);
}

/* Quicksort implemented like the native qsort in c 
 * Cf. original qsort definition */
void qsortg(void *t, size_t len, size_t size,
           int (*compare)(const void*, const void*)) {
    if (len <= 1)
        return;
    size_t r = rand() % len;
    size_t n = len-1;
    cpyswap(t + r*size, t + n*size, size);
    void *x = t + n*size;
    for (size_t i=len; i >= 1; --i) {
        void *elem = t + (i-1) * size;
        if (compare(elem, x) > 0){ // compare(a,b) > 0 if a > b
            memcpy(t + n * size, elem, size);
            memcpy(elem, t + (n-1) * size, size);
            n--;
        }
    }
    memcpy(t + n*size, x, size);
    qsortg(t, n, size, compare);
    qsortg(t + (n + 1)*size, len-n-1, size, compare);
}

