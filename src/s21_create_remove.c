#include "s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int key = OK;
  if (rows <= 0 || columns <= 0 || result == NULL) {
    key = INCORRECT;
  } else {
    result->columns = columns;
    result->rows = rows;
    result->matrix = malloc(result->rows * sizeof(double *));
    if (result->matrix == NULL) {
      key = INCORRECT;
    } else {
      for (int i = 0; i < result->rows; i++) {
        result->matrix[i] = malloc(result->columns * sizeof(double));
        if (result->matrix[i] == NULL) {
          key = INCORRECT;
          break;
        }
      }
    }

    for (int i = 0; i < result->rows; i++) {
      for (int j = 0; j < result->columns; j++) {
        result->matrix[i][j] = 0;
      }
    }
  }

  return key;
}

void s21_remove_matrix(matrix_t *A) {
  if (A != NULL && A->matrix != NULL) {
    for (int i = 0; i < A->rows; i++) {
      free(A->matrix[i]);
    }
    free(A->matrix);
    A->rows = 0;
    A->columns = 0;
    A->matrix = NULL;
  }
}

int is_matrix_exist(matrix_t *A) {
  int key = OK;
  if (A == NULL || A->columns <= 0 || A->rows <= 0 || A->matrix == NULL) {
    key = INCORRECT;
  }
  return key;
}