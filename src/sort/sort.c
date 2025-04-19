#include <klib/macros.h>
#include <klib/sort.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void sort_bubble(int *arr, int size) {
  int flag, tmp;
  for (int i = 0; i < size - 1; i++) {
    flag = 0;
    for (int j = 0; j < size - i - 1; j++) {
      if (arr[j] > arr[j + 1]) {
        XOR_SWAP(arr[j], arr[j + 1]);
        flag = 1;
      }
    }
    if (!flag)
      break;
  }
}

static int min(int *arr, int start, int end) {
  int min = arr[start];
  int id;
  for (int i = start + 1; i < end; i++) {
    if (arr[i] < min) {
      min = arr[i];
      id = i;
    }
  }
  return id;
}

void sort_selection(int *arr, int size) {
  int minid;
  for (int i = 0; i < size - 1; i++) {
    minid = min(arr, i + 1, size);

    XOR_SWAP(arr[minid], arr[i]);
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
        XOR_SWAP(arr[i], arr[i + 1]);
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
        XOR_SWAP(arr[i], arr[i - 1]);
        new_start = 1;
      }
    }

    start = new_start;
  }
}

void sort_comb(int *arr, int size) {
  int flag = 0;
  int step = size - 1;

  float factor = 11.f / 8.f;

  while (step > 1 || flag) {
    if (step <= 1) {
      step = 1;
    }
    flag = 0;

    for (int i = 0; i < size - step; i++) {
      if (arr[i] > arr[i + step]) {
        flag = 1;
        XOR_SWAP(arr[i], arr[i + step]);
      }
    }
    step /= factor;
  }
}

static void gap_insertion(int *arr, int size, int gap) {
  int temp, j;
  for (int i = gap; i < size; i++) {
    temp = arr[i];
    for (j = i; (j >= gap) && (arr[j - gap] > temp); j -= gap) {
      arr[j] = arr[j - gap];
    }

    arr[j] = temp;
  }
}

void sort_shell(int *arr, int size, int *(*gen)(int, int)) {
  int max_steps = 0;
  // log2(size) of elements
  for (int i = size / 2; i > 0; i /= 2) {
    max_steps++;
  }

  int *steps = gen(max_steps, size);
  for (int step = 0; step < max_steps; step++) {
    gap_insertion(arr, size, steps[step]);
  }
}

int *sort_seqSed(int size, int arrayLen) {
  int *res = malloc(sizeof(int) * size);

  for (int i = 0; i < size; i++) {
    if (i % 1 == 0)
      res[i] = 9 * pow(2, i) - 9 * pow(2, i / 2) + 1;
    else
      res[i] = 8 * pow(2, i) - 6 * pow(2, (i + 1) / 2) + 1;
  }
  return res;
}

int *sort_seqShell(int size, int arrayLen) {
  int *res = malloc(sizeof(int) * size);

  res[0] = arrayLen / 2;

  for (int i = 1; i < size; i++) {
    res[i] = res[i - 1] / 2;
  }

  res[size - 1] = 1;
  return res;
}

static void sort_hoarRec(int *arr, int first, int last) {
  if (first >= last) {
    return;
  }

  int med = arr[first + ((last - first) / 2)];
  int i = first;
  int j = last;
  while (i <= j) {
    // search for values, >= than med
    while (arr[i] < med)
      i++;

    // search for values, <= than med
    while (arr[j] > med)
      j--;
    if (i <= j) {
      // when both are found, swap
      if (i < j) {
        XOR_SWAP(arr[i], arr[j]);
      }
      // advance counters
      i++;
      j--;
    }
  }

  // recursive calls for both parts
  if (first < j)
    sort_hoarRec(arr, first, j);
  if (i < last)
    sort_hoarRec(arr, i, last);
}

void sort_hoar(int *arr, int size) { sort_hoarRec(arr, 0, size - 1); }

void merge(int arr[], int temp[], int left, int mid, int right) {
  int i = left, j = mid, k = left;

  // Merge until one run is exhausted
  while (i < mid && j < right) {
    if (arr[i] <= arr[j])
      temp[k++] = arr[i++];
    else
      temp[k++] = arr[j++];
  }

  // Copy any remaining elements of the left run
  while (i < mid)
    temp[k++] = arr[i++];

  // Copy any remaining elements of the right run
  while (j < right)
    temp[k++] = arr[j++];

  // Copy merged elements back to arr
  for (i = left; i < right; i++)
    arr[i] = temp[i];
}

void sort_merge(int *arr, int start, int end) {
  if (end - start <= 1) {
    return;
  }

  int mid = start + (end - start) / 2;

  // recursion
  sort_merge(arr, start, mid);
  sort_merge(arr, mid, end);

  int *temp = malloc(sizeof(int) * end - start);
  merge(arr, temp, start, mid, end);
}

void sort_raising_merge(int *arr, int size) {
  int *temp = malloc(sizeof(int) * size);

  for (int step = 1; step < size; step *= 2)
    for (int left = 0; left < size; left += 2 * step) {
      int mid = left + step;
      int right = left + 2 * step;

      if (mid > size)
        mid = size;
      if (right > size)
        right = size;

      if (mid < right) {
        merge(arr, temp, left, mid, right);
      }
    }
  free(temp);
}

sort_Stats *sort_bubbleStats(int *arr, int size) {
  int comp = 0;
  int swaps = 0;

  int flag;
  for (int i = 0; i < size - 1; i++) {
    flag = 0;
    for (int j = 0; j < size - 1; j++) {
      comp++;
      if (arr[j] > arr[j + 1]) {
        XOR_SWAP(arr[j], arr[j + 1]);
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
        XOR_SWAP(arr[i], arr[i + 1]);
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
        XOR_SWAP(arr[i], arr[i - 1]);
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

sort_Stats *sort_shellStats(int *arr, int size) {
  int comp = 1;
  int swaps = 0;

  int gap = size / 2;
  while (gap >= 1 && comp++) {
    int temp, j;
    for (int i = gap; i < size && comp++; i++) {
      temp = arr[i];
      for (j = i; (j >= gap) && (arr[j - gap] > temp); j -= gap) {
        comp += 2;
        swaps++;
        arr[j] = arr[j - gap];
      }

      swaps++;
      arr[j] = temp;
    }
    gap /= 2;
  }
  sort_Stats *res = malloc(sizeof(sort_Stats));
  res->comparisons = comp;
  res->swaps = swaps;
  return res;
}

sort_Stats *sort_mergeStats(int *arr, int size) {
  int comp = 1;
  int swaps = 0;

  int *temp = malloc(sizeof(int) * size);

  for (int step = 1; step < size && comp++; step *= 2)
    for (int left = 0; left < size && comp++; left += 2 * step) {
      // getting middle and right offsets for current section
      int mid = left + step;
      int right = left + 2 * step;

      if (mid > size && comp++)
        mid = size;
      if (right > size && comp++)
        right = size;

      int i = left, j = mid, k = left;

      // merging two arrays until one of arrays is depleted
      while (i < mid && j < right) {
        comp += 3;
        if (arr[i] <= arr[j]) {
          temp[k++] = arr[i++];
        } else {
          temp[k++] = arr[j++];
        }
        swaps++;
      }

      // Copying left elemnts
      int copy = 0;
      int end = 0;
      if (i < j && comp++) {
        copy = i;
        end = mid;
      } else {
        copy = j;
        end = right;
      }
      while (copy < end) {
        temp[k++] = arr[copy++];
        swaps++;
      }

      // Copy merged elements back to arr
      for (i = left; i < right; i++) {
        arr[i] = temp[i];
        swaps++;
      }
    }
  free(temp);

  sort_Stats *res = malloc(sizeof(sort_Stats));
  res->comparisons = comp - 1;
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
