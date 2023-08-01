#ifndef PARSER_H_
#define PARSER_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 - @brief Структура для хранения матриц.
 - @param matrix - представление матрицы
 - @param rows - количество строк
 - @param columns - количество столбцов
 */
typedef struct matrix {
  double **matrix;
  int rows;
  int columns;
} s21_matrix;

/**
 - @brief Структура для хранения полигонов (f).
 - @param vert - массив номеров вершин
 - @param count_number_vert - количество вершин, необходимых для соединения
 */
typedef struct facets {
  int *vert;
  int count_number_vert;
} s21_facets;

/**
 - @brief Структура для хранения данных.
 - @param count_vert - количество вершин
 - @param count_facets - количество полигонов
 - @param matrix_3d - структура матрицы
 - @param polygons - структура хранения полигонов
 */
typedef struct data {
  unsigned count_vert;
  unsigned count_facets;
  s21_matrix *matrix_3d;
  s21_facets *polygons;
} s21_data;

#define OK 0
#define ERROR 404
#define IS_NOT_A_NUMBER 123

int parser(const char *filename, s21_data *model, size_t *count_vert,
           size_t *count_facets);

void free_vertices_in_facets(s21_data *model);

int open_and_parse(s21_data *model, const char *filename,
                   int *blocks_to_free_in_matrix);
int scan_vertices(FILE *fp, s21_data *model, size_t *count_vert);
int scan_facets(FILE *fp, s21_data *model, size_t *count_of_facet);

int found_number(int letter, int *count_vertice_in_facet,
                 size_t *facets_counter, FILE *fp, s21_data *model,
                 int *flag_end_of_line);

int scan_vertice(size_t *vertices_counter, char *line, s21_data *model);

int scan_facet(size_t *facets_counter, FILE *fp, s21_data *model);

// int is_number(char symbol);
int is_number(int symbol);
// print
void print_polygon(s21_data *model);

// =================== matrix ===================
void print_matrix(s21_matrix matrix);
int create_matrix(s21_matrix *matrix_3d, int rows, int columns);
void free_matrix(s21_matrix *matrix_3d, int rows_to_free);
int realloc_matrix(s21_matrix *matrix_3d, int rows, int columns);

#endif  //  PARSER_H_
