#include <check.h>
#include "../3d-viewer/parser.h"
#include "../3d-viewer/s21_affine_transform.h"

// ========== example ================
// int main(void) {
//  s21_data model;
//  model.count_vert = 10;
//  model.count_facets = 10;
//  model.matrix_3d = (s21_matrix *)malloc(sizeof(s21_matrix));
//  if (model.matrix_3d != NULL) {
//    if (create_matrix(model.matrix_3d, model.count_vert, 4) == OK) {
//      model.polygons = (s21_facets *)malloc(model.count_facets * sizeof(s21_facets));
//      int count_allocated_blocks = 0;
//      if (model.polygons != NULL) {
//       if(open_and_parse(&model, "../tests/cube.obj", &count_allocated_blocks) == OK){
//         // something
//       //     printf("%d\n", model.count_vert);
//       //  printf("%d", model.count_facets);
//       }
//        free(model.polygons);
//      }
//      free_matrix(model.matrix_3d, count_allocated_blocks);
//      free(model.matrix_3d);
//    }
//  }
  
//  return 0;
// }
// ========== test open file and parser ==========
START_TEST(check_count_vert_and_facets_alf) {
 s21_data model;
 model.count_vert = 10;
 model.count_facets = 10;
 model.matrix_3d = (s21_matrix *)malloc(sizeof(s21_matrix));
 if (model.matrix_3d != NULL) {
   if (create_matrix(model.matrix_3d, model.count_vert, 4) == OK) {
     model.polygons = (s21_facets *)malloc(model.count_facets * sizeof(s21_facets));
     int count_allocated_blocks = 0;
     if (model.polygons != NULL) {
      if(open_and_parse(&model, "tests/alf.obj", &count_allocated_blocks) == OK){
        ck_assert_int_eq(3618, model.count_vert);
        ck_assert_int_eq(3442, model.count_facets);
      }
      free(model.polygons);
     }
     free_matrix(model.matrix_3d, count_allocated_blocks);
     free(model.matrix_3d);
   }
 }
}
END_TEST

START_TEST(open_error_file) {
 s21_data model;
 model.count_vert = 10;
 model.count_facets = 10;
 model.matrix_3d = (s21_matrix *)malloc(sizeof(s21_matrix));
 if (model.matrix_3d != NULL) {
   if (create_matrix(model.matrix_3d, model.count_vert, 4) == OK) {
     model.polygons = (s21_facets *)malloc(model.count_facets * sizeof(s21_facets));
     int count_allocated_blocks = 0;
     if (model.polygons != NULL) {
      int res = open_and_parse(&model, "error_file.obj", &count_allocated_blocks);
      ck_assert_int_eq(ERROR, res);
       free(model.polygons);
     }
     free_matrix(model.matrix_3d, count_allocated_blocks);
     free(model.matrix_3d);
   }
 }
}
END_TEST

START_TEST(check_count_vert_and_facets_cube) {
 s21_data model;
 model.count_vert = 10;
 model.count_facets = 10;
 model.matrix_3d = (s21_matrix *)malloc(sizeof(s21_matrix));
 if (model.matrix_3d != NULL) {
   if (create_matrix(model.matrix_3d, model.count_vert, 4) == OK) {
     model.polygons = (s21_facets *)malloc(model.count_facets * sizeof(s21_facets));
     int count_allocated_blocks = 0;
     if (model.polygons != NULL) {
      if(open_and_parse(&model, "tests/cube.obj", &count_allocated_blocks) == OK){
        ck_assert_int_eq(8, model.count_vert);
        ck_assert_int_eq(10, model.count_facets);
      }
       free(model.polygons);
     }
     free_matrix(model.matrix_3d, count_allocated_blocks);
     free(model.matrix_3d);
   }
 }
}
END_TEST




// == test rotation, moving and resize model (test affine transform) ==
START_TEST(s21_rotationX) {
  s21_matrix result;
  result.matrix = (double **) malloc(8 * sizeof(double *));
  result.rows = 8;
  result.columns = 4;
  double mat1[4] = {-1.000000, -1.158456, -0.811160, 1.000000};
  double mat2[4] = {-1.000000, -0.811160, 1.158456, 1.000000};
  double mat3[4] = {-1.000000, 0.811160, -1.158456, 1.000000};
  double mat4[4] = {-1.000000, 1.158456, 0.811160, 1.000000};
  double mat5[4] = {1.000000, -1.158456, -0.811160, 1.000000};
  double mat6[4] = {1.000000, -0.811160, 1.158456, 1.000000};
  double mat7[4] = {1.000000, 0.811160, -1.158456, 1.000000};
  double mat8[4] = {1.000000, 1.158456, 0.811160, 1.000000};
  result.matrix[0] = &mat1[0];
  result.matrix[1] = &mat2[0];
  result.matrix[2] = &mat3[0];
  result.matrix[3] = &mat4[0];
  result.matrix[4] = &mat5[0];
  result.matrix[5] = &mat6[0];
  result.matrix[6] = &mat7[0];
  result.matrix[7] = &mat8[0];

 s21_data model;
 model.count_vert = 10;
 model.count_facets = 10;
 model.matrix_3d = (s21_matrix *)malloc(sizeof(s21_matrix));
 if (model.matrix_3d != NULL) {
   if (create_matrix(model.matrix_3d, model.count_vert, 4) == OK) {
     model.polygons = (s21_facets *)malloc(model.count_facets * sizeof(s21_facets));
     int count_allocated_blocks = 0;
     if (model.polygons != NULL) {
      if(open_and_parse(&model, "tests/cube.obj", &count_allocated_blocks) == OK){
        rotation(&model, 10, 0 , 0);
        int not_error = s21_eq_matrix(model.matrix_3d, &result);
        ck_assert_int_eq(0, not_error);
        free(result.matrix);
      }
       free(model.polygons);
     }
     free_matrix(model.matrix_3d, count_allocated_blocks);
     free(model.matrix_3d);
   }
 }
}
END_TEST

START_TEST(s21_rotationY) {
  s21_matrix result;
  result.matrix = (double **) malloc(8 * sizeof(double *));
  result.rows = 8;
  result.columns = 4;
  double mat1[4] = {1.383310, -1.000000, -0.294032, 1.000000};
  double mat2[4] = {-0.294032, -1.000000, -1.383310, 1.000000};
  double mat3[4] = {1.383310, 1.000000, -0.294032, 1.000000};
  double mat4[4] = {-0.294032, 1.000000, -1.383310, 1.000000};
  double mat5[4] = {0.294032, -1.000000, 1.383310, 1.000000};
  double mat6[4] = {-1.383310, -1.000000, 0.294032, 1.000000};
  double mat7[4] = {0.294032, 1.000000, 1.383310, 1.000000};
  double mat8[4] = {-1.383310, 1.000000, 0.294032, 1.000000};
  result.matrix[0] = &mat1[0];
  result.matrix[1] = &mat2[0];
  result.matrix[2] = &mat3[0];
  result.matrix[3] = &mat4[0];
  result.matrix[4] = &mat5[0];
  result.matrix[5] = &mat6[0];
  result.matrix[6] = &mat7[0];
  result.matrix[7] = &mat8[0];

 s21_data model;
 model.count_vert = 10;
 model.count_facets = 10;
 model.matrix_3d = (s21_matrix *)malloc(sizeof(s21_matrix));
 if (model.matrix_3d != NULL) {
   if (create_matrix(model.matrix_3d, model.count_vert, 4) == OK) {
     model.polygons = (s21_facets *)malloc(model.count_facets * sizeof(s21_facets));
     int count_allocated_blocks = 0;
     if (model.polygons != NULL) {
      if(open_and_parse(&model, "tests/cube.obj", &count_allocated_blocks) == OK){
        rotation(&model, 0, 123 , 0);
        int not_error = s21_eq_matrix(model.matrix_3d, &result);
        ck_assert_int_eq(0, not_error);
        free(result.matrix);
      }
       free(model.polygons);
     }
     free_matrix(model.matrix_3d, count_allocated_blocks);
     free(model.matrix_3d);
   }
 }
}
END_TEST

START_TEST(s21_rotationZ) {
  s21_matrix result;
  result.matrix = (double **) malloc(8 * sizeof(double *));
  result.rows = 8;
  result.columns = 4;
  double mat1[4] = {-1.083350, -0.901774, -1.000000, 1.000000};
  double mat2[4] = {-1.083350, -0.901774, 1.000000, 1.000000};
  double mat3[4] = {-0.909039, 1.075423, -1.000000, 1.000000};
  double mat4[4] = {-0.909039, 1.075423, 1.000000, 1.000000};
  double mat5[4] = {0.909039, -1.075423, -1.000000, 1.000000};
  double mat6[4] = {0.909039, -1.075423, 1.000000, 1.000000};
  double mat7[4] = {1.083350, 0.901774, -1.000000, 1.000000};
  double mat8[4] = {1.083350, 0.901774, 1.000000, 1.000000};
  result.matrix[0] = &mat1[0];
  result.matrix[1] = &mat2[0];
  result.matrix[2] = &mat3[0];
  result.matrix[3] = &mat4[0];
  result.matrix[4] = &mat5[0];
  result.matrix[5] = &mat6[0];
  result.matrix[6] = &mat7[0];
  result.matrix[7] = &mat8[0];

 s21_data model;
 model.count_vert = 10;
 model.count_facets = 10;
 model.matrix_3d = (s21_matrix *)malloc(sizeof(s21_matrix));
 if (model.matrix_3d != NULL) {
   if (create_matrix(model.matrix_3d, model.count_vert, 4) == OK) {
     model.polygons = (s21_facets *)malloc(model.count_facets * sizeof(s21_facets));
     int count_allocated_blocks = 0;
     if (model.polygons != NULL) {
      if(open_and_parse(&model, "tests/cube.obj", &count_allocated_blocks) == OK){
        rotation(&model, 0, 0 , 5);
        int not_error = s21_eq_matrix(model.matrix_3d, &result);
        ck_assert_int_eq(0, not_error);
        free(result.matrix);
      }
       free(model.polygons);
     }
     free_matrix(model.matrix_3d, count_allocated_blocks);
     free(model.matrix_3d);
   }
 }
}
END_TEST

START_TEST(s21_rotation) {
  s21_matrix result;
  result.matrix = (double **) malloc(8 * sizeof(double *));
  result.rows = 8;
  result.columns = 4;
  double mat1[4] = {-1.000000, -1.114415, -0.870677, 1.000000};
  double mat2[4] = {-1.000000, -0.870677, 1.114415, 1.000000};
  double mat3[4] = {-1.000000, 0.870677, -1.114415, 1.000000};
  double mat4[4] = {-1.000000, 1.114415, 0.870677, 1.000000};
  double mat5[4] = {1.000000, -1.114415, -0.870677, 1.000000};
  double mat6[4] = {1.000000, -0.870677, 1.114415, 1.000000};
  double mat7[4] = {1.000000, 0.870677, -1.114415, 1.000000};
  double mat8[4] = {1.000000, 1.114415, 0.870677, 1.000000};
  result.matrix[0] = &mat1[0];
  result.matrix[1] = &mat2[0];
  result.matrix[2] = &mat3[0];
  result.matrix[3] = &mat4[0];
  result.matrix[4] = &mat5[0];
  result.matrix[5] = &mat6[0];
  result.matrix[6] = &mat7[0];
  result.matrix[7] = &mat8[0];

 s21_data model;
 model.count_vert = 10;
 model.count_facets = 10;
 model.matrix_3d = (s21_matrix *)malloc(sizeof(s21_matrix));
 if (model.matrix_3d != NULL) {
   if (create_matrix(model.matrix_3d, model.count_vert, 4) == OK) {
     model.polygons = (s21_facets *)malloc(model.count_facets * sizeof(s21_facets));
     int count_allocated_blocks = 0;
     if (model.polygons != NULL) {
      if(open_and_parse(&model, "tests/cube.obj", &count_allocated_blocks) == OK){
        rotation(&model, 7, 23 , 89);
        int not_error = s21_eq_matrix(model.matrix_3d, &result);
        ck_assert_int_eq(0, not_error);
        free(result.matrix);
      }
       free(model.polygons);
     }
     free_matrix(model.matrix_3d, count_allocated_blocks);
     free(model.matrix_3d);
   }
 }
}
END_TEST

START_TEST(test_resize_model) {
  s21_matrix result;
  result.matrix = (double **) malloc(8 * sizeof(double *));
  result.rows = 8;
  result.columns = 4;

  double mat1[] = {-0.500000, -0.500000, -0.500000, 1.000000};
  double mat2[] = {-0.500000, -0.500000, 1.500000, 1.000000};
  double mat3[] = {-0.500000, 1.500000, -0.500000, 1.000000};
  double mat4[] = {-0.500000, 1.500000, 1.500000, 1.000000 };
  double mat5[] = {1.500000, -0.500000, -0.500000, 1.000000};
  double mat6[] = {1.500000, -0.500000, 1.500000, 1.000000};
  double mat7[] = {1.500000, 1.500000, -0.500000, 1.000000};
  double mat8[] = {1.500000, 1.500000, 1.500000, 1.000000};
  result.matrix[0] = &mat1[0];
  result.matrix[1] = &mat2[0];
  result.matrix[2] = &mat3[0];
  result.matrix[3] = &mat4[0];
  result.matrix[4] = &mat5[0];
  result.matrix[5] = &mat6[0];
  result.matrix[6] = &mat7[0];
  result.matrix[7] = &mat8[0];

 s21_data model;
 model.count_vert = 10;
 model.count_facets = 10;
 model.matrix_3d = (s21_matrix *)malloc(sizeof(s21_matrix));
 if (model.matrix_3d != NULL) {
   if (create_matrix(model.matrix_3d, model.count_vert, 4) == OK) {
     model.polygons = (s21_facets *)malloc(model.count_facets * sizeof(s21_facets));
     int count_allocated_blocks = 0;
     if (model.polygons != NULL) {
      if(open_and_parse(&model, "tests/cube.obj", &count_allocated_blocks) == OK){
        resize_model(&model, 0.5, 0.5, 0.5);
        int not_error = s21_eq_matrix(model.matrix_3d, &result);
        free(result.matrix);
        ck_assert_int_eq(0, not_error);
      }
       free(model.polygons);
     }
     free_matrix(model.matrix_3d, count_allocated_blocks);
     free(model.matrix_3d);
   }
 }
  
}
END_TEST

// START_TEST(test_moving_X) {
//   s21_matrix result;
//   result.matrix = (double **) malloc(8 * sizeof(double *));
//   result.rows = 8;
//   result.columns = 4;

//   double mat1[4] = {-1.000000, -1.000000, 1.000000, 1.000000};
//   double mat2[4] = {-1.000000, -1.000000, 3.000000, 1.000000};
//   double mat3[4] = {-1.000000, 1.000000, 1.000000, 1.000000};
//   double mat4[4] = {-1.000000, 1.000000, 3.000000, 1.000000};
//   double mat5[4] = {1.000000, -1.000000, 1.000000, 1.000000};
//   double mat6[4] = {1.000000, -1.000000, 3.000000, 1.000000};
//   double mat7[4] = {1.000000, 1.000000, 1.000000, 1.000000};
//   double mat8[4] = {1.000000, 1.000000, 3.000000, 1.000000};

//   result.matrix[0] = &mat1[0];
//   result.matrix[1] = &mat2[0];
//   result.matrix[2] = &mat3[0];
//   result.matrix[3] = &mat4[0];
//   result.matrix[4] = &mat5[0];
//   result.matrix[5] = &mat6[0];
//   result.matrix[6] = &mat7[0];
//   result.matrix[7] = &mat8[0];
// // print_matrix(result);
// // printf("\n");
//  s21_data model;
//  model.count_vert = 10;
//  model.count_facets = 10;
//  model.matrix_3d = (s21_matrix *)malloc(sizeof(s21_matrix));
//  if (model.matrix_3d != NULL) {
//    if (create_matrix(model.matrix_3d, model.count_vert, 4) == OK) {
//      model.polygons = (s21_facets *)malloc(model.count_facets * sizeof(s21_facets));
//      int count_allocated_blocks = 0;
//      if (model.polygons != NULL) {
//       if(open_and_parse(&model, "tests/cube.obj", &count_allocated_blocks) == OK){
//         // resize_model(&model, 0.5, 0.5, 0.5);
//         moving(&model, 0, 0, 2);
//         // printf("%d\t%d\n", model.count_vert, model.count_facets);
//         // print_matrix(*model.matrix_3d);
//         // printf("\n");
//         // print_polygon(&model);
//         int not_error = s21_eq_matrix(model.matrix_3d, &result);
//         ck_assert_int_eq(0, not_error);
//         free(result.matrix);
//         // ck_assert_int_eq(0, not_error);
//       }
//        free(model.polygons);
//      }
//      free_matrix(model.matrix_3d, count_allocated_blocks);
//      free(model.matrix_3d);
//    }
//  }
  
// }
// END_TEST

// START_TEST(test_moving_Y) {
//   s21_matrix result;
//   result.matrix = (double **) malloc(8 * sizeof(double *));
//   result.rows = 8;
//   result.columns = 4;

//   double mat1[4] = {-1.000000, -1.000000, 1.000000, 1.000000};
//   double mat2[4] = {-1.000000, -1.000000, 3.000000, 1.000000};
//   double mat3[4] = {-1.000000, 1.000000, 1.000000, 1.000000};
//   double mat4[4] = {-1.000000, 1.000000, 3.000000, 1.000000};
//   double mat5[4] = {1.000000, -1.000000, 1.000000, 1.000000};
//   double mat6[4] = {1.000000, -1.000000, 3.000000, 1.000000};
//   double mat7[4] = {1.000000, 1.000000, 1.000000, 1.000000};
//   double mat8[4] = {1.000000, 1.000000, 3.000000, 1.000000};

//   result.matrix[0] = &mat1[0];
//   result.matrix[1] = &mat2[0];
//   result.matrix[2] = &mat3[0];
//   result.matrix[3] = &mat4[0];
//   result.matrix[4] = &mat5[0];
//   result.matrix[5] = &mat6[0];
//   result.matrix[6] = &mat7[0];
//   result.matrix[7] = &mat8[0];
// // print_matrix(result);
// // printf("\n");
//  s21_data model;
//  model.count_vert = 10;
//  model.count_facets = 10;
//  model.matrix_3d = (s21_matrix *)malloc(sizeof(s21_matrix));
//  if (model.matrix_3d != NULL) {
//    if (create_matrix(model.matrix_3d, model.count_vert, 4) == OK) {
//      model.polygons = (s21_facets *)malloc(model.count_facets * sizeof(s21_facets));
//      int count_allocated_blocks = 0;
//      if (model.polygons != NULL) {
//       if(open_and_parse(&model, "tests/cube.obj", &count_allocated_blocks) == OK){
//         // resize_model(&model, 0.5, 0.5, 0.5);
//         moving(&model, 0, 0, 2);
//         // printf("%d\t%d\n", model.count_vert, model.count_facets);
//         // print_matrix(*model.matrix_3d);
//         // printf("\n");
//         // print_polygon(&model);
//         int not_error = s21_eq_matrix(model.matrix_3d, &result);
//         ck_assert_int_eq(0, not_error);
//         free(result.matrix);
//         // ck_assert_int_eq(0, not_error);
//       }
//        free(model.polygons);
//      }
//      free_matrix(model.matrix_3d, count_allocated_blocks);
//      free(model.matrix_3d);
//    }
//  }
  
// }
// END_TEST

// START_TEST(test_moving_Z) {
//   s21_matrix result;
//   result.matrix = (double **) malloc(8 * sizeof(double *));
//   result.rows = 8;
//   result.columns = 4;

//   double mat1[4] = {-1.000000, -1.000000, 1.000000, 1.000000};
//   double mat2[4] = {-1.000000, -1.000000, 3.000000, 1.000000};
//   double mat3[4] = {-1.000000, 1.000000, 1.000000, 1.000000};
//   double mat4[4] = {-1.000000, 1.000000, 3.000000, 1.000000};
//   double mat5[4] = {1.000000, -1.000000, 1.000000, 1.000000};
//   double mat6[4] = {1.000000, -1.000000, 3.000000, 1.000000};
//   double mat7[4] = {1.000000, 1.000000, 1.000000, 1.000000};
//   double mat8[4] = {1.000000, 1.000000, 3.000000, 1.000000};

//   result.matrix[0] = &mat1[0];
//   result.matrix[1] = &mat2[0];
//   result.matrix[2] = &mat3[0];
//   result.matrix[3] = &mat4[0];
//   result.matrix[4] = &mat5[0];
//   result.matrix[5] = &mat6[0];
//   result.matrix[6] = &mat7[0];
//   result.matrix[7] = &mat8[0];
// // print_matrix(result);
// // printf("\n");
//  s21_data model;
//  model.count_vert = 10;
//  model.count_facets = 10;
//  model.matrix_3d = (s21_matrix *)malloc(sizeof(s21_matrix));
//  if (model.matrix_3d != NULL) {
//    if (create_matrix(model.matrix_3d, model.count_vert, 4) == OK) {
//      model.polygons = (s21_facets *)malloc(model.count_facets * sizeof(s21_facets));
//      int count_allocated_blocks = 0;
//      if (model.polygons != NULL) {
//       if(open_and_parse(&model, "tests/cube.obj", &count_allocated_blocks) == OK){
//         // resize_model(&model, 0.5, 0.5, 0.5);
//         moving(&model, 0, 0, 2);
//         // printf("%d\t%d\n", model.count_vert, model.count_facets);
//         // print_matrix(*model.matrix_3d);
//         // printf("\n");
//         // print_polygon(&model);
//         int not_error = s21_eq_matrix(model.matrix_3d, &result);
//         ck_assert_int_eq(0, not_error);
//         free(result.matrix);
//         // ck_assert_int_eq(0, not_error);
//       }
//        free(model.polygons);
//      }
//      free_matrix(model.matrix_3d, count_allocated_blocks);
//      free(model.matrix_3d);
//    }
//  }
  
// }
// END_TEST

// START_TEST(test_moving) {
//   s21_matrix result;
//   result.matrix = (double **) malloc(8 * sizeof(double *));
//   result.rows = 8;
//   result.columns = 4;

//   double mat1[4] = {-1.000000, -1.000000, 1.000000, 1.000000};
//   double mat2[4] = {-1.000000, -1.000000, 3.000000, 1.000000};
//   double mat3[4] = {-1.000000, 1.000000, 1.000000, 1.000000};
//   double mat4[4] = {-1.000000, 1.000000, 3.000000, 1.000000};
//   double mat5[4] = {1.000000, -1.000000, 1.000000, 1.000000};
//   double mat6[4] = {1.000000, -1.000000, 3.000000, 1.000000};
//   double mat7[4] = {1.000000, 1.000000, 1.000000, 1.000000};
//   double mat8[4] = {1.000000, 1.000000, 3.000000, 1.000000};

//   result.matrix[0] = &mat1[0];
//   result.matrix[1] = &mat2[0];
//   result.matrix[2] = &mat3[0];
//   result.matrix[3] = &mat4[0];
//   result.matrix[4] = &mat5[0];
//   result.matrix[5] = &mat6[0];
//   result.matrix[6] = &mat7[0];
//   result.matrix[7] = &mat8[0];
// // print_matrix(result);
// // printf("\n");
//  s21_data model;
//  model.count_vert = 10;
//  model.count_facets = 10;
//  model.matrix_3d = (s21_matrix *)malloc(sizeof(s21_matrix));
//  if (model.matrix_3d != NULL) {
//    if (create_matrix(model.matrix_3d, model.count_vert, 4) == OK) {
//      model.polygons = (s21_facets *)malloc(model.count_facets * sizeof(s21_facets));
//      int count_allocated_blocks = 0;
//      if (model.polygons != NULL) {
//       if(open_and_parse(&model, "tests/cube.obj", &count_allocated_blocks) == OK){
//         // resize_model(&model, 0.5, 0.5, 0.5);
//         moving(&model, 0, 0, 2);
//         // printf("%d\t%d\n", model.count_vert, model.count_facets);
//         // print_matrix(*model.matrix_3d);
//         // printf("\n");
//         // print_polygon(&model);
//         int not_error = s21_eq_matrix(model.matrix_3d, &result);
//         ck_assert_int_eq(0, not_error);
//         free(result.matrix);
//         // ck_assert_int_eq(0, not_error);
//       }
//        free(model.polygons);
//      }
//      free_matrix(model.matrix_3d, count_allocated_blocks);
//      free(model.matrix_3d);
//    }
//  }
  
// }
// END_TEST

int main(void) {
  Suite *s1 = suite_create("Core");
  TCase *tc = tcase_create("Core");
  SRunner *sr = srunner_create(s1);
  int nf;
  suite_add_tcase(s1, tc);
  tcase_add_test(tc, check_count_vert_and_facets_alf);
  tcase_add_test(tc, check_count_vert_and_facets_cube);
  tcase_add_test(tc, open_error_file);

  tcase_add_test(tc, s21_rotationX);
  tcase_add_test(tc, s21_rotationY);
  tcase_add_test(tc, s21_rotationZ);
  tcase_add_test(tc, s21_rotation);
  tcase_add_test(tc, test_resize_model);

  // tcase_add_test(tc, test_moving_X);
  // tcase_add_test(tc, test_moving_Y);
  // tcase_add_test(tc, test_moving_Z);
  // tcase_add_test(tc, test_moving);

  srunner_run_all(sr, CK_ENV);
  nf = srunner_ntests_failed(sr);
  srunner_free(sr);

  return nf == 0 ? 0 : 1;
}
