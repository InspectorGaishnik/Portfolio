#ifndef TESTS_OPERATORS_CPP
#define TESTS_OPERATORS_CPP

#include <gtest/gtest.h>

#include "../matrix_oop.h"

// Operator(+):

TEST(OperatorSum, TEST_1) {
  Matrix matrix1(3, 3);
  Matrix Matrix2(3, 3);
  Matrix matrixRes(3, 3);
  matrix1.InitializerMatrix();
  Matrix2.InitializerMatrix();

  matrixRes = matrix1 + Matrix2;

  EXPECT_EQ(matrixRes.GetValue(0, 0), 2);
  EXPECT_EQ(matrixRes.GetValue(0, 1), 4);
  EXPECT_EQ(matrixRes.GetValue(0, 2), 6);
  EXPECT_EQ(matrixRes.GetValue(1, 0), 8);
  EXPECT_EQ(matrixRes.GetValue(1, 1), 10);
  EXPECT_EQ(matrixRes.GetValue(1, 2), 12);
  EXPECT_EQ(matrixRes.GetValue(2, 0), 14);
  EXPECT_EQ(matrixRes.GetValue(2, 1), 16);
  EXPECT_EQ(matrixRes.GetValue(2, 2), 18);
}

TEST(OperatorSum, TEST_2) {
  Matrix matrix1(3, 3);
  Matrix matrix2(3, 2);
  matrix1.InitializerMatrix();
  matrix2.InitializerMatrix();

  EXPECT_THROW({ matrix1.operator+(matrix2); }, std::invalid_argument);
}

// Operator(-):

TEST(OperatorSub, TEST_1) {
  Matrix matrix1(3, 3);
  Matrix matrix2(3, 3);
  Matrix matrixRes(3, 3);
  matrix1.InitializerMatrix();
  matrix2.InitializerMatrix();

  matrixRes = matrix1 - matrix2 - matrix2 - matrix2;

  EXPECT_EQ(matrixRes.GetValue(0, 0), -2);
  EXPECT_EQ(matrixRes.GetValue(0, 1), -4);
  EXPECT_EQ(matrixRes.GetValue(0, 2), -6);
  EXPECT_EQ(matrixRes.GetValue(1, 0), -8);
  EXPECT_EQ(matrixRes.GetValue(1, 1), -10);
  EXPECT_EQ(matrixRes.GetValue(1, 2), -12);
  EXPECT_EQ(matrixRes.GetValue(2, 0), -14);
  EXPECT_EQ(matrixRes.GetValue(2, 1), -16);
  EXPECT_EQ(matrixRes.GetValue(2, 2), -18);
}

TEST(OperatorSub, TEST_2) {
  Matrix matrix1(3, 3);
  Matrix matrix2(3, 2);
  matrix1.InitializerMatrix();
  matrix2.InitializerMatrix();

  EXPECT_THROW({ matrix1.operator-(matrix2); }, std::invalid_argument);
}

// Operator(*):

TEST(OperatorMul, TEST_1) {
  Matrix matrix1(3, 3);
  Matrix matrix2(3, 3);
  Matrix matrixRes(3, 3);
  matrix1.InitializerMatrix();
  matrix2.InitializerMatrix();

  matrixRes = matrix1 * matrix2;

  EXPECT_EQ(matrixRes.GetValue(0, 0), 30);
  EXPECT_EQ(matrixRes.GetValue(0, 1), 36);
  EXPECT_EQ(matrixRes.GetValue(0, 2), 42);
  EXPECT_EQ(matrixRes.GetValue(1, 0), 66);
  EXPECT_EQ(matrixRes.GetValue(1, 1), 81);
  EXPECT_EQ(matrixRes.GetValue(1, 2), 96);
  EXPECT_EQ(matrixRes.GetValue(2, 0), 102);
  EXPECT_EQ(matrixRes.GetValue(2, 1), 126);
  EXPECT_EQ(matrixRes.GetValue(2, 2), 150);
}

TEST(OperatorMul, TEST_2) {
  Matrix matrix1(3, 3);
  Matrix matrix2(3, 2);
  Matrix matrixRes(3, 2);
  matrix1.InitializerMatrix();

  matrix2.SetValue(0, 0, 1.0);
  matrix2.SetValue(0, 1, 2.0);
  matrix2.SetValue(1, 0, 3.0);
  matrix2.SetValue(1, 1, 4.0);
  matrix2.SetValue(2, 0, 5.0);
  matrix2.SetValue(2, 1, 6.0);

  matrixRes = matrix1 * matrix2;

  EXPECT_EQ(matrixRes.GetValue(0, 0), 22.0);
  EXPECT_EQ(matrixRes.GetValue(0, 1), 28.0);
  EXPECT_EQ(matrixRes.GetValue(1, 0), 49.0);
  EXPECT_EQ(matrixRes.GetValue(1, 1), 64.0);
  EXPECT_EQ(matrixRes.GetValue(2, 0), 76.0);
  EXPECT_EQ(matrixRes.GetValue(2, 1), 100.0);
}

TEST(OperatorMul, TEST_3) {
  Matrix matrix1(3, 3);
  Matrix matrix2(4, 3);
  matrix1.InitializerMatrix();
  matrix2.InitializerMatrix();

  EXPECT_THROW({ matrix1.operator*(matrix2); }, std::invalid_argument);
}

// Operator(==):

TEST(OperatorEqEq, TEST_1) {
  Matrix matrix1(3, 3);
  Matrix matrix2(3, 3);
  matrix1.InitializerMatrix();
  matrix2.InitializerMatrix();

  bool res = (matrix1 == matrix2);

  EXPECT_EQ(res, 1);
}

TEST(OperatorEqEq, TEST_2) {
  Matrix matrix1(3, 3);
  Matrix matrix2(3, 3);
  matrix1.InitializerMatrix();
  matrix2.InitializerMatrix2();

  bool res = (matrix1 == matrix2);

  EXPECT_EQ(res, 0);
}

TEST(OperatorEqEq, TEST_3) {
  Matrix matrix1(2, 3);
  Matrix matrix2(3, 3);
  matrix1.InitializerMatrix();
  matrix2.InitializerMatrix2();

  bool res = (matrix1 == matrix2);

  EXPECT_EQ(res, 0);
}

TEST(OperatorEqEq, TEST4) {
  Matrix matrix1(3, 13);
  Matrix matrix2(3, 3);
  matrix1.InitializerMatrix();
  matrix2.InitializerMatrix2();

  bool res = (matrix1 == matrix2);

  EXPECT_EQ(res, 0);
}

TEST(OperatorEqEq, TEST_5) {
  Matrix matrix1;
  Matrix matrix2;

  bool res = (matrix1 == matrix2);

  EXPECT_EQ(res, 0);
}

TEST(OperatorEqEq, TEST_6) {
  Matrix matrix1(3, 3);
  Matrix matrix2;
  matrix1.InitializerMatrix();

  bool res = (matrix1 == matrix2);

  EXPECT_EQ(res, 0);
}

TEST(OperatorEqEq, TEST_7) {
  Matrix matrix1;
  Matrix matrix2(3, 3);
  matrix2.InitializerMatrix();

  bool res = (matrix1 == matrix2);

  EXPECT_EQ(res, 0);
}

TEST(OperatorEqEq, TEST_8) {
  Matrix matrix1(3, 3);
  Matrix matrix2;
  matrix1.InitializerMatrix();

  bool res = (matrix2 == matrix1);

  EXPECT_EQ(res, 0);
}

TEST(OperatorEqEq, TEST_9) {
  Matrix matrix1;
  Matrix matrix2(3, 3);
  matrix2.InitializerMatrix();

  bool res = (matrix2 == matrix1);

  EXPECT_EQ(res, 0);
}

// Operator(=):

TEST(OperatorEq, TEST_1) {
  Matrix matrix1(3, 3);
  Matrix matrix2(3, 3);
  matrix1.InitializerMatrix();
  matrix2.InitializerMatrix2();

  matrix1 = matrix2;

  EXPECT_EQ(matrix1.GetValue(0, 0), 2);
  EXPECT_EQ(matrix1.GetValue(0, 1), 5);
  EXPECT_EQ(matrix1.GetValue(0, 2), 7);
  EXPECT_EQ(matrix1.GetValue(1, 0), 6);
  EXPECT_EQ(matrix1.GetValue(1, 1), 3);
  EXPECT_EQ(matrix1.GetValue(1, 2), 4);
  EXPECT_EQ(matrix1.GetValue(2, 0), 5);
  EXPECT_EQ(matrix1.GetValue(2, 1), -2);
  EXPECT_EQ(matrix1.GetValue(2, 2), -3);
}

TEST(OperatorEq, TEST_2) {
  Matrix matrix1(3, 3);
  Matrix matrix2(3, 3);
  matrix2.InitializerMatrix2();

  matrix1 = matrix2;

  EXPECT_EQ(matrix1.GetValue(0, 0), 2);
  EXPECT_EQ(matrix1.GetValue(0, 1), 5);
  EXPECT_EQ(matrix1.GetValue(0, 2), 7);
  EXPECT_EQ(matrix1.GetValue(1, 0), 6);
  EXPECT_EQ(matrix1.GetValue(1, 1), 3);
  EXPECT_EQ(matrix1.GetValue(1, 2), 4);
  EXPECT_EQ(matrix1.GetValue(2, 0), 5);
  EXPECT_EQ(matrix1.GetValue(2, 1), -2);
  EXPECT_EQ(matrix1.GetValue(2, 2), -3);
}

TEST(OperatorEq, TEST_3) {
  Matrix matrix1;
  Matrix matrix2;

  EXPECT_THROW({ matrix1 = matrix2; }, std::invalid_argument);
}

TEST(OperatorEq, TEST_4) {
  Matrix matrix1;
  Matrix matrix2(3, 3);
  matrix2.InitializerMatrix();

  EXPECT_THROW({ matrix1 = matrix2; }, std::invalid_argument);
}

TEST(OperatorEq, TEST_5) {
  Matrix matrix1(3, 3);
  Matrix matrix2;
  matrix1.InitializerMatrix();

  EXPECT_THROW({ matrix1 = matrix2; }, std::invalid_argument);
}

TEST(OperatorEq, TEST_6) {
  Matrix matrix1;
  Matrix matrix2(3, 3);
  matrix2.InitializerMatrix();

  EXPECT_THROW({ matrix2 = matrix1; }, std::invalid_argument);
}

TEST(OperatorEq, TEST_7) {
  Matrix matrix1(3, 3);
  Matrix matrix2;
  matrix1.InitializerMatrix();

  EXPECT_THROW({ matrix2 = matrix1; }, std::invalid_argument);
}

// Operator(+=):

TEST(OperatorSumEq, TEST_1) {
  Matrix matrix1(3, 3);
  Matrix matrix2(3, 3);
  matrix1.InitializerMatrix();
  matrix2.InitializerMatrix();

  matrix1 += matrix2;

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

TEST(OperatorSumEq, TEST_2) {
  Matrix matrix1(3, 3);
  Matrix matrix2(1, 4);
  matrix1.InitializerMatrix();
  matrix2.InitializerMatrix();

  EXPECT_THROW({ matrix1.operator+=(matrix2); }, std::invalid_argument);
}

TEST(OperatorSumEq, TEST_3) {
  Matrix matrix1(3, 3);
  Matrix matrix2(1, 3);
  matrix1.InitializerMatrix();
  matrix2.InitializerMatrix();

  EXPECT_THROW({ matrix1.operator+=(matrix2); }, std::invalid_argument);
}

TEST(OperatorSumEq, TEST_4) {
  Matrix matrix1(3, 3);
  Matrix matrix2(3, 4);
  matrix1.InitializerMatrix();
  matrix2.InitializerMatrix();

  EXPECT_THROW({ matrix1.operator+=(matrix2); }, std::invalid_argument);
}

TEST(OperatorSumEq, TEST_5) {
  Matrix matrix1;
  Matrix matrix2;

  EXPECT_THROW({ matrix1.operator+=(matrix2); }, std::invalid_argument);
}

TEST(OperatorSumEq, TEST_6) {
  Matrix matrix1;
  Matrix matrix2(3, 4);
  matrix2.InitializerMatrix();

  EXPECT_THROW({ matrix1.operator+=(matrix2); }, std::invalid_argument);
}

TEST(OperatorSumEq, TEST_7) {
  Matrix matrix1(3, 3);
  Matrix matrix2;
  matrix1.InitializerMatrix();

  EXPECT_THROW({ matrix1.operator+=(matrix2); }, std::invalid_argument);
}

// Operator(-=):

TEST(OperatorSubEq, TEST_1) {
  Matrix matrix1(3, 3);
  Matrix matrix2(3, 3);
  matrix1.InitializerMatrix();
  matrix2.InitializerMatrix();

  matrix1.operator-=(matrix2);
  matrix1.operator-=(matrix2);

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

TEST(OperatorSubEq, TEST_2) {
  Matrix matrix1(3, 3);
  Matrix matrix2(1, 4);
  matrix1.InitializerMatrix();
  matrix2.InitializerMatrix();

  EXPECT_THROW({ matrix1.operator-=(matrix2); }, std::invalid_argument);
}

TEST(OperatorSubEq, TEST_3) {
  Matrix matrix1(3, 3);
  Matrix matrix2(1, 3);
  matrix1.InitializerMatrix();
  matrix2.InitializerMatrix();

  EXPECT_THROW({ matrix1.operator-=(matrix2); }, std::invalid_argument);
}

TEST(OperatorSubEq, TEST_4) {
  Matrix matrix1(3, 3);
  Matrix matrix2(3, 4);
  matrix1.InitializerMatrix();
  matrix2.InitializerMatrix();

  EXPECT_THROW({ matrix1.operator-=(matrix2); }, std::invalid_argument);
}

TEST(OperatorSubEq, TEST_5) {
  Matrix matrix1;
  Matrix matrix2;

  EXPECT_THROW({ matrix1.operator-=(matrix2); }, std::invalid_argument);
}

TEST(OperatorSubEq, TEST_6) {
  Matrix matrix1;
  Matrix matrix2(3, 4);
  matrix2.InitializerMatrix();

  EXPECT_THROW({ matrix1.operator-=(matrix2); }, std::invalid_argument);
}

TEST(OperatorSubEq, TEST_7) {
  Matrix matrix1(3, 3);
  Matrix matrix2;
  matrix1.InitializerMatrix();

  EXPECT_THROW({ matrix1.operator-=(matrix2); }, std::invalid_argument);
}

// Operator(*=):

TEST(OperatorMulEq, TEST_1) {
  Matrix matrix1(3, 3);
  Matrix matrix2(3, 3);
  matrix1.InitializerMatrix();
  matrix2.InitializerMatrix();

  matrix1.operator*=(matrix2);

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

TEST(OperatorMulEq, TEST_2) {
  Matrix matrix1(3, 3);
  Matrix matrix2(13, 3);
  matrix1.InitializerMatrix();
  matrix2.InitializerMatrix();

  EXPECT_THROW({ matrix1.operator*=(matrix2); }, std::invalid_argument);
}

TEST(OperatorMulEq, TEST_3) {
  Matrix matrix1;
  Matrix matrix2;

  EXPECT_THROW({ matrix1.operator*=(matrix2); }, std::invalid_argument);
}

TEST(OperatorMulEq, TEST_4) {
  Matrix matrix1;
  Matrix matrix2(3, 4);
  matrix2.InitializerMatrix();

  EXPECT_THROW({ matrix1.operator*=(matrix2); }, std::invalid_argument);
}

TEST(OperatorMulEq, TEST_5) {
  Matrix matrix1(3, 3);
  Matrix matrix2;
  matrix1.InitializerMatrix();

  EXPECT_THROW({ matrix1.operator*=(matrix2); }, std::invalid_argument);
}

// Operator():

TEST(OperatorIndex, TEST_1) {
  Matrix matrix(3, 3);
  matrix.InitializerMatrix3();

  matrix(0, 0) = 10;

  EXPECT_EQ(matrix(0, 0), 10);
}

TEST(OperatorIndex, TEST_2) {
  Matrix matrix(3, 3);
  matrix.InitializerMatrix3();

  double res = matrix(0, 0) = 10;

  EXPECT_EQ(res, 10);
}

TEST(OperatorIndex, TEST_3) {
  Matrix matrix(3, 3);
  matrix.InitializerMatrix3();

  matrix(0, 0) = 10;
  double res = matrix(0, 0) * 2;

  EXPECT_EQ(res, 20);
}

TEST(OperatorIndex, TEST_4) {
  Matrix matrix(3, 3);
  matrix.InitializerMatrix3();

  matrix(0, 0) = 10;
  matrix(2, 2) = 12;
  double res = matrix(0, 0) * matrix(2, 2);

  EXPECT_EQ(res, 120);
}

TEST(OperatorIndex, TEST_5) {
  Matrix matrix(3, 3);
  matrix.InitializerMatrix3();

  matrix(0, 0) = 10;
  matrix(2, 2) = 12;
  matrix(1, 1) = matrix(0, 0) * matrix(2, 2);

  EXPECT_EQ(matrix(1, 1), 120);
}

TEST(OperatorIndex, TEST_6) {
  Matrix matrix(3, 3);
  matrix.InitializerMatrix3();

  EXPECT_THROW({ matrix(3, 3) = 10; }, std::out_of_range);
}

TEST(OperatorIndex, TEST_7) {
  Matrix matrix(1, 3);
  matrix.InitializerMatrix3();

  EXPECT_THROW({ matrix(3, 3) = 10; }, std::out_of_range);
}

TEST(OperatorIndex, TEST_8) {
  Matrix matrix(3, 1);
  matrix.InitializerMatrix3();

  EXPECT_THROW({ matrix(3, 3) = 10; }, std::out_of_range);
}

#endif  // TESTS_OPERATORS_CPP