#include "opengl.h"

OpenGL::OpenGL(QWidget *parent)
    :QOpenGLWidget(parent) {
    pointSize = 10;
    edgeSize = 5;
    noVerticles = false;
    dashed = false;
    backgroundColor = Qt::white;
}

OpenGL::~OpenGL()
{
    if (model.polygons != NULL)
    {
//        if (model.polygons->vert != NULL)
//            free(model.polygons->vert);
        free(model.polygons);
    }
}

void OpenGL::initializeGL()
{

//    s21_data model;
    model.count_vert = 10;
    model.count_facets = 10;
    model.matrix_3d = (s21_matrix *)malloc(sizeof(s21_matrix));
    if (model.matrix_3d != NULL) {
      if (create_matrix(model.matrix_3d, model.count_vert, 3) == OK) {
        model.polygons = (s21_facets *)malloc(model.count_facets * sizeof(s21_facets));
        int count_allocated_blocks = 0;
        if (model.polygons != NULL) {
         if(open_and_parse(&model, "../objs/test_cat.obj", &count_allocated_blocks) == OK){
             qDebug("AAAA %u\n", model.matrix_3d->rows);
         }
        }
      }
    }
    //преобразование матрицы так, чтобы
   //создавалась ортогональная проекци
   glOrtho(0, 800, 0, 600, 1, 100);
}

void OpenGL::paintGL()
{
    glClearColor(backgroundColor.redF(), backgroundColor.greenF(), backgroundColor.blueF(), 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
//     загрузка в стек единичной матрицы
    glLoadIdentity();
    glRotatef(xRot, 1, 0, 0);
    glRotatef(yRot, 0, 1, 0);
    glScalef(0.005, 0.005, 0.005);
    glPointSize(pointSize);
    if (noVerticles)
        glPointSize(1);
    glLineWidth(edgeSize);
    if (dashed)
    {
        glLineStipple(10, 0xAAAA);
        glEnable(GL_LINE_STIPPLE);
    }
    else
        glDisable(GL_LINE_STIPPLE);
    glColor3d(verticlesColor.redF(), verticlesColor.greenF(), verticlesColor.blueF());
    drawVerticles();
    glColor3d(edgesColor.redF(), edgesColor.greenF(), edgesColor.blueF());
    drawLines();
}

void OpenGL::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
}

//void OpenGL::drawModel(double a)
//{
//    //glVertexPointer(количество координат, тип, смещение, адрес)
//    MyGLWidget(QWidget *parent = nullptr) : QOpenGLWidget(parent), isRecording(false) {
// Создаем таймер, который будет вызывать slotCaptureFrame() каждые 33 мс (приближенно к 30 кадрам в секунду)
//    //разрешение использования вершинного буфера
//    glEnableClientState(GL_VERTEX_ARRAY);

//    glColorPointer(3, GL_double, 0, &color_arr);
//    glEnableClientState(GL_COLOR_ARRAY);

//        // (указываем, что будем рисовать, первый элемент, сколько всего вершин)
//        glDrawArrays(GL_QUADS, 0, 24);
//    glDisableClientState(GL_COLOR_ARRAY);
//    glDisableClientState(GL_VERTEX_ARRAY);
//}

void OpenGL::drawVerticles()
{
    double a = 100;
    double verticles[] = {
            -a, -a, a,   a, -a, a,     a, a, a,     -a, a, a,
            a, -a, -a,   -a, -a, -a,   -a, a, -a,   a, a, -a,
            -a, -a, -a,   -a, -a, a,   -a, a, a,    -a, a, -a,
            a, -a, a,    a, -a, -a,    a, a, -a,    a, a, a,
            -a, -a, a,    a, -a, a,    a, -a, -a,    -a, -a, -a,
            -a, a, a,    a, a, a,     a, a, -a,     -a, a, -a
        };
    //рисует вершины
    glBegin(GL_POINTS);
        qDebug("rows: %d\n", model.count_vert);
        for (size_t i = 0;  i < model.count_vert; i++)
        {
//            double x = model.matrix_3d->matrix[i][0];
//            double y = model.matrix_3d->matrix[i][1];
//            double z = model.matrix_3d->matrix[i][2];

            double x = verticles[i];
            double y = verticles[i+1];
            double z = verticles[i+2];
            i+= 3;
            glVertex3d(x, y, z);
            qDebug("x: %f y: %f z: %f", x, y, z);
        }
    glEnd();
}

void OpenGL::drawLines()
{
    double a = 100;
    double verticles[] = {
            -a, -a, a,   a, -a, a,     a, a, a,     -a, a, a,
            a, -a, -a,   -a, -a, -a,   -a, a, -a,   a, a, -a,
            -a, -a, -a,   -a, -a, a,   -a, a, a,    -a, a, -a,
            a, -a, a,    a, -a, -a,    a, a, -a,    a, a, a,
            -a, -a, a,    a, -a, a,    a, -a, -a,    -a, -a, -a,
            -a, a, a,    a, a, a,     a, a, -a,     -a, a, -a
        };
    //соединяет линии по точкам подряд
    glBegin(GL_LINE_LOOP);
        for (size_t i = 0; i < model.count_facets; i++)
        {
            qDebug("facets: %d\n", model.count_facets);
            for (size_t j = 0; j < model.polygons->count_number_vert; j++)
            {
//                qDebug("count: %d\n", model.matrix_3d->matrix[1][1]);
//                double x = model.matrix_3d->matrix[model.polygons->vert[j]][0];
//                double y = model.matrix_3d->matrix[model.polygons->vert[j]][1];
//                double z = model.matrix_3d->matrix[model.polygons->vert[j]][2];
//                glVertex3f(x, y, z);
    //            qDebug("x: %f y: %f z: %f", x, y, z);
            }
        }
    glEnd();
}

void OpenGL::mousePressEvent(QMouseEvent *mo)
{
    mousePosition = mo->pos();
}

void OpenGL::mouseMoveEvent(QMouseEvent *mo)
{
    xRot = 1 / M_PI * (mo->pos().y() - mousePosition.y());
    yRot = 1 / M_PI * (mo->pos().x() - mousePosition.x());
    update();
}


