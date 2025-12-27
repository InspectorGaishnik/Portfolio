#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define SUCCESS 1
#define FAILURE 0
#define INCORRECT_MATRIX 1
#define CALCULATION_ERROR 2
#define OK 0
#define EPS 1e-7  // 0.0000001

typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;
} matrix_t;

int danya_get_minor(matrix_t *A, int row, int col, matrix_t *minor);
int danya_create_matrix(int rows, int columns, matrix_t *result);
void danya_remove_matrix(matrix_t *A);
int danya_eq_matrix(matrix_t *A, matrix_t *B);
int danya_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int danya_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int danya_mult_number(matrix_t *A, double number, matrix_t *result);
int danya_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int danya_transpose(matrix_t *A, matrix_t *result);
int danya_calc_complements(matrix_t *A, matrix_t *result);
int danya_determinant(matrix_t *A, double *result);
int danya_inverse_matrix(matrix_t *A, matrix_t *result);
