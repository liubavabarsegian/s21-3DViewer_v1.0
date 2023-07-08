#include "parser.h"

int main_parser(void) {
  data model;
  model.count_of_vertices = 10;
  model.count_of_facets = 10;
  model.vertices = (vertice *)malloc(model.count_of_vertices * sizeof(vertice));

  if (model.vertices != NULL) {
    model.polygons = (polygon_t *)malloc(model.count_of_facets * sizeof(polygon_t));
    if (model.polygons != NULL) {
      ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      open_and_parse(&model);
      ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      free(model.polygons);
    }
    free(model.vertices);
  }
  
  return 0;
}

void print_vertices(data *model) {
  for (size_t i = 1; i <= model->count_of_vertices; ++i) {
    //printf("%ld\t", i + 1);
    printf("%ld\t%lf %lf %lf\n", i, model->vertices[i].x, model->vertices[i].y, model->vertices[i].z);
  }
}

void print_polygon(data *model) {
  for (size_t i = 0; i < model->count_of_facets; ++i) {
    printf("%ld\t", i);
    for (size_t j = 0; j < model->polygons[i].numbers_of_vertices_in_facets; ++j) {
      printf("%d ", model->polygons[i].vertices[j]);
    }
    //printf("\t%ld", model->polygons[i].numbers_of_vertices_in_facets);
    printf("\n");
  }
}

void free_vertices_in_facets(data *model) {
  for (size_t i = 0; i < model->count_of_facets; ++i) {
    free(model->polygons[i].vertices);
  }
}

void open_and_parse(data *model) {
  char filename[13] = "test_cat.obj";
  size_t vertice_counter = 0;
  size_t facet_counter = 0;
  int ExitCode = parser(filename, model, &vertice_counter, &facet_counter);
  if (ExitCode == OK) {
  model->count_of_vertices = vertice_counter;
  model->count_of_facets = facet_counter;
    print_vertices(model);
    printf("\n");
    print_polygon(model);
  } else {
    printf("\nERROR\n");
  }
  free_vertices_in_facets(model);
}

int scan_vertice(size_t *vertices_counter, char *line, data *model) {
  int ExitCode = OK;
  double x, y, z;

  if (sscanf(line, "%lf%lf%lf", &x, &y, &z) == 3) {
    ++*vertices_counter;
    if (*vertices_counter >= model->count_of_vertices) {
      model->count_of_vertices *= 2;
      model->vertices = (vertice *)realloc(model->vertices, model->count_of_vertices * sizeof(vertice));
    }
    if (model->vertices != NULL) {
      model->vertices[*vertices_counter].x = x;
      model->vertices[*vertices_counter].y = y;
      model->vertices[*vertices_counter].z = z;
    } else {
      ExitCode = ERROR;
    }
  }
  return ExitCode;
}

int parser(char *filename, data *model, size_t *count_of_vertices, size_t *count_of_facet) {
  int ExitCode = OK;

  FILE *fp;
  fp = fopen(filename, "r");

  if (fp != NULL) {
    char letter = getc(fp);
    while (letter != EOF && ExitCode == OK) {
      if (letter == 'v') {
        ExitCode = scan_vertices(fp, model, count_of_vertices);
      } else if (letter == 'f') {
        ExitCode = scan_facets(fp, model, count_of_facet);
      }
      letter = getc(fp);
    }
  } else {
    ExitCode = ERROR;
    getchar();
  }

  return ExitCode;
}

int scan_facet(size_t *facets_counter, FILE *fp, data *model) {
  int ExitCode = OK;

  size_t count_vertice_in_facet = 0;
  int flag_end_of_line = 0;
  char letter = getc(fp);
  if (is_number(letter)){
  while (letter != EOF && ExitCode == OK && !flag_end_of_line) {
    if (is_number(letter)) {
      ExitCode = found_number(letter, &count_vertice_in_facet, facets_counter, fp, model, &flag_end_of_line);
    }
    if (letter == '\n') {
        flag_end_of_line = 1;
    }
    if (!flag_end_of_line) {
      letter = getc(fp);
    }
  }
  model->polygons[*facets_counter].numbers_of_vertices_in_facets = count_vertice_in_facet;
} else {
  while (letter != EOF && letter != '\n') {
    ExitCode = IS_NOT_A_NUMBER;
    letter = getc(fp);
  }
} 
  return ExitCode;
}

int found_number(char letter, size_t *count_vertice_in_facet, size_t *facets_counter, FILE *fp, data *model, int *flag_end_of_line) {
  int ExitCode = OK;

  size_t number = 0;
  while (letter != '/' && letter != ' ' && letter != '\n') {
    number *= 10;
    number += letter - '0';
    letter = getc(fp);    
  }
  if (*count_vertice_in_facet >= model->polygons[*facets_counter].numbers_of_vertices_in_facets) {
    model->polygons[*facets_counter].numbers_of_vertices_in_facets *= 2;
    model->polygons[*facets_counter].vertices = (int *)realloc(model->polygons[*facets_counter].vertices, model->polygons[*facets_counter].numbers_of_vertices_in_facets * sizeof(int));
  }
  if (model->polygons[*facets_counter].vertices != NULL) {
    model->polygons[*facets_counter].vertices[*count_vertice_in_facet] = number;
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


int is_number(char symbol) {
  int ExitCode = 0;
  if (symbol >= '0' && symbol <= '9') {
    ExitCode = 1;
  }
  return ExitCode;
}

int scan_vertices(FILE *fp, data *model, size_t *count_of_vertices) {
  int ExitCode = OK;
  char letter = getc(fp);
  if (letter == ' ') {
    char line[51];
    if (fgets(line, sizeof(line), fp) != NULL) {
      ExitCode = scan_vertice(count_of_vertices, line, model);
    } else {
      ExitCode = ERROR;  //  ?
    }
  }
  return ExitCode;
}

int scan_facets(FILE *fp, data *model, size_t *count_of_facet) {
  int ExitCode = OK;
  char letter = getc(fp);
  if (letter == ' ') {
      if (*count_of_facet >= model->count_of_facets) {
        model->count_of_facets *= 2;
        model->polygons = (polygon_t *)realloc(model->polygons,model->count_of_facets * sizeof(polygon_t));
      }
      if (model->polygons != NULL) {
        model->polygons[*count_of_facet].numbers_of_vertices_in_facets = 10;
        model->polygons[*count_of_facet].vertices = (int *)malloc(model->polygons[*count_of_facet].numbers_of_vertices_in_facets * sizeof(int));
        if (model->polygons[*count_of_facet].vertices != NULL) {
          ExitCode = scan_facet(count_of_facet, fp, model);
          if (ExitCode == IS_NOT_A_NUMBER) {
            ExitCode = OK;
          } else if (ExitCode == OK){
            ++*count_of_facet;
          }
        }
      } else {
        ExitCode = ERROR;
      }
  }
  return ExitCode;
}
