#include "opengl.h"

OpenGL::OpenGL(QWidget *parent) : QOpenGLWidget(parent) {
  pointSize = 10;
  edgeSize = 5;
  noVerticles = false;
  dashed = false;
  backgroundColor = Qt::white;
  //    file = "../objs/cube2.obj";
}

OpenGL::~OpenGL() {
  //    if (model.polygons != NULL) {
  //        free_vertices_in_facets(&(model));
  //         free(model.polygons);
  //       }
//  if (model.matrix_3d != NULL) {
//    free_matrix(model.matrix_3d, allocated_blocks);
//  }
  //    if (model.matrix_3d)
  //    {
  //         free(model.matrix_3d);
  //    }
}

void OpenGL::initializeGL() {
  //преобразование матрицы так, чтобыe
  //создавалась ортогональная проекци
  //   glOrtho(0, 800, 0, 600, 1, 100);
}

void OpenGL::paintGL() {
  glClearColor(backgroundColor.redF(), backgroundColor.greenF(),
               backgroundColor.blueF(), 0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  //     загрузка в стек единичной матрицы
  glLoadIdentity();
  glRotatef(xRot, 1, 0, 0);
  glRotatef(yRot, 0, 1, 0);
  glScalef(0.01, 0.01, 0.01);

  if (model.polygons != NULL) {
    glPointSize(pointSize);
    if (noVerticles == false) {
      qDebug("CIRCLE:  %d  SQUARE: %d\n", circleVerticles, squareVerticles);
      if (circleVerticles == true) glEnable(GL_POINT_SMOOTH);
      if (squareVerticles == true) glDisable(GL_POINT_SMOOTH);
      glColor3d(verticlesColor.redF(), verticlesColor.greenF(),
                verticlesColor.blueF());
      drawVerticles();
    }

    glLineWidth(edgeSize);
    if (dashed) {
      glLineStipple(10, 0xAAAA);
      glEnable(GL_LINE_STIPPLE);
    } else
      glDisable(GL_LINE_STIPPLE);
    glColor3d(edgesColor.redF(), edgesColor.greenF(), edgesColor.blueF());
    drawLines();
  }
}

void OpenGL::resizeGL(int w, int h) { glViewport(0, 0, w, h); }

// void OpenGL::drawModel(double a)
//{
//     //glVertexPointer(количество координат, тип, смещение, адрес)
//     MyGLWidget(QWidget *parent = nullptr) : QOpenGLWidget(parent),
//     isRecording(false) {
//  Создаем таймер, который будет вызывать slotCaptureFrame() каждые 33 мс
//  (приближенно к 30 кадрам в секунду)
//     //разрешение использования вершинного буфера
//     glEnableClientState(GL_VERTEX_ARRAY);

//    glColorPointer(3, GL_double, 0, &color_arr);
//    glEnableClientState(GL_COLOR_ARRAY);

//        // (указываем, что будем рисовать, первый элемент, сколько всего
//        вершин) glDrawArrays(GL_QUADS, 0, 24);
//    glDisableClientState(GL_COLOR_ARRAY);
//    glDisableClientState(GL_VERTEX_ARRAY);
//}

void OpenGL::drawVerticles() {
  //рисует вершины

  glBegin(GL_POINTS);
  //        qDebug("rows: %d\n", model.count_vert);
  for (unsigned int i = 0; i < model.matrix_3d->rows; i++) {
    double x = model.matrix_3d->matrix[i][0];
    double y = model.matrix_3d->matrix[i][1];
    double z = model.matrix_3d->matrix[i][2];
    glVertex3d(x, y, z);
    //            qDebug("x: %f y: %f z: %f", x, y, z);
  }
  glEnd();
}

void OpenGL::drawLines() {
  //соединяет линии по точкам подряд
  //        printf("Vert = %u\n", model.count_vert);    //
  //        printf("Polygons = %u\n", model.count_facets);
  //        print_polygon(&model);
  for (size_t i = 0; i < model.count_facets; i++) {
    glBegin(GL_LINE_LOOP);
    //            qDebug("facets: %d\n", model.count_facets);
    for (size_t j = 0; j < model.polygons->count_number_vert; j++) {
      //                qDebug("##: %lf\n",
      //                model.matrix_3d->matrix[model.polygons[i].vert[j]][0]);
      double x = model.matrix_3d->matrix[model.polygons[i].vert[j] - 1][0];
      double y = model.matrix_3d->matrix[model.polygons[i].vert[j] - 1][1];
      double z = model.matrix_3d->matrix[model.polygons[i].vert[j] - 1][2];
      glVertex3f(x, y, z);
      //                qDebug("x: %f y: %f z: %f", x, y, z);
    }
    // не забыть почистить память
    glEnd();
  }
}

void OpenGL::mousePressEvent(QMouseEvent *mo) { mousePosition = mo->pos(); }

void OpenGL::mouseMoveEvent(QMouseEvent *mo) {
  xRot = 1 / M_PI * (mo->pos().y() - mousePosition.y());
  yRot = 1 / M_PI * (mo->pos().x() - mousePosition.x());
  update();
}
