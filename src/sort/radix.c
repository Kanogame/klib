#include <klib/error.h>
#include <klib/macros.h>
#include <klib/sort.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

inline static int bin(int value, int digit) { return ((value >> digit) & 1); }

// fast binary sort
void radix_msd_binary(int *array, int size, int digit) {
  if (digit < 0 || size == 0) {
    return;
  }

  int i = 0;
  int j = size - 1;
  while (i <= j) {
    if (!bin(array[i], digit)) {
      i++;
    } else if (bin(array[j], digit)) {
      j--;
    } else {
      XOR_SWAP(array[i], array[j]);
      i++;
      j--;
    }
  }

  radix_msd_binary(array, i, digit - 1);
  radix_msd_binary(array + i, size - i, digit - 1);
}

sort_Stats *radix_msd_binary_stats(int *array, int size, int digit) {
  if (digit < 0 || size == 0) {
    return malloc(sizeof(sort_Stats));
  }

  int i = 0;
  int j = size - 1;
  int cmp = 0;
  int swaps = 0;
  while (i <= j) {
    cmp++;
    if (!bin(array[i], digit)) {
      i++;
    } else if (bin(array[j], digit)) {
      j--;
    } else {
      XOR_SWAP(array[i], array[j]);
      swaps++;
      i++;
      j--;
    }
    cmp++;
  }

  sort_Stats *val1 = radix_msd_binary_stats(array, i, digit - 1);
  sort_Stats *val2 = radix_msd_binary_stats(array + i, size - i, digit - 1);
  val1->comparisons += val2->comparisons + cmp;
  val1->swaps += val2->swaps + swaps;
  return val1;
}

#define R 256 // ASCII

#define CUTOFF 15

void radix_msd_stings(char **a, int start, int end, int digit, int maxDigit) {
  if (end <= start || digit >= maxDigit)
    return;

  int *count = calloc(R + 1, sizeof(int));
  if (count == NULL) {
    EXIT_WITH_ERROR("err");
  }

  for (int i = start; i <= end; i++) {
    int c = a[i][digit];
    count[c + 1]++;
  }

  int *bound = NULL;
  int bsize = 0;

  for (int r = 0; r < R; r++) {
    count[r + 1] += count[r];
    if (count[r + 1] - count[r] > 1) {
      bsize += 2;
      bound = realloc(bound, bsize * sizeof(int));
      bound[bsize - 2] = start + count[r];
      bound[bsize - 1] = start + count[r + 1];
    }
  }

  int size = end - start + 1;
  char **aux = calloc(size, sizeof(char *));
  if (aux == NULL) {
    EXIT_WITH_ERROR("err");
  }

  for (int i = start; i <= end; i++) {
    int c = a[i][digit];
    aux[count[c]++] = a[i];
  }
  for (int i = 0; i < size; i++) {
    a[start + i] = aux[i];
  }

  free(aux);
  free(count);

  for (int r = 0; r < bsize / 2; r++) {
    radix_msd_stings(a, bound[r * 2], bound[r * 2 + 1] - 1, digit + 1,
                     maxDigit);
  }
  free(bound);
}

void radix_lsd_strings(char **a, int size, int digit) {
  int *count = calloc(R, sizeof(int));
  if (count == NULL) {
    EXIT_WITH_ERROR("err");
  }

  char **aux = calloc(size, sizeof(char *));
  if (aux == NULL) {
    EXIT_WITH_ERROR("err");
  }

  while (digit >= 0) {
    for (int i = 0; i < size; ++i) {
      int c = a[i][digit];
      count[c + 1]++;
    }

    for (int r = 0; r < R; r++) {
      count[r + 1] += count[r];
    }

    for (int i = 0; i < size; i++) {
      int c = a[i][digit];
      aux[count[c]++] = a[i];
    }

    for (int i = 0; i < size; i++) {
      a[i] = aux[i];
    }

    for (int i = 0; i < R; i++) {
      count[i] = 0;
    }
    digit--;
  }
}
