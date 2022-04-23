#include <iomanip>
#include <iostream>

#include "matrix.h"
#include "exceptions.h"

namespace prep {
    using std::endl;

    Matrix::Matrix(size_t row, size_t col) : rows(row), cols(col) {
        createMatrix();
    }

    Matrix::Matrix(std::istream &is) {
        is >> rows >> cols;
        if (!is) {
            throw InvalidMatrixStream();
        }

        createMatrix();

        for (size_t i = 0; i < rows; i++) {
            for (size_t j = 0; j < cols; j++) {
                is >> matrix[i][j];

                if (!is) {
                    throw InvalidMatrixStream();
                }
            }
        }
    }

    size_t Matrix::getRows() const { return rows; }

    size_t Matrix::getCols() const { return cols; }

    double Matrix::operator()(size_t i, size_t j) const {
        if (i >= rows || j >= cols) {
            throw OutOfRange(i, j, *this);
        }
        return matrix[i][j];
    }

    double& Matrix::operator()(size_t i, size_t j) {
        if (i >= rows || j >= cols) {
            throw OutOfRange(i, j, *this);
        }
        return matrix[i][j];
    }

    Matrix Matrix::operator+(const Matrix &rhs) const {
        return performAddMatrix(rhs, '+');
    }

    Matrix Matrix::operator-(const Matrix &rhs) const {
        return performAddMatrix(rhs, '-');
    }

    Matrix Matrix::operator*(const Matrix &rhs) const {
        if (cols != rhs.rows) {
            throw DimensionMismatch(*this, rhs);
        }

        Matrix newMatrix(rows, rhs.cols);

        for (size_t i = 0; i < newMatrix.rows; i++) {
            for (size_t j = 0; j < newMatrix.cols; j++) {
                double value = 0;

                for (size_t k = 0; k < cols; k++) {
                    value += matrix[i][k] * rhs.matrix[k][j];
                }

                newMatrix.matrix[i][j] = value;
            }
        }
        return newMatrix;
    }

    bool Matrix::operator==(const Matrix &rhs) const {
        if (rows != rhs.rows || cols != rhs.cols) {
            return false;
        }

        bool equal = true;

        for (size_t i = 0; i < rows; i++) {
            for (size_t j = 0; j < cols; j++) {
                if (!almostEqual(matrix[i][j], rhs.matrix[i][j])) {
                    equal = false;
                    break;
                }
            }
            if (!equal) {
                break;
            }
        }
        return equal;
    }

    bool Matrix::operator!=(const Matrix &rhs) const { return !(*this == rhs); }

    Matrix Matrix::operator*(double val) const {
        Matrix newMatrix(rows, cols);

        for (size_t i = 0; i < rows; i++) {
            for (size_t j = 0; j < cols; j++) {
                newMatrix.matrix[i][j] = matrix[i][j] * val;
            }
        }
        return newMatrix;
    }

    Matrix operator*(double val, const Matrix &matrix) { return matrix * val; }

    std::ostream &operator<<(std::ostream &os, const Matrix &matrix) {
        os << matrix.rows << ' ' << matrix.cols << endl;

        for (size_t i = 0; i < matrix.rows; ++i) {
            for (size_t j = 0; j < matrix.cols; ++j) {
                os << std::setprecision(9) << matrix.matrix[i][j];
                if (j != matrix.cols - 1) {
                    os << ' ';
                }
            }
            if (i != matrix.rows - 1) {
                os << endl;
            }
        }
        return os;
    }

    Matrix Matrix::transp() const {
        Matrix newMatrix(cols, rows);

        for (size_t i = 0; i < newMatrix.rows; i++) {
            for (size_t j = 0; j < newMatrix.cols; j++) {
                newMatrix.matrix[i][j] = matrix[j][i];
            }
        }

        return newMatrix;
    }

    double Matrix::det() const {
        if (rows != cols) {
            throw DimensionMismatch(*this);
        }
        return countDet();
    }

    Matrix Matrix::adj() const {
        if (rows != cols) {
            throw DimensionMismatch(*this);
        }

        Matrix adjMatrix(rows, cols);

        if (rows == 1) {
            adjMatrix.matrix[0][0] = 1;
            return adjMatrix;
        }

        Matrix partOfMatrix(cols - 1, rows - 1);

        for (size_t i = 0; i < rows; i++) {
            for (size_t j = 0; j < cols; j++) {
                matrixPartCpy(&partOfMatrix, j, i);  // поменял i и j местами для транспонирования

                adjMatrix.matrix[i][j] = partOfMatrix.countDet();
                if ((i + j) % 2 == 1) {
                    adjMatrix.matrix[i][j] *= -1;
                }
            }
        }

        return adjMatrix;
    }

    Matrix Matrix::inv() const {
        if (rows != cols) {
            throw DimensionMismatch(*this);
        }

        double determinant = det();
        if (determinant == 0) {
            throw SingularMatrix();
        }

        Matrix invMatrix = adj() * (1 / determinant);

        return invMatrix;
    }
}  // namespace prep
