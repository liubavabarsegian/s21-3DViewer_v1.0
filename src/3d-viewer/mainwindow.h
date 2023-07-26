#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include "opengl.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    Ui::MainWindow *ui;
public slots:
    void circleVerticles();
    void squareVerticles();
    void noVerticles();
    void resizeVerticles();
    void resizeEdges();
    void edgesSolid();
    void edgesDashed();
    void verticlesColor();
    void edgesColor();
    void backgroundColor();
    void inputFile();
    void openFile();
};
#endif // MAINWINDOW_H
