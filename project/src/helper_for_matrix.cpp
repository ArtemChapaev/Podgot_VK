#include <cmath>
#include <limits>

#include "matrix.h"
#include "exceptions.h"

#define ONE_ROW_MATRIX 1
#define TWO_ROW_MATRIX 2

#define ROW_FOR_DECOMP 0

namespace prep {
    using std::vector;
    using std::string;

    void Matrix::createMatrix() {
        matrix.resize(rows);
        for (size_t i = 0; i < rows; i++) {
            matrix[i].resize(cols);
            for (size_t j = 0; j < cols; j++) {
                matrix[i][j] = 0;
            }
        }
    }

    double add(const double x, const double y) { return x + y; }

    double subtract(const double x, const double y) { return x - y; }

    void Matrix::calculateMatrix(const Matrix &rhs, Matrix *NewMatrix,
                                 double (*operationFunc)(double, double)) const {
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; j++) {
                NewMatrix->matrix[i][j] = operationFunc(matrix[i][j], rhs.matrix[i][j]);
            }
        }
    }

    Matrix Matrix::performAddMatrix(const Matrix &rhs, const char operation) const {
        if (rows != rhs.rows || cols != rhs.cols) {
            throw DimensionMismatch(*this, rhs);
        }

        Matrix newMatrix(rows, cols);
        double (*operationFunc)(double, double) = NULL;

        switch (operation) {
            case ('+'): {
                operationFunc = add;
                break;
            }
            case ('-'): {
                operationFunc = subtract;
                break;
            }
            default:
                return newMatrix;
        }
        calculateMatrix(rhs, &newMatrix, operationFunc);
        return newMatrix;
    }

    bool almostEqual(double x, double y) {
        return std::abs(x - y) <= 1e-7;
    }

    double Matrix::countDet() const {
        if (rows == ONE_ROW_MATRIX) {
            return matrix[0][0];
        }
        if (rows == TWO_ROW_MATRIX) {
            return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
        }

        Matrix partOfMatrix(cols - 1, rows - 1);

        double val = 0.0;
        size_t i = ROW_FOR_DECOMP;

        for (size_t j = 0; j < cols; j++) {
            matrixPartCpy(&partOfMatrix, i, j);

            if ((i + j) % 2 == 0) {
                val += matrix[i][j] * partOfMatrix.countDet();
            } else {
                val -= matrix[i][j] * partOfMatrix.countDet();
            }
        }
        return val;
    }

    void Matrix::matrixPartCpy(Matrix *ptrNewMatrix, size_t row, size_t col) const {
        size_t x = 0;

        for (size_t i = 0; i < rows; ++i) {
            if (i == row) {
                --x;
            } else {
                size_t y = 0;

                for (size_t j = 0; j < cols; ++j) {
                    if (j == col) {
                        --y;
                    } else {
                        ptrNewMatrix->matrix[x][y] = matrix[i][j];
                    }
                    ++y;
                }
            }
            ++x;
        }
    }

}  // namespace prep
