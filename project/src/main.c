#include <stdio.h>

#include "matrix.h"

void print_matrix(matrix_t *matrix);

int main(void) {
    matrix_t *first_matrix = create_matrix_from_file("first_matrix.dat");
    if (first_matrix == NULL) {
        printf("%s\n", "Error creating first matrix from file");
        return -1;
    }
    printf("%s\n", "First matrix:");
    print_matrix(first_matrix);

    matrix_t *second_matrix = create_matrix_from_file("second_matrix.dat");
    if (second_matrix == NULL) {
        printf("%s\n", "Error creating second matrix from file");
        return -1;
    }
    printf("%s\n", "Second matrix:");
    print_matrix(second_matrix);

    putchar('\n');

    size_t second_rows;
    int return_code = get_rows(second_matrix, &second_rows);
    if (return_code != 0) {
        printf("%s\n", "Error getting rows");
        return 1;
    }
    printf("%s %zu\n", "Number of rows of the second matrix =", second_rows);

    size_t second_cols;
    return_code = get_cols(second_matrix, &second_cols);
    if (return_code != 0) {
        printf("%s\n", "Error getting cols");
        return 2;
    }
    printf("%s %zu\n", "Number of cols of the second matrix =", second_cols);

    double first_m_null_elem;
    return_code = get_elem(first_matrix, 0, 0, &first_m_null_elem);
    if (return_code != 0) {
        printf("%s\n", "Error getting null elem");
        return 3;
    }
    printf("%s %lf\n", "Null elem of the first matrix =", first_m_null_elem);

    double second_m_last_elem;
    return_code = get_elem(second_matrix, second_rows - 1, second_cols - 1, &second_m_last_elem);
    if (return_code != 0) {
        printf("%s\n", "Error getting last elem");
        return 4;
    }
    printf("%s %lf\n", "Last elem of the second matrix =", second_m_last_elem);

    return_code = set_elem(first_matrix, 0, 0, 0);
    if (return_code != 0) {
        printf("%s\n", "Error setting first elem");
        return 5;
    }
    return_code = get_elem(first_matrix, 0, 0, &first_m_null_elem);
    if (return_code != 0) {
        printf("%s\n", "Error getting null elem after change");
        return 6;
    }
    printf("%s %lf\n", "Null elem first matrix after change =", first_m_null_elem);

    putchar('\n');

    double scalar = 2.2;
    matrix_t *new_matrix = mul_scalar(first_matrix, scalar);
    if (new_matrix == NULL) {
        printf("%s\n", "Error multiplication first matrix");
        return 7;
    }
    printf("%s%lf:\n", "Multiplication first matrix and ", scalar);
    print_matrix(new_matrix);
    free_matrix(new_matrix);

    new_matrix = transp(second_matrix);
    if (new_matrix == NULL) {
        printf("%s\n", "Error transposition second matrix");
        return 8;
    }
    printf("%s\n", "Transposed second matrix:");
    print_matrix(new_matrix);
    free_matrix(new_matrix);

    putchar('\n');

    new_matrix = sum(first_matrix, second_matrix);
    if (new_matrix == NULL) {
        printf("%s\n", "Error sum first and second matrix");
        return 9;
    }
    printf("%s\n", "Sum of first and second matrix:");
    print_matrix(new_matrix);
    free_matrix(new_matrix);

    new_matrix = sub(first_matrix, second_matrix);
    if (new_matrix == NULL) {
        printf("%s\n", "Error subtraction of first and second matrix");
        return 10;
    }
    printf("%s\n", "Subtraction of first and second matrix:");
    print_matrix(new_matrix);
    free_matrix(new_matrix);

    new_matrix = mul(first_matrix, second_matrix);
    if (new_matrix == NULL) {
        printf("%s\n", "Error multiplication first and second matrix");
        return 11;
    }
    printf("%s\n", "Multiplication first and second matrix:");
    print_matrix(new_matrix);
    free_matrix(new_matrix);

    putchar('\n');

    double determinant;
    return_code = det(first_matrix, &determinant);
    if (return_code != 0) {
        printf("%s", "Error calculation of det of first matrix");
        return 12;
    }
    printf("%s %lf\n", "Determinant of first matrix =", determinant);

    new_matrix = adj(second_matrix);
    if (new_matrix == NULL) {
        printf("%s\n", "Error adj matrix of second matrix");
        return 13;
    }
    printf("%s\n", "Adj matrix of second matrix:");
    print_matrix(new_matrix);
    free_matrix(new_matrix);

    new_matrix = inv(first_matrix);
    if (new_matrix == NULL) {
        printf("%s\n", "Error inverse matrix of first matrix");
        return 14;
    }
    printf("%s\n", "Inverse matrix of first matrix:");
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
