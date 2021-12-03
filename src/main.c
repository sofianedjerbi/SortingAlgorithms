#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <time.h>

#include "tests.h"
#include "sort.h"


void print_help(){
    printf("Usage: ./out [sort] [min] [max] [inc] [pow]\n");
    printf("    min: Min lenght of the test array\n");
    printf("    max: Max lenght of the test array\n");
    printf("    inc: Lenght incrementation of each test array\n");
    printf("    pow: Max bits of each element of the array (< 32)\n");
    printf("Sorts:\n");
    printf("    -qc: Quicksort native sort\n");
    printf("    -qu: Quicksort on u32, latest element as pivot\n");
    printf("    -qg: Quicksort on u32, random pivot\n");
    printf("    -qg: Quicksort replication of C native qsort (random pivot)\n");
    printf("    -cs: Counting sort (aka denomsort)\n");
    printf("    -rx: Radixsort (LSD)\n");
}


int main(int argc, char *argv[]) {
    uint32_t min;
    uint32_t max;
    uint32_t inc;
    if (argc != 6) 
        print_help();
}
