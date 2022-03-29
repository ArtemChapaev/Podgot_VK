#ifndef PROJECT_INCLUDE_HELPER_FOR_MATRIX_H_
#define PROJECT_INCLUDE_HELPER_FOR_MATRIX_H_

#include "matrix.h"

#define ROW_FOR_DECOMP 0


enum errors {
    ERR_WRONG_POINTER = 1,
    ERR_NOT_MATCHING_COND,
    ERR_MEMORY,
    ERR_WRONG_SCANF,
    ERR_WRONG_OPERATOR
};

Matrix* addition_matrix(const Matrix *l, const Matrix *r, const char operation);
double det_of_m(const Matrix *matrix, int *err);
void matrix_part_cpy(const Matrix *matrix, Matrix *new_matrix, size_t row, size_t col);

#endif  // PROJECT_INCLUDE_HELPER_FOR_MATRIX_H_
