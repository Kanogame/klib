#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>

// utils
static int matrix_alloc(matrix *mat) {
  mat->value = (double **)malloc(mat->height * sizeof(double *));
  if (mat->value == NULL) {
    return -1;
  }
  for (int i = 0; i < mat->width; i++) {
    mat->value[i] = (double *)malloc(mat->width * sizeof(double));
    if (mat->value[i] == NULL) {
      return -1;
    }
  }
  return 0;
}

// actual
matrix *matrix_multiply(matrix *a, matrix *b) {
  if (a->width != b->height) {
    return 0;
  }

  matrix *ret = (matrix *)malloc(sizeof(matrix));

  ret->height = a->height;
  ret->width = b->width;

  int er = matrix_alloc(ret);
  if (er != 0) {
    fprintf(stderr, "error while allocaing new matrix");
    return NULL;
  }

  int tmp = 0;
  for (int i = 0; i < ret->width; i++) {
    for (int j = 0; j < ret->height; j++) {
      tmp = 0;
      for (int k = 0; k < ret->width; k++) {
        tmp += a->value[i][k] * b->value[k][j];
      }
      ret->value[i][j] = tmp;
    }
  }

  return ret;
}
