#include "parser.h"

#include <math.h>

// ========== example ================
// int main(void) {
// s21_data model;
// model.count_vert = 10;
// model.count_facets = 10;
// model.matrix_3d = (s21_matrix *)malloc(sizeof(s21_matrix));
// if (model.matrix_3d != NULL) {
//   if (create_matrix(model.matrix_3d, model.count_vert, 4) == OK) {
//     model.polygons = (s21_facets *)malloc(model.count_facets *
//     sizeof(s21_facets)); int count_allocated_blocks = 0; if (model.polygons
//     != NULL) {
//      if(open_and_parse(&model, "../tests/cube.obj", &count_allocated_blocks)
//      == OK){
//        // something
//      //     printf("%d\n", model.count_vert);
//      //  printf("%d", model.count_facets);
//      }
//       free(model.polygons);
//     }
//     free_matrix(model.matrix_3d, count_allocated_blocks);
//     free(model.matrix_3d);
//   }
// }

// return 0;
//}

// void print_polygon(s21_data *model) {
//   for (size_t i = 0; i < model->count_facets; ++i) {
//     printf("%ld\t", i);
//     for (int j = 0; j < model->polygons[i].count_number_vert; ++j) {
//       printf("%d ", model->polygons[i].vert[j]);
//     }
//     printf("\n");
//   }
// }

void free_vertices_in_facets(s21_data *model) {
  for (size_t i = 0; i < model->count_facets; ++i) {
    free(model->polygons[i].vert);
  }
}

int open_and_parse(s21_data *model, const char *filename,
                   int *blocks_to_free_in_matrix) {
  // int ExitCode = OK;
  size_t vertice_counter = 0;
  size_t facet_counter = 0;
  int ExitCode = parser(filename, model, &vertice_counter, &facet_counter);
  if (ExitCode == OK) {
    model->count_vert = vertice_counter;
    *blocks_to_free_in_matrix = model->matrix_3d->rows;
    model->matrix_3d->rows = vertice_counter;
    model->count_facets = facet_counter;
    //  free_vertices_in_facets(model);   ///// нужно где-нибудь очистить
  }
  return ExitCode;
}

int scan_vertice(size_t *vertices_counter, char *line, s21_data *model) {
  int ExitCode = OK;
  double x, y, z;

  if (sscanf(line, "%lf%lf%lf", &x, &y, &z) == 3) {
    if (*vertices_counter >= model->count_vert) {
      model->count_vert *= 2;
      realloc_matrix(model->matrix_3d, model->count_vert, 4);
    }
    if (model->matrix_3d->matrix != NULL) {
      model->matrix_3d->matrix[*vertices_counter][0] = x;
      model->matrix_3d->matrix[*vertices_counter][1] = y;
      model->matrix_3d->matrix[*vertices_counter][2] = z;
      model->matrix_3d->matrix[*vertices_counter][3] = 1;
    } else {
      ExitCode = ERROR;
    }
    ++*vertices_counter;
  }
  return ExitCode;
}

int parser(const char *filename, s21_data *model, size_t *count_vert,
           size_t *count_facets) {
  int ExitCode = OK;

  FILE *fp = NULL;
  fp = fopen(filename, "r");

  if (fp != NULL) {
    int letter = getc(fp);
    while (letter != EOF && ExitCode == OK) {
      if (letter == 'v') {
        ExitCode = scan_vertices(fp, model, count_vert);
      } else if (letter == 'f') {
        ExitCode = scan_facets(fp, model, count_facets);
      }
      letter = getc(fp);
    }
    fclose(fp);
  } else {
    ExitCode = ERROR;
    // getchar();
  }

  return ExitCode;
}

int scan_facet(size_t *facets_counter, FILE *fp, s21_data *model) {
  int ExitCode = OK;

  int count_vertice_in_facet = 0;
  int flag_end_of_line = 0;
  int letter = getc(fp);
  if (is_number(letter)) {
    while (letter != EOF && ExitCode == OK && !flag_end_of_line) {
      if (is_number(letter)) {
        ExitCode = found_number(letter, &count_vertice_in_facet, facets_counter,
                                fp, model, &flag_end_of_line);
      }
      if (letter == '\n') {
        flag_end_of_line = 1;
      }
      if (!flag_end_of_line) {
        letter = getc(fp);
      }
    }
    model->polygons[*facets_counter].count_number_vert = count_vertice_in_facet;
  } else {
    while (letter != EOF && letter != '\n') {
      ExitCode = IS_NOT_A_NUMBER;
      letter = getc(fp);
    }
  }
  return ExitCode;
}
int found_number(int letter, int *count_vertice_in_facet,
                 size_t *facets_counter, FILE *fp, s21_data *model,
                 int *flag_end_of_line) {
  int ExitCode = OK;

  size_t number = 0;
  while (letter != '/' && letter != ' ' && letter != '\n') {
    number *= 10;
    number += letter - '0';
    letter = getc(fp);
  }
  if (*count_vertice_in_facet >=
      model->polygons[*facets_counter].count_number_vert) {
    model->polygons[*facets_counter].count_number_vert *= 2;
    model->polygons[*facets_counter].vert = (int *)realloc(
        model->polygons[*facets_counter].vert,
        model->polygons[*facets_counter].count_number_vert * sizeof(int));
  }
  if (model->polygons[*facets_counter].vert != NULL) {
    model->polygons[*facets_counter].vert[*count_vertice_in_facet] = number;
    ++*count_vertice_in_facet;
  } else {
    ExitCode = ERROR;
  }
  while (letter != EOF && letter != '\n' && letter != ' ') {
    letter = getc(fp);
  }
  if (letter == '\n') {
    *flag_end_of_line = 1;
  }

  return ExitCode;
}

int is_number(int symbol) {
  int ExitCode = 0;
  if (symbol >= '0' && symbol <= '9') {
    ExitCode = 1;
  }
  return ExitCode;
}

int scan_vertices(FILE *fp, s21_data *model, size_t *count_vert) {
  int ExitCode = OK;
  // char letter = getc(fp);
  int letter = getc(fp);
  if (letter == ' ') {
    char line[51];
    if (fgets(line, sizeof(line), fp) != NULL) {
      ExitCode = scan_vertice(count_vert, line, model);
    } else {
      ExitCode = ERROR;  //  ?
    }
  }
  return ExitCode;
}

int scan_facets(FILE *fp, s21_data *model, size_t *count_facets) {
  int ExitCode = OK;
  // char letter = getc(fp);
  int letter = getc(fp);
  if (letter == ' ') {
    if (*count_facets >= model->count_facets) {
      model->count_facets *= 2;
      model->polygons = (s21_facets *)realloc(
          model->polygons, model->count_facets * sizeof(s21_facets));
    }
    if (model->polygons != NULL) {
      model->polygons[*count_facets].count_number_vert = 10;
      model->polygons[*count_facets].vert = (int *)malloc(
          model->polygons[*count_facets].count_number_vert * sizeof(int));
      if (model->polygons[*count_facets].vert != NULL) {
        ExitCode = scan_facet(count_facets, fp, model);
        if (ExitCode == IS_NOT_A_NUMBER) {
          ExitCode = OK;
        } else if (ExitCode == OK) {
          ++*count_facets;
        }
      }
    } else {
      ExitCode = ERROR;
    }
  }
  return ExitCode;
}

// void print_matrix(s21_matrix matrix_3d) {
//     for(int i = 0; i < matrix_3d.rows; ++i) {
//       printf("%d\t", i);
//         for (int j = 0; j < matrix_3d.columns; ++j) {
//             printf("%lf ", matrix_3d.matrix[i][j]);
//         }
//         printf("\n");
//     }
// }

int create_matrix(s21_matrix *matrix_3d, int rows, int columns) {
  int ExitCode = OK;
  matrix_3d->rows = rows;
  matrix_3d->columns = columns;
  matrix_3d->matrix = (double **)malloc(sizeof(double *) * matrix_3d->rows);
  if (matrix_3d->matrix != NULL) {
    for (int i = 0; i < rows; ++i) {
      matrix_3d->matrix[i] = (double *)malloc(sizeof(double) * columns);
    }
  } else {
    ExitCode = ERROR;
  }
  return ExitCode;
}

void free_matrix(s21_matrix *matrix_3d, int rows_to_free) {
  for (int i = 0; i < rows_to_free; ++i) {
    free(matrix_3d->matrix[i]);
  }
  free(matrix_3d->matrix);
}

int realloc_matrix(s21_matrix *matrix_3d, int rows, int columns) {
  int ExitCode = OK;
  matrix_3d->matrix =
      (double **)realloc(matrix_3d->matrix, sizeof(double *) * rows);
  if (matrix_3d->matrix != NULL) {
    for (int i = matrix_3d->rows; i < rows; ++i) {
      matrix_3d->matrix[i] = (double *)malloc(sizeof(double) * columns);
    }
  } else {
    ExitCode = ERROR;
  }
  matrix_3d->rows = rows;
  matrix_3d->columns = columns;
  return ExitCode;
}
