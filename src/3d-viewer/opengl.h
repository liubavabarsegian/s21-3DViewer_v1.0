#ifndef OPENGL_H
#define OPENGL_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>

class OpenGL : public QOpenGLWidget, public QOpenGLFunctions
{
    Q_OBJECT;
public:
    OpenGL(QWidget *parent = nullptr);
protected:
    virtual void initializeGL() override;
    virtual void paintGL() override;
    virtual void resizeGL(int w, int h) override;
    void qColorToRGB(const QColor &C, float &r, float &g, float &b) const;
    float normalize_0_1(float val, float min, float max) const;
};

#endif // OPENGL_H
