#include "s21_affine_transform.h"

#include <math.h>
#define PI 3.1415926535

int s21_create_matrix(int rows, int columns, s21_matrix* result) {
  int return_value = RETURN_OK;
  if (result == NULL) {
    return_value = RETURN_WRONG_MATRIX;
  } else if (rows < 1 || columns < 1) {
    return_value = RETURN_WRONG_MATRIX;
    result->rows = rows;
    result->columns = columns;
    result->matrix = NULL;
  } else {
    result->rows = rows;
    result->columns = columns;
    result->matrix = calloc(rows, sizeof(double*) + sizeof(double) * columns);
    if (result->matrix == NULL) {
      return_value = RETURN_CALC_ERROR;
    } else {
      double* ptr = (double*)(result->matrix + rows);
      for (size_t i = 0; i < (size_t)rows; ++i) {
        result->matrix[i] = ptr + i * columns;
      }
    }
  }
  return return_value;
}

void mult_matrix(double** A, double** B, double** result) {
  double** tmp_res = (double**)malloc(sizeof(double*));
  tmp_res[0] = (double*)malloc(4 * sizeof(double));

  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 1; ++j) {
      double sum = 0;
      for (int k = 0; k < 4; ++k) {
        sum += A[i][k] * B[j][k];
      }
      tmp_res[j][i] = sum;
    }
  }

  for (int j = 0; j < 4; j++) {
    result[0][j] = tmp_res[0][j];
  }

  free(tmp_res[0]);
  free(tmp_res);
}

void s21_remove_matrix(s21_matrix* A) {
  if (A != NULL) {
    A->rows = 0;
    A->columns = 0;
    free(A->matrix);
    A->matrix = NULL;
  }
}

s21_matrix create_af_matrix(double x, double y, double z) {
  s21_matrix result = {0};
  s21_create_matrix(4, 4, &result);
  for (int i = 0; i < result.rows; ++i) {
    result.matrix[i][i] = 1;
  }
  result.matrix[0][3] = x;
  result.matrix[1][3] = y;
  result.matrix[2][3] = z;
  return result;
}

s21_matrix create_resize_matrix(double x, double y, double z) {
  s21_matrix result = {0};
  s21_create_matrix(4, 4, &result);
  result.matrix[0][0] = x;
  result.matrix[1][1] = y;
  result.matrix[2][2] = z;
  result.matrix[3][3] = 1;
  return result;
}

s21_matrix create_x_rotation_matrix(double x) {
  s21_matrix result = {0};
  s21_create_matrix(4, 4, &result);
  x = (x * PI) / 180;
  result.matrix[0][0] = 1;
  result.matrix[1][1] = cos(x);
  result.matrix[1][2] = sin(x);
  result.matrix[2][2] = cos(x);
  result.matrix[2][1] = -1 * sin(x);
  result.matrix[3][3] = 1;
  return result;
}

s21_matrix create_y_rotation_matrix(double y) {
  s21_matrix result = {0};
  s21_create_matrix(4, 4, &result);
  y = (y * PI) / 180;
  result.matrix[0][0] = cos(y);
  result.matrix[1][1] = 1;
  result.matrix[0][2] = -1 * sin(y);
  result.matrix[2][2] = cos(y);
  result.matrix[2][0] = sin(y);
  result.matrix[3][3] = 1;
  return result;
}

s21_matrix create_z_rotation_matrix(double z) {
  s21_matrix result = {0};
  s21_create_matrix(4, 4, &result);
  z = (z * PI) / 180;
  result.matrix[0][0] = cos(z);
  result.matrix[1][1] = cos(z);
  result.matrix[0][1] = sin(z);
  result.matrix[2][2] = 1;
  result.matrix[1][0] = -1 * sin(z);
  result.matrix[3][3] = 1;
  return result;
}

void moving(s21_data* data, double x, double y, double z) {
  s21_matrix result = create_af_matrix(x, y, z);
  for (unsigned i = 0; i < data->count_vert; ++i) {
    mult_matrix(result.matrix, &(data->matrix_3d->matrix[i]),
                &(data->matrix_3d->matrix[i]));
  }
  s21_remove_matrix(&result);
}

void resize_model(s21_data* data, double x, double y, double z) {
  s21_matrix tmp = create_resize_matrix(x, y, z);
  for (unsigned i = 0; i < data->count_vert; ++i) {
    mult_matrix(tmp.matrix, &(data->matrix_3d->matrix[i]),
                &(data->matrix_3d->matrix[i]));
  }
  s21_remove_matrix(&tmp);
}

void rotation(s21_data* data, double x, double y, double z) {
  if (x != 0) {
    s21_matrix x_matrix = create_x_rotation_matrix(x);
    for (unsigned i = 0; i < data->count_vert; ++i) {
      mult_matrix(x_matrix.matrix, &(data->matrix_3d->matrix[i]),
                  &(data->matrix_3d->matrix[i]));
    }
    s21_remove_matrix(&x_matrix);
  } else if (y != 0) {
    s21_matrix y_matrix = create_y_rotation_matrix(y);
    for (unsigned i = 0; i < data->count_vert; ++i) {
      mult_matrix(y_matrix.matrix, &(data->matrix_3d->matrix[i]),
                  &(data->matrix_3d->matrix[i]));
    }
    s21_remove_matrix(&y_matrix);
  } else if (z != 0) {
    s21_matrix z_matrix = create_z_rotation_matrix(z);
    for (unsigned i = 0; i < data->count_vert; ++i) {
      mult_matrix(z_matrix.matrix, &(data->matrix_3d->matrix[i]),
                  &(data->matrix_3d->matrix[i]));
    }
    s21_remove_matrix(&z_matrix);
  }
}
