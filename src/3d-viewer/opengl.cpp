#include "opengl.h"

OpenGL::OpenGL(QWidget *parent)
    :QOpenGLWidget(parent)
{

}

void OpenGL::initializeGL()
{

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 800, 600, 0, 0, 1);
}

void OpenGL::paintGL()
{
    float r, g, b, a = 1.0f;
    initializeOpenGLFunctions();
    qColorToRGB(Qt::red, r, g, b);
    glClearColor(Qt::red, Qt::white, Qt::yellow, Qt::blue);
    glLineWidth(2);
     glEnable(GL_LINE_STIPPLE);
     glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
     glBegin(GL_TRIANGLE_FAN);
      glColor3d(0,0,100);
      glVertex3d(400,200,0);
      glVertex3d(260,280,0);
      glVertex3d(200,200,0);
      glVertex3d(300,110,0);
     glEnd();
     glDisable(GL_LINE_STIPPLE);
}

void OpenGL::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
}

void OpenGL::qColorToRGB(const QColor &C, float &r, float &g, float &b) const
{
    r = normalize_0_1(C.red(), 1.0f, 255.0f);
    g = normalize_0_1(C.green(), 1.0f, 255.0f);
    b = normalize_0_1(C.blue(), 1.0f, 255.0f);
}

float OpenGL::normalize_0_1(float val, float min, float max) const
{
    return (val - min) / (max - min);
}

