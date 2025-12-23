#ifndef TEST_CPP
#define TEST_CPP

#include <gtest/gtest.h>

#include "../s21_matrix_oop.h"

// EqMatrix:

TEST(EqMatrix, TEST_1) {
  S21Matrix matrix1(3, 3);
  S21Matrix matrix2(3, 3);
  matrix1.InitializerMatrix();
  matrix2.InitializerMatrix();

  bool res = matrix1.EqMatrix(matrix2);

  EXPECT_EQ(res, 1);
}

TEST(EqMatrix, TEST_2) {
  S21Matrix matrix1(2, 3);
  S21Matrix matrix2(2, 3);
  matrix1.InitializerMatrix();
  matrix2.InitializerMatrix();

  bool res = matrix1.EqMatrix(matrix2);

  EXPECT_EQ(res, 1);
}

TEST(EqMatrix, TEST_3) {
  S21Matrix matrix1(1, 1);
  S21Matrix matrix2(3, 3);
  matrix1.InitializerMatrix();
  matrix2.InitializerMatrix();

  bool res = matrix1.EqMatrix(matrix2);

  EXPECT_EQ(res, 0);
}

TEST(EqMatrix, TEST_4) {
  S21Matrix matrix1(2, 3);
  S21Matrix matrix2(2, 1);
  matrix1.InitializerMatrix();
  matrix2.InitializerMatrix();

  bool res = matrix1.EqMatrix(matrix2);

  EXPECT_EQ(res, 0);
}

TEST(EqMatrix, TEST_5) {
  S21Matrix matrix1(3, 3);
  S21Matrix matrix2(3, 3);
  matrix1.InitializerMatrix();
  matrix2.InitializerMatrix();

  matrix1.SetValue(0, 0, 11.0);

  bool res = matrix1.EqMatrix(matrix2);

  EXPECT_EQ(res, 0);
}

TEST(EqMatrix, TEST_6) {
  S21Matrix matrix1(3, 2);
  S21Matrix matrix2(3, 2);
  matrix1.InitializerMatrix();
  matrix2.InitializerMatrix();

  matrix1.SetValue(0, 1, 11.0);

  bool res = matrix1.EqMatrix(matrix2);

  EXPECT_EQ(res, 0);
}

TEST(EqMatrix, TEST_7) {
  S21Matrix matrix1(3, 2);
  S21Matrix matrix2;
  matrix1.InitializerMatrix();

  bool res = matrix1.EqMatrix(matrix2);

  EXPECT_EQ(res, 0);
}

TEST(EqMatrix, TEST_8) {
  S21Matrix matrix1;
  S21Matrix matrix2(3, 2);
  matrix2.InitializerMatrix();

  bool res = matrix1.EqMatrix(matrix2);

  EXPECT_EQ(res, 0);
}

TEST(EqMatrix, TEST_9) {
  S21Matrix matrix1;
  S21Matrix matrix2;

  bool res = matrix1.EqMatrix(matrix2);

  EXPECT_EQ(res, 0);
}

TEST(EqMatrix, TEST_10) {
  S21Matrix matrix1;
  S21Matrix matrix2;

  bool res = matrix2.EqMatrix(matrix1);

  EXPECT_EQ(res, 0);
}

// SumMatrix:

TEST(SumMatrix, TEST_1) {
  S21Matrix matrix1(3, 3);
  S21Matrix matrix2(3, 3);
  matrix1.InitializerMatrix();
  matrix2.InitializerMatrix();

  matrix1.SumMatrix(matrix2);

  EXPECT_EQ(matrix1.GetValue(0, 0), 2);
  EXPECT_EQ(matrix1.GetValue(0, 1), 4);
  EXPECT_EQ(matrix1.GetValue(0, 2), 6);
  EXPECT_EQ(matrix1.GetValue(1, 0), 8);
  EXPECT_EQ(matrix1.GetValue(1, 1), 10);
  EXPECT_EQ(matrix1.GetValue(1, 2), 12);
  EXPECT_EQ(matrix1.GetValue(2, 0), 14);
  EXPECT_EQ(matrix1.GetValue(2, 1), 16);
  EXPECT_EQ(matrix1.GetValue(2, 2), 18);
}

TEST(SumMatrix, TEST_2) {
  S21Matrix matrix1;
  S21Matrix matrix2;

  EXPECT_THROW({ matrix1.SumMatrix(matrix2); }, std::invalid_argument);
}

TEST(SumMatrix, TEST_3) {
  S21Matrix matrix1(3, 3);
  S21Matrix matrix2;
  matrix1.InitializerMatrix();

  EXPECT_THROW({ matrix1.SumMatrix(matrix2); }, std::invalid_argument);
}

TEST(SumMatrix, TEST_4) {
  S21Matrix matrix1;
  S21Matrix matrix2(3, 3);
  matrix2.InitializerMatrix();

  EXPECT_THROW({ matrix1.SumMatrix(matrix2); }, std::invalid_argument);
}

TEST(SumMatrix, TEST_5) {
  S21Matrix matrix1(3, 3);
  S21Matrix matrix2;
  matrix1.InitializerMatrix();

  EXPECT_THROW({ matrix2.SumMatrix(matrix1); }, std::invalid_argument);
}

TEST(SumMatrix, TEST_6) {
  S21Matrix matrix1;
  S21Matrix matrix2(3, 3);
  matrix2.InitializerMatrix();

  EXPECT_THROW({ matrix2.SumMatrix(matrix1); }, std::invalid_argument);
}

// SubMatrix:

TEST(SubMatrix, TEST_1) {
  S21Matrix matrix1(3, 3);
  S21Matrix matrix2(3, 3);
  matrix1.InitializerMatrix();
  matrix2.InitializerMatrix();

  matrix1.SubMatrix(matrix2);
  matrix1.SubMatrix(matrix2);

  EXPECT_EQ(matrix1.GetValue(0, 0), -1);
  EXPECT_EQ(matrix1.GetValue(0, 1), -2);
  EXPECT_EQ(matrix1.GetValue(0, 2), -3);
  EXPECT_EQ(matrix1.GetValue(1, 0), -4);
  EXPECT_EQ(matrix1.GetValue(1, 1), -5);
  EXPECT_EQ(matrix1.GetValue(1, 2), -6);
  EXPECT_EQ(matrix1.GetValue(2, 0), -7);
  EXPECT_EQ(matrix1.GetValue(2, 1), -8);
  EXPECT_EQ(matrix1.GetValue(2, 2), -9);
}

TEST(SubMatrix, TEST_2) {
  S21Matrix matrix1;
  S21Matrix matrix2;

  EXPECT_THROW({ matrix1.SubMatrix(matrix2); }, std::invalid_argument);
}

TEST(SubMatrix, TEST_3) {
  S21Matrix matrix1(3, 3);
  S21Matrix matrix2;
  matrix1.InitializerMatrix();

  EXPECT_THROW({ matrix1.SubMatrix(matrix2); }, std::invalid_argument);
}

TEST(SubMatrix, TEST_4) {
  S21Matrix matrix1;
  S21Matrix matrix2(3, 3);
  matrix2.InitializerMatrix();

  EXPECT_THROW({ matrix1.SubMatrix(matrix2); }, std::invalid_argument);
}

TEST(SubMatrix, TEST_5) {
  S21Matrix matrix1(3, 3);
  S21Matrix matrix2;
  matrix1.InitializerMatrix();

  EXPECT_THROW({ matrix2.SubMatrix(matrix1); }, std::invalid_argument);
}

TEST(SubMatrix, TEST_6) {
  S21Matrix matrix1;
  S21Matrix matrix2(3, 3);
  matrix2.InitializerMatrix();

  EXPECT_THROW({ matrix2.SubMatrix(matrix1); }, std::invalid_argument);
}

// MulNumber:

TEST(MulNumber, TEST_1) {
  S21Matrix matrix1(3, 3);
  matrix1.InitializerMatrix();

  matrix1.MulNumber(2);

  EXPECT_EQ(matrix1.GetValue(0, 0), 2);
  EXPECT_EQ(matrix1.GetValue(0, 1), 4);
  EXPECT_EQ(matrix1.GetValue(0, 2), 6);
  EXPECT_EQ(matrix1.GetValue(1, 0), 8);
  EXPECT_EQ(matrix1.GetValue(1, 1), 10);
  EXPECT_EQ(matrix1.GetValue(1, 2), 12);
  EXPECT_EQ(matrix1.GetValue(2, 0), 14);
  EXPECT_EQ(matrix1.GetValue(2, 1), 16);
  EXPECT_EQ(matrix1.GetValue(2, 2), 18);
}

TEST(MulNumber, TEST_2) {
  S21Matrix matrix1(3, 3);
  matrix1.InitializerMatrix();

  matrix1.MulNumber(-2);

  EXPECT_EQ(matrix1.GetValue(0, 0), -2);
  EXPECT_EQ(matrix1.GetValue(0, 1), -4);
  EXPECT_EQ(matrix1.GetValue(0, 2), -6);
  EXPECT_EQ(matrix1.GetValue(1, 0), -8);
  EXPECT_EQ(matrix1.GetValue(1, 1), -10);
  EXPECT_EQ(matrix1.GetValue(1, 2), -12);
  EXPECT_EQ(matrix1.GetValue(2, 0), -14);
  EXPECT_EQ(matrix1.GetValue(2, 1), -16);
  EXPECT_EQ(matrix1.GetValue(2, 2), -18);
}

TEST(MulNumber, TEST_3) {
  S21Matrix matrix1;

  EXPECT_THROW({ matrix1.MulNumber(-2); }, std::invalid_argument);
}

// MulMatrix:

TEST(MulMatrix, TEST_1) {
  S21Matrix matrix1(3, 3);
  S21Matrix matrix2(3, 3);
  matrix1.InitializerMatrix();
  matrix2.InitializerMatrix();

  matrix1.MulMatrix(matrix2);

  EXPECT_EQ(matrix1.GetValue(0, 0), 30);
  EXPECT_EQ(matrix1.GetValue(0, 1), 36);
  EXPECT_EQ(matrix1.GetValue(0, 2), 42);
  EXPECT_EQ(matrix1.GetValue(1, 0), 66);
  EXPECT_EQ(matrix1.GetValue(1, 1), 81);
  EXPECT_EQ(matrix1.GetValue(1, 2), 96);
  EXPECT_EQ(matrix1.GetValue(2, 0), 102);
  EXPECT_EQ(matrix1.GetValue(2, 1), 126);
  EXPECT_EQ(matrix1.GetValue(2, 2), 150);
}

TEST(MulMatrix, TEST_2) {
  S21Matrix matrix1(3, 2);
  S21Matrix matrix2(3, 3);

  EXPECT_THROW({ matrix1.MulMatrix(matrix2); }, std::invalid_argument);
}

TEST(MulMatrix, TEST_3) {
  S21Matrix matrix1(3, 3);
  S21Matrix matrix2(10, 3);

  EXPECT_THROW({ matrix1.MulMatrix(matrix2); }, std::invalid_argument);
}

TEST(MulMatrix, TEST_4) {
  S21Matrix matrix1(3, 3);
  S21Matrix matrix2(3, 2);
  matrix1.InitializerMatrix();

  matrix2.SetValue(0, 0, 1.0);
  matrix2.SetValue(0, 1, 2.0);
  matrix2.SetValue(1, 0, 3.0);
  matrix2.SetValue(1, 1, 4.0);
  matrix2.SetValue(2, 0, 5.0);
  matrix2.SetValue(2, 1, 6.0);

  matrix1.MulMatrix(matrix2);

  EXPECT_EQ(matrix1.GetValue(0, 0), 22.0);
  EXPECT_EQ(matrix1.GetValue(0, 1), 28.0);
  EXPECT_EQ(matrix1.GetValue(1, 0), 49.0);
  EXPECT_EQ(matrix1.GetValue(1, 1), 64.0);
  EXPECT_EQ(matrix1.GetValue(2, 0), 76.0);
  EXPECT_EQ(matrix1.GetValue(2, 1), 100.0);
}

// Transpose:

TEST(Transpose, TEST_1) {
  S21Matrix matrix(3, 3);
  S21Matrix matrixRes(3, 3);
  matrix.InitializerMatrix();

  matrixRes = matrix.Transpose();

  EXPECT_EQ(matrixRes.GetValue(0, 0), 1);
  EXPECT_EQ(matrixRes.GetValue(0, 1), 4);
  EXPECT_EQ(matrixRes.GetValue(0, 2), 7);
  EXPECT_EQ(matrixRes.GetValue(1, 0), 2);
  EXPECT_EQ(matrixRes.GetValue(1, 1), 5);
  EXPECT_EQ(matrixRes.GetValue(1, 2), 8);
  EXPECT_EQ(matrixRes.GetValue(2, 0), 3);
  EXPECT_EQ(matrixRes.GetValue(2, 1), 6);
  EXPECT_EQ(matrixRes.GetValue(2, 2), 9);
}

// Determinant:

TEST(Determinant, TEST_1) {
  S21Matrix matrix(3, 3);
  matrix.InitializerMatrix2();
  double res;

  res = matrix.Determinant();

  EXPECT_EQ(res, -1);
}

TEST(Determinant, TEST_2) {
  S21Matrix matrix(1, 1);
  matrix.SetValue(0, 0, 9);
  double res;

  res = matrix.Determinant();

  EXPECT_EQ(res, 9);
}

TEST(Determinant, TEST_3) {
  S21Matrix matrix(2, 2);
  matrix.InitializerMatrix();
  double res;

  res = matrix.Determinant();

  EXPECT_EQ(res, -2);
}

TEST(Determinant, TEST_4) {
  S21Matrix matrix(1, 3);

  EXPECT_THROW({ matrix.Determinant(); }, std::invalid_argument);
}

// CalcComplements:

TEST(CalsComplements, TEST_1) {
  S21Matrix matrix(3, 3);
  S21Matrix matrixRes(3, 3);
  matrix.InitializerMatrix();

  matrixRes = matrix.CalcComplements();

  EXPECT_EQ(matrixRes.GetValue(0, 0), -3);
  EXPECT_EQ(matrixRes.GetValue(0, 1), 6);
  EXPECT_EQ(matrixRes.GetValue(0, 2), -3);
  EXPECT_EQ(matrixRes.GetValue(1, 0), 6);
  EXPECT_EQ(matrixRes.GetValue(1, 1), -12);
  EXPECT_EQ(matrixRes.GetValue(1, 2), 6);
  EXPECT_EQ(matrixRes.GetValue(2, 0), -3);
  EXPECT_EQ(matrixRes.GetValue(2, 1), 6);
  EXPECT_EQ(matrixRes.GetValue(2, 2), -3);
}

TEST(CalsComplements, TEST_2) {
  S21Matrix matrix(3, 2);
  S21Matrix matrixRes(3, 2);
  matrix.InitializerMatrix();

  EXPECT_THROW(
      { matrixRes = matrix.CalcComplements(); }, std::invalid_argument);
}

TEST(CalsComplements, TEST_3) {
  S21Matrix matrix(1, 1);
  S21Matrix matrixRes(1, 1);
  matrix.SetValue(0, 0, 19);

  matrixRes = matrix.CalcComplements();

  EXPECT_EQ(matrixRes.GetValue(0, 0), 19);
}

// InverseMatrix:

TEST(InverseMatrix, TEST_1) {
  S21Matrix matrix(3, 3);
  S21Matrix matrixRes(3, 3);
  matrix.InitializerMatrix2();

  matrixRes = matrix.InverseMatrix();

  EXPECT_EQ(matrixRes.GetValue(0, 0), 1);
  EXPECT_EQ(matrixRes.GetValue(0, 1), -1);
  EXPECT_EQ(matrixRes.GetValue(0, 2), 1);
  EXPECT_EQ(matrixRes.GetValue(1, 0), -38);
  EXPECT_EQ(matrixRes.GetValue(1, 1), 41);
  EXPECT_EQ(matrixRes.GetValue(1, 2), -34);
  EXPECT_EQ(matrixRes.GetValue(2, 0), 27);
  EXPECT_EQ(matrixRes.GetValue(2, 1), -29);
  EXPECT_EQ(matrixRes.GetValue(2, 2), 24);

  S21Matrix test(3, 3);
  test.InitializerMatrix2();
  test.MulMatrix(matrixRes);

  EXPECT_EQ(test.GetValue(0, 0), 1);
  EXPECT_EQ(test.GetValue(0, 1), 0);
  EXPECT_EQ(test.GetValue(0, 2), 0);
  EXPECT_EQ(test.GetValue(1, 0), 0);
  EXPECT_EQ(test.GetValue(1, 1), 1);
  EXPECT_EQ(test.GetValue(1, 2), 0);
  EXPECT_EQ(test.GetValue(2, 0), 0);
  EXPECT_EQ(test.GetValue(2, 1), 0);
  EXPECT_EQ(test.GetValue(2, 2), 1);
}

TEST(InverseMatrix, TEST_2) {
  S21Matrix matrix(3, 3);
  S21Matrix matrixRes(3, 3);
  matrix.InitializerMatrix();

  EXPECT_THROW({ matrixRes = matrix.InverseMatrix(); }, std::invalid_argument);
}

// GetValue:

TEST(GetValue, TEST_1) {
  S21Matrix matrix(3, 3);
  matrix.InitializerMatrix();

  EXPECT_THROW({ matrix.GetValue(3, 3); }, std::out_of_range);
}

// SetValue:

TEST(SetValue, TEST_1) {
  S21Matrix matrix(3, 3);
  matrix.InitializerMatrix();

  EXPECT_THROW({ matrix.SetValue(3, 3, 19); }, std::out_of_range);
}

// InitializerMatrix:

TEST(InitializerMatrix, TEST_2) {
  S21Matrix matrix;

  EXPECT_THROW({ matrix.InitializerMatrix(); }, std::invalid_argument);
}

// InitializerMatrix2:

TEST(InitializerMatrix2, TEST_2) {
  S21Matrix matrix;

  EXPECT_THROW({ matrix.InitializerMatrix2(); }, std::invalid_argument);
}

// InitializerMatrix3:

TEST(InitializerMatrix3, TEST_2) {
  S21Matrix matrix;

  EXPECT_THROW({ matrix.InitializerMatrix3(); }, std::invalid_argument);
}

#endif  // TEST_CPP