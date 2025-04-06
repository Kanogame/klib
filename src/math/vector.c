#include <klib/matrix.h>
#include <klib/vector.h>
#include <stdlib.h>

vector3 *vector_multiplyBy4x4(vector3 *vec, matrix *matrix) {
  vector3 *res = malloc(sizeof(vector3));
  res->x = vec->x * matrix->value[0][0] + vec->y * matrix->value[1][0] +
           vec->z * matrix->value[2][0] + matrix->value[3][0];

  res->y = vec->x * matrix->value[0][1] + vec->y * matrix->value[1][1] +
           vec->z * matrix->value[2][1] + matrix->value[3][1];

  res->z = vec->x * matrix->value[0][2] + vec->y * matrix->value[1][2] +
           vec->z * matrix->value[2][2] + matrix->value[3][2];

  double w = vec->x * matrix->value[0][3] + vec->y * matrix->value[1][3] +
             vec->z * matrix->value[2][3] + matrix->value[3][3];

  if (w != 0) {
    res->x /= w;
    res->y /= w;
    res->z /= w;
  }
  return res;
}