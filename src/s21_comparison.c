#include "s21_matrix.h"

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  if (is_matrix_exist(A) == OK && is_matrix_exist(B) == OK &&
      (A->rows == B->rows && A->columns == B->columns)) {
    int key = SUCCESS;
    for (int i = 0; i < A->rows && key == SUCCESS; i++) {
      for (int j = 0; j < A->columns && key == SUCCESS; j++) {
        if (fabs(A->matrix[i][j] - B->matrix[i][j]) >= EPS) {
          key = FAILURE;
        }
      }
    }
    return key;
  } else
    return FAILURE;
}