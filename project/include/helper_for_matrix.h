#ifndef PROJECT_INCLUDE_HELPER_FOR_MATRIX_H_
#define PROJECT_INCLUDE_HELPER_FOR_MATRIX_H_

#include "matrix.h"

#define ROW_FOR_DECOMP 0

enum matrix {
    ONE_ROW_MATRIX = 1,
    TWO_ROW_MATRIX
};


enum errors {
    ERR_WRONG_POINTER = 1,
    ERR_NOT_MATCHING_COND,
    ERR_MEMORY,
    ERR_WRONG_SCANF,
    ERR_WRONG_OPERATOR
};

matrix_t *perform_addition_matrix(const matrix_t *left_matrix,
                                  const matrix_t *right_matrix, const char operation);
double count_det(const matrix_t *matrix, int *err);
void matrix_part_cpy(const matrix_t *matrix, matrix_t *new_matrix, size_t row, size_t col);

#endif  // PROJECT_INCLUDE_HELPER_FOR_MATRIX_H_
