#include <klib/binary_heap.h>
#include <klib/error.h>
#include <stdio.h>
#include <stdlib.h>

void binaryHeap_heapifyUp(int *heap, int size, int child) {
  if (child == 0) {
    return;
  }
  int parent_pos = (child - 1) >> 1;

  // one of children is bigger that parent, move parent down until children are
  // smaller
  if (child < size && heap[child] > heap[parent_pos]) {
    int tmp = heap[child];
    heap[child] = heap[parent_pos];
    heap[parent_pos] = tmp;

    binaryHeap_heapifyUp(heap, size, parent_pos);
  }
}

void binaryHeap_heapifyDown(int *heap, int size, int parent_pos) {
  int left = parent_pos * 2 + 1;
  int right = parent_pos * 2 + 2;
  int largest = parent_pos;

  if (left < size && heap[left] > heap[largest]) {
    largest = left;
  }
  if (right < size && heap[right] > heap[largest]) {
    largest = right;
  }

  // one of children is bigger that parent, move parent down until children are
  // smaller
  if (largest != parent_pos) {
    int tmp = heap[largest];
    heap[largest] = heap[parent_pos];
    heap[parent_pos] = tmp;

    binaryHeap_heapifyDown(heap, size, largest);
  }
}

void binaryHeap_buildHeap(int *heap, int size) {
  for (int i = size / 2 - 1; i >= 0; i--) {
    binaryHeap_heapifyDown(heap, size, i);
  }
}

int binaryHeap_readHeap(char *path, int **heap, int *size) {
  FILE *f = fopen(path, "rt");
  if (f == NULL) {
    return -1;
  }

  int filelen = 0, value;
  int er = fscanf(f, "%d", &filelen);
  if (er != 1) {
    return -2;
  }
  *size = filelen;

  (*heap) = malloc(filelen * sizeof(int));
  if ((*heap) == NULL) {
    return -3;
  }

  for (int i = 0; i < filelen; i++) {
    value = 0;
    er = fscanf(f, "%d", &value);
    if (er != 1) {
      return -4;
    }

    (*heap)[i] = value;
  }
  binaryHeap_buildHeap(*heap, *size);
  fclose(f);
  return 0;
}

int binaryHeap_push(int **heap, int *size, int value) {
  (*size)++;
  *heap = realloc(*heap, (*size) * sizeof(int));
  if (*heap == NULL) {
    return -1;
  }
  (*heap)[*size - 1] = value;

  binaryHeap_heapifyUp(*heap, *size, *size - 1);
  return 0;
}

int binaryHeap_popValue(int **heap, int *size, int value) {
  int el_pos = binaryHeap_search(*heap, *size, 0, value);
  if (el_pos == -1) {
    return -1;
  }

  (*size)--;

  int end = (*heap)[*size];
  *heap = realloc(*heap, (*size) * sizeof(int));
  if (*heap == NULL) {
    return -2;
  }
  (*heap)[el_pos] = end;

  binaryHeap_heapifyDown(*heap, *size, el_pos);
  return value;
}

int binaryHeap_changeKey(int **heap, int *size, int before, int after) {
  int el_pos = binaryHeap_search(*heap, *size, 0, before);
  if (el_pos == -1) {
    return -1;
  }
  (*heap)[el_pos] = after;

  if (before > after) {
    binaryHeap_heapifyDown(*heap, *size, el_pos);
  } else {
    binaryHeap_heapifyUp(*heap, *size, el_pos);
  }
  return after;
}

int binaryHeap_popMax(int **heap, int *size) {
  (*size)--;
  int max = (*heap)[0];
  (*heap)[0] = (*heap)[*size];

  *heap = realloc(*heap, (*size) * sizeof(int));
  if (*heap == NULL) {
    return -1;
  }

  binaryHeap_heapifyDown(*heap, *size, 0);
  return max;
}

int binaryHeap_search(int *heap, int size, int node, int value) {
  if (node < size && heap[node] == value) {
    return node;
  }

  if (heap[node] < value) {
    return -1;
  }

  // left
  int left = binaryHeap_search(heap, size, node * 2 + 1, value);
  if (left >= 0) {
    return left;
  }
  // right
  return binaryHeap_search(heap, size, node * 2 + 2, value);
}

BinaryTree *binaryHeap_buildTree(int *tree, int i, int rootsEnd, int size,
                                 BinaryTree *parent) {
  if (i < rootsEnd) {
    return NULL;
  }
  BinaryTree *current = malloc(sizeof(BinaryTree));
  current->value = tree[i];
  current->parent = parent;
  if ((i * 2 + 1) < size) {
    current->left =
        binaryHeap_buildTree(tree, i * 2 + 1, rootsEnd, size, current);
  } else {
    current->left = NULL;
  }

  if ((i * 2 + 2) < size) {
    current->right =
        binaryHeap_buildTree(tree, i * 2 + 2, rootsEnd, size, current);
  } else {
    current->right = NULL;
  }
  return current;
}
