#include "danya_matrix.h"

int danya_get_minor(matrix_t *A, int row, int col, matrix_t *minor) {
  int status = 0;

  if (A->rows <= 0)
    status = INCORRECT_MATRIX;
  else {
    if (A->rows == 1) {
      int status = danya_create_matrix(A->rows, A->columns, minor);
      if (status != 0) status = INCORRECT_MATRIX;
    } else {
      int status = danya_create_matrix(A->rows - 1, A->columns - 1, minor);
      if (status != 0)
        status = INCORRECT_MATRIX;

      else {
        int minor_i = 0;
        for (int i = 0; i < A->rows; i++) {
          if (i == row) continue;

          int minor_j = 0;
          for (int j = 0; j < A->columns; j++) {
            if (j == col) continue;

            minor->matrix[minor_i][minor_j] = A->matrix[i][j];
            minor_j++;
          }
          minor_i++;
        }
      }
    }
  }

  return status;
}

int danya_create_matrix(int rows, int columns, matrix_t *result) {
  int status = OK;

  if (rows <= 0 || columns <= 0 || result == NULL)
    status = INCORRECT_MATRIX;
  else {
    result->matrix = (double **)calloc(rows, sizeof(double *));
    if (result->matrix == NULL)
      status = INCORRECT_MATRIX;
    else {
      for (int i = 0; i < rows; i++) {
        result->matrix[i] = (double *)calloc(columns, sizeof(double));
        if (result->matrix[i] == NULL) {
          for (int j = 0; j < i; j++) {
            free(result->matrix[j]);
          }
          free(result->matrix);
          result->matrix = NULL;
          status = INCORRECT_MATRIX;
        } else {
          result->rows = rows;
          result->columns = columns;
        }
      }
    }
  }

  return status;
}

void danya_remove_matrix(matrix_t *A) {
  if (A != NULL && A->matrix != NULL) {
    for (int i = 0; i < A->rows; i++) {
      free(A->matrix[i]);
    }
    free(A->matrix);
    A->matrix = NULL;
    A->rows = 0;
    A->columns = 0;
  }
}

int danya_eq_matrix(matrix_t *A, matrix_t *B) {
  int status = SUCCESS;

  if (A == NULL || B == NULL || A->matrix == NULL || B->matrix == NULL)
    status = FAILURE;
  else if (A->rows != B->rows || A->columns != B->columns)
    status = FAILURE;
  else
    for (int i = 0; i < A->rows; i++)
      for (int j = 0; j < A->columns; j++)
        if (fabs(A->matrix[i][j] - B->matrix[i][j]) > EPS) status = FAILURE;

  return status;
}

int danya_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int status = 0;

  if (A == NULL || B == NULL || result == NULL)
    status = INCORRECT_MATRIX;
  else if (A->matrix == NULL || B->matrix == NULL || A->rows <= 0 ||
           A->columns <= 0 || B->rows <= 0 || B->columns <= 0)
    status = INCORRECT_MATRIX;
  else if (A->rows != B->rows || A->columns != B->columns)
    status = CALCULATION_ERROR;
  else if (danya_create_matrix(A->rows, A->columns, result) != 0)
    status = INCORRECT_MATRIX;
  else
    for (int i = 0; i < A->rows; i++)
      for (int j = 0; j < A->columns; j++)
        result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];

  return status;
}

int danya_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int status = 0;

  if (A == NULL || B == NULL || result == NULL)
    status = INCORRECT_MATRIX;
  else if (A->matrix == NULL || B->matrix == NULL || A->rows <= 0 ||
           A->columns <= 0 || B->rows <= 0 || B->columns <= 0)
    status = INCORRECT_MATRIX;
  else if (A->rows != B->rows || A->columns != B->columns)
    status = CALCULATION_ERROR;
  else if (danya_create_matrix(A->rows, A->columns, result) != 0)
    status = INCORRECT_MATRIX;
  else
    for (int i = 0; i < A->rows; i++)
      for (int j = 0; j < A->columns; j++)
        result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];

  return status;
}

int danya_mult_number(matrix_t *A, double number, matrix_t *result) {
  int status = 0;

  if (A == NULL || result == NULL)
    status = INCORRECT_MATRIX;
  else if (A->matrix == NULL || A->rows <= 0 || A->columns <= 0)
    status = INCORRECT_MATRIX;
  else if (danya_create_matrix(A->rows, A->columns, result) != 0)
    status = INCORRECT_MATRIX;
  else
    for (int i = 0; i < A->rows; i++)
      for (int j = 0; j < A->columns; j++)
        if (A->matrix[i][j] == -0)
          result->matrix[i][j] = 0;
        else
          result->matrix[i][j] = A->matrix[i][j] * number;

  return status;
}

int danya_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int status = 0;

  if (A == NULL || B == NULL || result == NULL)
    status = INCORRECT_MATRIX;
  else if (A->matrix == NULL || B->matrix == NULL || A->rows <= 0 ||
           A->columns <= 0 || B->rows <= 0 || B->columns <= 0)
    status = INCORRECT_MATRIX;
  else if (A->columns != B->rows)
    status = CALCULATION_ERROR;
  else if (danya_create_matrix(A->rows, B->columns, result) != 0)
    status = INCORRECT_MATRIX;
  else {
    for (int i = 0; i < A->rows; i++)
      for (int j = 0; j < B->columns; j++) {
        result->matrix[i][j] = 0.0;
        for (int k = 0; k < A->columns; k++)
          result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
      }
  }

  return status;
}

int danya_transpose(matrix_t *A, matrix_t *result) {
  int status = 0;

  if (A == NULL || result == NULL)
    status = INCORRECT_MATRIX;
  else if (A->rows <= 0 || A->columns <= 0 || A->matrix == NULL)
    status = INCORRECT_MATRIX;
  else if (danya_create_matrix(A->columns, A->rows, result) != 0)
    status = INCORRECT_MATRIX;
  else
    for (int i = 0; i < A->rows; i++)
      for (int j = 0; j < A->columns; j++)
        result->matrix[j][i] = A->matrix[i][j];

  return status;
}

int danya_calc_complements(matrix_t *A, matrix_t *result) {
  int status = 0;

  if (A == NULL || result == NULL)
    status = INCORRECT_MATRIX;
  else if (A->rows <= 0 || A->columns <= 0 || A->matrix == NULL)
    status = INCORRECT_MATRIX;
  else if (A->rows != A->columns)
    status = CALCULATION_ERROR;
  else if (danya_create_matrix(A->rows, A->columns, result) != 0)
    status = INCORRECT_MATRIX;
  else
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        matrix_t minor;
        if (danya_get_minor(A, i, j, &minor) == 0) {
          double det;

          if (danya_determinant(&minor, &det) != 0) {
            danya_remove_matrix(result);
            status = INCORRECT_MATRIX;
          }

          danya_remove_matrix(&minor);
          result->matrix[i][j] = pow(-1, i + j) * det;
        } else {
          danya_remove_matrix(result);
          status = INCORRECT_MATRIX;
        }
      }
    }

  return status;
}

int danya_determinant(matrix_t *A, double *result) {
  int status = 0;

  if (A == NULL || result == NULL)
    status = INCORRECT_MATRIX;
  else if (A->rows <= 0 || A->columns <= 0 || A->matrix == NULL)
    status = INCORRECT_MATRIX;
  else if (A->rows != A->columns)
    status = CALCULATION_ERROR;
  else if (A->rows == 1) {
    *result = A->matrix[0][0];
    status = OK;
  } else if (A->rows == 2) {
    *result =
        A->matrix[0][0] * A->matrix[1][1] - A->matrix[0][1] * A->matrix[1][0];
    status = OK;
  } else {
    double det = 0.0;
    matrix_t minor;
    double minor_det;

    for (int j = 0; j < A->columns; j++) {
      if (A->matrix[0][j] == 0.0) {
        status = 0;
        continue;
      }

      if (danya_get_minor(A, 0, j, &minor) != 0) {
        status = INCORRECT_MATRIX;
      } else {
        if (danya_determinant(&minor, &minor_det) != 0)
          status = INCORRECT_MATRIX;
        else
          status = OK;
        danya_remove_matrix(&minor);

        det += A->matrix[0][j] * pow(-1, j) * minor_det;
      }
    }

    *result = det;
  }
  return status;
}

int danya_inverse_matrix(matrix_t *A, matrix_t *result) {
  int status = 0;

    matrix_t matrix_temp = {0};
    matrix_t matrix_temp2 = {0};

  if (A == NULL || result == NULL)
    status = INCORRECT_MATRIX;
  else if (A->rows <= 0 || A->columns <= 0 || A->matrix == NULL)
    status = INCORRECT_MATRIX;
  else if (A->rows != A->columns)
    status = CALCULATION_ERROR;
  else {
    double det;

    danya_determinant(A, &det);

    if (det == 0)
      status = 1;
    else if (danya_create_matrix(A->rows, A->columns, result) != 0)
      status = INCORRECT_MATRIX;
    else if (danya_calc_complements(A, &matrix_temp) != 0)
      status = INCORRECT_MATRIX;
    else if (danya_transpose(&matrix_temp, &matrix_temp2))
      status = INCORRECT_MATRIX;
    else if (danya_mult_number(&matrix_temp2, 1.0 / det, result) != 0)
      status = INCORRECT_MATRIX;
    else
      status = OK;
  }

  danya_remove_matrix(&matrix_temp);
  danya_remove_matrix(&matrix_temp2);

  return status;
}
