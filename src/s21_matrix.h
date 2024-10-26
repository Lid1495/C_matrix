#ifndef S21_MATRIX
#define S21_MATRIX

/*для всех функций, кроме s21_eq_matrix*/
#define OK 0
#define INCORRECT 1
#define CALC_ERROR 2

/* для s21_eq_matrix */
#define SUCCESS 1
#define FAILURE 0

/* для сравнения 7 знаков после запятой */
#define EPS 1e-7

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;
} matrix_t;

int s21_create_matrix(int rows, int columns, matrix_t *result);
void s21_remove_matrix(matrix_t *A);
int s21_eq_matrix(matrix_t *A, matrix_t *B);
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_mult_number(matrix_t *A, double number, matrix_t *result);
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_transpose(matrix_t *A, matrix_t *result);
int s21_determinant(matrix_t *A, double *result);
int s21_calc_complements(matrix_t *A, matrix_t *result);
int s21_inverse_matrix(matrix_t *A, matrix_t *result);

/* Дополнительные функции*/

int is_matrix_exist(matrix_t *A);
matrix_t find_matrix_for_minor(matrix_t *A, int crossed_row, int crossed_col);
void swap(int *a, int *b);
int factorial(int a);
int sign_by_even_or_odd(const int mass[], int len);
matrix_t find_all_column_combinations_for_determinant(int count_elem_to_swap);
void heapPermutation(int *a, int size, int n, matrix_t *result, int *index);
void print_matrix(matrix_t *result);

#endif  // S21_MATRIX
