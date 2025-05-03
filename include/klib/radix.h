#ifndef KLIB_MATH_RADIX
#define KLIB_MATH_RADIX
#include <klib/sort.h>

void radix_msd_binary(int *array, int size, int digit);
sort_Stats *radix_msd_binary_stats(int *array, int size, int digit);
void radix_msd_stings(char **a, int start, int end, int digit, int maxDigit);

#endif