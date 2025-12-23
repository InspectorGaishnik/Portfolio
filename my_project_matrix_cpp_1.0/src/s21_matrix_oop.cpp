#include "s21_matrix_oop.h"

std::ostream& operator<<(std::ostream& os, const S21Matrix& other) {
  for (int i = 0; i < other.rows_; i++) {
    for (int j = 0; j < other.cols_; j++) {
      os << other.matrix_[i][j] << "\t";
    }
    os << std::endl << std::endl;
  }
  return os;
}

S21Matrix::S21Matrix() : rows_(0), cols_(0), matrix_(nullptr) {}

S21Matrix::S21Matrix(int rows, int cols) {
  if (rows <= 0 || cols <= 0)
    throw std::invalid_argument(
        "Error (S21Matrix(int rows, int cols)): rows (matrix_) <= 0 || cols "
        "(matrix_) <= 0 ");

  rows_ = rows;
  cols_ = cols;
  matrix_ = new double*[rows];
  for (int i = 0; i < rows; i++) {
    matrix_[i] = new double[cols];
  }
  InitializerMatrix3();
}

S21Matrix::S21Matrix(const S21Matrix& other) {
  matrix_ = new double*[other.rows_];
  for (int i = 0; i < other.rows_; i++) {
    matrix_[i] = new double[other.cols_];
  }
  for (int i = 0; i < other.rows_; i++) {
    for (int j = 0; j < other.cols_; j++) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
  rows_ = other.rows_;
  cols_ = other.cols_;
}

S21Matrix::S21Matrix(S21Matrix&& other) noexcept(true)
    : rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_) {
  other.matrix_ = nullptr;
  other.rows_ = 0;
  other.cols_ = 0;
}

S21Matrix::~S21Matrix() noexcept(true) {
  if (matrix_ != nullptr) {
    for (int i = 0; i < rows_; i++) {
      delete[] matrix_[i];
      matrix_[i] = nullptr;
    }
    delete[] matrix_;
    matrix_ = nullptr;
  }
}

bool S21Matrix::EqMatrix(const S21Matrix& other) {
  bool ErrorCode = SUCCESS_EQ;
  if (rows_ != other.rows_ || cols_ != other.cols_)
    ErrorCode = ERROR_EQ;
  else if (matrix_ == nullptr || other.matrix_ == nullptr)
    ErrorCode = ERROR_EQ;
  else {
    for (int i = 0; i < other.rows_; i++) {
      for (int j = 0; j < other.cols_; j++) {
        if (matrix_[i][j] != other.matrix_[i][j]) {
          return ERROR_EQ;
        }
      }
    }
  }

  return ErrorCode;
}

void S21Matrix::SumMatrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_)
    throw std::invalid_argument(
        "Error (SumMatrix): rows_(matrix_) != other.rows_(other.matrix) || \
                                             cols_(matrix_) != other.cols_(other.matrix)");
  else if (matrix_ == nullptr || other.matrix_ == nullptr)
    throw std::invalid_argument(
        "Error (SumMatrix): matrix_ || other.matrix_ = nullptr");
  else {
    for (int i = 0; i < other.rows_; i++) {
      for (int j = 0; j < other.cols_; j++) {
        matrix_[i][j] += other.matrix_[i][j];
      }
    }
  }
  return;
}

void S21Matrix::SubMatrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_)
    throw std::invalid_argument(
        "Error (SubMatrix): rows_(matrix_) != other.rows_(other.matrix)");
  else if (matrix_ == nullptr || other.matrix_ == nullptr)
    throw std::invalid_argument(
        "Error (SubMatrix): matrix_ || other.matrix_ = nullptr");
  else {
    for (int i = 0; i < other.rows_; i++) {
      for (int j = 0; j < other.cols_; j++) {
        matrix_[i][j] -= other.matrix_[i][j];
      }
    }
  }
  return;
}

void S21Matrix::MulNumber(const double num) {
  if (matrix_ == nullptr)
    throw std::invalid_argument("Error (MulNumber): matrix_ = nullptr");
  else {
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        matrix_[i][j] *= num;
      }
    }
  }
  return;
}

void S21Matrix::MulMatrix(const S21Matrix& other) {
  if (cols_ != other.rows_) {
    throw std::invalid_argument(
        "Error (MulMatrix): cols_(matrix_) != other.rows_(other.matrix_)");
  }
  S21Matrix temp(rows_, other.cols_);
  temp.InitializerMatrix3();
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < other.cols_; j++) {
      for (int k = 0; k < rows_; k++) {
        temp.matrix_[i][j] += (matrix_[i][k] * other.matrix_[k][j]);
      }
    }
  }
  *this = temp;
}

S21Matrix S21Matrix::Transpose() {
  S21Matrix temp(rows_, cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      temp.matrix_[i][j] = matrix_[j][i];
    }
  }

  return temp;
}

S21Matrix S21Matrix::GetMinor(int ExcludedRows, int ExcludedCols) {
  S21Matrix minor(rows_ - 1, cols_ - 1);

  int minor_row = 0;
  for (int i = 0; i < rows_; i++) {
    if (i == ExcludedRows) continue;

    int minor_col = 0;
    for (int j = 0; j < cols_; j++) {
      if (j == ExcludedCols) continue;
      minor.matrix_[minor_row][minor_col] = matrix_[i][j];
      minor_col++;
    }
    minor_row++;
  }
  return minor;
}

double S21Matrix::Determinant() {
  double det = 0;
  if (rows_ != cols_)
    throw std::invalid_argument(
        "Error (Determinant): rows_(matrix) != cols_(matrix)");
  else if (rows_ == 1)
    det = matrix_[0][0];
  else if (rows_ == 2)
    det = (matrix_[0][0] * matrix_[1][1]) - (matrix_[0][1] * matrix_[1][0]);
  else {
    for (int i = 0; i < cols_; i++) {
      double sign = (i % 2 == 0) ? 1 : -1;
      S21Matrix minor = GetMinor(0, i);
      det += sign * matrix_[0][i] * minor.Determinant();
    }
  }
  return det;
}

S21Matrix S21Matrix::CalcComplements() {
  S21Matrix MatrixComplement(rows_, cols_);
  if (rows_ != cols_)
    throw std::invalid_argument(
        "Error (CalcComplements): rows_(matrix) != cols_(matrix)");
  else if (rows_ == 1)
    MatrixComplement.matrix_[0][0] = matrix_[0][0];
  else {
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        S21Matrix minor = GetMinor(i, j);
        double sign = ((i + j) % 2 == 0) ? 1 : -1;
        MatrixComplement.matrix_[i][j] = sign * minor.Determinant();
      }
    }
  }

  return MatrixComplement;
}

S21Matrix S21Matrix::InverseMatrix() {
  int det = Determinant();

  if (det == 0)
    throw std::invalid_argument(
        "Error (InverseMatrix): Determinant(matrix) = 0");

  S21Matrix temp = CalcComplements();
  S21Matrix tempRes = temp.Transpose();
  tempRes.MulNumber(1 / det);

  return tempRes;
}

S21Matrix S21Matrix::operator+(const S21Matrix& other) {
  if (rows_ != other.cols_)
    throw std::invalid_argument(
        "Error (operator+): rows_(matrix) != other.cols_(other.matrix)");

  S21Matrix temp(rows_, cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      temp.matrix_[i][j] = matrix_[i][j] + other.matrix_[i][j];
    }
  }
  return temp;
}

S21Matrix S21Matrix::operator-(const S21Matrix& other) {
  if (rows_ != other.cols_)
    throw std::invalid_argument(
        "Error (operator-): rows_(matrix) != other.cols_(other.matrix)");

  S21Matrix temp(rows_, cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      temp.matrix_[i][j] = matrix_[i][j] - other.matrix_[i][j];
    }
  }
  return temp;
}

S21Matrix S21Matrix::operator*(const S21Matrix& other) {
  if (cols_ != other.rows_)
    throw std::invalid_argument(
        "Error (operator*): cols_(matrix_) != other.rows_(other.matrix_)");

  S21Matrix temp(rows_, other.cols_);
  temp.InitializerMatrix3();
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < other.cols_; j++) {
      for (int k = 0; k < rows_; k++) {
        temp.matrix_[i][j] += (matrix_[i][k] * other.matrix_[k][j]);
      }
    }
  }

  return temp;
}

bool S21Matrix::operator==(const S21Matrix& other) const {
  bool ErrorCode = SUCCESS_EQ;
  if (rows_ != other.rows_ || cols_ != other.cols_)
    ErrorCode = ERROR_EQ;
  else if (matrix_ == nullptr || other.matrix_ == nullptr)
    ErrorCode = ERROR_EQ;
  else {
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        if (matrix_[i][j] != other.matrix_[i][j]) {
          return ERROR_EQ;
        }
      }
    }
  }

  return ErrorCode;
}

S21Matrix& S21Matrix::operator=(const S21Matrix& other) {
  if (matrix_ == nullptr || other.matrix_ == nullptr)
    throw std::invalid_argument(
        "Error (operator=): matrix_ || other.matrix_ = nullptr");

  if (rows_ > 0 || cols_ > 0) this->~S21Matrix();

  rows_ = other.rows_;
  cols_ = other.cols_;

  matrix_ = new double*[other.rows_];
  for (int i = 0; i < other.rows_; i++) {
    matrix_[i] = new double[other.cols_];
  }

  for (int i = 0; i < other.rows_; i++) {
    for (int j = 0; j < other.cols_; j++) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
  return *this;
}

S21Matrix& S21Matrix::operator+=(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_)
    throw std::invalid_argument(
        "Error (operator+=): rows_(matrix_) != other.rows_(other.matrix) || \
                                             cols_(matrix_) != other.cols_(other.matrix)");
  else if (matrix_ == nullptr || other.matrix_ == nullptr)
    throw std::invalid_argument(
        "Error (operator+=): matrix_ || other.matrix_ = nullptr");
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] += other.matrix_[i][j];
    }
  }
  return *this;
}

S21Matrix& S21Matrix::operator-=(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_)
    throw std::invalid_argument(
        "Error (operator-=): rows_(matrix_) != other.rows_(other.matrix) || \
                                             cols_(matrix_) != other.cols_(other.matrix)");
  else if (matrix_ == nullptr || other.matrix_ == nullptr)
    throw std::invalid_argument(
        "Error (operator-=): matrix_ || other.matrix_ = nullptr");
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] -= other.matrix_[i][j];
    }
  }
  return *this;
}

S21Matrix& S21Matrix::operator*=(const S21Matrix& other) {
  if (cols_ != other.rows_)
    throw std::invalid_argument(
        "Error (operator*=): cols_(matrix_) != other.rows_(other.matrix_)");
  else if (matrix_ == nullptr || other.matrix_ == nullptr)
    throw std::invalid_argument(
        "Error (operator*=): matrix_ || other.matrix_ = nullptr");
  S21Matrix temp(rows_, other.cols_);
  temp.InitializerMatrix3();
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < other.cols_; j++) {
      for (int k = 0; k < rows_; k++) {
        temp.matrix_[i][j] += (matrix_[i][k] * other.matrix_[k][j]);
      }
    }
  }
  *this = temp;

  return *this;
}

double& S21Matrix::operator()(int i, int j) {
  if (i >= rows_ || j >= cols_)
    throw std::out_of_range(
        "Error (operator()): i >= rows_ || j >= cols_. The index is outside "
        "the matrix.");
  else if (matrix_ == nullptr && matrix_[i] == nullptr)
    throw std::invalid_argument(
        "Error (operator()): matrix_ != nullptr && matrix_[i] != nullptr");

  return matrix_[i][j];
}

S21Matrix S21Matrix::Move() { return static_cast<S21Matrix&&>(*this); }

double S21Matrix::GetValue(int i, int j) {
  if (matrix_ == nullptr && matrix_[i] == nullptr)
    throw std::invalid_argument(
        "Error (GetValue): matrix_ != nullptr && matrix_[i] != nullptr");
  else if (i >= rows_ || j >= cols_)
    throw std::out_of_range(
        "Error (GetValue): i >= rows_ || j >= cols_. The index is outside "
        "the matrix.");
  else
    return matrix_[i][j];
}

int S21Matrix::GetRowsValue() { return rows_; }

int S21Matrix::GetColsValue() { return cols_; }

void S21Matrix::SetValue(int i, int j, double num) {
  if (matrix_ == nullptr && matrix_[i] == nullptr)
    throw std::invalid_argument(
        "Error (SetValue): matrix_ != nullptr && matrix_[i] != nullptr");
  else if (i >= rows_ || j >= cols_)
    throw std::out_of_range(
        "Error (SetValue): i >= rows_ || j >= cols_. The index is outside "
        "the matrix.");
  else
    matrix_[i][j] = num;
}

void S21Matrix::InitializerMatrix() {
  if (rows_ <= 0 || cols_ <= 0)
    throw std::invalid_argument(
        "Error (InitializerMatrix): rows_ <= 0 || cols_ <= 0");

  int k = 1;
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = k++;
    }
  }
}

void S21Matrix::InitializerMatrix2() {
  if (rows_ <= 0 || cols_ <= 0)
    throw std::invalid_argument(
        "Error (InitializerMatrix2): rows_ <= 0 || cols_ <= 0");

  matrix_[0][0] = 2;
  matrix_[0][1] = 5;
  matrix_[0][2] = 7;

  matrix_[1][0] = 6;
  matrix_[1][1] = 3;
  matrix_[1][2] = 4;

  matrix_[2][0] = 5;
  matrix_[2][1] = -2;
  matrix_[2][2] = -3;

  // matrix_[0][0] = 5;
  // matrix_[0][1] = 2;

  // matrix_[1][0] = 3;
  // matrix_[1][1] = 1;
}

void S21Matrix::InitializerMatrix3() {
  if (rows_ <= 0 || cols_ <= 0)
    throw std::invalid_argument(
        "Error (InitializerMatrix3): rows_ <= 0 || cols_ <= 0");

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = 0;
    }
  }
}

void PrintMatrix(S21Matrix& other);

std::ostream& operator<<(std::ostream& os, const S21Matrix& other);