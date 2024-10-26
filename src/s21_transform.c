#include "s21_matrix.h"

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  if (is_matrix_exist(A) != OK) {
    return INCORRECT;
  } else {
    int key = OK;
    double det = 0;
    s21_determinant(A, &det);
    if (det == 0 || A->rows != A->columns) {
      key = CALC_ERROR;
    } else {
      matrix_t complement_matrix = {};
      matrix_t transposed_matrix = {};
      s21_calc_complements(A, &complement_matrix);
      s21_transpose(&complement_matrix, &transposed_matrix);
      s21_remove_matrix(&complement_matrix);
      s21_mult_number(&transposed_matrix, 1 / det, result);
      s21_remove_matrix(&transposed_matrix);
    }
    return key;
  }
}

int s21_transpose(matrix_t *A, matrix_t *result) {
  int key = OK;
  if (is_matrix_exist(A) != OK) {
    return INCORRECT;
  } else {
    s21_create_matrix(A->columns, A->rows, result);
    for (int i = 0; i < result->rows; i++) {
      for (int j = 0; j < result->columns; j++) {
        result->matrix[i][j] = A->matrix[j][i];
      }
    }
  }
  return key;
}
