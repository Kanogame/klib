#ifndef KLIB_APPROX
#define KLIB_APPROX
// f - function itself
// df - derivative of f
// x0 - inital value
// delta - precision
// depth - steps to take (might exit earlier if target accuracy is met)
// tail-recursion for optimization
double approx_newtonRec(double xn, double (*f)(double), double (*df)(double),
                        double delta, int depth);

double approx_newtonIter(double xn, double (*f)(double), double (*df)(double),
                         double delta, int depth);
#endif
