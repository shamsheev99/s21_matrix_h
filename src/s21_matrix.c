#include "s21_matrix.h"

// 1. Создание матрицы

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int exit = INCORRECT_MATRIX;
  if (result != NULL) {
    if (rows > 0 && columns > 0) {
      result->rows = rows;
      result->columns = columns;
      result->matrix = (double **)calloc(result->rows, sizeof(double *));
      for (int i = 0; i < result->rows; i++) {
        result->matrix[i] = (double *)calloc(result->columns, sizeof(double));
      }
      exit = OK;
    } else {
      zero_matrix_pole(result);
    }
  }
  return exit;
}

// 2-> Очистка матриц
void s21_remove_matrix(matrix_t *A) {
  if (A != NULL) {
    if (A->rows > 0 && A->columns > 0 && A->matrix != NULL) {
      for (int i = 0; i < A->rows; i++) {
        free(A->matrix[i]);
      }
      free(A->matrix);
    } else {
      zero_matrix_pole(A);
    }
    A->rows = 0;
    A->columns = 0;
    A->matrix = NULL;
  }
}

// 3. Сравнение матриц
// Две матрицы A, B совпадают |A = B|, если совпадают их размеры и
// соответствующие элементы равны, то есть при всех i, j A(i,j) = B(i,j).
// Сравнение должно происходить вплоть до 7 знака после запятой включительно.
int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int exit = FAILURE;
  if (check_matrix(A) == SUCCESS && check_matrix(B) == SUCCESS) {
    if (check_size_matrix(A, B) == SUCCESS) {
      int break_point = SUCCESS;
      for (int i = 0; i < A->rows; i++) {
        if (break_point == FAILURE) break;
        for (int j = 0; j < A->columns; j++) {
          if (fabs(A->matrix[i][j] - B->matrix[i][j]) <= EPS) {
            exit = SUCCESS;
          } else {
            break_point = FAILURE;
            exit = FAILURE;
            break;
          }
        }
      }
    }
  }
  return exit;
}

// // //4. Сложение и вычитание матриц
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int exit = INCORRECT_MATRIX;
  if (check_matrix(A) == SUCCESS && check_matrix(B) == SUCCESS &&
      result != NULL) {
    if (check_size_matrix(A, B) == SUCCESS) {
      s21_create_matrix(A->rows, A->columns, result);
      exit = OK;
      int sign = PLUS;
      easy_compute(A, B, result, sign);
    } else {
      zero_matrix_pole(result);
      exit = ERROR_COMPUTE;
    }
  } else {
    zero_matrix_pole(result);
  }
  return exit;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int exit = INCORRECT_MATRIX;
  if (check_matrix(A) == SUCCESS && check_matrix(B) == SUCCESS &&
      result != NULL) {
    if (check_size_matrix(A, B) == SUCCESS) {
      s21_create_matrix(A->rows, A->columns, result);
      exit = OK;
      int sign = MINUS;
      easy_compute(A, B, result, sign);
    } else {
      zero_matrix_pole(result);
      exit = ERROR_COMPUTE;
    }
  } else {
    zero_matrix_pole(result);
  }
  return exit;
}

// int s21_create_matrix(int rows, int columns, matrix_t *result) {
//   int exit = INCORRECT_MATRIX;
//   if (result != NULL) {
//     if (rows > 0 && columns > 0) {
//       result->rows = rows;
//       result->columns = columns;
//       result->matrix = (double **)calloc(result->rows, sizeof(double *));
//       for (int i = 0; i < result->rows; i++) {
//         result->matrix[i] = (double *)calloc(result->columns,
//         sizeof(double));
//       }
//       exit = OK;
//     } else {
//       zero_matrix_pole(result);
//     }
//   }

//   return exit;
// }

// // //5. Умножение матрицы на число. Умножение двух матриц
int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int exit = INCORRECT_MATRIX;
  if (result != NULL) {
    if (check_matrix(A) == SUCCESS) {
      s21_create_matrix(A->rows, A->columns, result);
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          result->matrix[i][j] = A->matrix[i][j] * number;
        }
        exit = OK;
      }
    } else {
      zero_matrix_pole(result);
    }
  }
  return exit;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int exit = INCORRECT_MATRIX;
  if (result != NULL) {
    if (check_matrix(A) == SUCCESS && check_matrix(B) == SUCCESS) {
      if (check_rows_with_columns(A, B) == SUCCESS) {
        s21_create_matrix(A->rows, B->columns, result);
        for (int i = 0; i < A->rows; i++) {
          for (int j = 0; j < B->columns; j++) {
            result->matrix[i][j] = 0;
            for (int r = 0; r < A->columns; r++) {
              result->matrix[i][j] += A->matrix[i][r] * B->matrix[r][j];
            }
          }
        }
        exit = OK;
      } else {
        exit = ERROR_COMPUTE;
        zero_matrix_pole(result);
      }
    } else {
      zero_matrix_pole(result);
    }
  }
  return exit;
}

// // //6. Транспонирование матрицы
int s21_transpose(matrix_t *A, matrix_t *result) {
  int exit = INCORRECT_MATRIX;
  if (result != NULL) {
    if (check_matrix(A) == SUCCESS) {
      s21_create_matrix(A->columns, A->rows, result);
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          result->matrix[j][i] = A->matrix[i][j];
        }
      }
      exit = OK;
    } else {
      zero_matrix_pole(result);
    }
  }
  return exit;
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int exit = INCORRECT_MATRIX;
  if (result != NULL) {
    if (check_matrix(A) == SUCCESS && result != NULL) {
      if (check_square_matrix(A) == SUCCESS) {
        s21_create_matrix(A->rows, A->columns, result);
        if (A->rows == 1) {
          result->matrix[0][0] = 1;
        } else {
          for (int i = 0; i < A->rows; i++) {
            for (int j = 0; j < A->columns; j++) {
              matrix_t minor;
              s21_get_minor(A, i, j, &minor);
              double number = 0.0 / 0.0;
              s21_determinant(&minor, &number);
              result->matrix[i][j] = ((i + j) % 2 == 1 ? -1 : 1) * number;
              s21_remove_matrix(&minor);
            }
          }
        }
        exit = OK;
      } else {
        exit = ERROR_COMPUTE;
        zero_matrix_pole(result);
      }
    } else {
      zero_matrix_pole(result);
    }
  }
  return exit;
}

// // //8. Определитель матрицы
int s21_determinant(matrix_t *A, double *result) {
  int exit = INCORRECT_MATRIX;
  if (check_matrix(A)) {
    if (check_square_matrix(A) == SUCCESS && result != NULL) {
      int minus = -1;
      double determinant = 0.0;
      if (A->rows == 1) {
        determinant = A->matrix[0][0];
      } else if (A->rows == 2) {
        determinant += (A->matrix[0][0] * A->matrix[1][1] -
                        A->matrix[1][0] * A->matrix[0][1]);
      } else {
        for (int i = 0; i < A->rows; i++) {
          minus *= -1;
          matrix_t MINOR;
          s21_get_minor(A, i, 0, &MINOR);
          s21_determinant(&MINOR, result);
          determinant += (minus * A->matrix[i][0] * *result);
          s21_remove_matrix(&MINOR);
        }
      }
      *result = determinant;
      exit = OK;
    } else {
      exit = ERROR_COMPUTE;
    }
  }
  return exit;
}

// // //9. Обратная матрица
int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int exit = INCORRECT_MATRIX;
  if (result != NULL) {
    if (check_matrix(A) == SUCCESS && result != NULL) {
      double determinant = 0.0;
      s21_determinant(A, &determinant);
      if (check_square_matrix(A) == SUCCESS && determinant != 0.0) {
        // s21_create_matrix(A->rows, A->columns, result);
        if (determinant != 0.0) {
          s21_calc_complements(A, result);
          matrix_t tmp;
          s21_transpose(result, &tmp);
          for (int i = 0; i < A->rows; i++) {
            for (int j = 0; j < A->columns; j++) {
              result->matrix[i][j] = 0.0;
              result->matrix[i][j] =
                  (double)tmp.matrix[i][j] / (double)determinant;
            }
          }
          s21_remove_matrix(&tmp);
          exit = OK;
        }
      } else {
        exit = ERROR_COMPUTE;
        zero_matrix_pole(result);
      }
    } else {
      zero_matrix_pole(result);
    }
  }
  return exit;
}

// other foo
void zero_matrix_pole(matrix_t *result) {
  result->columns = 0;
  result->rows = 0;
  result->matrix = NULL;
}

int check_matrix(matrix_t *matrix) {
  int result = FAILURE;
  if (matrix != NULL) {
    if (matrix->rows > 0 && matrix->columns > 0 && matrix->matrix != NULL) {
      result = SUCCESS;
    } else {
      matrix->rows = 0;
      matrix->columns = 0;
      matrix->matrix = NULL;
    }
  }
  return result;
}

int check_square_matrix(matrix_t *matrix) {
  int result = FAILURE;
  if (matrix->rows == matrix->columns) result = SUCCESS;
  return result;
}

int check_size_matrix(matrix_t *A, matrix_t *B) {
  int result = FAILURE;
  if (A->rows == B->rows && A->columns == B->columns) result = SUCCESS;
  return result;
}

int check_rows_with_columns(matrix_t *A, matrix_t *B) {
  int result = FAILURE;
  if (A->columns == B->rows) result = SUCCESS;
  return result;
}

int easy_compute(matrix_t *A, matrix_t *B, matrix_t *result, int sign) {
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      result->matrix[i][j] =
          (sign == PLUS ? (A->matrix[i][j] + B->matrix[i][j])
                        : (A->matrix[i][j] - B->matrix[i][j]));
    }
  }
  return 0;
}

// // //7. Минор матрицы и матрица алгебраических дополнений (calc_complements)
// // //Минором M(i,j) называется определитель (n-1)-го порядка,
// // //полученный вычёркиванием из матрицы A i-й строки и j-го столбца.
int s21_get_minor(matrix_t *A, int row, int column, matrix_t * result) {
  if (check_square_matrix(A) == SUCCESS) {
    s21_create_matrix(A->rows - 1, A->columns - 1, result);
    int z = 0;
    for (int i = 0; i < A->rows; i++) {
      if (i != row) {
        int k = 0;
        for (int j = 0; j < A->columns; j++) {
          if (j != column) {
            result->matrix[z][k] = A->matrix[i][j];
            k++;
          }
        }
        z++;
      }
    }
  } else {
    zero_matrix_pole(result);
  }
  return 0;
}
