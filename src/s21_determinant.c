#include "s21_matrix.h"

int s21_determinant(matrix_t *A, double *result) {
  int key = is_matrix_exist(A);
  if (key != OK) {
    return key;
  } else {
    *result = 0;
    if (A->columns == A->rows) {
      if (A->rows == 1) {
        *result = A->matrix[0][0];
      } else {
        int len = A->rows;
        matrix_t all_combinations =
            find_all_column_combinations_for_determinant(len);

        for (int i = 0; i < all_combinations.rows; i++) {
          int *row_of_combinations = malloc(len * sizeof(int));
          for (int k = 0; k < len; k++) {
            row_of_combinations[k] = (int)all_combinations.matrix[i][k];
          }
          int sign = 1;
          sign = sign_by_even_or_odd(row_of_combinations, len);
          free(row_of_combinations);

          double multiplier_comb = 1;
          for (int j = 0; j < all_combinations.columns; j++) {
            multiplier_comb *= A->matrix[j][(int)all_combinations.matrix[i][j]];
          }

          *result += sign * multiplier_comb;
        }
        s21_remove_matrix(&all_combinations);
      }
    } else
      key = CALC_ERROR;
  }
  return key;
}

/* генерация комбинации для j-ых множителей в определителе*/
matrix_t find_all_column_combinations_for_determinant(int count_elem_to_swap) {
  int *mass = malloc(count_elem_to_swap * sizeof(int));
  for (int k = 0; k < count_elem_to_swap; k++) {
    mass[k] = k;
  }

  matrix_t result = {NULL, 0, 0};
  int permutation_count =
      factorial(count_elem_to_swap);  // количество сочетаний
  s21_create_matrix(permutation_count, count_elem_to_swap, &result);

  int index = 0;
  heapPermutation(mass, count_elem_to_swap, count_elem_to_swap, &result,
                  &index);
  free(mass);
  return result;
}

/*метод Хипа для поиска всех неповторяющихся сочетаний*/
void heapPermutation(int *a, int size, int n, matrix_t *result, int *index) {
  if (size == 1) {
    // Сохраняем текущую перестановку в результат
    for (int i = 0; i < n; i++) {
      result->matrix[*index][i] = a[i];
    }
    (*index)++;
    return;
  }

  for (int i = 0; i < size; i++) {
    heapPermutation(a, size - 1, n, result, index);

    if (size % 2 == 1)
      swap(&a[0], &a[size - 1]);
    else
      swap(&a[i], &a[size - 1]);
  }
}

void swap(int *a, int *b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}

int factorial(int a) {
  int rez = 1;
  for (int i = 1; i <= a; i++) rez = rez * i;
  return rez;
}

/* знак слагаемого при подсчете детерминанта согласно четности количества
 * перестановок */
int sign_by_even_or_odd(const int mass[], int len) {
  int reverse_count = 0;
  for (int i = 0; i < len; ++i) {
    for (int j = i + 1; j < len; ++j) {
      if (mass[i] > mass[j]) {
        reverse_count++;
      }
    }
  }
  return (reverse_count % 2 == 0 ? 1 : -1);
}