#include <check.h>

#include "../s21_matrix.h"

void fill_matrix_with_meanings(matrix_t *A, double start_point, double step) {
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      A->matrix[i][j] = start_point;
      start_point += step;
    }
  }
}

/* Создание матрицы */

START_TEST(s21_create_matrix_1) {
  matrix_t A = {};
  ck_assert_int_eq(s21_create_matrix(3, 3, &A), OK);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_create_matrix_2) {
  ck_assert_int_eq(s21_create_matrix(4, 4, NULL), INCORRECT);
}
END_TEST

START_TEST(s21_create_matrix_3) {
  matrix_t A = {};
  ck_assert_int_eq(s21_create_matrix(-3, 2, &A), INCORRECT);
}
END_TEST

START_TEST(s21_create_matrix_4) {
  matrix_t A = {};
  ck_assert_int_eq(s21_create_matrix(0, 6, &A), INCORRECT);
}
END_TEST

START_TEST(s21_create_matrix_5) {
  matrix_t A = {};
  ck_assert_int_eq(s21_create_matrix(-7, -4, &A), INCORRECT);
}
END_TEST

/* Удаление матрицы*/

START_TEST(s21_remove_matrix_1) {
  matrix_t A = {};
  s21_create_matrix(6, 6, &A);
  s21_remove_matrix(&A);
  ck_assert_ptr_null(A.matrix);
}
END_TEST

START_TEST(s21_remove_matrix_2) {
  matrix_t A = {};
  s21_create_matrix(1, 1, &A);
  s21_remove_matrix(&A);
  ck_assert_ptr_null(A.matrix);
}
END_TEST

START_TEST(s21_remove_matrix_3) {
  matrix_t A = {};
  s21_remove_matrix(&A);
  ck_assert_int_eq(1, 1);
}
END_TEST

/* Сравнение матриц */

START_TEST(s21_eq_matrix_1) {
  matrix_t A = {};
  matrix_t B = {};

  s21_create_matrix(6, 6, &A);
  s21_create_matrix(6, 6, &B);

  fill_matrix_with_meanings(&A, 0, 5);
  fill_matrix_with_meanings(&B, 0, 5);

  ck_assert_int_eq(s21_eq_matrix(&A, &B), SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(s21_eq_matrix_2) {
  matrix_t A = {};
  matrix_t B = {};

  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);

  fill_matrix_with_meanings(&A, 0, 1.12345678);
  fill_matrix_with_meanings(&B, 0, 1.12345679);

  ck_assert_int_eq(s21_eq_matrix(&A, &B), SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(s21_eq_matrix_3) {
  matrix_t A = {};
  matrix_t B = {};

  s21_create_matrix(4, 4, &A);
  s21_create_matrix(4, 4, &B);

  ck_assert_int_eq(s21_eq_matrix(&A, &B), SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(s21_eq_matrix_4) {
  matrix_t A = {};
  matrix_t B = {};

  s21_create_matrix(6, 3, &A);
  s21_create_matrix(2, 3, &B);

  ck_assert_int_eq(s21_eq_matrix(&A, &B), FAILURE);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(s21_eq_matrix_5) {
  matrix_t A = {};
  matrix_t B = {};

  s21_create_matrix(3, 3, &B);

  ck_assert_int_eq(s21_eq_matrix(&A, &B), FAILURE);

  s21_remove_matrix(&B);
}
END_TEST

START_TEST(s21_eq_matrix_6) {
  matrix_t A = {};
  matrix_t B = {};

  s21_create_matrix(1, 1, &A);
  s21_create_matrix(1, 1, &B);

  fill_matrix_with_meanings(&A, 5.456, 1);
  fill_matrix_with_meanings(&B, 5.456, 1);

  ck_assert_int_eq(s21_eq_matrix(&A, &B), SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(s21_eq_matrix_7) {
  matrix_t A = {};
  matrix_t B = {};

  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);

  fill_matrix_with_meanings(&A, 1, 3);
  fill_matrix_with_meanings(&B, 1, 3);
  B.matrix[2][0] = 0;

  ck_assert_int_eq(s21_eq_matrix(&A, &B), FAILURE);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

/* Сложение матриц */

START_TEST(s21_sum_matrix_1) {
  matrix_t A = {};
  matrix_t B = {};
  matrix_t result = {};
  matrix_t eq_matrix = {};

  s21_create_matrix(4, 4, &A);
  s21_create_matrix(4, 4, &B);
  s21_create_matrix(4, 4, &eq_matrix);

  fill_matrix_with_meanings(&A, 5, 1);
  fill_matrix_with_meanings(&B, 5, 1);
  fill_matrix_with_meanings(&eq_matrix, 10, 2);

  ck_assert_int_eq(s21_sum_matrix(&A, &B, &result), OK);
  ck_assert_int_eq(s21_eq_matrix(&result, &eq_matrix), SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
  s21_remove_matrix(&eq_matrix);
}
END_TEST

START_TEST(s21_sum_matrix_2) {
  matrix_t A = {};
  matrix_t B = {};
  matrix_t result = {};
  matrix_t eq_matrix = {};

  s21_create_matrix(7, 7, &A);
  s21_create_matrix(7, 7, &B);
  s21_create_matrix(7, 7, &eq_matrix);

  ck_assert_int_eq(s21_sum_matrix(&A, &B, &result), OK);
  ck_assert_int_eq(s21_eq_matrix(&result, &eq_matrix), SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
  s21_remove_matrix(&eq_matrix);
}
END_TEST

START_TEST(s21_sum_matrix_3) {
  matrix_t A = {};
  matrix_t B = {};
  matrix_t result = {};
  matrix_t eq_matrix = {};

  s21_create_matrix(4, 4, &A);
  s21_create_matrix(4, 4, &B);
  s21_create_matrix(4, 4, &eq_matrix);

  fill_matrix_with_meanings(&A, 1.66, 0.1666);
  fill_matrix_with_meanings(&B, 0, 1);
  fill_matrix_with_meanings(&eq_matrix, 1.66, 1.1666);

  ck_assert_int_eq(s21_sum_matrix(&A, &B, &result), OK);
  ck_assert_int_eq(s21_eq_matrix(&result, &eq_matrix), SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
  s21_remove_matrix(&eq_matrix);
}
END_TEST

START_TEST(s21_sum_matrix_4) {
  matrix_t A = {};
  matrix_t B = {};
  matrix_t result = {};
  matrix_t eq_matrix = {};

  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);
  s21_create_matrix(3, 3, &eq_matrix);

  A.matrix[0][0] = 3;
  A.matrix[0][1] = 8;
  A.matrix[0][2] = 4;
  A.matrix[1][0] = 0;
  A.matrix[1][1] = 13;
  A.matrix[1][2] = 888;
  A.matrix[2][0] = 67;
  A.matrix[2][1] = 0;
  A.matrix[2][2] = 11;

  B.matrix[0][0] = 0;
  B.matrix[0][1] = 887;
  B.matrix[0][2] = 1;
  B.matrix[1][0] = 9;
  B.matrix[1][1] = 87;
  B.matrix[1][2] = 45;
  B.matrix[2][0] = 76;
  B.matrix[2][1] = 55;
  B.matrix[2][2] = 1;

  eq_matrix.matrix[0][0] = 3;
  eq_matrix.matrix[0][1] = 895;
  eq_matrix.matrix[0][2] = 5;
  eq_matrix.matrix[1][0] = 9;
  eq_matrix.matrix[1][1] = 100;
  eq_matrix.matrix[1][2] = 933;
  eq_matrix.matrix[2][0] = 143;
  eq_matrix.matrix[2][1] = 55;
  eq_matrix.matrix[2][2] = 12;

  ck_assert_int_eq(s21_sum_matrix(&A, &B, &result), OK);
  ck_assert_int_eq(s21_eq_matrix(&result, &eq_matrix), SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
  s21_remove_matrix(&eq_matrix);
}
END_TEST

START_TEST(s21_sum_matrix_5) {
  matrix_t A = {};
  matrix_t B = {};

  ck_assert_int_eq(s21_sum_matrix(&A, &B, NULL), INCORRECT);
}
END_TEST

START_TEST(s21_sum_matrix_6) {
  matrix_t A = {};
  matrix_t B = {};
  matrix_t result = {};

  s21_create_matrix(7, 7, &A);
  s21_create_matrix(8, 3, &B);

  ck_assert_int_eq(s21_sum_matrix(&A, &B, &result), CALC_ERROR);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

/* Вычитание матриц*/

START_TEST(s21_sub_matrix_1) {
  matrix_t A = {};
  matrix_t B = {};
  matrix_t result = {};
  matrix_t eq_matrix = {};

  s21_create_matrix(4, 4, &A);
  s21_create_matrix(4, 4, &B);
  s21_create_matrix(4, 4, &eq_matrix);

  fill_matrix_with_meanings(&A, 1, 3);
  fill_matrix_with_meanings(&B, 1, 3);

  ck_assert_int_eq(s21_sub_matrix(&A, &B, &result), OK);
  ck_assert_int_eq(s21_eq_matrix(&result, &eq_matrix), SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
  s21_remove_matrix(&eq_matrix);
}
END_TEST

START_TEST(s21_sub_matrix_2) {
  matrix_t A = {};
  matrix_t B = {};
  matrix_t result = {};
  matrix_t eq_matrix = {};

  s21_create_matrix(5, 5, &A);
  s21_create_matrix(5, 5, &B);
  s21_create_matrix(5, 5, &eq_matrix);

  ck_assert_int_eq(s21_sub_matrix(&A, &B, &result), OK);
  ck_assert_int_eq(s21_eq_matrix(&result, &eq_matrix), SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
  s21_remove_matrix(&eq_matrix);
}
END_TEST

START_TEST(s21_sub_matrix_3) {
  matrix_t A = {};
  matrix_t B = {};
  matrix_t result = {};
  matrix_t eq_matrix = {};

  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);
  s21_create_matrix(3, 3, &eq_matrix);

  A.matrix[0][0] = 3;
  A.matrix[0][1] = 8;
  A.matrix[0][2] = 4;
  A.matrix[1][0] = 0;
  A.matrix[1][1] = 13;
  A.matrix[1][2] = 888;
  A.matrix[2][0] = 67;
  A.matrix[2][1] = 0;
  A.matrix[2][2] = 11;

  B.matrix[0][0] = 0;
  B.matrix[0][1] = 887;
  B.matrix[0][2] = 1;
  B.matrix[1][0] = 9;
  B.matrix[1][1] = 87;
  B.matrix[1][2] = 45;
  B.matrix[2][0] = 76;
  B.matrix[2][1] = 55;
  B.matrix[2][2] = 1;

  eq_matrix.matrix[0][0] = 3;
  eq_matrix.matrix[0][1] = -879;
  eq_matrix.matrix[0][2] = 3;
  eq_matrix.matrix[1][0] = -9;
  eq_matrix.matrix[1][1] = -74;
  eq_matrix.matrix[1][2] = 843;
  eq_matrix.matrix[2][0] = -9;
  eq_matrix.matrix[2][1] = -55;
  eq_matrix.matrix[2][2] = 10;

  ck_assert_int_eq(s21_sub_matrix(&A, &B, &result), OK);
  ck_assert_int_eq(s21_eq_matrix(&result, &eq_matrix), SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
  s21_remove_matrix(&eq_matrix);
}
END_TEST

START_TEST(s21_sub_matrix_4) {
  matrix_t A = {};
  matrix_t B = {};

  ck_assert_int_eq(s21_sub_matrix(&A, &B, NULL), INCORRECT);
}
END_TEST

START_TEST(s21_sub_matrix_5) {
  matrix_t A = {};
  matrix_t B = {};
  matrix_t result = {};

  s21_create_matrix(5, 5, &A);
  s21_create_matrix(3, 3, &B);

  ck_assert_int_eq(s21_sub_matrix(&A, &B, &result), CALC_ERROR);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

/* Умножение матрицы на число */

START_TEST(s21_mult_number_1) {
  matrix_t A = {};
  matrix_t result = {};
  matrix_t eq_matrix = {};
  double number = 8.5;

  s21_create_matrix(4, 4, &A);
  s21_create_matrix(4, 4, &eq_matrix);

  ck_assert_int_eq(s21_mult_number(&A, number, &result), OK);
  ck_assert_int_eq(s21_eq_matrix(&result, &eq_matrix), SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&eq_matrix);
}
END_TEST

START_TEST(s21_mult_number_2) {
  matrix_t A = {};
  matrix_t result = {};
  matrix_t eq_matrix = {};
  double number = 8.5;

  s21_create_matrix(4, 4, &A);
  s21_create_matrix(4, 4, &eq_matrix);

  fill_matrix_with_meanings(&A, 1, 1);
  fill_matrix_with_meanings(&eq_matrix, 8.5, 8.5);

  ck_assert_int_eq(s21_mult_number(&A, number, &result), OK);
  ck_assert_int_eq(s21_eq_matrix(&result, &eq_matrix), SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&eq_matrix);
}
END_TEST

START_TEST(s21_mult_number_3) {
  matrix_t A = {};
  matrix_t result = {};
  matrix_t eq_matrix = {};
  double number = 2;

  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &eq_matrix);

  A.matrix[0][0] = 0;
  A.matrix[0][1] = 15;
  A.matrix[0][2] = 3;
  A.matrix[1][0] = 4;
  A.matrix[1][1] = -10;
  A.matrix[1][2] = 86;
  A.matrix[2][0] = 3.5;
  A.matrix[2][1] = 8;
  A.matrix[2][2] = 100;

  eq_matrix.matrix[0][0] = 0;
  eq_matrix.matrix[0][1] = 30;
  eq_matrix.matrix[0][2] = 6;
  eq_matrix.matrix[1][0] = 8;
  eq_matrix.matrix[1][1] = -20;
  eq_matrix.matrix[1][2] = 172;
  eq_matrix.matrix[2][0] = 7;
  eq_matrix.matrix[2][1] = 16;
  eq_matrix.matrix[2][2] = 200;

  ck_assert_int_eq(s21_mult_number(&A, number, &result), OK);
  ck_assert_int_eq(s21_eq_matrix(&result, &eq_matrix), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&eq_matrix);
}
END_TEST

START_TEST(s21_mult_number_4) {
  matrix_t A = {};
  double number = 15;

  s21_create_matrix(5, 5, &A);
  fill_matrix_with_meanings(&A, 0, 5);

  ck_assert_int_eq(s21_mult_number(&A, number, NULL), INCORRECT);

  s21_remove_matrix(&A);
}

END_TEST

/* Перемножение матриц */

START_TEST(s21_mult_matrix_1) {
  matrix_t A = {};
  matrix_t B = {};
  matrix_t result = {};
  matrix_t eq_matrix = {};

  s21_create_matrix(4, 4, &A);
  s21_create_matrix(4, 4, &B);
  s21_create_matrix(4, 4, &eq_matrix);

  ck_assert_int_eq(s21_mult_matrix(&A, &B, &result), OK);
  ck_assert_int_eq(s21_eq_matrix(&result, &eq_matrix), SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
  s21_remove_matrix(&eq_matrix);
}
END_TEST

START_TEST(s21_mult_matrix_2) {
  matrix_t A = {};
  matrix_t B = {};
  matrix_t result = {};
  matrix_t eq_matrix = {};

  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);
  s21_create_matrix(3, 3, &eq_matrix);

  A.matrix[0][0] = 3;
  A.matrix[0][1] = 8;
  A.matrix[0][2] = 4;
  A.matrix[1][0] = 0;
  A.matrix[1][1] = 13;
  A.matrix[1][2] = 888;
  A.matrix[2][0] = 67;
  A.matrix[2][1] = 0;
  A.matrix[2][2] = 11;

  B.matrix[0][0] = 0;
  B.matrix[0][1] = 887;
  B.matrix[0][2] = 1;
  B.matrix[1][0] = 9;
  B.matrix[1][1] = 87;
  B.matrix[1][2] = 45;
  B.matrix[2][0] = 76;
  B.matrix[2][1] = 55;
  B.matrix[2][2] = 1;

  eq_matrix.matrix[0][0] = 376;
  eq_matrix.matrix[0][1] = 3577;
  eq_matrix.matrix[0][2] = 367;
  eq_matrix.matrix[1][0] = 67605;
  eq_matrix.matrix[1][1] = 49971;
  eq_matrix.matrix[1][2] = 1473;
  eq_matrix.matrix[2][0] = 836;
  eq_matrix.matrix[2][1] = 60034;
  eq_matrix.matrix[2][2] = 78;

  ck_assert_int_eq(s21_mult_matrix(&A, &B, &result), OK);
  ck_assert_int_eq(s21_eq_matrix(&result, &eq_matrix), SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
  s21_remove_matrix(&eq_matrix);
}
END_TEST

START_TEST(s21_mult_matrix_3) {
  matrix_t A = {};
  matrix_t B = {};
  matrix_t result = {};
  matrix_t eq_matrix = {};

  s21_create_matrix(1, 3, &A);
  s21_create_matrix(3, 2, &B);
  s21_create_matrix(1, 2, &eq_matrix);

  A.matrix[0][0] = 3;
  A.matrix[0][1] = 8;
  A.matrix[0][2] = 4;

  B.matrix[0][0] = 0;
  B.matrix[0][1] = 887;
  B.matrix[1][0] = 9;
  B.matrix[1][1] = 87;
  B.matrix[2][0] = 76;
  B.matrix[2][1] = 55;

  eq_matrix.matrix[0][0] = 376;
  eq_matrix.matrix[0][1] = 3577;

  ck_assert_int_eq(s21_mult_matrix(&A, &B, &result), OK);
  ck_assert_int_eq(s21_eq_matrix(&result, &eq_matrix), SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
  s21_remove_matrix(&eq_matrix);
}
END_TEST

START_TEST(s21_mult_matrix_4) {
  matrix_t A = {};
  matrix_t B = {};
  matrix_t result = {};

  s21_create_matrix(5, 2, &A);
  s21_create_matrix(3, 3, &B);

  ck_assert_int_eq(s21_mult_matrix(&A, &B, &result), CALC_ERROR);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(s21_mult_matrix_5) {
  matrix_t A = {};
  matrix_t B = {};
  matrix_t result = {};

  s21_create_matrix(5, 2, &A);

  ck_assert_int_eq(s21_mult_matrix(&A, &B, &result), INCORRECT);

  s21_remove_matrix(&A);
}
END_TEST

/* Транспонирование матрицы */

START_TEST(s21_transpose_1) {
  matrix_t A = {};
  matrix_t result = {};

  s21_create_matrix(4, 3, &A);

  ck_assert_int_eq(s21_transpose(&A, &result), OK);
  ck_assert_int_eq(result.rows, 3);
  ck_assert_int_eq(result.columns, 4);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_transpose_2) {
  matrix_t A = {};
  matrix_t result = {};

  s21_create_matrix(1, 1, &A);
  A.matrix[0][0] = 3.16;

  ck_assert_int_eq(s21_transpose(&A, &result), OK);
  ck_assert_int_eq(result.rows, 1);
  ck_assert_int_eq(result.columns, 1);
  ck_assert_int_eq(s21_eq_matrix(&result, &A), SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_transpose_3) {
  matrix_t A = {};
  matrix_t result = {};
  matrix_t eq_matrix = {};

  s21_create_matrix(3, 2, &A);
  s21_create_matrix(2, 3, &eq_matrix);
  fill_matrix_with_meanings(&A, 0, 2);

  eq_matrix.matrix[0][0] = 0, eq_matrix.matrix[0][1] = 4,
  eq_matrix.matrix[0][2] = 8, eq_matrix.matrix[1][0] = 2,
  eq_matrix.matrix[1][1] = 6, eq_matrix.matrix[1][2] = 10;

  ck_assert_int_eq(s21_transpose(&A, &result), OK);
  ck_assert_int_eq(result.rows, 2);
  ck_assert_int_eq(result.columns, 3);
  ck_assert_int_eq(s21_eq_matrix(&result, &eq_matrix), SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&eq_matrix);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_transpose_4) {
  matrix_t A = {};
  matrix_t result = {};

  ck_assert_int_eq(s21_transpose(&A, &result), INCORRECT);
}
END_TEST

/* Расчет матрицы алгебраических дополнений */

START_TEST(s21_calc_complements_1) {
  // success with task reference values
  matrix_t A = {};
  matrix_t result = {};
  matrix_t eq_matrix = {};
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &eq_matrix);

  A.matrix[0][0] = 3, A.matrix[0][1] = 8, A.matrix[0][2] = 4,
  A.matrix[1][0] = 0, A.matrix[1][1] = 13, A.matrix[1][2] = 888,
  A.matrix[2][0] = 67, A.matrix[2][1] = 0, A.matrix[2][2] = 11;

  eq_matrix.matrix[0][0] = 143, eq_matrix.matrix[0][1] = 59496,
  eq_matrix.matrix[0][2] = -871, eq_matrix.matrix[1][0] = -88,
  eq_matrix.matrix[1][1] = -235, eq_matrix.matrix[1][2] = 536,
  eq_matrix.matrix[2][0] = 7052, eq_matrix.matrix[2][1] = -2664,
  eq_matrix.matrix[2][2] = 39;

  ck_assert_int_eq(s21_calc_complements(&A, &result), OK);
  ck_assert_int_eq(s21_eq_matrix(&result, &eq_matrix), SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&eq_matrix);
}
END_TEST

START_TEST(s21_calc_complements_2) {
  matrix_t A = {};

  s21_create_matrix(4, 4, &A);

  ck_assert_int_eq(s21_calc_complements(&A, NULL), INCORRECT);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_calc_complements_3) {
  matrix_t A = {};
  matrix_t result = {};

  s21_create_matrix(4, 1, &A);
  fill_matrix_with_meanings(&A, 4, 1);

  ck_assert_int_eq(s21_calc_complements(&A, &result), CALC_ERROR);

  s21_remove_matrix(&A);
}
END_TEST

/* Детерминант (определитель) */

START_TEST(s21_determinant_1) {
  matrix_t A = {};
  double det = 0;

  s21_create_matrix(1, 1, &A);
  A.matrix[0][0] = 100;

  ck_assert_int_eq(s21_determinant(&A, &det), OK);
  ck_assert_double_eq(det, 100);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_determinant_2) {
  matrix_t A = {};
  double det = 0;

  s21_create_matrix(2, 2, &A);
  fill_matrix_with_meanings(&A, 5, 2);

  ck_assert_int_eq(s21_determinant(&A, &det), OK);
  ck_assert_double_eq(det, -8);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_determinant_3) {
  matrix_t A = {};
  double det = 0;

  s21_create_matrix(3, 3, &A);
  fill_matrix_with_meanings(&A, 1, 1);

  ck_assert_int_eq(s21_determinant(&A, &det), OK);
  ck_assert_double_eq(det, 0);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_determinant_4) {
  matrix_t A = {};
  double det = 0;

  s21_create_matrix(5, 5, &A);

  A.matrix[0][0] = 3, A.matrix[0][1] = 8, A.matrix[0][2] = 4,
  A.matrix[0][3] = 7, A.matrix[0][4] = -11,

  A.matrix[1][0] = 0, A.matrix[1][1] = 13, A.matrix[1][2] = 888,
  A.matrix[1][3] = 65, A.matrix[1][4] = -1,

  A.matrix[2][0] = 67, A.matrix[2][1] = 0, A.matrix[2][2] = 11,
  A.matrix[2][3] = 1, A.matrix[2][4] = 1,

  A.matrix[3][0] = 887, A.matrix[3][1] = -1, A.matrix[3][2] = 9,
  A.matrix[3][3] = 6, A.matrix[3][4] = 123,

  A.matrix[4][0] = 87, A.matrix[4][1] = 45, A.matrix[4][2] = 76,
  A.matrix[4][3] = 55, A.matrix[4][4] = 1;

  ck_assert_int_eq(s21_determinant(&A, &det), OK);
  ck_assert_double_eq(det, -575723841);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_determinant_5) {
  matrix_t A = {};
  double det = 0;

  ck_assert_int_eq(s21_determinant(&A, &det), INCORRECT);
}
END_TEST

START_TEST(s21_determinant_6) {
  matrix_t A = {};
  double det = 0;
  s21_create_matrix(6, 1, &A);
  fill_matrix_with_meanings(&A, 0, 2);

  ck_assert_int_eq(s21_determinant(&A, &det), CALC_ERROR);

  s21_remove_matrix(&A);
}
END_TEST

/* Расчет обратной матрицы */

START_TEST(s21_inverse_matrix_1) {
  matrix_t A = {};
  matrix_t result = {};
  matrix_t eq_matrix = {};

  s21_create_matrix(1, 1, &A);
  s21_create_matrix(1, 1, &eq_matrix);

  A.matrix[0][0] = 100;

  eq_matrix.matrix[0][0] = 0.01;

  ck_assert_int_eq(s21_inverse_matrix(&A, &result), OK);
  ck_assert_int_eq(s21_eq_matrix(&result, &eq_matrix), SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&eq_matrix);
}
END_TEST

START_TEST(s21_inverse_matrix_2) {
  // success with task reference values
  matrix_t A = {};
  matrix_t result = {};
  matrix_t eq_matrix = {};

  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &eq_matrix);

  A.matrix[0][0] = 2, A.matrix[0][1] = 5, A.matrix[0][2] = 7,
  A.matrix[1][0] = 6, A.matrix[1][1] = 3, A.matrix[1][2] = 4,
  A.matrix[2][0] = 5, A.matrix[2][1] = -2, A.matrix[2][2] = -3;

  eq_matrix.matrix[0][0] = 1, eq_matrix.matrix[0][1] = -1,
  eq_matrix.matrix[0][2] = 1, eq_matrix.matrix[1][0] = -38,
  eq_matrix.matrix[1][1] = 41, eq_matrix.matrix[1][2] = -34,
  eq_matrix.matrix[2][0] = 27, eq_matrix.matrix[2][1] = -29,
  eq_matrix.matrix[2][2] = 24;

  ck_assert_int_eq(s21_inverse_matrix(&A, &result), OK);
  ck_assert_int_eq(s21_eq_matrix(&result, &eq_matrix), SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&eq_matrix);
}
END_TEST

START_TEST(s21_inverse_matrix_3) {
  matrix_t A = {};
  matrix_t result = {};

  ck_assert_int_eq(s21_inverse_matrix(&A, &result), INCORRECT);
}
END_TEST

START_TEST(s21_inverse_matrix_4) {
  matrix_t A = {};
  matrix_t result = {};

  s21_create_matrix(3, 3, &A);
  fill_matrix_with_meanings(&A, 1, 1);

  ck_assert_int_eq(s21_inverse_matrix(&A, &result), CALC_ERROR);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_inverse_matrix_5) {
  matrix_t A = {};
  matrix_t result = {};

  s21_create_matrix(4, 2, &A);
  fill_matrix_with_meanings(&A, 0, 3);

  ck_assert_int_eq(s21_inverse_matrix(&A, &result), CALC_ERROR);

  s21_remove_matrix(&A);
}
END_TEST

/*  Создание групп тестовых случаев в разрезе функций */

Suite *s21_create_matrix_suite(void) {
  Suite *suite = suite_create("s21_create_matrix");
  TCase *tc_core = tcase_create("core_of_create_matrix");
  tcase_add_test(tc_core, s21_create_matrix_1);
  tcase_add_test(tc_core, s21_create_matrix_2);
  tcase_add_test(tc_core, s21_create_matrix_3);
  tcase_add_test(tc_core, s21_create_matrix_4);
  tcase_add_test(tc_core, s21_create_matrix_5);
  suite_add_tcase(suite, tc_core);

  return suite;
}

Suite *s21_remove_matrix_suite(void) {
  Suite *suite = suite_create("s21_remove_matrix");
  TCase *tc_core = tcase_create("core_of_remove_matrix");
  tcase_add_test(tc_core, s21_remove_matrix_1);
  tcase_add_test(tc_core, s21_remove_matrix_2);
  tcase_add_test(tc_core, s21_remove_matrix_3);
  suite_add_tcase(suite, tc_core);

  return suite;
}

Suite *s21_eq_matrix_suite(void) {
  Suite *suite = suite_create("s21_eq_matrix");
  TCase *tc_core = tcase_create("core_of_eq_matrix");
  tcase_add_test(tc_core, s21_eq_matrix_1);
  tcase_add_test(tc_core, s21_eq_matrix_2);
  tcase_add_test(tc_core, s21_eq_matrix_3);
  tcase_add_test(tc_core, s21_eq_matrix_4);
  tcase_add_test(tc_core, s21_eq_matrix_5);
  tcase_add_test(tc_core, s21_eq_matrix_6);
  tcase_add_test(tc_core, s21_eq_matrix_7);
  suite_add_tcase(suite, tc_core);

  return suite;
}

Suite *s21_sum_matrix_suite(void) {
  Suite *suite = suite_create("s21_sum_matrix");
  TCase *tc_core = tcase_create("core_of_sum_matrix");
  tcase_add_test(tc_core, s21_sum_matrix_1);
  tcase_add_test(tc_core, s21_sum_matrix_2);
  tcase_add_test(tc_core, s21_sum_matrix_3);
  tcase_add_test(tc_core, s21_sum_matrix_4);
  tcase_add_test(tc_core, s21_sum_matrix_5);
  tcase_add_test(tc_core, s21_sum_matrix_6);
  suite_add_tcase(suite, tc_core);

  return suite;
}

Suite *s21_sub_matrix_suite(void) {
  Suite *suite = suite_create("s21_sub_matrix");
  TCase *tc_core = tcase_create("core_of_sub_matrix");
  tcase_add_test(tc_core, s21_sub_matrix_1);
  tcase_add_test(tc_core, s21_sub_matrix_2);
  tcase_add_test(tc_core, s21_sub_matrix_3);
  tcase_add_test(tc_core, s21_sub_matrix_4);
  tcase_add_test(tc_core, s21_sub_matrix_5);
  suite_add_tcase(suite, tc_core);

  return suite;
}

Suite *s21_mult_number_suite(void) {
  Suite *suite = suite_create("s21_mult_number");
  TCase *tc_core = tcase_create("core_of_mult_number");
  tcase_add_test(tc_core, s21_mult_number_1);
  tcase_add_test(tc_core, s21_mult_number_2);
  tcase_add_test(tc_core, s21_mult_number_3);
  tcase_add_test(tc_core, s21_mult_number_4);
  suite_add_tcase(suite, tc_core);

  return suite;
}

Suite *s21_mult_matrix_suite(void) {
  Suite *suite = suite_create("s21_mult_matrix");
  TCase *tc_core = tcase_create("core_of_mult_matrix");
  tcase_add_test(tc_core, s21_mult_matrix_1);
  tcase_add_test(tc_core, s21_mult_matrix_2);
  tcase_add_test(tc_core, s21_mult_matrix_3);
  tcase_add_test(tc_core, s21_mult_matrix_4);
  tcase_add_test(tc_core, s21_mult_matrix_5);
  suite_add_tcase(suite, tc_core);

  return suite;
}

Suite *s21_transpose_suite(void) {
  Suite *suite = suite_create("s21_transpose");
  TCase *tc_core = tcase_create("core_of_transpose");
  tcase_add_test(tc_core, s21_transpose_1);
  tcase_add_test(tc_core, s21_transpose_2);
  tcase_add_test(tc_core, s21_transpose_3);
  tcase_add_test(tc_core, s21_transpose_4);
  suite_add_tcase(suite, tc_core);

  return suite;
}

Suite *s21_calc_complements_suite(void) {
  Suite *suite = suite_create("s21_calc_complements");
  TCase *tc_core = tcase_create("core_of_calc_complements");
  tcase_add_test(tc_core, s21_calc_complements_1);
  tcase_add_test(tc_core, s21_calc_complements_2);
  tcase_add_test(tc_core, s21_calc_complements_3);
  suite_add_tcase(suite, tc_core);

  return suite;
}

Suite *s21_determinant_suite(void) {
  Suite *suite = suite_create("s21_determinant");
  TCase *tc_core = tcase_create("core_of_determinant");
  tcase_add_test(tc_core, s21_determinant_1);
  tcase_add_test(tc_core, s21_determinant_2);
  tcase_add_test(tc_core, s21_determinant_3);
  tcase_add_test(tc_core, s21_determinant_4);
  tcase_add_test(tc_core, s21_determinant_5);
  tcase_add_test(tc_core, s21_determinant_6);
  suite_add_tcase(suite, tc_core);

  return suite;
}

Suite *s21_inverse_matrix_suite(void) {
  Suite *suite = suite_create("s21_inverse_matrix");
  TCase *tc_core = tcase_create("core_of_inverse_matrix");
  tcase_add_test(tc_core, s21_inverse_matrix_1);
  tcase_add_test(tc_core, s21_inverse_matrix_2);
  tcase_add_test(tc_core, s21_inverse_matrix_3);
  tcase_add_test(tc_core, s21_inverse_matrix_4);
  tcase_add_test(tc_core, s21_inverse_matrix_5);
  suite_add_tcase(suite, tc_core);

  return suite;
}

/*  Функция для запуска каждой группы тестовых случаев */

int running_suite(Suite *suite) {
  int number_failed = 0;
  SRunner *sr = srunner_create(suite);
  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

int main(void) {
  Suite *functions_suite[] = {
      s21_create_matrix_suite(),    s21_remove_matrix_suite(),
      s21_eq_matrix_suite(),        s21_sum_matrix_suite(),
      s21_sub_matrix_suite(),       s21_mult_number_suite(),
      s21_mult_matrix_suite(),      s21_transpose_suite(),
      s21_calc_complements_suite(), s21_determinant_suite(),
      s21_inverse_matrix_suite(),   NULL};

  int number_failed = 0;

  for (Suite **current_test = functions_suite; *current_test != NULL;
       current_test++) {
    if (running_suite(*current_test) == EXIT_FAILURE) {
      printf("Test № %d failed\n", number_failed + 1);
    }
    number_failed++;
  }
  return 0;
}
