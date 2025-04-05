#include "../../include/klib/sort.h"
#include <stdio.h>
#include <stdlib.h>

void sort_bubble(int *arr, int size) {
  int flag, tmp;
  for (int i = 0; i < size - 1; i++) {
    flag = 0;
    for (int j = 0; j < size - i - 1; j++) {
      if (arr[j] > arr[j + 1]) {
        tmp = arr[j];
        arr[j] = arr[j + 1];
        arr[j + 1] = tmp;
        flag = 1;
      }
    }
    if (!flag)
      break;
  }
}

static int min(int *arr, int size) {
  int min = arr[0];
  int id;
  for (int i = 1; i < size; i++) {
    if (arr[i] < min) {
      min = arr[i];
      id = i;
    }
  }
  return id;
}

void sort_selection(int *arr, int size) {
  int minid, tmp;
  for (int i = 0; i < size; i++) {
    minid = min(arr + (sizeof(int) * i), size - i) + i;
    if (minid == i) {
      continue;
    }

    tmp = arr[minid];
    arr[minid] = arr[i];
    arr[i] = tmp;
  }
}

void sort_insertion(int *arr, int size) {
  int k, j;
  for (int i = 1; i < size; i++) {
    k = arr[i];
    j = i;
    while (j > 0 && arr[j - 1] > k) {
      arr[j] = arr[j - 1];
      j--;
    }
    arr[j] = k;
  }
}

void sort_binaryInsertion(int *arr, int size) {
  int k, m, start, sorted;
  for (int i = 1; i < size; i++) {
    k = arr[i];
    start = 0;
    sorted = i;

    // bin search
    while (start < sorted) {
      m = (start + sorted) / 2;
      if (arr[m] > k) {
        sorted = m;
      } else {
        start = m + 1;
      }
    }

    // moving elements back (w/ reversed for) & swapping the value
    for (int j = i - 1; j >= start; j--) {
      arr[j + 1] = arr[j];
    }
    arr[start] = k;
  }
}

void sort_cocktail(int *arr, int size) {
  int new_start, new_end;

  int tmp = 0;

  int start = 0;
  int end = size - 1;
  while (start < end) {
    new_end = start;
    for (int i = start; i < end; i++) {
      if (arr[i] > arr[i + 1]) {
        tmp = arr[i];
        arr[i] = arr[i + 1];
        arr[i + 1] = tmp;
        new_end = i;
      }
    }

    end = new_end;

    if (start >= end) {
      break;
    }

    new_start = end;

    for (int i = end; i >= start; i--) {
      if (arr[i] < arr[i - 1]) {
        tmp = arr[i];
        arr[i] = arr[i - 1];
        arr[i - 1] = tmp;
        new_start = 1;
      }
    }

    start = new_start;
  }
}

sort_Stats *sort_bubbleStats(int *arr, int size) {
  int comp = 0;
  int swaps = 0;

  int flag, tmp;
  for (int i = 0; i < size - 1; i++) {
    flag = 0;
    for (int j = 0; j < size - 1; j++) {
      comp++;
      if (arr[j] > arr[j + 1]) {
        tmp = arr[j];
        arr[j] = arr[j + 1];
        arr[j + 1] = tmp;
        flag = 1;
        swaps++;
      }
    }
  }

  sort_Stats *res = malloc(sizeof(sort_Stats));
  res->comparisons = comp;
  res->swaps = swaps;
  return res;
}

sort_Stats *sort_cocktailStats(int *arr, int size) {
  int comp = 0;
  int swaps = 0;
  int new_start, new_end;

  int tmp = 0;

  int start = 0;
  int end = size - 1;
  while (start < end) {
    new_end = start;
    for (int i = start; i < end; i++) {
      comp++;
      if (arr[i] > arr[i + 1]) {
        tmp = arr[i];
        arr[i] = arr[i + 1];
        arr[i + 1] = tmp;
        new_end = i;
        swaps++;
      }
    }

    end = new_end;

    if (start >= end) {
      break;
    }

    new_start = end;

    for (int i = end; i >= start; i--) {
      comp++;
      if (arr[i] < arr[i - 1]) {
        tmp = arr[i];
        arr[i] = arr[i - 1];
        arr[i - 1] = tmp;
        new_start = 1;
        swaps++;
      }
    }

    start = new_start;
  }

  sort_Stats *res = malloc(sizeof(sort_Stats));
  res->comparisons = comp;
  res->swaps = swaps;
  return res;
}

void sort_bubbleComp(void **arr, int size, int (*bigger)(void *, void *)) {
  int flag;
  void *tmp;
  for (int i = 0; i < size - 1; i++) {
    flag = 0;
    for (int j = 0; j < size - i - 1; j++) {
      if (bigger(arr[j], arr[j + 1])) {
        flag = 1;
        tmp = arr[j];
        arr[j] = arr[j + 1];
        arr[j + 1] = tmp;
      }
    }
    if (!flag) {
      break;
    }
  }
}

static int minComp(void **arr, int size, int (*bigger)(void *, void *)) {
  void *min = arr[0];
  int id;
  for (int i = 1; i < size; i++) {
    if (!bigger(arr[i], min)) {
      min = arr[i];
      id = i;
    }
  }
  return id;
}

void sort_selectionComp(void **arr, int size, int (*bigger)(void *, void *)) {
  int minid;
  void *tmp;
  for (int i = 0; i < size; i++) {
    minid = minComp(arr + (sizeof(void *) * i), size - i, bigger) + i;
    if (minid == i) {
      continue;
    }

    tmp = arr[minid];
    arr[minid] = arr[i];
    arr[i] = tmp;
  }
}

void sort_insertionComp(void **arr, int size, int (*bigger)(void *, void *)) {
  void *k;
  int j;
  for (int i = 1; i < size; i++) {
    k = arr[i];
    j = i;
    while (j > 0 && bigger(arr[j - 1], k)) {
      arr[j] = arr[j - 1];
      j--;
    }
    arr[j] = k;
  }
}
