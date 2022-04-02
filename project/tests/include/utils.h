#ifndef PROJECT_TESTS_INCLUDE_UTILS_H_
#define PROJECT_TESTS_INCLUDE_UTILS_H_

#include <string.h>

#include "matrix.h"
// FIXME(t.razumov): base accuracy
#define eps_base 1e-6

char *path_join(const char *, ...);

matrix_t *create_identity_matrix(int);
void print_matrix(const matrix_t *);
void assert_matrix_equal(matrix_t *, matrix_t *, double);

int double_equals(double, double, double);


#endif  // PROJECT_TESTS_INCLUDE_UTILS_H_
