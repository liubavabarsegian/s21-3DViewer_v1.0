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

//    model.count_vert = 10;
//      model.count_facets = 10;
//    if (create_matrix(model.matrix_3d, model.count_vert, 3) == OK) {
//        model.polygons = (s21_facets *)malloc(model.count_facets * sizeof(s21_facets));
//        if (model.polygons != NULL) {
//          int blocks_to_free_in_matrix = 0;
//          open_and_parse(&model, file.toStdString().c_str(), &blocks_to_free_in_matrix);
//        }
//      }

    //загрузка единичной матрицы
//   glLoadIdentity();
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
    glScalef(0.001, 0.001, 0.001);
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

//void OpenGL::drawModel(float a)
//{
//    //glVertexPointer(количество координат, тип, смещение, адрес)
//    MyGLWidget(QWidget *parent = nullptr) : QOpenGLWidget(parent), isRecording(false) {
// Создаем таймер, который будет вызывать slotCaptureFrame() каждые 33 мс (приближенно к 30 кадрам в секунду)
//    //разрешение использования вершинного буфера
//    glEnableClientState(GL_VERTEX_ARRAY);

//    glColorPointer(3, GL_FLOAT, 0, &color_arr);
//    glEnableClientState(GL_COLOR_ARRAY);

//        // (указываем, что будем рисовать, первый элемент, сколько всего вершин)
//        glDrawArrays(GL_QUADS, 0, 24);
//    glDisableClientState(GL_COLOR_ARRAY);
//    glDisableClientState(GL_VERTEX_ARRAY);
//}

void OpenGL::drawVerticles()
{
    float a = 100;
    float verticles[] = {
            -a, -a, a,   a, -a, a,     a, a, a,     -a, a, a,
            a, -a, -a,   -a, -a, -a,   -a, a, -a,   a, a, -a,
            -a, -a, -a,   -a, -a, a,   -a, a, a,    -a, a, -a,
            a, -a, a,    a, -a, -a,    a, a, -a,    a, a, a,
            -a, -a, a,    a, -a, a,    a, -a, -a,    -a, -a, -a,
            -a, a, a,    a, a, a,     a, a, -a,     -a, a, -a
        };
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
}

void OpenGL::drawLines()
{
    float a = 100;
    float verticles[] = {
            -a, -a, a,   a, -a, a,     a, a, a,     -a, a, a,
            a, -a, -a,   -a, -a, -a,   -a, a, -a,   a, a, -a,
            -a, -a, -a,   -a, -a, a,   -a, a, a,    -a, a, -a,
            a, -a, a,    a, -a, -a,    a, a, -a,    a, a, a,
            -a, -a, a,    a, -a, a,    a, -a, -a,    -a, -a, -a,
            -a, a, a,    a, a, a,     a, a, -a,     -a, a, -a
        };
    //соединяет линии по точкам подряд
    glBegin(GL_LINE_LOOP);
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


