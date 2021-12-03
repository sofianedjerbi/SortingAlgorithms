#pragma once
#include <stdint.h>
#include <stdlib.h>

void qsortu(size_t, uint32_t *);
void qsorth(size_t, uint32_t *);
void qsortg(uint32_t *, size_t, size_t, int (*)(const void*, const void*));
void denomsort(size_t, uint32_t *, uint32_t);
void bit_denomsort(size_t, uint32_t *, size_t, size_t, size_t);
void radixsort(size_t, uint32_t *, size_t, size_t);

