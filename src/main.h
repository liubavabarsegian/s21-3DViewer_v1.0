#ifndef MAIN_H_
#define MAIN_H_

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
	size_t numbers_of_vertexes_in_facets;
} polygon_t;

typedef struct data {
	size_t count_of_vertexes;
	size_t count_of_facets;
    vertice *vertices;
	//matrix_t matrix_3d; == vertice *vertices;
	polygon_t *polygons;
} data;

#define  OK 0
#define ERROR 404

int parser(char *filename, data *model, size_t *real_count_of_vertices, size_t *real_count_of_facet);

void free_vertices_in_facets(data *model);

void open_and_parse(data *model);

// print
void print_vertexes(data *model);
void print_polygon(data *model);

#endif  //  MAIN_H_