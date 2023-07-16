#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("3D VIEWER");
    connect(ui->circleVerticles, &QRadioButton::clicked, this, &MainWindow::circleVerticles);
    connect(ui->squareVerticles, &QRadioButton::clicked, this,  &MainWindow::squareVerticles);
    connect(ui->noVerticles, &QRadioButton::clicked, this, &MainWindow::noVerticles);
    connect(ui->verticlesSlider, &QSlider::sliderMoved, this, &MainWindow::resizeVerticles);
    connect(ui->edgesSize, &QSlider::sliderMoved, this, &MainWindow::resizeEdges);
    connect(ui->edgesSolid, &QRadioButton::clicked, this, &MainWindow::edgesSolid);
    connect(ui->edgesDashed, &QRadioButton::clicked, this, &MainWindow::edgesDashed);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::circleVerticles()
{
    glClearColor(0, 1, 1, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //сглаживание вершин
    glEnable(GL_POINT_SMOOTH);
    glPointSize(ui->viewerWidget->pointSize);
    ui->viewerWidget->noVerticles = false;
    ui->viewerWidget->repaint();
}

void MainWindow::squareVerticles()
{
    glClearColor(0, 1, 1, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDisable(GL_POINT_SMOOTH);
    glPointSize(ui->viewerWidget->pointSize);
    ui->viewerWidget->noVerticles = false;
    ui->viewerWidget->repaint();
}

void MainWindow::noVerticles()
{
    glClearColor(0, 1, 1, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    ui->viewerWidget->noVerticles = true;
    ui->viewerWidget->repaint();
}

void MainWindow::resizeVerticles()
{
    glClearColor(0, 1, 1, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    ui->viewerWidget->pointSize = ui->verticlesSlider->value();
    glPointSize(ui->viewerWidget->pointSize);
    ui->viewerWidget->repaint();
}

void MainWindow::resizeEdges()
{
    glClearColor(0, 1, 1, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    ui->viewerWidget->edgeSize = ui->edgesSize->value();
    glLineWidth(ui->viewerWidget->edgeSize);
    ui->viewerWidget->repaint();
}

void MainWindow::edgesSolid()
{
    glClearColor(0, 1, 1, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    ui->viewerWidget->dashed = false;
    ui->viewerWidget->repaint();
}

void MainWindow::edgesDashed()
{
    glClearColor(0, 1, 1, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushAttrib(GL_ENABLE_BIT);
    ui->viewerWidget->dashed = true;
    ui->viewerWidget->repaint();
    glPopAttrib();
}
