#ifndef KLIB_SORT
#define KLIB_SORT

typedef struct sort_Stats {
  int swaps;
  int comparisons;
} sort_Stats;

// bigger  >
void sort_bubble(int *arr, int size);
void sort_insertion(int *arr, int size);
void sort_selection(int *arr, int size);
void sort_binaryInsertion(int *arr, int size);
void sort_cocktail(int *arr, int size);
void sort_comb(int *arr, int size);
void sort_hoar(int *arr, int size);
void sort_shell(int *arr, int size, int *(*gen)(int, int));
int *sort_seqSed(int size, int arrayLen);
int *sort_seqShell(int size, int arrayLen);

void sort_merge(int *arr, int start, int end);
void sort_raising_merge(int *arr, int size);
sort_Stats *sort_bubbleStats(int *arr, int size);
sort_Stats *sort_cocktailStats(int *arr, int size);
sort_Stats *sort_shellStats(int *arr, int size);
sort_Stats *sort_mergeStats(int *arr, int size);

// generic implementation with comparator functions
void sort_bubbleComp(void **arr, int size, int (*bigger)(void *, void *));
void sort_insertionComp(void **arr, int size, int (*bigger)(void *, void *));
void sort_selectionComp(void **arr, int size, int (*bigger)(void *, void *));
#endif