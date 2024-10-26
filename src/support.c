#include "s21_matrix.h"

// void print_matrix(matrix_t *result);

void print_matrix(matrix_t *result) {
  printf("Вывожу матрицу:\n");
  printf("rows = %d, columns = %d\n", result->rows, result->columns);
  for (int i = 0; i < result->rows; i++) {
    for (int j = 0; j < result->columns; j++) {
      printf("%f ", result->matrix[i][j]);
    }
    printf("\n");
  }
}