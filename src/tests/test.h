#ifndef TEST_H_
#define TEST_H_

#include <check.h>
#include "../3d-viewer/parser.h"
#include "../3d-viewer/s21_affine_transform.h"

#define SUCCESS 1
#define FAILURE 0
#define OK 0
#define INCORRECT_MATRIX 1  //  Ошибка, некорректная матрица
#define CALCULATION_ERROR

int s21_eq_matrix(s21_matrix *A, s21_matrix *B);
int s21_check_matrix(s21_matrix *A);
int s21_eq_size(s21_matrix A, s21_matrix B);

#endif  //  TEST_H_