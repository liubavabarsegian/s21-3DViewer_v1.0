#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    std::setlocale(LC_NUMERIC, "C");

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
    connect(ui->scaleSlider, &QSlider::sliderMoved, this, &MainWindow::resizeModel);

    // Загрузка параметров при открытии окна
    QSettings settings("S21", "3DV");
    int verticlesSize = settings.value("verticlesSize", 5).toInt();
    int edgesSize = settings.value("edgesSize", 1).toInt();
    bool dashedEdges = settings.value("dashedEdges", false).toBool();
    bool showVerticles = settings.value("showVerticles", true).toBool();
    QColor verticlesColor = settings.value("verticlesColor", QColor(Qt::red)).value<QColor>();
    QColor edgesColor = settings.value("edgesColor", QColor(Qt::blue)).value<QColor>();
    QColor backgroundColor = settings.value("backgroundColor", QColor(Qt::white)).value<QColor>();
    QString file = settings.value("file", "").toString();
    bool circleVerticles = settings.value("circleVerticles", true).toBool();
    bool squreVerticles = settings.value("squareVerticles", false).toBool();
    bool noVerticles = settings.value("noVerticles", false).toBool();

    // Применение загруженных параметров
    ui->verticlesSlider->setValue(verticlesSize);
    ui->edgesSize->setValue(edgesSize);
    if (dashedEdges)
      ui->edgesDashed->setChecked(true);
    else
      ui->edgesSolid->setChecked(true);
    if (showVerticles)
      ui->circleVerticles->setChecked(true);
    else
      ui->noVerticles->setChecked(true);
    ui->viewerWidget->verticlesColor = verticlesColor;
    ui->viewerWidget->edgesColor = edgesColor;
    ui->viewerWidget->backgroundColor = backgroundColor;
    ui->viewerWidget->file = file;
    ui->viewerWidget->noVerticles = noVerticles;
    ui->viewerWidget->circleVerticles = circleVerticles;
    ui->viewerWidget->squareVerticles = squreVerticles;
    ui->viewerWidget->repaint();
}

MainWindow::~MainWindow()
{
    // Сохранение параметров при закрытии окна
    QSettings settings("S21", "3DV");
    settings.setValue("verticlesSize", ui->verticlesSlider->value());
    settings.setValue("edgesSize", ui->edgesSize->value());
    settings.setValue("dashedEdges", ui->edgesDashed->isChecked());
    settings.setValue("showVerticles", ui->circleVerticles->isChecked());
    settings.setValue("verticlesColor", ui->viewerWidget->verticlesColor);
    settings.setValue("edgesColor", ui->viewerWidget->edgesColor);
    settings.setValue("backgroundColor", ui->viewerWidget->backgroundColor);
    settings.setValue("file", ui->viewerWidget->file);
    settings.setValue("noVerticles", ui->viewerWidget->noVerticles);
    settings.setValue("circleVarticles", ui->viewerWidget->circleVerticles);
    settings.setValue("squareVerticles", ui->viewerWidget->squareVerticles);
    delete ui;
}

void MainWindow::circleVerticles()
{
    ui->viewerWidget->squareVerticles = false;
    ui->viewerWidget->circleVerticles = true;
    //сглаживание вершин
    glEnable(GL_POINT_SMOOTH);
    glPointSize(ui->viewerWidget->pointSize);
    ui->viewerWidget->noVerticles = false;
    ui->viewerWidget->repaint();
}

void MainWindow::squareVerticles()
{
    ui->viewerWidget->circleVerticles = false;
    ui->viewerWidget->squareVerticles = true;
    glDisable(GL_POINT_SMOOTH);
    glPointSize(ui->viewerWidget->pointSize);
    ui->viewerWidget->noVerticles = false;
    ui->viewerWidget->repaint();
}

void MainWindow::noVerticles()
{
    ui->viewerWidget->noVerticles = true;
    ui->viewerWidget->circleVerticles = false;
    ui->viewerWidget->squareVerticles = false;
    ui->viewerWidget->repaint();
}

void MainWindow::resizeVerticles()
{
    ui->viewerWidget->pointSize = ui->verticlesSlider->value() / 10;
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

    if (ui->viewerWidget->model.polygons != NULL) {
         free(ui->viewerWidget->model.polygons);
         free_matrix(ui->viewerWidget->model.matrix_3d, ui->viewerWidget->allocated_blocks);
         free(ui->viewerWidget->model.matrix_3d);
       }

    //    s21_data model;
        ui->viewerWidget->model.count_vert = 10;
        ui->viewerWidget->model.count_facets = 10;
        ui->viewerWidget->model.matrix_3d = (s21_matrix *)malloc(sizeof(s21_matrix));
        if (ui->viewerWidget->model.matrix_3d != NULL) {
          if (create_matrix(ui->viewerWidget->model.matrix_3d, ui->viewerWidget->model.count_vert, 3) == OK) {
            ui->viewerWidget->model.polygons = (s21_facets *)malloc(ui->viewerWidget->model.count_facets * sizeof(s21_facets));
            int count_allocated_blocks = 0;
            if (ui->viewerWidget->model.polygons != NULL) {
             if(open_and_parse(&(ui->viewerWidget->model), ui->viewerWidget->file.toStdString().c_str(), &count_allocated_blocks) == OK){
                 qDebug("AAAA %u\n", ui->viewerWidget->model.count_vert);
                 QFileInfo fi(ui->viewerWidget->file);
                 ui->filenameLabel->setText(fi.fileName());
//                 ui->edgesLabel->setText(QString(ui->viewerWidget->model.count_edges));
                 ui->verticlesLabel->setText(QString(ui->viewerWidget->model.count_vert));
             }
            }
          }
        }

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

void MainWindow::resizeModel()
{
    double scale = ui->scaleSlider->value() / 100;
    resize_model(&(ui->viewerWidget->model), scale, scale, scale);
    glScalef(scale, scale, scale);
    ui->viewerWidget->repaint();
}
