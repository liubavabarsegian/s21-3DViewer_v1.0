#ifndef OPENGL_H
#define OPENGL_H

#include <QtOpenGL>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QFile>

extern "C" {
    #include "parser.h"
};

class OpenGL : public QGLWidget
{
    Q_OBJECT;
public:
    OpenGL(QWidget *parent = nullptr);
    ~OpenGL();
    virtual void paintGL() override;
    int pointSize;
    int edgeSize;
    bool noVerticles;
    bool dashed;
    QColor verticlesColor;
    QColor edgesColor;
    QColor backgroundColor;
    QString file;
private:
    float xRot, yRot, zRot;
    QPoint mousePosition;
    QTimer timer;
    struct data model;
    virtual void initializeGL() override;
    virtual void resizeGL(int w, int h) override;
    virtual void mousePressEvent(QMouseEvent *) override;
    virtual void mouseMoveEvent(QMouseEvent  *) override;
    void drawModel(float a);
    void drawVerticles();
    void drawLines();
public slots:

};

#endif // OPENGL_H
