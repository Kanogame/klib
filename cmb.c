#include <stdlib.h>

// cmb_Combination создает подмножества множества, порядок не важен, есть
// повторения - от нуля до srclen подмножества возможно использовать как массивы
// индексов, что и происходит
void cmb_CombinationRepeat(int srclen, int len, int *source) {
  int *comb = (int *)malloc(len * sizeof(int));
  for (int i = 0; i < len; i++) {
    comb[i] = i;
  }

  int j = 1;
  while (j >= 0) {
    j = len - 1;
    // printArr(comb, len, source);
    while (j >= 0 && comb[j] == srclen - len + j) {
      j--;
    }

    if (j < 0) {
      break;
    }

    comb[j]++;
    for (int i = j + 1; i < len; i++) {
      comb[i] = comb[j - 1] + j - 1;
    }
  }

  free(comb);
}

// cmb_Combination создает подмножества множества, порядок не важен, нет
// повторений - от нуля до srclen подмножества возможно использовать как массивы
// индексов
void cmb_Combination(int srclen, int len, int *source) {
  int *comb = (int *)malloc(len * sizeof(int));
  for (int i = 0; i < len; i++) {
    comb[i] = i;
  }

  int j = 1;
  while (j >= 0) {
    j = len - 1;
    // printArr(comb, len, source);
    while (j >= 0 && comb[j] == srclen - len + j) {
      j--;
    }

    if (j < 0) {
      break;
    }

    comb[j]++;
    for (int i = j + 1; i < len; i++) {
      comb[i] = comb[i - 1] + 1;
    }
  }

  free(comb);
}