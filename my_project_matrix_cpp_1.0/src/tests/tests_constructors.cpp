#ifndef TESTS_CONSTRUCTORS_CPP
#define TESTS_CONSTRUCTORS_CPP

#include <gtest/gtest.h>

#include "../s21_matrix_oop.h"

// S21Matrix():

TEST(S21Matrix_default, TEST_1) {
  S21Matrix matrix;

  EXPECT_EQ(matrix.GetRowsValue(), 0);
  EXPECT_EQ(matrix.GetColsValue(), 0);
}

// S21Matrix(int rows, int cols):

TEST(S21Matrix_rows_cols, TEST_1) {
  S21Matrix matrix(3, 3);

  EXPECT_EQ(matrix.GetRowsValue(), 3);
  EXPECT_EQ(matrix.GetColsValue(), 3);
}

TEST(S21Matrix_rows_cols, TEST_2) {
  EXPECT_THROW({ S21Matrix matrix(-3, -3); }, std::invalid_argument);
  ;
}

// S21Matrix(const S21Matrix& other):

TEST(S21Matrix_COPY, TEST_1) {
  S21Matrix matrix1(3, 3);
  matrix1.InitializerMatrix();
  S21Matrix matrix2(matrix1);

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

// S21Matrix(S21Matrix&& other):

TEST(S21Matrix_transfer, TEST_1) {
  S21Matrix matrix1(3, 3);
  matrix1.InitializerMatrix();
  S21Matrix matrix2(matrix1.Move());

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