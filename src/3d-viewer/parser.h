#ifndef PARSER_H_
#define PARSER_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// #####################################################################
// typedef struct facets {     // хранения полигонов(f)
//     int *vert;              // массив номеров вершин
//     int count_number_vert;  // кол-во вершин необходимых для соединения
// } s21_facets;

// typedef struct data {
//     unsigned count_vert;    // кол-во вершин
//     unsigned count_facets;  // кол-во полигон
//     unsigned count_edge;    // кол-во рёбер
//     s21_matrix *matrix_3d;
//     s21_facets *polygons;
// } s21_data;

// typedef struct matrix {  // структура матриц
//     double **matrix;
//     int rows;
//     int columns;
// } s21_matrix;
// #####################################################################
// typedef struct vertice {
//     double x;
//     double y;
//     double z;
// } vertice;

// typedef struct facets {
	//int *vertices;  /////////   int *vert;              // массив номеров вершин
//	size_t numbers_of_vertices_in_facets;   ////// int count_number_vert;  // кол-во вершин необходимых для соединения
//} polygon_t;  /// s21_facets;

typedef struct facets {     // хранения полигонов(f)
    int *vert;              // массив номеров вершин
    int count_number_vert;  // кол-во вершин необходимых для соединения
} s21_facets;

//typedef struct data {
	//size_t count_of_vertices;  ///// unsigned count_vert;    // кол-во вершин
	//size_t count_of_facets;  ///// unsigned count_facets;  // кол-во полигон
    //vertice *vertices;
	//polygon_t *polygons;   ///// s21_facets *polygons;
//} data; ///// s21_data;

typedef struct matrix {  // структура матриц
    double **matrix;
    int rows;
    int columns;
} s21_matrix;

typedef struct data {
    unsigned count_vert;    // кол-во вершин
    unsigned count_facets;  // кол-во полигон
    /// unsigned count_edge;    // кол-во рёбер  потом сделаем, если нужно будет
    s21_matrix *matrix_3d;
    s21_facets *polygons;
} s21_data;



#define  OK 0
#define ERROR 404
#define IS_NOT_A_NUMBER 123

int parser(const char *filename, s21_data *model, size_t *count_vert, size_t *count_facets);

void free_vertices_in_facets(s21_data *model);

void open_and_parse(s21_data *model, const char *);

int scan_vertices(FILE *fp, s21_data *model, size_t *count_vert);
int scan_facets(FILE *fp, s21_data *model, size_t *count_of_facet);

int found_number(char letter, int *count_vertice_in_facet, size_t *facets_counter, FILE *fp, s21_data *model, int *flag_end_of_line);


//size_t count_line_size(FILE *fp);
int scan_vertice(size_t *vertices_counter, char *line, s21_data *model);

int scan_facet(size_t *facets_counter, FILE *fp, s21_data *model);

int is_number(char symbol);

// print
// void print_vertices(data *model);
void print_polygon(s21_data *model);

// ==================================== matrix ====================================
void print_matrix(s21_matrix matrix);
int create_matrix(s21_matrix *matrix_3d, int rows, int columns);
void free_matrix(s21_matrix *matrix_3d);
int realloc_matrix(s21_matrix *matrix_3d, int rows, int columns);

#endif  //  MAIN_H_
