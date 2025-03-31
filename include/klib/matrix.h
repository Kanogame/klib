#ifndef KLIB_MATH_MATRIX
#define KLIB_MATH_MATRIX

typedef struct {
  double **value;
  int width;
  int height;
} matrix;

matrix *matrix_multiply(matrix *a, matrix *b);

int matrix_alloc(matrix *mat);

#endif