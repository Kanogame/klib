#ifndef KLIB_HEAP_BINARY
#define KLIB_HEAP_BINARY

typedef struct BinaryTree {
  int value;
  struct BinaryTree *left;
  struct BinaryTree *right;

  struct BinaryTree *parent;
} BinaryTree;

// In binary heap, tree is implemented as an array,
// where for each parent: array[i] has 2 children:
// array[2*i + 1]; array[2*i + 2].
// Arrays are simply easier to handle and smaller in size

// this function is used to convert regular array-heaps to
// proper structurized trees
BinaryTree *binaryHeap_buildTree(int *tree, int i, int rootsEnd, int size,
                                 BinaryTree *parent);

int binaryHeap_readHeap(char *path, int **heap, int *size);
int binaryHeap_push(int **heap, int *size, int value);
int binaryHeap_popValue(int **heap, int *size, int value);
int binaryHeap_changeKey(int **heap, int *size, int before, int after);
int binaryHeap_popMax(int **heap, int *size);
int binaryHeap_search(int *heap, int size, int node, int target);
#endif
