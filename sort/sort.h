#ifndef KLIB_SORT
#define KLIB_SORT

// bigger  > 
void sort_bubble(int *arr, int size);

void sort_insertion(int *arr, int size);

void sort_selection(int *arr, int size);

int sort_bubbleComp(void **arr, int size, int (*bigger)(void*, void*));
void sort_insertionComp(void **arr, int size, int (*bigger)(void*, void*));
void sort_selectionComp(void **arr, int size, int (*bigger)(void*, void*));
#endif