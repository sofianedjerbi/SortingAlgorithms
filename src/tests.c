#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <time.h>

#include "sort.h"
#include "tests.h"


void print_array(size_t n, uint32_t *t) {
    for (size_t i=0; i<n; i++)
        printf("%d ", t[i]);
    printf("\n");
}

/* Generates a random number between min and max */
int rand_number(uint32_t min, uint32_t max) {
    return rand() % (max + 1 - min) + min;
}

/* Tells if a list is sorted
 * - len: Size of the list
 * - t: List */
bool sorted(size_t len, const uint32_t *t) {
    for (size_t i=1; i<len; i++)
        if (t[i-1] > t[i])
            return false;
    return true;
}

/* Sort a random list and increment the size at each iteration
 * Synopsis: Benchmarking 
 * Params: 
 *  - csort: sorting func (pointer)
 *  - max_length: maximum length of the list 
 *  - inc: incrementation at each iteration */
void test_sort(void (*csort)(size_t, uint32_t *), 
                   size_t max_length, size_t inc) {
    clock_t start, end;
    double time;
    for (size_t d=inc; d <= max_length; d+=inc){
        uint32_t *t = malloc(sizeof(uint32_t)*d);  // Random list
        for (size_t i=0; i < d; i++) // Init the array
            t[i] = rand_number(0, d*2);
        start = clock();
        (*csort)(d, t); // We multiply here
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


/* Sort a list in decreasing order and increment the size at each iteration
 * Synopsis: Benchmarking 
 * Params: 
 *  - csort: sorting func (pointer)
 *  - max_length: maximum length of the list 
 *  - inc: incrementation at each iteration */
void test_dec(void (*csort)(size_t, uint32_t *), 
                   size_t max_length, size_t inc) {
    clock_t start, end;
    double time;
    for (size_t d=inc; d <= max_length; d+=inc){
        uint32_t *t = malloc(sizeof(uint32_t)*d);  // Random list
        for (size_t i=0; i < d; i++) // Init the array
            t[i] = d-i;
        start = clock();
        (*csort)(d, t); // We multiply here
        end = clock();
        if (!sorted(d, t)) {
            printf("Error on list of size %zu: ", d);
            print_array(d, t);
        }
        free(t);
        time = ((double)(end-start))/CLOCKS_PER_SEC;
        printf("Time for size %zu (dec): %lf\n", d, time);
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


