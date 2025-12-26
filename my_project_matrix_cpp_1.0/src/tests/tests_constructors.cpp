#ifndef TESTS_CONSTRUCTORS_CPP
#define TESTS_CONSTRUCTORS_CPP

#include <gtest/gtest.h>

#include "../matrix_oop.h"

// Matrix():

TEST(Matrix_default, TEST_1) {
  Matrix matrix;

  EXPECT_EQ(matrix.GetRowsValue(), 0);
  EXPECT_EQ(matrix.GetColsValue(), 0);
}

// Matrix(int rows, int cols):

TEST(Matrix_rows_cols, TEST_1) {
  Matrix matrix(3, 3);

  EXPECT_EQ(matrix.GetRowsValue(), 3);
  EXPECT_EQ(matrix.GetColsValue(), 3);
}

TEST(Matrix_rows_cols, TEST_2) {
  EXPECT_THROW({ Matrix matrix(-3, -3); }, std::invalid_argument);
  ;
}

// Matrix(const Matrix& other):

TEST(Matrix_COPY, TEST_1) {
  Matrix matrix1(3, 3);
  matrix1.InitializerMatrix();
  Matrix matrix2(matrix1);

  EXPECT_EQ(matrix2.GetValue(0, 0), 1);
  EXPECT_EQ(matrix2.GetValue(0, 1), 2);
  EXPECT_EQ(matrix2.GetValue(0, 2), 3);
  EXPECT_EQ(matrix2.GetValue(1, 0), 4);
  EXPECT_EQ(matrix2.GetValue(1, 1), 5);
  EXPECT_EQ(matrix2.GetValue(1, 2), 6);
  EXPECT_EQ(matrix2.GetValue(2, 0), 7);
  EXPECT_EQ(matrix2.GetValue(2, 1), 8);
  EXPECT_EQ(matrix2.GetValue(2, 2), 9);
}

// Matrix(Matrix&& other):

TEST(Matrix_transfer, TEST_1) {
  Matrix matrix1(3, 3);
  matrix1.InitializerMatrix();
  Matrix matrix2(matrix1.Move());

  EXPECT_EQ(matrix2.GetValue(0, 0), 1);
  EXPECT_EQ(matrix2.GetValue(0, 1), 2);
  EXPECT_EQ(matrix2.GetValue(0, 2), 3);
  EXPECT_EQ(matrix2.GetValue(1, 0), 4);
  EXPECT_EQ(matrix2.GetValue(1, 1), 5);
  EXPECT_EQ(matrix2.GetValue(1, 2), 6);
  EXPECT_EQ(matrix2.GetValue(2, 0), 7);
  EXPECT_EQ(matrix2.GetValue(2, 1), 8);
  EXPECT_EQ(matrix2.GetValue(2, 2), 9);
}

#endif  // TESTS_CONSTRUCTORS_CPP