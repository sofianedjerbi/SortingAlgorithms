#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "tests.h"
#include "sort.h"

int main(int argc, char *argv[]) {
    srand(time(0));
    test_sort(qsortg_wrapper, 100000, 5000);
    test_sort(qsortu, 100000, 5000); /*Lorsque on trie un tableau de taille 2
                                       fois supérieur on prends plus de 2 fois
                                       plus de temps a le trier mais moins de 
                                       plus de temps a le trier mais moins de 
                                       4 fois plus de temps ce qui veut dire 
                                       que notre algorithme a une complexite 
                                       comprise entre O(n) et O(n²) (de grandes
                                       chances que ce soit donc en O(nlog(n))
                                       */
    test_sort(qsorth, 100000, 5000);
    test_dec(qsortu, 100000, 5000);  // Worst case donc O(n²)
    test_dec(qsorth, 100000, 5000);  // Worst case fixed O(n²)
}
