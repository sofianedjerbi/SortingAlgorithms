#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <time.h>

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
 *  - sort: sorting func (pointer)
 *  - max_length: maximum length of the list 
 *  - inc: incrementation at each iteration */
void test_sort(void (*sort)(size_t, uint32_t *), 
                   size_t max_length, size_t inc) {
    clock_t start, end;
    double time;
    for (size_t d=0; d <= max_length; d+=inc){
        uint32_t t[d];  // Random list
        for (size_t i=0; i <= d; i++) // Init p
            t[i] = rand_number(0, d*2);
        start = clock();
        (*sort)(d, t); // We multiply here
        end = clock();
        time = ((double)(end-start))/CLOCKS_PER_SEC;
        printf("Time for size %zu: %lf\n", d, time);
    }
}

/* Compute the square of the polynomial nX^n + ... + 0
 * From degree 1 to degree 1000 and compare with mulpu. 
 * Synopsis: Check if the sorting algorithm is correct */ 
void compare_sort(void (*sort)(size_t, uint32_t *)) {
    printf("Beginning test\n");
    for (size_t d=0; d <= 2; d++) {
        uint32_t t[d];  // random list
        uint32_t c[d];  // copy of random list
        for (size_t i=0; i <= d; i++) { // Initialize p
            t[i] = rand_number(0, 2*d);
            c[i] = t[i];
        }
        (*sort)(d, t); // We multiply here
        print_array(d, t);
        print_array(d, c);
        if (!sorted(d, t)){
            printf("ERROR\n");
            printf("list:  ");
            print_array(d, c);
            printf("sorted list:     "); // Error
            print_array(d, t);
        }
    }
    printf("End test\n");
}

