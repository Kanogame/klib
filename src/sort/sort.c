#include <stdio.h>

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
  int flag = 1;
  int tmp = 0;
  while (flag) {
    flag = 0;
    for (int i = 0; i < size - 1; i++) {
      if (arr[i] > arr[i + 1]) {
        tmp = arr[i];
        arr[i] = arr[i + 1];
        arr[i + 1] = tmp;
        flag = 1;
      }
    }
    if (!flag) {
      break;
    }

    flag = 0;
    for (int i = size - 1; i >= 0; i--) {
      if (arr[i] < arr[i - 1]) {
        tmp = arr[i];
        arr[i] = arr[i - 1];
        arr[i - 1] = tmp;
        flag = 1;
      }
    }
  }
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
