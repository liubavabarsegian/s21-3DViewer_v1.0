#include "opengl.h"

OpenGL::OpenGL(QWidget *parent)
    :QGLWidget(parent) {}

OpenGL::~OpenGL()
{
    if (model.vertices != NULL){
      if (model.polygons != NULL){
        free(model.polygons);
      }
      free(model.vertices);
    }
}

void OpenGL::initializeGL()
{
    model.count_of_vertices = 15;
    model.count_of_facets = 15;
    qDebug("V %d", model.count_of_vertices);
    model.vertices = (vertice *)malloc(model.count_of_vertices * sizeof(vertice));
    if (model.vertices != NULL) {
      model.polygons = (polygon_t *)malloc(model.count_of_facets * sizeof(polygon_t));
      if (model.polygons != NULL) {
        open_and_parse(&model);
        qDebug("V %d", model.count_of_vertices);
      }
    }

    //загрузка единичной матрицы
//   glLoadIdentity();
   //преобразование матрицы так, чтобы
   //создавалась ортогональная проекци
   glOrtho(0, 800, 0, 600, 1, 100);
}

void OpenGL::paintGL()
{
    glClearColor(0, 1, 1, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
//     загрузка в стек единичной матрицы
    glLoadIdentity();
    glRotatef(xRot, 1, 0, 0);
    glRotatef(yRot, 0, 1, 0);
    glScalef(0.001, 0.001, 0.001);
//    glFlush();
    drawModel(100);
}

void OpenGL::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
}


void OpenGL::drawModel(float a)
{
    float verticles[] = {
            -a, -a, a,   a, -a, a,     a, a, a,     -a, a, a,
            a, -a, -a,   -a, -a, -a,   -a, a, -a,   a, a, -a,
            -a, -a, -a,   -a, -a, a,   -a, a, a,    -a, a, -a,
            a, -a, a,    a, -a, -a,    a, a, -a,    a, a, a,
            -a, -a, a,    a, -a, a,    a, -a, -a,    -a, -a, -a,
            -a, a, a,    a, a, a,     a, a, -a,     -a, a, -a
        };
//    //glVertexPointer(количество координат, тип, смещение, адрес)
//    glVertexPointer(3, GL_FLOAT, 0, &arr_cube);
//    //разрешение использования вершинного буфера
//    glEnableClientState(GL_VERTEX_ARRAY);

//    glColorPointer(3, GL_FLOAT, 0, &color_arr);
//    glEnableClientState(GL_COLOR_ARRAY);

//        // (указываем, что будем рисовать, первый элемент, сколько всего вершин)
//        glDrawArrays(GL_QUADS, 0, 24);
//    glDisableClientState(GL_COLOR_ARRAY);
//    glDisableClientState(GL_VERTEX_ARRAY);

    glPointSize(20);
    //сглаживание вершин
    glEnable(GL_POINT_SMOOTH);

    glLineWidth(5);
    //соединяет линии по 2 точкам
    glBegin(GL_LINES);
          //X_axis red
         glColor3f( 1.0, 0.0, 0.0);
         glVertex3f(0.0, 0.0, 0.0);
         glVertex3f(1.0, 0.0, 0.0);
         //Y_axis green
         glColor3f (0.0, 1.0, 0.0);
         glVertex3f(0.0, 0.0, 0.0);
         glVertex3f(0.0, 1.0, 0.0);
         //Z_axis blue
         glColor3f (0.0, 0.0, 1.0);
         glVertex3f(0.0, 0.0, 0.0);
         glVertex3f(0.0, 0.0, 1.0);
    glEnd();

    //рисует вершины
    glBegin(GL_POINTS);
        for (size_t i = 0; i <  24; i++)
        {
            float x = verticles[i];
            float y = verticles[i + 1];
            float z = verticles[i + 2];
            i+= 2;
            glVertex3d(x, y, z);
            qDebug("x: %f y: %f z: %f", x, y, z);
        }
    glEnd();

    //соединяет линии по точкам подряд
    glBegin(GL_LINE_STRIP);
        for (size_t i = 0; i <  24; i++)
        {
            float x = verticles[i];
            float y = verticles[i + 1];
            float z = verticles[i + 2];
            i+= 2;
            glVertex3f(x, y, z);
            qDebug("x: %f y: %f z: %f", x, y, z);
        }
    glEnd();

//    glBegin(GL_POINTS);

//        for (size_t i = 0; i <  model.count_of_vertices; i++)
//        {
//            float x = model.vertices[i].x;
//            float y = model.vertices[i].y;
//            float z = model.vertices[i].z;
//            glVertex3f(x, y, z);
//            qDebug("x: %f y: %f z: %f", x, y, z);
//        }
//    glEnd();
}

void OpenGL::mousePressEvent(QMouseEvent *mo)
{
    mousePosition = mo->pos();
}

void OpenGL::mouseMoveEvent(QMouseEvent *mo)
{
    xRot = 1 / M_PI * (mo->pos().y() - mousePosition.y());
    yRot = 1 / M_PI * (mo->pos().x() - mousePosition.x());
    updateGL();
}
