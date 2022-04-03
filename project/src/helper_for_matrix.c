#include <stdio.h>
#include <stdlib.h>

#include "helper_for_matrix.h"
#include "matrix.h"


double add(double a, double b) { return a + b; }

double subtract(double a, double b) { return a - b; }

void calculate_matrix(const matrix_t *new_matrix, const matrix_t *left_matrix, const matrix_t *right_matrix,
                      double (*operation_func)(double, double)) {
    for (size_t i = 0; i < new_matrix->rows; i++) {
        for (size_t k = 0; k < new_matrix->cols; k++) {
            size_t index = i * new_matrix->cols + k;
            new_matrix->array[index] = operation_func(left_matrix->array[index], right_matrix->array[index]);
        }
    }
}

matrix_t *perform_addition_matrix(const matrix_t *left_matrix,
                                  const matrix_t *right_matrix, const char operation) {
    if (left_matrix == NULL || right_matrix == NULL) {
        return NULL;
    }
    if (left_matrix->cols != right_matrix->cols || left_matrix->rows != right_matrix->rows) {
        return NULL;
    }

    matrix_t *new_matrix = create_matrix(right_matrix->rows, right_matrix->cols);
    if (new_matrix == NULL) {
        return NULL;
    }

    double (*operation_func)(double, double);

    switch (operation) {
        case ('+'): {
            operation_func = add;
            break;
        }
        case ('-'): {
            operation_func = subtract;
            break;
        }
        default: {
            free_matrix(new_matrix);
            return NULL;
        }
    }
    calculate_matrix(new_matrix, left_matrix, right_matrix, operation_func);
    return new_matrix;
}

double count_det(const matrix_t *matrix, int *err) {
    if (matrix->rows == ONE_ROW_MATRIX) {
        return matrix->array[0];
    }
    if (matrix->rows == TWO_ROW_MATRIX) {
        return matrix->array[0] * matrix->array[3] - matrix->array[1] * matrix->array[2];
    }

    matrix_t *part_of_matrix = create_matrix(matrix->cols - 1, matrix->rows - 1);
    if (part_of_matrix == NULL) {
        *err = ERR_MEMORY;
        return 0.0;
    }

    double val = 0.0;
    size_t i = ROW_FOR_DECOMP;

    for (size_t k = 0; k < matrix->cols; k++) {
        matrix_part_cpy(matrix, part_of_matrix, i, k);
        if ((i + k) % 2 == 0) {
            val += matrix->array[i * matrix->cols + k] * count_det(part_of_matrix, err);
        } else {
            val -= matrix->array[i * matrix->cols + k] * count_det(part_of_matrix, err);
        }
    }
    free_matrix(part_of_matrix);

    return val;
}

void matrix_part_cpy(const matrix_t *matrix, matrix_t *new_matrix, size_t row, size_t col) {
    size_t x = 0;
    for (size_t i = 0; i < matrix->rows; ++i) {
        if (i == row) {
            --x;
        } else {
            size_t y = 0;

            for (size_t k = 0; k < matrix->cols; ++k) {
                if (k == col) {
                    --y;
                } else {
                    new_matrix->array[x * new_matrix->cols + y] = matrix->array[i * matrix->cols + k];
                }
                ++y;
            }
        }
        ++x;
    }
}
