#pragma once
#include <stdbool.h>

void print_array(size_t, uint32_t *);
bool sorted(size_t, const uint32_t *);
void test_sort(void (*)(size_t, uint32_t *), size_t, size_t);
void test_dec(void (*)(size_t, uint32_t *), size_t, size_t);
void qsortg_wrapper(size_t, uint32_t *);

