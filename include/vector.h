#ifndef KLIB_MATH_VEC
#define KLIB_MATH_VEC

typedef struct {
  double x;
  double y;
  double z;
} vector3;

#ifdef KLIB_MATH_MATRIX
vector3 *vector_multiplyBy4x4(vector3 *vec, matrix *matrix);
#endif
#endif