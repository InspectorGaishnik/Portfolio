#ifndef MATRIX_OOP_H
#define MATRIX_OOP_H

#include <iostream>

#define SUCCESS 0
#define ERROR 1
#define SUCCESS_EQ 1
#define ERROR_EQ 0

class Matrix {
 private:
  int rows_ = 0, cols_ = 0;
  double** matrix_;

 public:
  Matrix();
  Matrix(int rows, int cols);
  Matrix(const Matrix& other);
  Matrix(Matrix&& other) noexcept(true);
  ~Matrix() noexcept(true);

  bool EqMatrix(const Matrix& other);
  void SumMatrix(const Matrix& other);
  void SubMatrix(const Matrix& other);
  void MulNumber(const double num);
  void MulMatrix(const Matrix& other);
  Matrix Transpose();
  Matrix GetMinor(int ExcludedRows, int ExcludedCols);
  double Determinant();
  Matrix CalcComplements();
  Matrix InverseMatrix();

  Matrix operator+(const Matrix& other);
  Matrix operator-(const Matrix& other);
  Matrix operator*(const Matrix& other);
  bool operator==(const Matrix& other) const;
  Matrix& operator=(const Matrix& other);
  Matrix& operator+=(const Matrix& other);
  Matrix& operator-=(const Matrix& other);
  Matrix& operator*=(const Matrix& other);
  double& operator()(int i, int j);

  Matrix Move();
  double GetValue(int i, int j);
  int GetRowsValue();
  int GetColsValue();
  void SetValue(int i, int j, double num);
  void InitializerMatrix();
  void InitializerMatrix2();
  void InitializerMatrix3();

  friend std::ostream& operator<<(std::ostream& os, const Matrix& other);
};

std::ostream& operator<<(std::ostream& os, const Matrix& other);

#endif  // MATRIX_OOP_H