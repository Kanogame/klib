#include <float.h>
#include <klib/error.h>
#include <math.h>
#include <stdio.h>

double approx_newtonRec(double xn, double (*f)(double), double (*df)(double),
                        double delta, int depth) {
  // base-case, выходим если достигли максимальной глубины рекурсии
  if (depth == 0) {
    return xn;
  }

  // получаем значения для функции и производной в точке
  double fx = f(xn);
  double dfx = df(xn);
  // сравниваем dfx с нулем, чтобы избежать деления на 0
  // if (fabs(dfx) < DBL_EPSILON) {
  if (dfx == 0) {
    EXIT_WITH_ERROR("dfx is too small, exiting");
  }

  // подсчитываем следющее значение
  double xnp = xn - (fx / dfx);
  // если разница в значениях меньше дельты выходим
  if (depth == 0 || fabs(xnp - xn) <= delta) {
    return xnp;
  }

  // заходим в рекурсию
  return approx_newtonRec(xnp, f, df, delta, depth - 1);
}

double approx_newtonIter(double xn, double (*f)(double), double (*df)(double),
                         double delta, int depth) {
  double xnp;

  // проверяем количество итераций
  while (depth >= 0) {
    // получаем значения для функции и производной в точке
    double fx = f(xn);
    double dfx = df(xn);
    // сравниваем dfx с нулем, чтобы избежать деления на 0
    // if (fabs(dfx) < DBL_EPSILON) {
    if (dfx == 0) {
      EXIT_WITH_ERROR("dfx is too small, exiting");
    }

    // подсчитываем следющее значение
    xnp = xn - (fx / dfx);
    // если разница в значениях меньше дельты выходим
    if (fabs(xnp - xn) <= delta) {
      return xnp;
    }

    xn = xnp;
    depth--;
  }

  return xn;
}
