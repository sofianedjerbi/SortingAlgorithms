#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <time.h>

#include "sort.h"
#include "tests.h"


/* print an array t of size n */
void print_array(size_t n, uint32_t *t) {
    for (size_t i=0; i<n; i++)
        printf("%d ", t[i]);
    printf("\n");
}

/* Generates a random number in [min;max[ */
int rand_number(uint32_t min, uint32_t max) {
    return rand() % (max - min) + min;
}

/* Return true if the array t is sorted else false
 * - len: Size of the array
 * - t: array pointer */
bool sorted(size_t len, const uint32_t *t) {
    for (size_t i=1; i<len; i++)
        if (t[i-1] > t[i])
            return false;
    return true;
}

/* Sort a random array and increment the size at each iteration
 * Synopsis: Benchmarking 
 * Params: 
 *  - csort: sorting func (pointer)
 *  - min: minimum length of the array 
 *  - max: maximum length of the array 
 *  - inc: incrementation at each iteration
 *  - pow: for integers in interval [0;2^pow[ */
void test_sort(void (*csort)(size_t, uint32_t *), 
               size_t min, size_t max, size_t inc, size_t pow) {           
    clock_t start, end;
    double time;
    for (size_t d=min; d <= max; d+=inc){
        uint32_t *t = malloc(sizeof(uint32_t)*d);  // Test array 
        for (size_t i=0; i < d; i++) // Init the array
            t[i] = rand_number(0, 1 << pow);
        start = clock();
        (*csort)(d, t); // We sort here
        end = clock();
        if (!sorted(d, t)) {
            printf("Error on list of size %zu: ", d);
            print_array(d, t);
        }
        free(t);
        time = ((double)(end-start))/CLOCKS_PER_SEC;
        printf("Time for size %zu: %lf\n", d, time);
    }
}


/* Sort an array in decreasing order and increment the size at each iteration
 * Synopsis: Benchmarking 
 * Params: 
 *  - csort: sorting func (pointer)
 *  - min: minimum length of the array 
 *  - max: maximum length of the array
 *  - inc: incrementation at each iteration */
void test_dec(void (*csort)(size_t, uint32_t *), 
               size_t min, size_t max, size_t inc) {           
    clock_t start, end;
    double time;
    for (size_t d=min; d <= max; d+=inc){
        uint32_t *t = malloc(sizeof(uint32_t)*d);  // Test array 
        for (size_t i=0; i < d; i++) // Init the array
            t[i] = d-i;
        start = clock();
        (*csort)(d, t); // We sort here
        end = clock();
        if (!sorted(d, t)) {
            printf("Error on list of size %zu: ", d);
            print_array(d, t);
        }
        free(t);
        time = ((double)(end-start))/CLOCKS_PER_SEC;
        printf("Time for size %zu: %lf\n", d, time);
    }
}

/* Radixsort (basis b) a random array and increment the size at each iteration
 * Synopsis: Benchmarking 
 * Params: 
 *  - b: basis of the radix sort
 *  - min: minimum length of the array 
 *  - max: maximum length of the array 
 *  - inc: incrementation at each iteration
 *  - pow: for integers in interval [0;2^pow[ */
void test_radix(size_t b, size_t min, size_t max, size_t inc, size_t pow) {
    clock_t start, end;
    double time;
    for (size_t d=min; d <= max; d+=inc){
        uint32_t *t = malloc(sizeof(uint32_t)*d); // Test array
        for (size_t i=0; i < d; i++) // Init the array
            t[i] = rand_number(0, (1 << pow)-1); 
        start = clock();
        radixsort(d, t, b, pow);
        end = clock();
        if (!sorted(d, t)) {
            printf("Error on list of size %zu: ", d);
            print_array(d, t);
        }
        free(t);
        time = ((double)(end-start))/CLOCKS_PER_SEC;
        printf("Time for size %zu: %lf\n", d, time);
    }
}

/* > 0 if a > b, 0 if a == b, < 0 if a < b */
int compare_u32(const void *a, const void *b){
    const uint32_t *ua = (uint32_t *)a;
    const uint32_t *ub = (uint32_t *)b;
    if (*ua > *ub)
        return 1;
    else if (*ua < *ub)
        return -1;
    else
        return 0;
}

/* Call qsortg on a uint32_t array */
void qsortg_wrapper(size_t len, uint32_t *t) {
    qsortg(t, len, sizeof(uint32_t), compare_u32);
}

/* Call qsort on a uint32_t array */
void qsort_wrapper(size_t len, uint32_t *t) {
    qsort(t, len, sizeof(uint32_t), compare_u32);
}

/* Get the maximum of an array */
uint32_t max(uint32_t *t, size_t len) {
    uint32_t max = 0;
    for (size_t i=0; i < len; i++)
        max = t[i] > max ? t[i] : max;
    return max;
}

/* Call denomsort with the maximum of the array */
void denomsort_wrapper(size_t len, uint32_t *t) {
    denomsort(len, t, max(t, len));
}

