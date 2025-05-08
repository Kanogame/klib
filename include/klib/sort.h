#ifndef KLIB_SORT
#define KLIB_SORT

typedef struct sort_Stats {
  int swaps;
  int comparisons;
} sort_Stats;

// simplest
void sort_bubble(int *arr, int size);
void sort_insertion(int *arr, int size);
void sort_selection(int *arr, int size);

// improved
void sort_binaryInsertion(int *arr, int size);
void sort_cocktail(int *arr, int size);
void sort_comb(int *arr, int size);

// fast
void sort_hoar(int *arr, int size);
void sort_shell(int *arr, int size, int *(*gen)(int, int));
int *sort_seqSed(int size, int arrayLen);
int *sort_seqShell(int size, int arrayLen);

// merge

void sort_merge(int *arr, int start, int end);
void sort_mergeRaising(int *arr, int size);

// stats
sort_Stats *sort_bubbleStats(int *arr, int size);
sort_Stats *sort_cocktailStats(int *arr, int size);
sort_Stats *sort_shellStats(int *arr, int size);
sort_Stats *sort_mergeStats(int *arr, int size);
sort_Stats *radix_MSDBinaryStats(int *array, int size, int digit);

// radix
void radix_MSDBinary(int *array, int size, int digit);

// radix strings
void radix_MSDString(char **a, int start, int end, int digit, int maxDigit);

void radix_LSDString(char **a, int size, int digit);

// generic implementation with comparator functions

// bigger  >
void sort_bubbleComp(void **arr, int size, int (*bigger)(void *, void *));
void sort_insertionComp(void **arr, int size, int (*bigger)(void *, void *));
void sort_selectionComp(void **arr, int size, int (*bigger)(void *, void *));
#endif
