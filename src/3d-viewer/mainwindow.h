#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include "opengl.h"
#include "qgifimage.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/**
 - @brief Класс главного окна
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
      Ui::MainWindow *ui;
      QGifImage *gif;
      QImage *frame;
      QTimer *timer;
      int count;
public slots:
    /**
    - @brief Функция округления вершин
    */
    void circleVerticles();
    /**
    - @brief Функция, делающая вершины квадратными
    */
    void squareVerticles();
    /**
    - @brief Функция отмены вершин
    */
    void noVerticles();
    /**
    - @brief Функция регулирования размера вершин
    */
    void resizeVerticles();
    /**
    - @brief Функция регулирования толщины ребер
    */
    void resizeEdges();
    /**
    - @brief Функция, делающая ребра сплошными
    */
    void edgesSolid();
    /**
    - @brief Функция, делающая ребра пунктирными
    */
    void edgesDashed();
    /**
    - @brief Функция для выбора цвета вершин
    */
    void verticlesColor();
    /**
    - @brief Функция для выбора цвета ребер
    */
    void edgesColor();
    /**
    - @brief Функция для выбора цвета фона
    */
    void backgroundColor();
    /**
    - @brief Функция выбора файла
    */
    void inputFile();
    /**
    - @brief Функция открытия файла
    */
    void openFile();
    void record();
    void save();
    void saveImage();
};
#endif // MAINWINDOW_H
