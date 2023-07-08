#include "opengl.h"

OpenGL::OpenGL(QWidget *parent)
    :QGLWidget(parent)
{

}

void OpenGL::initializeGL()
{
    glEnable(GL_DEPTH_TEST);
//   glMatrixMode(GL_PROJECTION);
    //загрузка единичной матрицы
//   glLoadIdentity();
   //преобразование матрицы так, чтобы
   //создавалась ортогональная проекци
//   glOrtho(-1, 1, -1, 1, 1, 2);

   //для отдаления и приближения изображения
   glFrustum(-1, 1, -1, 1, 1, 3);
}

void OpenGL::paintGL()
{
    glClearColor(0, 1, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
//     загрузка в стек единичной матрицы
    glLoadIdentity();
    glTranslatef(0, 0, -2);
    glRotatef(xRot, 1, 0, 0);
    glRotatef(yRot, 0, 1, 0);
    drawModel(0.5);
}

void OpenGL::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
}

void OpenGL::drawModel(float a)
{
    float arr_cube[] = {
        -a, -a, a,   a, -a, a,     a, a, a,     -a, a, a,
        a, -a, -a,   -a, -a, -a,   -a, a, -a,   a, a, -a,
        -a, -a, -a,   -a, -a, a,   -a, a, a,    -a, a, -a,
        a, -a, a,    a, -a, -a,    a, a, -a,    a, a, a,
        -a, -a, a,    a, -a, a,    a, -a, -a,    -a, -a, -a,
        -a, a, a,    a, a, a,     a, a, -a,     -a, a, -a
    };

    float color_arr[] = {
        1, 0, 0,       1, 0, 0,      1, 0, 0,      1, 0, 0,
        0, 0, 1,       0, 0, 1,      0, 0, 1,      0, 0, 1,
        1, 1, 0,       1, 1, 0,      1, 1, 0,      1, 1, 0,
        0, 1, 1,       0, 1, 1,      0, 1, 1,      0, 1, 1,
        1, 0.5, 0.5,   1, 0.5, 0.5,  1, 0.5, 0.5,  1, 0.5, 0.5
    };

    //glVertexPointer(количество координат, тип, смещение, адрес)
    glVertexPointer(3, GL_FLOAT, 0, &arr_cube);
    //разрешение использования вершинного буфера
    glEnableClientState(GL_VERTEX_ARRAY);

    glColorPointer(3, GL_FLOAT, 0, &color_arr);
    glEnableClientState(GL_COLOR_ARRAY);

        // (указываем, что будем рисовать, первый элемент, сколько всего вершин)
        glDrawArrays(GL_QUADS, 0, 24);
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
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
