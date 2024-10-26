#include "s21_matrix.h"

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int key = OK;
  if (is_matrix_exist(A) != OK || result == NULL) {
    return INCORRECT;
  } else {
    if (A->rows == A->columns) {
      s21_create_matrix(A->rows, A->columns, result);
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          double det = 0;
          matrix_t matrix_for_minor = find_matrix_for_minor(A, i, j);
          s21_determinant(&matrix_for_minor, &det);
          result->matrix[i][j] = pow(-1, i + j) * det;
          s21_remove_matrix(&matrix_for_minor);
        }
      }
    } else {
      key = CALC_ERROR;
    }
  }
  return key;
}

matrix_t find_matrix_for_minor(matrix_t *A, int crossed_row, int crossed_col) {
  matrix_t matr_for_minor = {NULL, 0, 0};
  if (A->columns == 1 && A->rows == 1) {
    s21_create_matrix(A->rows, A->columns, &matr_for_minor);
    matr_for_minor.matrix[0][0] = 1;
  } else {
    s21_create_matrix(A->rows - 1, A->columns - 1, &matr_for_minor);
    int k = 0;
    int l = 0;
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        if (i != crossed_row && j != crossed_col) {
          matr_for_minor.matrix[k][l] = A->matrix[i][j];
          l++;
          if (l == matr_for_minor.columns) {
            l = 0;
            k++;
          }
        }
      }
    }
  }
  return matr_for_minor;
}