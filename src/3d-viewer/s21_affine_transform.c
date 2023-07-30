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

s21_matrix s21_mult_matrix(s21_matrix *A, s21_matrix *B) {
    s21_matrix result = {0};
    s21_create_matrix(A->rows, B->columns, &result);
    for (int i = 0; i < result.rows; ++i) {
        for (int j = 0; j < result.columns; ++j) {
            for (int k = 0; k < A->columns;) {
                result.matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
                k++;
            }
        }
    }
    return result;
}

void mult_matrix(double** A, double** B, double** result) {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 1; ++j) {
            double sum = 0;
            for (int k = 0; k < 4; ++k) {
                sum += A[i][k] * B[j][k];
            }
            result[j][i] = sum;
        }
    }
}

void s21_remove_matrix(s21_matrix *A) {
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

s21_matrix* create_resize_matrix(double x, double y, double z) {
    s21_matrix* result = (s21_matrix*)malloc(sizeof(s21_matrix));
    create_matrix(result, 4, 4);
    result->matrix[0][0] = x;
    result->matrix[1][1] = y;
    result->matrix[2][2] = z;
    result->matrix[3][3] = 1;
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

void moving(s21_data *data, double x, double y, double z) {
    s21_matrix result = create_af_matrix(x, y, z);
    for (int i = 0; i < data->count_vert; ++i) {
        s21_matrix temp = data->matrix_3d[i];
        data->matrix_3d[i] = s21_mult_matrix(&result, &(data->matrix_3d[i]));
        s21_remove_matrix(&temp);
    }
    s21_remove_matrix(&result);
}

void resize_model(s21_data *data, double x, double y, double z) {
    s21_matrix* tmp = create_resize_matrix(x, y, z);
    for (int i = 0; i < data->count_vert; ++i) {
//        data->matrix_3d[i] = s21_mult_matrix(&result, &(data->matrix_3d[i]));
        mult_matrix(tmp->matrix, &(data->matrix_3d->matrix[i]), &(data->matrix_3d->matrix[i]));
    }
//    s21_remove_matrix(&tmp);
}

void rotation(s21_data *data, double x, double y, double z) {
    s21_matrix x_matrix = create_x_rotation_matrix(x);
    s21_matrix y_matrix = create_y_rotation_matrix(y);
    s21_matrix z_matrix = create_z_rotation_matrix(z);
    s21_matrix temp_res = s21_mult_matrix(&x_matrix, &y_matrix);
    s21_matrix res = s21_mult_matrix(&temp_res, &z_matrix);
    for (int i = 0; i < data->count_vert; ++i) {
        s21_matrix temp = data->matrix_3d[i];
        data->matrix_3d[i] = s21_mult_matrix(&res, &(data->matrix_3d[i]));
        s21_remove_matrix(&temp);
    }

    s21_remove_matrix(&x_matrix);
    s21_remove_matrix(&y_matrix);
    s21_remove_matrix(&z_matrix);
    s21_remove_matrix(&temp_res);
    s21_remove_matrix(&res);
}
