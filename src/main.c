#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <time.h>

#include "tests.h"
#include "sort.h"


void print_help(){
    printf("Usage: ./out [sort] [min] [max] [inc] [pow] <basis>\n");
    printf("    min: Min lenght of the test array\n");
    printf("    max: Max lenght of the test array\n");
    printf("    inc: Lenght incrementation of each test array\n");
    printf("    pow: Max bits of each element of the array (< 32)\n");
    printf("Sorts:\n");
    printf("    -qc: Quicksort native sort\n");
    printf("    -qu: Quicksort on u32, latest element as pivot\n");
    printf("    -qr: Quicksort on u32, random pivot\n");
    printf("    -qg: Quicksort replication of C native qsort (random pivot)\n");
    printf("    -cs: Counting sort (aka denomsort)\n");
    printf("    -rx: Radixsort (LSD)\n");
    printf("    Please add 'd' char at the end for decreasing sort. (ex: -qcd)\n");
}

// We're sure all arguments are correct
int main(int argc, char *argv[]) {
    uint32_t min;
    uint32_t max;
    uint32_t inc;
    uint32_t pow;
    void (*f)(size_t, uint32_t *);
    char *sort;
    if (argc != 6 && argc != 7) {
        print_help();
        return 1;
    }
    min = atoi(argv[2]);
    max = atoi(argv[3]);
    inc = atoi(argv[4]);
    pow = atoi(argv[5]);
    sort = argv[1] + 1;
    // Parsing sort type
    if (sort[0] == 'r') {
        test_radix(atoi(argv[6]), min, max, inc, pow);
        return 0;
    }
    else if (sort[0] == 'c')
        f = denomsort_wrapper;
    else if (sort[1] == 'c')
        f = qsort_wrapper;
    else if (sort[1] == 'u')
        f = qsortu;
    else if (sort[1] == 'r')
        f = qsorth;
    else if (sort[1] == 'g')
        f = qsortg_wrapper;
    
    // Test if dec test
    if (sort[2] == 'd')
        test_dec(f, min, max, inc);
    else
        test_sort(f, min, max, inc, pow);
    return 0;
}
