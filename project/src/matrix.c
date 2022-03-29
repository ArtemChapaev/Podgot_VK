#include <stdio.h>
#include <stdlib.h>

#include "matrix.h"
#include "helper_for_matrix.h"

Matrix *create_matrix_from_file(const char *path_file) {
    if (path_file == NULL) {
        return NULL;
    }

    FILE *file = fopen(path_file, "r");
    if (file == NULL) {
        return NULL;
    }

    Matrix *new_matrix;
    new_matrix = malloc(sizeof(Matrix));
    if (new_matrix == NULL) {
        fclose(file);
        return NULL;
    }

    int return_code = fscanf(file, "%zu %zu", &new_matrix->rows, &new_matrix->cols);
    if (return_code != 2) {
        free(new_matrix);
        fclose(file);
        return NULL;
    }

    int size = new_matrix->rows * new_matrix->cols;
    new_matrix->array = malloc(sizeof(double) * size);
    if (new_matrix->array == NULL) {
        free(new_matrix);
        fclose(file);
        return NULL;
    }

    int err_code = 0;
    for (int i = 0; i < size; i++) {
        double elem;
        return_code = fscanf(file, "%lf", &elem);
        if (return_code != 1) {
            err_code = ERR_WRONG_SCANF;
        }
        new_matrix->array[i] = elem;
    }

    fclose(file);
    if (err_code != 0) {
        free_matrix(new_matrix);
        return NULL;
    }
    return new_matrix;
}

Matrix *create_matrix(size_t rows, size_t cols) {
    if (rows < 1 || cols < 1) {
        return NULL;
    }
    Matrix *new_matrix;
    new_matrix = malloc(sizeof(Matrix));
    if (new_matrix == NULL) {
        return NULL;
    }

    new_matrix->rows = rows;
    new_matrix->cols = cols;

    new_matrix->array = calloc(rows * cols, sizeof(double));
    if (new_matrix->array == NULL) {
        free(new_matrix);
        return NULL;
    }

    return new_matrix;
}

void free_matrix(Matrix *matrix) {
    if (matrix != NULL) {
        if (matrix->array != NULL) {
            free(matrix->array);
        }
        free(matrix);
    }
}

int get_rows(const Matrix *matrix, size_t *rows) {
    if (matrix == NULL) {
        return ERR_WRONG_POINTER;
    }
    *rows = matrix->rows;
    return 0;
}

int get_cols(const Matrix *matrix, size_t *cols) {
    if (matrix == NULL) {
        return ERR_WRONG_POINTER;
    }
    *cols = matrix->cols;
    return 0;
}

int get_elem(const Matrix *matrix, size_t row, size_t col, double *val) {
    if (matrix == NULL) {
        return ERR_WRONG_POINTER;
    }
    if (matrix->rows < row || matrix->cols < col) {
        return ERR_NOT_MATCHING_COND;
    }
    *val = matrix->array[row * matrix->cols + col];
    return 0;
}

int set_elem(Matrix *matrix, size_t row, size_t col, double val) {
    if (matrix == NULL) {
        return ERR_WRONG_POINTER;
    }
    if (matrix->rows < row || matrix->cols < col) {
        return ERR_NOT_MATCHING_COND;
    }
    matrix->array[row * matrix->cols + col] = val;
    return 0;
}

Matrix *mul_scalar(const Matrix *matrix, double val) {
    if (matrix == NULL) {
        return NULL;
    }

    Matrix *new_matrix = create_matrix(matrix->rows, matrix->cols);
    if (new_matrix == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < matrix->rows * matrix->cols; i++) {
        new_matrix->array[i] = matrix->array[i] * val;
    }

    return new_matrix;
}

Matrix *transp(const Matrix *matrix) {
    if (matrix == NULL) {
        return NULL;
    }

    Matrix *new_matrix = create_matrix(matrix->cols, matrix->rows);
    if (new_matrix == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < new_matrix->rows; i++) {
        for (size_t k = 0; k < new_matrix->cols; k++) {
            new_matrix->array[i * new_matrix->cols + k] = matrix->array[k * matrix->cols + i];
        }
    }

    return new_matrix;
}

Matrix *sum(const Matrix *l, const Matrix *r) {
    Matrix *new_matrix = addition_matrix(l, r, '+');
    return new_matrix;  // если в выполнении вызываемой функции ошибка, то ошибку выдаст и эта функция
}

Matrix *sub(const Matrix *l, const Matrix *r) {
    Matrix *new_matrix = addition_matrix(l, r, '-');
    return new_matrix;
}

Matrix *mul(const Matrix *l, const Matrix *r) {
    if (l == NULL || r == NULL) {
        return NULL;
    }
    if (l->cols != r->rows) {
        return NULL;
    }

    Matrix *new_matrix = create_matrix(l->rows, r->cols);
    if (new_matrix == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < new_matrix->rows; i++) {
        for (size_t k = 0; k < new_matrix->cols; k++) {
            double value = 0;
            for (size_t g = 0; g < l->cols; g++) {
                value += l->array[i * l->cols + g] * r->array[g * r->cols + k];
            }
            new_matrix->array[i * new_matrix->cols + k] = value;
        }
    }
    return new_matrix;
}

int det(const Matrix *matrix, double *val) {
    if (matrix == NULL) {
        return ERR_WRONG_POINTER;
    }
    if (matrix->rows != matrix->cols) {
        return ERR_NOT_MATCHING_COND;
    }

    int err = 0;
    *val = det_of_m(matrix, &err);
    if (err != 0) {
        return ERR_MEMORY;
    }
    return 0;
}

Matrix *adj(const Matrix *matrix) {
    if (matrix == NULL) {
        return NULL;
    }
    if (matrix->rows != matrix->cols) {
        return NULL;
    }

    Matrix *adj_matrix = create_matrix(matrix->rows, matrix->cols);
    if (adj_matrix == NULL) {
        return NULL;
    }

    if (adj_matrix->rows == 1) {
        adj_matrix->array[0] = 1;
        return adj_matrix;
    }

    Matrix *part_of_matrix = create_matrix(matrix->cols - 1, matrix->rows - 1);
    if (part_of_matrix == NULL) {
        free_matrix(adj_matrix);
        return NULL;
    }

    int err = 0;
    for (size_t i = 0; i < adj_matrix->rows; i++) {
        for (size_t k = 0; k < adj_matrix->cols; k++) {
            matrix_part_cpy(matrix, part_of_matrix, k, i);  // поменял i и k местами для транспонирования

            adj_matrix->array[i * matrix->cols + k] = det_of_m(part_of_matrix, &err);
            if ((i + k) % 2 == 1) {
                adj_matrix->array[i * matrix->cols + k] *= -1;
            }
        }
    }

    free_matrix(part_of_matrix);
    if (err != 0) {
        free_matrix(adj_matrix);
        return NULL;
    }
    return adj_matrix;
}

Matrix *inv(const Matrix *matrix) {
    if (matrix == NULL) {
        return NULL;
    }
    if (matrix->rows != matrix->cols) {
        return NULL;
    }

    double determinant = 0.0;
    int return_code = det(matrix, &determinant);
    if (return_code != 0) {
        return NULL;
    }

    Matrix *adj_matrix = adj(matrix);
    if (adj_matrix == NULL) {
        return NULL;
    }

    Matrix *inv_matrix = mul_scalar(adj_matrix, 1 / determinant);
    free_matrix(adj_matrix);

    if (inv_matrix == NULL) {
        return NULL;
    }
    return inv_matrix;
}
