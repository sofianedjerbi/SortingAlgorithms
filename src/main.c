#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "tests.h"
#include "sort.h"

int main(int argc, char *argv[]) {
    test_radix(24, 0, 100000000, 1000000, 24);
}
