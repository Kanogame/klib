#include <klib/macros.h>
#include <stdio.h>
#include <stdlib.h>

static int bin(int value, int digit) { return ((value >> digit) & 1); }

// fast binary sort
void msd_binary_sort(int *array, int size, int digit) {
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

  msd_binary_sort(array, i, digit - 1);
  msd_binary_sort(array + i, size - i, digit - 1);
}

static const int RADIX = 255; // ASCII

void msd_sort(char **arr, int start, int end, int digit, int maxDigits) {
  if (end - start <= 1 || digit >= maxDigits)
    return;

  int *count = calloc(RADIX + 1, sizeof(int));
  int i;

  int pos = maxDigits - 1 - digit;
  for (i = start; i < end; i++) {
    char val = arr[i][pos];
    count[val + 1]++;
  }

  // pref sum
  for (i = 0; i < RADIX; i++) {
    count[i + 1] += count[i];
  }

  // Allocate temporary array for sorted order of current digit pass
  int size = end - start;
  char **aux = malloc(size * sizeof(char *));

  // Distribute: place elements in appropriate positions
  for (i = start; i < end; i++) {
    char val = arr[i][pos];
    aux[count[val]++] = arr[i];
  }

  // Copy back to original array
  for (i = 0; i < size; i++) {
    arr[start + i] = aux[i];
  }
  free(aux);

  int boundaries[RADIX + 1];
  boundaries[0] = start;
  for (i = 0; i < RADIX; i++) {
    int bucketCount = 0;
    for (int j = start; j < end; j++) {
      char val = arr[j][pos];
      if (val == i)
        bucketCount++;
    }
    boundaries[i + 1] = boundaries[i] + bucketCount;
  }

  // Recursively sort each bucket on the next digit.
  for (i = 0; i < RADIX; i++) {
    msd_sort(arr, boundaries[i], boundaries[i + 1], digit + 1, maxDigits);
  }
}
