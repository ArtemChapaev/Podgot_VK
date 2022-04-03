#include <stdio.h>

#include "matrix.h"
#include "main.h"

void print_matrix(matrix_t *matrix);

int main(void) {
    matrix_t *first_matrix = create_matrix_from_file(FIRST_M_FILE);
    if (first_matrix == NULL) {
        printf("%s\n", ERR_CREAT_FIRST_M);
        return 0;
    }
    printf("%s\n", "First matrix:");
    print_matrix(first_matrix);

    matrix_t *second_matrix = create_matrix_from_file(SECOND_M_FILE);
    if (second_matrix == NULL) {
        printf("%s\n", ERR_CREAT_SECOND_M);
        return 0;
    }
    printf("%s\n", "Second matrix:");
    print_matrix(second_matrix);

    printf("\n");

    size_t second_rows;
    int return_code = get_rows(second_matrix, &second_rows);
    if (return_code != 0) {
        printf("%s\n", ERR_GET_ROW);
        return 0;
    }
    printf("%s = %zu\n", OUTPUT_SECOND_ROWS, second_rows);

    size_t second_cols;
    return_code = get_cols(second_matrix, &second_cols);
    if (return_code != 0) {
        printf("%s\n", ERR_GET_COL);
        return 0;
    }
    printf("%s = %zu\n", OUTPUT_SECOND_COLS, second_cols);

    double first_m_null_elem;
    return_code = get_elem(first_matrix, 0, 0, &first_m_null_elem);
    if (return_code != 0) {
        printf("%s\n", ERR_GET_NULL_ELEM);
        return 0;
    }
    printf("%s = %lf\n", OUTPUT_NULL_ELEM, first_m_null_elem);

    double second_m_last_elem;
    return_code = get_elem(second_matrix, second_rows - 1, second_cols - 1, &second_m_last_elem);
    if (return_code != 0) {
        printf("%s\n", ERR_GET_LAST_ELEM);
        return 0;
    }
    printf("%s = %lf\n", OUTPUT_LAST_ELEM, second_m_last_elem);

    return_code = set_elem(first_matrix, 0, 0, 0);
    if (return_code != 0) {
        printf("%s\n", ERR_SET_NULL_ELEM);
        return 0;
    }
    return_code = get_elem(first_matrix, 0, 0, &first_m_null_elem);
    if (return_code != 0) {
        printf("%s\n", ERR_GET_NULL_ELEM_CHANGE);
        return 0;
    }
    printf("%s = %lf\n", OUTPUT_NULL_ELEM_CHANGE, first_m_null_elem);

    printf("\n");

    double scalar = 2.2;
    matrix_t *new_matrix = mul_scalar(first_matrix, scalar);
    if (new_matrix == NULL) {
        printf("%s\n", ERR_SCALAR_MUL_FIRST_M);
        return 0;
    }
    printf("%s%lf:\n", OUTPUT_SCALAR_MUL_FIRST_M, scalar);
    print_matrix(new_matrix);
    free_matrix(new_matrix);

    new_matrix = transp(second_matrix);
    if (new_matrix == NULL) {
        printf("%s\n", ERR_TRANSP_SECOND_M);
        return 0;
    }
    printf("%s:\n", OUTPUT_TRANSP_SECOND_M);
    print_matrix(new_matrix);
    free_matrix(new_matrix);

    printf("\n");

    new_matrix = sum(first_matrix, second_matrix);
    if (new_matrix == NULL) {
        printf("%s\n", ERR_SUM_MATRIX);
        return 0;
    }
    printf("%s:\n", OUTPUT_SUM_MATRIX);
    print_matrix(new_matrix);
    free_matrix(new_matrix);

    new_matrix = sub(first_matrix, second_matrix);
    if (new_matrix == NULL) {
        printf("%s\n", ERR_SUB_MATRIX);
        return 0;
    }
    printf("%s:\n", OUTPUT_SUB_MATRIX);
    print_matrix(new_matrix);
    free_matrix(new_matrix);

    new_matrix = mul(first_matrix, second_matrix);
    if (new_matrix == NULL) {
        printf("%s\n", ERR_MUL_MATRIX);
        return 0;
    }
    printf("%s:\n", OUTPUT_MUL_MATRIX);
    print_matrix(new_matrix);
    free_matrix(new_matrix);

    printf("\n");

    double determinant;
    return_code = det(first_matrix, &determinant);
    if (return_code != 0) {
        printf("%s", ERR_DET_FIRST_M);
        return 0;
    }
    printf("%s = %lf\n", OUTPUT_DET_FIRST_M, determinant);

    new_matrix = adj(second_matrix);
    if (new_matrix == NULL) {
        printf("%s\n", OUTPUT_ADJ_SECOND_M);
        return 0;
    }
    printf("%s:\n", OUTPUT_ADJ_SECOND_M);
    print_matrix(new_matrix);
    free_matrix(new_matrix);

    new_matrix = inv(first_matrix);
    if (new_matrix == NULL) {
        printf("%s\n", ERR_INV_FIRST_M);
        return 0;
    }
    printf("%s:\n", OUTPUT_INV_FIRST_M);
    print_matrix(new_matrix);
    free_matrix(new_matrix);

    free_matrix(second_matrix);
    free_matrix(first_matrix);
    return 0;
}

void print_matrix(matrix_t *matrix) {
    if (matrix == NULL) {
        return;
    }
    printf("Matrix rows = %zu, matrix cols = %zu\n", matrix->rows, matrix->cols);
    for (size_t i = 0; i < matrix->rows; i++) {
        for (size_t k = 0; k < matrix->cols; k++) {
            printf("%5lf ", matrix->array[i * matrix->cols + k]);
        }
        putchar('\n');
    }
}
