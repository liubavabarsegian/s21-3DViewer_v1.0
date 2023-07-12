#ifndef OPENGL_H
#define OPENGL_H

#include <QtOpenGL>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>

//sudo apt-get install freeglut3-dev
//#include<GL/glut.h>
#include "parser.h"
extern "C" void open_and_parse(data *model);

class OpenGL : public QGLWidget
{
    Q_OBJECT;
public:
    OpenGL(QWidget *parent = nullptr);
    ~OpenGL();
private:
    float xRot, yRot, zRot;
    QPoint mousePosition;
    QTimer timer;
    struct data model;
    virtual void initializeGL() override;
    virtual void paintGL() override;
    virtual void resizeGL(int w, int h) override;
    virtual void mousePressEvent(QMouseEvent *) override;
    virtual void mouseMoveEvent(QMouseEvent  *) override;
    void drawModel(float a);
public slots:

};

#endif // OPENGL_H
