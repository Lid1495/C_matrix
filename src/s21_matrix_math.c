#include "s21_matrix.h"

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int key = OK;
  if (is_matrix_exist(A) != OK || is_matrix_exist(B) != OK || result == NULL) {
    return INCORRECT;
  } else {
    if (A->rows == B->rows && A->columns == B->columns) {
      s21_create_matrix(A->rows, A->columns, result);
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
        }
      }
    } else {
      key = CALC_ERROR;
    }
  }
  return key;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int key = OK;
  if (is_matrix_exist(A) != OK || is_matrix_exist(B) != OK || result == NULL) {
    return INCORRECT;
  } else {
    if (A->rows == B->rows && A->columns == B->columns) {
      s21_create_matrix(A->rows, A->columns, result);
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
        }
      }
    } else {
      key = CALC_ERROR;
    }
  }
  return key;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  if (is_matrix_exist(A) != OK || result == NULL) {
    return INCORRECT;
  } else {
    s21_create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] * number;
      }
    }
  }
  return OK;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int key = OK;
  if (is_matrix_exist(A) != OK || is_matrix_exist(B) != OK || result == NULL) {
    return INCORRECT;
  } else {
    if (A->columns == B->rows) {
      s21_create_matrix(A->rows, B->columns, result);

      for (int i = 0; i < result->rows; i++) {
        for (int j = 0; j < result->columns; j++) {
          for (int k = 0; k < A->columns; k++) {
            result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
          }
        }
      }
    } else {
      key = CALC_ERROR;
    }
  }

  return key;
}