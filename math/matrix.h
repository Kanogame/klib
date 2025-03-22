
typedef struct {
  double **value;
  int width;
  int height;
} matrix;

matrix *matrix_multiply(matrix *a, matrix *b);