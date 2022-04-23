#pragma once // NOLINT

#include <vector>
#include <istream>

namespace prep {
    using std::vector;

class Matrix {
 public:
      explicit Matrix(size_t row = 0, size_t col = 0);
      explicit Matrix(std::istream& is);

      Matrix(const Matrix& rhs) = default;
      Matrix& operator=(const Matrix& rhs) = default;
      ~Matrix() = default;

      size_t getRows() const;
      size_t getCols() const;

      double operator()(size_t i, size_t j) const;
      double& operator()(size_t i, size_t j);

      bool operator==(const Matrix& rhs) const;
      bool operator!=(const Matrix& rhs) const;

      Matrix operator+(const Matrix& rhs) const;
      Matrix operator-(const Matrix& rhs) const;
      Matrix operator*(const Matrix& rhs) const;

      Matrix operator*(double val) const;

      friend Matrix operator*(double val, const Matrix& matrix);
      friend std::ostream& operator<<(std::ostream& os, const Matrix& matrix);

      Matrix transp() const;
      double det() const;
      Matrix adj() const;
      Matrix inv() const;

 private:
      vector <vector<double>> matrix;
      size_t rows;
      size_t cols;

      void createMatrix();

      friend bool almostEqual(const double x, const double y);
      friend double add(const double x, const double y);
      friend double subtract(const double x, const double y);

      void calculateMatrix(const Matrix &rhs, Matrix *NewMatrix,
                                  double (*operationFunc)(double, double)) const;
      Matrix performAddMatrix(const Matrix &rhs, const char operation) const;

      double countDet() const;
      void matrixPartCpy(Matrix* ptrNewMatrix, size_t row, size_t col) const;
};

    Matrix operator*(double val, const Matrix& matrix);
    std::ostream& operator<<(std::ostream& os, const Matrix& matrix);

    bool almostEqual(double x, double y);
}  // namespace prep
