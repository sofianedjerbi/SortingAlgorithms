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

/* Sort an array t via quicksort and random heuristics
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

/* Sort an array of 32 bit integer via counting sort. */
void denomsort(size_t len, uint32_t *t, uint32_t max) {
    // Creating the counting tab and init it to 0
    uint32_t *count = calloc(max+1, sizeof(uint32_t)); 
    // Output array
    uint32_t *output = malloc(sizeof(uint32_t) * len); 
    // Counting values
    for (size_t i=0; i < len; i++)
        count[t[i]]++;
    for (size_t i=1; i <= max; i++)
        count[i] += count[i-1];
    // Sorting the array
    for (size_t i=len; i >= 1; --i) {
        count[t[i-1]]--;
        output[count[t[i-1]]] = t[i-1];
    }
    // Swapping values
    for (size_t i=0; i < len; i++)
        swap(t + i, output + i);
    free(count);
    free(output);
}

/* Sort an array of 32 bit integer via counting sort BUT
 * only considering b bits in position n, n+1, ..., n+b 
 * (Starting from the left). */
void bit_denomsort(size_t len, uint32_t *t, size_t b, size_t n) {
    // Mask for extracting bytes
    uint32_t mask = (1 << b) - 1; // b times "1"
    // Constant shift applied to all numbers
    uint32_t shift = n*b;
    // Creating the counting tab and init it to 0
    uint32_t *count = calloc(mask + 1, sizeof(uint32_t)); 
    // Output array
    uint32_t *output = malloc(sizeof(uint32_t) * len); 
    // Counting values
    for (size_t i=0; i < len; i++) {
        uint32_t j = (t[i] << shift) & mask; 
        count[j]++;
    }
    for (size_t i=1; i <= mask; i++)
        count[i] += count[i-1];
   // Sorting the array 
    for (size_t i=len; i >= 1; --i) {
        uint32_t j = (t[i-1] << shift) & mask;
        count[j]--;
        output[count[j]] = t[i-1];
    }
    // Swapping values
    for (size_t i=0; i < len; i++)
        swap(t + i, output + i);
    free(count);
    free(output);
}

/* Implementing radixsort on basis b, with t[i] < 2^max for all i */
void radixsort(size_t len, uint32_t *t, size_t b, size_t max) {
    // Number of bytes (integer division so add 1 if a remainder exists)
    size_t nlen = max/b;
    nlen += max % b == 0 ? 0 : 1; // Check if remainder exists
    for (size_t i=0; i < nlen; i++)
        bit_denomsort(len, t, b, i);
}

