#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <time.h>

#include "sort.h"


/* Trie un tableau t via quicksort
 * len est la taille du tableau T */
void qsortu(size_t len, uint32_t *t) {
    uint32_t x = t[len-1];
    size_t n = len-1;
    for (size_t i=len; i>0; i--){
        printf("%d", i);
        if (t[i-1]>x){
            t[n] = t[i-1];
            t[i-1] = t[n-1];
            n = n-1;
        }
    }
    t[n] = x;
    //qsortu(n, t);
    //qsortu(len-n-1, t + n + 1);
}

