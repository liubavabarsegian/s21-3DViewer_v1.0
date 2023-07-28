/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>
#include "opengl.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLabel *label;
    OpenGL *viewerWidget;
    QLineEdit *inputFile;
    QPushButton *openFileButton;
    QComboBox *typeOfProjectionBox;
    QLabel *label_3;
    QTabWidget *tabWidget;
    QWidget *verticles;
    QLabel *label_7;
    QSlider *verticlesSlider;
    QRadioButton *noVerticles;
    QRadioButton *circleVerticles;
    QRadioButton *squareVerticles;
    QPushButton *verticlesColor;
    QWidget *edges;
    QLabel *label_4;
    QRadioButton *edgesSolid;
    QRadioButton *edgesDashed;
    QLabel *label_5;
    QSlider *edgesSize;
    QPushButton *edgesColor;
    QWidget *background;
    QPushButton *backgroundColor;
    QSlider *scaleSlider;
    QLabel *label_10;
    QLabel *label_11;
    QLabel *label_12;
    QLabel *label_13;
    QLabel *label_14;
    QSlider *XRotateSlider;
    QSlider *YRotateSlider;
    QSlider *ZRotateSlider;
    QLabel *label_15;
    QLabel *label_16;
    QSlider *XTranslateSlider;
    QLabel *label_17;
    QSlider *YTranslateSlider;
    QSlider *ZTranslateSlider;
    QLabel *label_18;
    QLabel *label_19;
    QLabel *label_20;
    QLabel *label_21;
    QPushButton *inputFileButton;
    QPushButton *recordButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;
    QButtonGroup *buttonGroup;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1189, 791);
#if QT_CONFIG(tooltip)
        MainWindow->setToolTip(QString::fromUtf8(""));
#endif // QT_CONFIG(tooltip)
        MainWindow->setStyleSheet(QString::fromUtf8("background-color: rgb(12, 11, 60);\n"
"border-radius: 20px;"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(40, 40, 221, 31));
        QFont font;
        font.setFamily(QString::fromUtf8("LKLUG"));
        font.setPointSize(23);
        font.setBold(true);
        font.setItalic(true);
        font.setUnderline(false);
        font.setWeight(75);
        font.setStrikeOut(false);
        label->setFont(font);
        label->setStyleSheet(QString::fromUtf8("color: white"));
        viewerWidget = new OpenGL(centralwidget);
        viewerWidget->setObjectName(QString::fromUtf8("viewerWidget"));
        viewerWidget->setGeometry(QRect(30, 90, 761, 561));
        inputFile = new QLineEdit(centralwidget);
        inputFile->setObjectName(QString::fromUtf8("inputFile"));
        inputFile->setGeometry(QRect(820, 90, 241, 31));
        inputFile->setStyleSheet(QString::fromUtf8("background-color:  rgb(153, 193, 241);\n"
"color: rgb(22, 7, 83);\n"
"border-radius: 10px;\n"
""));
        openFileButton = new QPushButton(centralwidget);
        openFileButton->setObjectName(QString::fromUtf8("openFileButton"));
        openFileButton->setGeometry(QRect(820, 130, 301, 41));
        QFont font1;
        font1.setFamily(QString::fromUtf8("LKLUG"));
        font1.setPointSize(14);
        font1.setBold(true);
        font1.setItalic(true);
        font1.setWeight(75);
        openFileButton->setFont(font1);
        openFileButton->setStyleSheet(QString::fromUtf8("color: rgb(0, 15, 88);\n"
"background-color: rgb(153, 193, 241);\n"
"border-radius: 20px;"));
        typeOfProjectionBox = new QComboBox(centralwidget);
        typeOfProjectionBox->addItem(QString());
        typeOfProjectionBox->addItem(QString());
        typeOfProjectionBox->setObjectName(QString::fromUtf8("typeOfProjectionBox"));
        typeOfProjectionBox->setGeometry(QRect(980, 190, 141, 31));
        typeOfProjectionBox->setStyleSheet(QString::fromUtf8("background-color: rgb(153, 193, 241);\n"
"color: rgb(12, 11, 60);\n"
"border-radius: 10px;\n"
""));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(830, 200, 141, 17));
        label_3->setStyleSheet(QString::fromUtf8("color: white"));
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setEnabled(true);
        tabWidget->setGeometry(QRect(830, 240, 291, 181));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(tabWidget->sizePolicy().hasHeightForWidth());
        tabWidget->setSizePolicy(sizePolicy);
        tabWidget->setMaximumSize(QSize(291, 16777215));
        tabWidget->setStyleSheet(QString::fromUtf8("background-color: rgb(12, 11, 60);\n"
"border-radius: 10px;\n"
"color: white;"));
        verticles = new QWidget();
        verticles->setObjectName(QString::fromUtf8("verticles"));
        verticles->setStyleSheet(QString::fromUtf8(""));
        label_7 = new QLabel(verticles);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(20, 110, 31, 17));
        label_7->setStyleSheet(QString::fromUtf8("color: white"));
        verticlesSlider = new QSlider(verticles);
        verticlesSlider->setObjectName(QString::fromUtf8("verticlesSlider"));
        verticlesSlider->setGeometry(QRect(70, 110, 91, 16));
        verticlesSlider->setMinimum(1);
        verticlesSlider->setMaximum(30);
        verticlesSlider->setOrientation(Qt::Horizontal);
        noVerticles = new QRadioButton(verticles);
        noVerticles->setObjectName(QString::fromUtf8("noVerticles"));
        noVerticles->setGeometry(QRect(10, 30, 61, 23));
        noVerticles->setStyleSheet(QString::fromUtf8("color: white;"));
        circleVerticles = new QRadioButton(verticles);
        circleVerticles->setObjectName(QString::fromUtf8("circleVerticles"));
        circleVerticles->setGeometry(QRect(100, 30, 71, 23));
        circleVerticles->setStyleSheet(QString::fromUtf8("color: white;"));
        squareVerticles = new QRadioButton(verticles);
        squareVerticles->setObjectName(QString::fromUtf8("squareVerticles"));
        squareVerticles->setGeometry(QRect(190, 30, 91, 23));
        squareVerticles->setStyleSheet(QString::fromUtf8("color: white;"));
        verticlesColor = new QPushButton(verticles);
        verticlesColor->setObjectName(QString::fromUtf8("verticlesColor"));
        verticlesColor->setGeometry(QRect(190, 100, 81, 31));
        verticlesColor->setStyleSheet(QString::fromUtf8("background-color: rgb(153, 193, 241);\n"
"color: rgb(0, 15, 88);"));
        tabWidget->addTab(verticles, QString());
        edges = new QWidget();
        edges->setObjectName(QString::fromUtf8("edges"));
        label_4 = new QLabel(edges);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(70, 20, 111, 21));
        label_4->setStyleSheet(QString::fromUtf8("color: white;"));
        label_4->setScaledContents(false);
        label_4->setAlignment(Qt::AlignCenter);
        label_4->setOpenExternalLinks(false);
        edgesSolid = new QRadioButton(edges);
        buttonGroup = new QButtonGroup(MainWindow);
        buttonGroup->setObjectName(QString::fromUtf8("buttonGroup"));
        buttonGroup->addButton(edgesSolid);
        edgesSolid->setObjectName(QString::fromUtf8("edgesSolid"));
        edgesSolid->setGeometry(QRect(0, 60, 112, 23));
        edgesSolid->setStyleSheet(QString::fromUtf8("color: white;"));
        edgesDashed = new QRadioButton(edges);
        buttonGroup->addButton(edgesDashed);
        edgesDashed->setObjectName(QString::fromUtf8("edgesDashed"));
        edgesDashed->setGeometry(QRect(170, 60, 112, 23));
        edgesDashed->setStyleSheet(QString::fromUtf8("color: white;"));
        label_5 = new QLabel(edges);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(0, 110, 31, 17));
        label_5->setStyleSheet(QString::fromUtf8("color: white"));
        edgesSize = new QSlider(edges);
        edgesSize->setObjectName(QString::fromUtf8("edgesSize"));
        edgesSize->setGeometry(QRect(50, 110, 91, 16));
        edgesSize->setMinimum(1);
        edgesSize->setMaximum(15);
        edgesSize->setOrientation(Qt::Horizontal);
        edgesColor = new QPushButton(edges);
        edgesColor->setObjectName(QString::fromUtf8("edgesColor"));
        edgesColor->setGeometry(QRect(170, 100, 101, 31));
        edgesColor->setStyleSheet(QString::fromUtf8("background-color: rgb(153, 193, 241);\n"
"color: rgb(0, 15, 88);"));
        tabWidget->addTab(edges, QString());
        background = new QWidget();
        background->setObjectName(QString::fromUtf8("background"));
        backgroundColor = new QPushButton(background);
        backgroundColor->setObjectName(QString::fromUtf8("backgroundColor"));
        backgroundColor->setGeometry(QRect(40, 50, 211, 41));
        backgroundColor->setStyleSheet(QString::fromUtf8("background-color: rgb(153, 193, 241);\n"
"color: rgb(0, 15, 88);"));
        tabWidget->addTab(background, QString());
        scaleSlider = new QSlider(centralwidget);
        scaleSlider->setObjectName(QString::fromUtf8("scaleSlider"));
        scaleSlider->setGeometry(QRect(920, 430, 201, 16));
        scaleSlider->setOrientation(Qt::Horizontal);
        label_10 = new QLabel(centralwidget);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(830, 430, 67, 17));
        label_10->setStyleSheet(QString::fromUtf8("color: white;"));
        label_11 = new QLabel(centralwidget);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(830, 470, 67, 17));
        label_11->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        label_12 = new QLabel(centralwidget);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setGeometry(QRect(920, 470, 21, 16));
        label_12->setStyleSheet(QString::fromUtf8("color: white;"));
        label_13 = new QLabel(centralwidget);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setGeometry(QRect(920, 500, 21, 16));
        label_13->setStyleSheet(QString::fromUtf8("color: white;"));
        label_14 = new QLabel(centralwidget);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setGeometry(QRect(920, 530, 21, 16));
        label_14->setStyleSheet(QString::fromUtf8("color: white;"));
        XRotateSlider = new QSlider(centralwidget);
        XRotateSlider->setObjectName(QString::fromUtf8("XRotateSlider"));
        XRotateSlider->setGeometry(QRect(960, 470, 160, 16));
        XRotateSlider->setOrientation(Qt::Horizontal);
        YRotateSlider = new QSlider(centralwidget);
        YRotateSlider->setObjectName(QString::fromUtf8("YRotateSlider"));
        YRotateSlider->setGeometry(QRect(960, 500, 160, 16));
        YRotateSlider->setOrientation(Qt::Horizontal);
        ZRotateSlider = new QSlider(centralwidget);
        ZRotateSlider->setObjectName(QString::fromUtf8("ZRotateSlider"));
        ZRotateSlider->setGeometry(QRect(960, 530, 160, 16));
        ZRotateSlider->setOrientation(Qt::Horizontal);
        label_15 = new QLabel(centralwidget);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setGeometry(QRect(920, 630, 21, 16));
        label_15->setStyleSheet(QString::fromUtf8("color: white;"));
        label_16 = new QLabel(centralwidget);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        label_16->setGeometry(QRect(920, 600, 21, 16));
        label_16->setStyleSheet(QString::fromUtf8("color: white;"));
        XTranslateSlider = new QSlider(centralwidget);
        XTranslateSlider->setObjectName(QString::fromUtf8("XTranslateSlider"));
        XTranslateSlider->setGeometry(QRect(960, 570, 160, 16));
        XTranslateSlider->setOrientation(Qt::Horizontal);
        label_17 = new QLabel(centralwidget);
        label_17->setObjectName(QString::fromUtf8("label_17"));
        label_17->setGeometry(QRect(830, 570, 67, 17));
        label_17->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        YTranslateSlider = new QSlider(centralwidget);
        YTranslateSlider->setObjectName(QString::fromUtf8("YTranslateSlider"));
        YTranslateSlider->setGeometry(QRect(960, 600, 160, 16));
        YTranslateSlider->setOrientation(Qt::Horizontal);
        ZTranslateSlider = new QSlider(centralwidget);
        ZTranslateSlider->setObjectName(QString::fromUtf8("ZTranslateSlider"));
        ZTranslateSlider->setGeometry(QRect(960, 630, 160, 16));
        ZTranslateSlider->setOrientation(Qt::Horizontal);
        label_18 = new QLabel(centralwidget);
        label_18->setObjectName(QString::fromUtf8("label_18"));
        label_18->setGeometry(QRect(920, 570, 21, 16));
        label_18->setStyleSheet(QString::fromUtf8("color: white;"));
        label_19 = new QLabel(centralwidget);
        label_19->setObjectName(QString::fromUtf8("label_19"));
        label_19->setGeometry(QRect(60, 670, 67, 17));
        label_19->setStyleSheet(QString::fromUtf8("color: white;"));
        label_20 = new QLabel(centralwidget);
        label_20->setObjectName(QString::fromUtf8("label_20"));
        label_20->setGeometry(QRect(230, 670, 67, 17));
        label_20->setStyleSheet(QString::fromUtf8("color: white;"));
        label_21 = new QLabel(centralwidget);
        label_21->setObjectName(QString::fromUtf8("label_21"));
        label_21->setGeometry(QRect(400, 670, 67, 17));
        label_21->setStyleSheet(QString::fromUtf8("color: white;"));
        inputFileButton = new QPushButton(centralwidget);
        inputFileButton->setObjectName(QString::fromUtf8("inputFileButton"));
        inputFileButton->setGeometry(QRect(1060, 80, 71, 41));
        inputFileButton->setStyleSheet(QString::fromUtf8(""));
        QIcon icon;
        icon.addFile(QString::fromUtf8("../3d-viewer/imgs/folder.png"), QSize(), QIcon::Selected, QIcon::On);
        inputFileButton->setIcon(icon);
        inputFileButton->setIconSize(QSize(50, 50));
        recordButton = new QPushButton(centralwidget);
        recordButton->setObjectName(QString::fromUtf8("recordButton"));
        recordButton->setGeometry(QRect(560, 670, 101, 61));
        recordButton->setStyleSheet(QString::fromUtf8("background-color: white;"));
        MainWindow->setCentralWidget(centralwidget);
        inputFileButton->raise();
        label->raise();
        viewerWidget->raise();
        inputFile->raise();
        openFileButton->raise();
        typeOfProjectionBox->raise();
        label_3->raise();
        tabWidget->raise();
        scaleSlider->raise();
        label_10->raise();
        label_11->raise();
        label_12->raise();
        label_13->raise();
        label_14->raise();
        XRotateSlider->raise();
        YRotateSlider->raise();
        ZRotateSlider->raise();
        label_15->raise();
        label_16->raise();
        XTranslateSlider->raise();
        label_17->raise();
        YTranslateSlider->raise();
        ZTranslateSlider->raise();
        label_18->raise();
        label_19->raise();
        label_20->raise();
        label_21->raise();
        recordButton->raise();
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1189, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "3D VIEWER", nullptr));
        openFileButton->setText(QCoreApplication::translate("MainWindow", "DRAW MODEL", nullptr));
        typeOfProjectionBox->setItemText(0, QCoreApplication::translate("MainWindow", "Central", nullptr));
        typeOfProjectionBox->setItemText(1, QCoreApplication::translate("MainWindow", "Parallel", nullptr));

        label_3->setText(QCoreApplication::translate("MainWindow", "Type of projection", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "Size", nullptr));
        noVerticles->setText(QCoreApplication::translate("MainWindow", "none", nullptr));
        circleVerticles->setText(QCoreApplication::translate("MainWindow", "circle", nullptr));
        squareVerticles->setText(QCoreApplication::translate("MainWindow", "square", nullptr));
        verticlesColor->setText(QCoreApplication::translate("MainWindow", "Pick color", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(verticles), QCoreApplication::translate("MainWindow", " Verticles ", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Type", nullptr));
        edgesSolid->setText(QCoreApplication::translate("MainWindow", "solid", nullptr));
        edgesDashed->setText(QCoreApplication::translate("MainWindow", "dashed", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "Size", nullptr));
        edgesColor->setText(QCoreApplication::translate("MainWindow", "Pick color", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(edges), QCoreApplication::translate("MainWindow", "    Edges    ", nullptr));
        backgroundColor->setText(QCoreApplication::translate("MainWindow", "Pick background color", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(background), QCoreApplication::translate("MainWindow", "Background", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "Scale", nullptr));
        label_11->setText(QCoreApplication::translate("MainWindow", "Rotate", nullptr));
        label_12->setText(QCoreApplication::translate("MainWindow", "X", nullptr));
        label_13->setText(QCoreApplication::translate("MainWindow", "Y", nullptr));
        label_14->setText(QCoreApplication::translate("MainWindow", "Z", nullptr));
        label_15->setText(QCoreApplication::translate("MainWindow", "Z", nullptr));
        label_16->setText(QCoreApplication::translate("MainWindow", "Y", nullptr));
        label_17->setText(QCoreApplication::translate("MainWindow", "Translate", nullptr));
        label_18->setText(QCoreApplication::translate("MainWindow", "X", nullptr));
        label_19->setText(QCoreApplication::translate("MainWindow", "filename", nullptr));
        label_20->setText(QCoreApplication::translate("MainWindow", "verticles", nullptr));
        label_21->setText(QCoreApplication::translate("MainWindow", "edges", nullptr));
        inputFileButton->setText(QString());
        recordButton->setText(QCoreApplication::translate("MainWindow", "Record", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
