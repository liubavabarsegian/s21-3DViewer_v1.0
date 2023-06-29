#include "main.h"

int main(void) {

    data model;
    model.count_of_vertexes = 10;
    model.count_of_facets = 10;
    model.vertices = (vertice *)malloc(model.count_of_vertexes * sizeof(vertice));
    model.polygons = (polygon_t *)malloc(model.count_of_facets * sizeof(polygon_t));

  char filename[13] = "test_cat.obj";
  size_t counter = 0;
  int ExitCode = parser(filename, &model, &counter);
  model.count_of_vertexes = counter;
    for (size_t i = 1; i <= model.count_of_vertexes; ++i) {
        //model.vertices[i];
        printf("%lf %lf %lf\n", model.vertices[i].x, model.vertices[i].y, model.vertices[i].z);
    }


  //printf("\n%d\n", ExitCode);



    free(model.vertices);
  if (ExitCode != OK) {
    printf("\nERROR\n");
  }
  return 0;
}

int parser(char *filename, data *model, size_t *real_count_of_vertices) {
  int ExitCode = OK;
  FILE *fp;
  fp = fopen(filename, "r");
  if (fp != NULL) {
    char line[50];
    size_t counter = 0;
    size_t counter_facet = 0;
    double x, y, z;
    char v[2];
    char *estr;
    estr = fgets(line, sizeof(line), fp);
    while (estr != NULL) {
        model->polygons->numbers_of_vertexes_in_facets = 10;
        size_t counter_numbers_of_vertexes_in_facets = 0;
        model->polygons->vertices = (int *)malloc(model->polygons->numbers_of_vertexes_in_facets * sizeof(int));
        v[0] = '\0';
        sscanf(line, "%s", v);
        if (strcmp(v, "v") == 0) {
            ++counter;
            sscanf(line, "%s%lf%lf%lf", v, &x, &y, &z);
            //printf("%d\t%s\t%lf %lf %lf\n", counter, v, x, y, z);
            
            if (counter < model->count_of_vertexes) {
                model->vertices[counter].x = x;
                model->vertices[counter].y = y;
                model->vertices[counter].z = z;
            } else {
                model->count_of_vertexes *= 2;
                model->vertices = (vertice *)realloc(model->vertices, model->count_of_vertexes * sizeof(vertice));
                model->vertices[counter].x = x;
                model->vertices[counter].y = y;
                model->vertices[counter].z = z;
            }
        } else if (strcmp(v, "f") == 0) {
            //  обработка facet' ов
            
            for (size_t i = 0; i < strlen(line); ++i) {
                if (line[i] >= '0' && line[i] <= '9') {
                    if (line[i - 1] == ' ') {
                        if (counter_facet <= model->count_of_facets) {
                            if (counter_numbers_of_vertexes_in_facets <= model->polygons->numbers_of_vertexes_in_facets) {
                                
                            } else {
                                model->polygons->numbers_of_vertexes_in_facets *= 2;
                                model->polygons->vertices = (int *)realloc(model->polygons->vertices, model->polygons->numbers_of_vertexes_in_facets * sizeof(int));
                            }
                            //model->polygons->numbers_of_vertexes_in_facets
                        } else {
                            model->count_of_facets *= 2;
                            model->polygons = (polygon_t *)realloc(model->polygons, model->count_of_facets * sizeof(polygon_t));
                        }
                        ++counter_facet;
                    }
                }
            }

        }


        
        estr = fgets(line, sizeof(line), fp);
    }
    *real_count_of_vertices = counter;

    //  проверка на нормальность завершения работы с файлом (если)
    if (feof(fp) == 0) {
        ExitCode = ERROR;
    }

    // Закрываем файл
    if (fclose(fp) == EOF) {
      ExitCode = ERROR;
    }
  } else {
    ExitCode = ERROR;
    getchar();
  }
  return ExitCode;
}