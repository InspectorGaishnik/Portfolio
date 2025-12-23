#ifndef S21_MATRIX_OOP_H
#define S21_MATRIX_OOP_H

#include <iostream>

#define SUCCESS 0
#define ERROR 1
#define SUCCESS_EQ 1
#define ERROR_EQ 0

class S21Matrix {
 private:
  int rows_ = 0, cols_ = 0;
  double** matrix_;

 public:
  S21Matrix();
  S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix& other);
  S21Matrix(S21Matrix&& other) noexcept(true);
  ~S21Matrix() noexcept(true);

  bool EqMatrix(const S21Matrix& other);
  void SumMatrix(const S21Matrix& other);
  void SubMatrix(const S21Matrix& other);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix& other);
  S21Matrix Transpose();
  S21Matrix GetMinor(int ExcludedRows, int ExcludedCols);
  double Determinant();
  S21Matrix CalcComplements();
  S21Matrix InverseMatrix();

  S21Matrix operator+(const S21Matrix& other);
  S21Matrix operator-(const S21Matrix& other);
  S21Matrix operator*(const S21Matrix& other);
  bool operator==(const S21Matrix& other) const;
  S21Matrix& operator=(const S21Matrix& other);
  S21Matrix& operator+=(const S21Matrix& other);
  S21Matrix& operator-=(const S21Matrix& other);
  S21Matrix& operator*=(const S21Matrix& other);
  double& operator()(int i, int j);

  S21Matrix Move();
  double GetValue(int i, int j);
  int GetRowsValue();
  int GetColsValue();
  void SetValue(int i, int j, double num);
  void InitializerMatrix();
  void InitializerMatrix2();
  void InitializerMatrix3();

  friend std::ostream& operator<<(std::ostream& os, const S21Matrix& other);
};

std::ostream& operator<<(std::ostream& os, const S21Matrix& other);

#endif  // S21_MATRIX_OOP_H