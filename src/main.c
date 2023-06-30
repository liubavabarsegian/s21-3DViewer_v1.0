#include "main.h"
#include <errno.h>

int main(void) {
  data model;
  model.count_of_vertexes = 10;
  model.count_of_facets = 10;
  model.vertices = (vertice *)malloc(model.count_of_vertexes * sizeof(vertice));
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

int parser(char *filename, data *model, size_t *real_count_of_vertices, size_t *real_count_of_facet) {
  int ExitCode = OK;
  FILE *fp;
  fp = fopen(filename, "r");
  if (fp != NULL) {
    size_t line_size = count_line_size(fp);
    size_t next_line_size = line_size;
    char *line = (char *)malloc((line_size + 1) * sizeof(char));
    size_t counter = 0;
    size_t counter_facet = 0;
    
    while (fgets(line, line_size + 1, fp) != NULL && next_line_size) {

      if (line[0] == 'v') {  
        ExitCode = scan_vertice(&counter, line, model);
      } else if (line[0] == 'f') {
        //  обработка facet' ов
        if (counter_facet >= model->count_of_facets) {
          model->count_of_facets *= 2;
          model->polygons = (polygon_t *)realloc(model->polygons,model->count_of_facets * sizeof(polygon_t));
        }
        model->polygons[counter_facet].numbers_of_vertexes_in_facets = 10;
        model->polygons[counter_facet].vertices = (int *)malloc(model->polygons[counter_facet].numbers_of_vertexes_in_facets * sizeof(int));
        if (model->polygons[counter_facet].vertices != NULL) {
          size_t counter_numbers_of_vertexes_in_facets = 0;
          for (size_t i = 0; i < strlen(line); ++i) {
            if (line[i] >= '0' && line[i] <= '9') {
              if (line[i - 1] == ' ') {
                int number = line[i] - '0';
                if (i + 1 < strlen(line)) {
                  int j = i + 1;
                  while (line[j] != ' ' && line[j] != '/' && line[j] != '\n') {
                    number *= 10;
                    number += line[j] - '0';
                    ++j;
                  }
                  
                }
                if (counter_numbers_of_vertexes_in_facets >= model->polygons->numbers_of_vertexes_in_facets) {
                  model->polygons->numbers_of_vertexes_in_facets *= 2;
                  model->polygons->vertices = (int *)realloc(model->polygons->vertices,model->polygons->numbers_of_vertexes_in_facets * sizeof(int));
                }
                model->polygons[counter_facet].vertices[counter_numbers_of_vertexes_in_facets] = number;
                ++counter_numbers_of_vertexes_in_facets;
              }
            }
          }
          model->polygons[counter_facet].numbers_of_vertexes_in_facets = counter_numbers_of_vertexes_in_facets;
          ++counter_facet;
          }
      }
      //estr = fgets(line, sizeof(line), fp);
      //fseek(fp, 1, SEEK_CUR);
      next_line_size = count_line_size(fp);
      if (next_line_size > line_size) {
        line = (char *)realloc(line, (next_line_size + 1) * sizeof(char));
        line_size = next_line_size;
      }
    }
    *real_count_of_vertices = counter;
    *real_count_of_facet = counter_facet;

    //  проверка на нормальность завершения работы с файлом (если)
    if (feof(fp) == 0) {
      ExitCode = ERROR;
    }

    // Закрываем файл
    if (fclose(fp) == EOF) {
      ExitCode = ERROR;
    }
    free(line);
  } else {
    ExitCode = ERROR;
    getchar();
  }
  return ExitCode;
}

void print_vertexes(data *model) {
  for (size_t i = 1; i <= model->count_of_vertexes; ++i) {
    //printf("%ld\t", i + 1);
    printf("%ld\t%lf %lf %lf\n", i, model->vertices[i].x, model->vertices[i].y, model->vertices[i].z);
  }
}

void print_polygon(data *model) {
  for (size_t i = 0; i < model->count_of_facets; ++i) {
    for (size_t j = 0; j < model->polygons[i].numbers_of_vertexes_in_facets; ++j) {
      printf("%d ", model->polygons[i].vertices[j]);
    }
    //printf("\t%ld", model->polygons[i].numbers_of_vertexes_in_facets);
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
  size_t counter = 0;
  size_t counter_facet = 0;
  int ExitCode = parser(filename, model, &counter, &counter_facet);
  if (ExitCode == OK) {
  model->count_of_vertexes = counter;
  model->count_of_facets = counter_facet;
   print_vertexes(model);
   printf("\n");
   print_polygon(model);
  } else {
    printf("\nERROR\n");
  }
  free_vertices_in_facets(model);
}

size_t count_line_size(FILE *fp) {
  size_t counter = 1;
  char ch = getc(fp);
  while(ch != EOF && ch != '\n') {
    ++counter;
    ch = getc(fp);
  }
  if (ch == EOF) {
    counter = 0;
  }
  fseek(fp, -((counter)* sizeof(char)), SEEK_CUR);
  return counter;
}

int scan_vertice(size_t *counter, char *line, data *model) {
  int ExitCode = OK;
  double x, y, z;
  ++*counter;
  char v[2];
  v[0] = '\0';
      //sscanf(line, "%s", v);
  sscanf(line, "%s%lf%lf%lf", v, &x, &y, &z);

  if (*counter >= model->count_of_vertexes) {  // ? >
    model->count_of_vertexes *= 2;
    model->vertices = (vertice *)realloc(model->vertices, model->count_of_vertexes * sizeof(vertice));
  }
  if (model->vertices != NULL) {
    model->vertices[*counter].x = x;
    model->vertices[*counter].y = y;
    model->vertices[*counter].z = z;
  } else {
    ExitCode = ERROR;
  }
  return ExitCode;
}