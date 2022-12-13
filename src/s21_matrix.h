#ifndef SRC_S21_MATRIX_H_
#define SRC_S21_MATRIX_H_

#include <math.h>
#include <stdlib.h>

#define SUCCESS 1
#define FAILURE 0

#define OK 0
#define INCORRECT_MATRIX 1
#define ERROR_COMPUTE 2

#define PLUS 1
#define MINUS 0
#define EPS 0.0000001

typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;
} matrix_t;

// 1. Создание матрицы
int s21_create_matrix(int rows, int columns, matrix_t *result);
// 2. Очистка матриц
void s21_remove_matrix(matrix_t *A);
// 3. Сравнение матриц
int s21_eq_matrix(matrix_t *A, matrix_t *B);
// 4. Сложение и вычитание матриц
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
// 5. Умножение матрицы на число. Умножение двух матриц
int s21_mult_number(matrix_t *A, double number, matrix_t *result);
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
// 6. Транспонирование матрицы
int s21_transpose(matrix_t *A, matrix_t *result);
int s21_calc_complements(matrix_t *A, matrix_t *result);
// 8. Определитель матрицы
int s21_determinant(matrix_t *A, double *result);
// 9. Обратная матрица
int s21_inverse_matrix(matrix_t *A, matrix_t *result);

// Другие функции
// Проверка матрицы на корректность
int check_matrix(matrix_t *matrix);

// Проверка матрицы на равенство сторон
int check_square_matrix(matrix_t *matrix);

// Проверка на равенство размера двух матриц
int check_size_matrix(matrix_t *A, matrix_t *B);

// Проверка равенства количества столбцов одной матрицы с количеством строк
// другой
int check_rows_with_columns(matrix_t *A, matrix_t *B);

// Функция сложения/вычитания
int easy_compute(matrix_t *A, matrix_t *B, matrix_t *result, int sign);

int check_result_matrix(int rows, int columns, matrix_t *result);
void zero_matrix_pole(matrix_t *result);
// Нахождение минорма матрицы
int s21_get_minor(matrix_t *A, int row, int column, matrix_t *result);

#endif  // SRC_S21_MATRIX_H_
