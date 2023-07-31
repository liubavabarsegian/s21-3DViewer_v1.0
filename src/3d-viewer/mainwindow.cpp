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
    connect(ui->x_dec, &QPushButton::clicked, this, [this]{rotateModel(-1, 0, 0);});
    connect(ui->x_inc, &QPushButton::clicked, this, [this]{rotateModel(1, 0, 0);});
    connect(ui->y_dec, &QPushButton::clicked, this, [this]{rotateModel(0, -1, 0);});
    connect(ui->y_inc, &QPushButton::clicked, this, [this]{rotateModel(0, 1, 0);});
    connect(ui->z_dec, &QPushButton::clicked, this, [this]{rotateModel(0, 0, -1);});
    connect(ui->z_inc, &QPushButton::clicked, this, [this]{rotateModel(0, 0, 1);});
    connect(ui->XTranslateSlider, &QSlider::sliderMoved, this, &MainWindow::moveModel);
    connect(ui->YTranslateSlider, &QSlider::sliderMoved, this, &MainWindow::moveModel);
    connect(ui->ZTranslateSlider, &QSlider::sliderMoved, this, &MainWindow::moveModel);

    // Загрузка параметров при открытии окна
    QSettings settings("S21", "3DV");
    int verticlesSize = settings.value("verticlesSize", 1).toInt();
    int edgesSize = settings.value("edgesSize", 1).toInt();
    bool dashedEdges = settings.value("dashedEdges", false).toBool();
    QColor verticlesColor = settings.value("verticlesColor", QColor(Qt::red)).value<QColor>();
    QColor edgesColor = settings.value("edgesColor", QColor(Qt::blue)).value<QColor>();
    QColor backgroundColor = settings.value("backgroundColor", QColor(Qt::white)).value<QColor>();
    QString file = settings.value("file", "").toString();
    bool circleVerticles = settings.value("circleVerticles", true).toBool();
    bool squreVerticles = settings.value("squareVerticles", false).toBool();
    bool noVerticles = settings.value("noVerticles", false).toBool();

    // Применение загруженных параметров
    ui->XTranslateSlider->setValue(0);
    ui->YTranslateSlider->setValue(0);
    ui->ZTranslateSlider->setValue(0);
    ui->verticlesSlider->setValue(verticlesSize);
    ui->viewerWidget->pointSize = verticlesSize;
    ui->edgesSize->setValue(edgesSize);
    ui->viewerWidget->edgeSize = edgesSize;
    if (dashedEdges)
    {
      ui->viewerWidget->dashed = true;
      ui->edgesDashed->setChecked(true);
    }
    else
    {
        ui->viewerWidget->dashed = false;
        ui->edgesSolid->setChecked(true);
    }
    ui->viewerWidget->noVerticles = noVerticles;
    ui->viewerWidget->verticlesColor = verticlesColor;
    ui->viewerWidget->edgesColor = edgesColor;
    ui->viewerWidget->backgroundColor = backgroundColor;
    ui->viewerWidget->file = file;
    ui->viewerWidget->noVerticles = noVerticles;
    ui->viewerWidget->circleVerticles = circleVerticles;
    ui->viewerWidget->squareVerticles = squreVerticles;
    ui->viewerWidget->repaint();

        ui->viewerWidget->model.count_vert = 10;
        ui->viewerWidget->model.count_facets = 10;
        ui->viewerWidget->model.matrix_3d = (s21_matrix *)malloc(sizeof(s21_matrix));
        if (ui->viewerWidget->model.matrix_3d != NULL) {
          if (create_matrix(ui->viewerWidget->model.matrix_3d, ui->viewerWidget->model.count_vert, 4) == OK) {
            ui->viewerWidget->model.polygons = (s21_facets *)malloc(ui->viewerWidget->model.count_facets * sizeof(s21_facets));
            int count_allocated_blocks = 0;
            if (ui->viewerWidget->model.polygons != NULL) {
             if(open_and_parse(&(ui->viewerWidget->model), ui->viewerWidget->file.toStdString().c_str(), &count_allocated_blocks) == OK){
                 qDebug("AAAA %u\n", ui->viewerWidget->model.count_vert);
                 QFileInfo fi(ui->viewerWidget->file);
                 ui->filenameLabel->setText(fi.fileName());
                 ui->edgesLabel->setText(QString::number(ui->viewerWidget->model.count_facets));
                 ui->verticlesLabel->setText(QString::number(ui->viewerWidget->model.count_vert));
             }
            }
          }
        }
}

MainWindow::~MainWindow()
{
//    if (ui->viewerWidget->model.polygons != NULL) {
//         free(ui->viewerWidget->model.polygons);
//         free_matrix(ui->viewerWidget->model.matrix_3d, ui->viewerWidget->allocated_blocks);
//         free(ui->viewerWidget->model.matrix_3d);
//       }


    // Сохранение параметров при закрытии окна
    QSettings settings("S21", "3DV");
    settings.setValue("verticlesSize", ui->verticlesSlider->value() / 10);
    settings.setValue("edgesSize", ui->edgesSize->value() / 10);
    settings.setValue("dashedEdges", ui->edgesDashed->isChecked());
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
    ui->viewerWidget->noVerticles = false;
    ui->viewerWidget->circleVerticles = true;
    //сглаживание вершин
    glEnable(GL_POINT_SMOOTH);
    glPointSize(ui->viewerWidget->pointSize);
    ui->viewerWidget->repaint();
}

void MainWindow::squareVerticles()
{
    ui->viewerWidget->noVerticles = false;
    ui->viewerWidget->circleVerticles = false;
    ui->viewerWidget->squareVerticles = true;
    glDisable(GL_POINT_SMOOTH);
    glPointSize(ui->viewerWidget->pointSize);
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
    ui->viewerWidget->edgeSize = ui->edgesSize->value() / 10;
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
    ui->viewerWidget->file = ui->inputFile->text();

//    if (ui->viewerWidget->model.polygons != NULL) {
//         free(ui->viewerWidget->model.polygons);
//         free_matrix(ui->viewerWidget->model.matrix_3d, ui->viewerWidget->allocated_blocks);
//         free(ui->viewerWidget->model.matrix_3d);
//       }

    //    s21_data model;
        ui->viewerWidget->model.count_vert = 10;
        ui->viewerWidget->model.count_facets = 10;
        ui->viewerWidget->model.matrix_3d = (s21_matrix *)malloc(sizeof(s21_matrix));
        if (ui->viewerWidget->model.matrix_3d != NULL) {
          if (create_matrix(ui->viewerWidget->model.matrix_3d, ui->viewerWidget->model.count_vert, 4) == OK) {
            ui->viewerWidget->model.polygons = (s21_facets *)malloc(ui->viewerWidget->model.count_facets * sizeof(s21_facets));
            int count_allocated_blocks = 0;
            if (ui->viewerWidget->model.polygons != NULL) {
             if(open_and_parse(&(ui->viewerWidget->model), ui->viewerWidget->file.toStdString().c_str(), &count_allocated_blocks) == OK){
                 qDebug("AAAA %u\n", ui->viewerWidget->model.count_vert);
                 QFileInfo fi(ui->viewerWidget->file);
                 ui->filenameLabel->setText(fi.fileName());
                 ui->edgesLabel->setText(QString::number(ui->viewerWidget->model.count_facets));
                 ui->verticlesLabel->setText(QString::number(ui->viewerWidget->model.count_vert));
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
    double scale = ui->scaleSlider->value();
    resize_model(&(ui->viewerWidget->model), scale, scale, scale);
    ui->viewerWidget->repaint();
}

void MainWindow::rotateModel(double x, double y, double z)
{
//    double xrotate = ui->XRotateSlider->value();
//    double yrotate = ui->YRotateSlider->value();
//    double zrotate = ui->ZRotateSlider->value();
    print_matrix(*(ui->viewerWidget->model.matrix_3d));
    printf("\n");
    rotation(&(ui->viewerWidget->model), x, y, z);
    ui->viewerWidget->repaint();
    print_matrix(*(ui->viewerWidget->model.matrix_3d));
}

void MainWindow::moveModel()
{
    double xmove = ui->XTranslateSlider->value();
    double ymove = ui->YTranslateSlider->value();
    double zmove = ui->ZTranslateSlider->value();
    moving(&(ui->viewerWidget->model), xmove, ymove, zmove);
    ui->viewerWidget->repaint();
}
