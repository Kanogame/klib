#include "../../include/klib/binary_heap.h"
#include <stdlib.h>

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
}

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

void binaryHeap_push(int **heap, int *size, int value) {
  (*size)++;
  *heap = realloc(*heap, (*size) * sizeof(int));
  (*heap)[*size - 1] = value;

  binaryHeap_heapifyUp(*heap, *size, *size - 1);
}

int binaryHeap_pop(int **heap, int *size) {
  (*size)--;
  int end = (*heap)[*size];
  int res = (*heap)[0];
  *heap = realloc(*heap, (*size) * sizeof(int));
  (*heap)[0] = end;

  binaryHeap_heapifyDown(*heap, *size, 0);
  return res;
}