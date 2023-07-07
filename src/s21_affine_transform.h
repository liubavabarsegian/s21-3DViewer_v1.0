#ifndef SRC_S21_AFFINE_TRANSFORM_H_
#define SRC_S21_AFFINE_TRANSFORM_H_
#include <stdlib.h>

#define RETURN_OK 0
#define RETURN_WRONG_MATRIX 1
#define RETURN_CALC_ERROR 2

typedef struct facets {     // хранения полигонов(f)
    int *vert;              // массив номеров вершин
    int count_number_vert;  // кол-во вершин необходимых для соединения
} s21_facets;

typedef struct data {
    unsigned count_vert;    // кол-во вершин
    unsigned count_facets;  // кол-во полигон
    unsigned count_edge;    // кол-во рёбер
    s21_matrix *matrix_3d;
    s21_facets *polygons;
} s21_data;

typedef struct matrix {  // структура матриц
    double **matrix;
    int rows;
    int columns;
} s21_matrix;

/**
 - @brief Функция создания матрицы.
 - @param rows - количество строк
 - @param columns - количество столбцов
 - @result возвращает матрицу размерности [rows, columns]
 */
int s21_create_matrix(int rows, int columns, s21_matrix* result);
/**
 - @brief Функция перемножения матриц.
 - @param A - указатель на левую матрицу
 - @param B - указатель на правую матрицу
 - @result возвращает результирующую матрицу
 */
s21_matrix s21_mult_matrix(s21_matrix *A, s21_matrix *B);
/**
 - @brief Функция создания матрицы.
 - @param A - указатель на матрицу
 - @result удаление матрицы с освобождением памяти
 */
void s21_remove_matrix(s21_matrix *A);

/**
 - @brief Функция создания матрицы афинных преобразований.
 - @param x - координата "x"
 - @param y - координата "y"
 - @param z - координата "z"
 - @result возвращает матрицу афинного вида
 */
s21_matrix create_af_matrix(double x, double y, double z);
/**
 - @brief Функция создания матрицы масштабных преобразований.
 - @param x - координата "x"
 - @param y - координата "y"
 - @param z - координата "z"
 - @result возвращает матрицу масштабирования
 */
s21_matrix create_resize_matrix(double x, double y, double z);
/**
 - @brief Функция вращения вокруг оси "x".
 - @param x - координата "x"
 - @result возвращает матрицу вращения вокруг оси "x"
 */
s21_matrix create_x_rotation_matrix(double x);
/**
 - @brief Функция вращения вокруг оси "y".
 - @param y - координата "y"
 - @result возвращает матрицу вращения вокруг оси "y"
 */
s21_matrix create_y_rotation_matrix(double y);
/**
 - @brief Функция вращения вокруг оси "z".
 - @param z - координата "z"
 - @result возвращает матрицу вращения вокруг оси "z"
 */
s21_matrix create_z_rotation_matrix(double z);
/**
 - @brief Функция перемещения.
 - @param x - координата "x"
 - @param y - координата "y"
 - @param z - координата "z"
 - @param data - указатель на данные
 - @result выполняет перемещение модели
 */
void moving(s21_data *data, double x, double y, double z);
/**
 - @brief Функция масштабирования.
 - @param x - координата "x"
 - @param y - координата "y"
 - @param z - координата "z"
 - @param data - указатель на данные
 - @result выполняет масштабирование модели
 */
void resize(s21_data *data, double x, double y, double z);
/**
 - @brief Функция вращения.
 - @param x - координата "x"
 - @param y - координата "y"
 - @param z - координата "z"
 - @param data - указатель на данные
 - @result выполняет вращение модели
 */
void rotation(s21_data *data, double x, double y, double z);

#endif  // SRC_S21_AFFINE_TRANSFORM_H_