#include <stdio.h>
#include <stdlib.h>

#include "helper_for_matrix.h"
#include "matrix.h"


Matrix* addition_matrix(const Matrix *l, const Matrix *r, const char operation) {
    if (l == NULL || r == NULL) {
        return NULL;
    }
    if (l->cols != r->cols || l->rows != r->rows) {
        return NULL;
    }

    Matrix *new_matrix = create_matrix(l->rows, l->cols);
    if (new_matrix == NULL) {
        return NULL;
    }

    int err_code = 0;
    // согласен, дальше копипаста, но я не знаю, как сделать это иначе
    // но при этом делая проверку передаваемой константы 1 раз
    if (operation == '+') {
        for (size_t i = 0; i < new_matrix->rows; i++) {
            for (size_t k = 0; k < new_matrix->cols; k++) {
                size_t index = i * new_matrix->cols + k;
                new_matrix->array[index] = l->array[index] + r->array[index];
            }
        }
    } else if (operation == '-') {
        for (size_t i = 0; i < new_matrix->rows; i++) {
            for (size_t k = 0; k < new_matrix->cols; k++) {
                size_t index = i * new_matrix->cols + k;
                new_matrix->array[index] = l->array[index] - r->array[index];
            }
        }
    } else {
        err_code = ERR_WRONG_OPERATOR;
    }

    if (err_code != 0) {
        free_matrix(new_matrix);
        return NULL;
    }
    return new_matrix;
}

double det_of_m(const Matrix *matrix, int *err) {
    if (matrix->rows == 1) {
        return matrix->array[0];    // я решил оставить return-ы в этих двух случаях,
    }                               // т.к это проверки на выход из рекурсии
    if (matrix->rows == 2) {
        return matrix->array[0] * matrix->array[3] - matrix->array[1] * matrix->array[2];
    }

    Matrix *part_of_matrix = create_matrix(matrix->cols - 1, matrix->rows - 1);
    if (part_of_matrix == NULL) {
        *err = ERR_MEMORY;
        return 0.0;
    }

    double val = 0.0;
    size_t i = ROW_FOR_DECOMP;

    for (size_t k = 0; k < matrix->cols; k++) {
        matrix_part_cpy(matrix, part_of_matrix, i, k);
        if ((i + k) % 2 == 0) {
            val += matrix->array[i * matrix->cols + k] * det_of_m(part_of_matrix, err);
        } else {
            val -= matrix->array[i * matrix->cols + k] * det_of_m(part_of_matrix, err);
        }
    }
    free_matrix(part_of_matrix);

    return val;
}

void matrix_part_cpy(const Matrix *matrix, Matrix *new_matrix, size_t row, size_t col) {
    for (size_t i = 0, x1 = 0; i < matrix->rows; ++i, ++x1) {
        if (i == row) {
            --x1;
        } else {
            for (size_t k = 0, x2 = 0; k < matrix->cols; ++k, ++x2) {
                if (k == col) {
                    --x2;
                } else {
                    new_matrix->array[x1 * new_matrix->cols + x2] = matrix->array[i * matrix->cols + k];
                }
            }
        }
    }
}
