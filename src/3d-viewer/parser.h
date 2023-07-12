#ifndef PARSER_H_
#define PARSER_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct vertice {
    double x;
    double y;
    double z;
} vertice;

typedef struct facets {
	int *vertices;
	size_t numbers_of_vertices_in_facets;
} polygon_t;

typedef struct data {
	size_t count_of_vertices;
	size_t count_of_facets;
    vertice *vertices;
	polygon_t *polygons;
} data;

#define  OK 0
#define ERROR 404
#define IS_NOT_A_NUMBER 123

int parser(char *filename, data *model, size_t *count_of_vertices, size_t *count_of_facet);

void free_vertices_in_facets(data *model);

//void open_and_parse(data *model);

int scan_vertices(FILE *fp, data *model, size_t *count_of_vertices);
int scan_facets(FILE *fp, data *model, size_t *count_of_facet);

int found_number(char letter, size_t *count_vertice_in_facet, size_t *facets_counter, FILE *fp, data *model, int *flag_end_of_line);


//size_t count_line_size(FILE *fp);
int scan_vertice(size_t *vertices_counter, char *line, data *model);

int scan_facet(size_t *facets_counter, FILE *fp, data *model);

int is_number(char symbol);

// print
void print_vertices(data *model);
void print_polygon(data *model);

#endif  //  MAIN_H_
