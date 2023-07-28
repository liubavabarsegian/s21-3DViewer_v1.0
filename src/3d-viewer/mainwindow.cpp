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
    connect(ui->verticlesColor, &QPushButton::clicked, this, &MainWindow::verticlesColor);
    connect(ui->edgesColor, &QPushButton::clicked, this, &MainWindow::edgesColor);
    connect(ui->backgroundColor, &QPushButton::clicked, this, &MainWindow::backgroundColor);
    connect(ui->inputFileButton, &QPushButton::clicked, this, &MainWindow::inputFile);
    connect(ui->openFileButton, &QPushButton::clicked, this, &MainWindow::openFile);
    connect(ui->recordButton, &QPushButton::clicked, this, &MainWindow::record);
    connect(ui->saveButton, &QPushButton::clicked, this, &MainWindow::saveImage);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::circleVerticles()
{
    //сглаживание вершин
    glEnable(GL_POINT_SMOOTH);
    glPointSize(ui->viewerWidget->pointSize);
    ui->viewerWidget->noVerticles = false;
    ui->viewerWidget->repaint();
}

void MainWindow::squareVerticles()
{
    glDisable(GL_POINT_SMOOTH);
    glPointSize(ui->viewerWidget->pointSize);
    ui->viewerWidget->noVerticles = false;
    ui->viewerWidget->repaint();
}

void MainWindow::noVerticles()
{
    ui->viewerWidget->noVerticles = true;
    ui->viewerWidget->repaint();
}

void MainWindow::resizeVerticles()
{
    ui->viewerWidget->pointSize = ui->verticlesSlider->value();
    ui->viewerWidget->repaint();
}

void MainWindow::resizeEdges()
{
    ui->viewerWidget->edgeSize = ui->edgesSize->value();
    ui->viewerWidget->repaint();
}

void MainWindow::edgesSolid()
{
    ui->viewerWidget->dashed = false;
    ui->viewerWidget->repaint();
}

void MainWindow::edgesDashed()
{
    glPushAttrib(GL_ENABLE_BIT);
    ui->viewerWidget->dashed = true;
    ui->viewerWidget->repaint();
    glPopAttrib();
}

void MainWindow::verticlesColor()
{
    ui->viewerWidget->verticlesColor = QColorDialog::getColor();
    ui->viewerWidget->repaint();
}

void MainWindow::edgesColor()
{
    ui->viewerWidget->edgesColor = QColorDialog::getColor();;
    ui->viewerWidget->repaint();
}

void MainWindow::backgroundColor()
{
    ui->viewerWidget->backgroundColor = QColorDialog::getColor();
    ui->viewerWidget->repaint();
}

void MainWindow::inputFile()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open Image"), "../objs", tr("Image Files (*.obj)"));
    ui->inputFile->setText(fileName);
    qDebug("%s\n", ui->inputFile->text().toStdString().c_str());
}

void MainWindow::openFile()
{
    QDir dir("../imgs/");
    if (ui->inputFile->text().contains(dir.absolutePath()))
        ui->viewerWidget->file = dir.absolutePath() + ui->inputFile->text();
    else
        ui->viewerWidget->file = ui->inputFile->text();
    ui->viewerWidget->repaint();
}

void MainWindow::saveImage() {
  QString save = NULL;
  save = QFileDialog::getSaveFileName(this, NULL, NULL,
                                      "JPEG (*.jpeg) ;; BMP (*.bmp)");
  if (!save.isNull()) ui->viewerWidget->grabFramebuffer().save(save, NULL, 100);
}

void MainWindow::record() {
  gif = new QGifImage;
  frame = new QImage;
  timer = new QTimer(this);
  count = 0;
  connect(timer, SIGNAL(timeout()), this, SLOT(save()));
  timer->start(50);
}


void MainWindow::save() {
  count++;
  *frame = ui->viewerWidget->grabFramebuffer();
  gif->addFrame(*frame);
  if (count == 50) {
    timer->stop();
    QString save = NULL;
    save = QFileDialog::getSaveFileName(this, NULL, NULL, "GIF (*.gif)");
    if (!save.isNull()) gif->save(save);
  }
}
