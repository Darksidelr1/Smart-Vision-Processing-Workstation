/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionOpen;
    QAction *actionSave;
    QAction *actionExit;
    QAction *actionOpenVideo;
    QAction *actionOpenCamera;
    QAction *actionDownloadYOLO;
    QAction *actionInitYOLO;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget;
    QWidget *tabImage;
    QVBoxLayout *verticalLayout_6;
    QHBoxLayout *horizontalLayout;
    QPushButton *btnOpen;
    QSpacerItem *horizontalSpacer;
    QLabel *lblImageInfo;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *btnPrev;
    QPushButton *btnNext;
    QSplitter *splitter;
    QFrame *frameControls;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBoxProcessing;
    QVBoxLayout *verticalLayout_3;
    QPushButton *btnOriginal;
    QPushButton *btnGrayscale;
    QGroupBox *groupBinary;
    QVBoxLayout *verticalLayout_4;
    QPushButton *btnBinarization;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QLabel *lblThreshold;
    QSlider *sliderThreshold;
    QPushButton *btnMeanBlur;
    QGroupBox *groupGamma;
    QVBoxLayout *verticalLayout_5;
    QPushButton *btnGamma;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_2;
    QLabel *lblGamma;
    QSlider *sliderGamma;
    QPushButton *btnEdgeDetection;
    QSpacerItem *verticalSpacer;
    QLabel *lblImage;
    QWidget *tabVideo;
    QVBoxLayout *verticalLayout_7;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *btnOpenVideo;
    QPushButton *btnOpenCamera;
    QSpacerItem *horizontalSpacer_3;
    QLabel *lblVideoInfo;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *btnStartVideo;
    QPushButton *btnStopVideo;
    QSplitter *splitter_2;
    QFrame *frameVideoControls;
    QVBoxLayout *verticalLayout_8;
    QGroupBox *groupBoxVideoProcessing;
    QVBoxLayout *verticalLayout_9;
    QRadioButton *radioOriginal;
    QRadioButton *radioGrayscale;
    QRadioButton *radioBinarization;
    QRadioButton *radioMeanBlur;
    QRadioButton *radioEdgeDetection;
    QRadioButton *radioMosaic;
    QRadioButton *radioObjectDetection;
    QRadioButton *radioFaceDetection;
    QGroupBox *groupBoxVideoParams;
    QVBoxLayout *verticalLayout_10;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_3;
    QLabel *lblVideoThreshold;
    QSlider *sliderVideoThreshold;
    QFrame *line;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_4;
    QSpinBox *spinBoxMosaicSize;
    QFormLayout *formLayout;
    QLabel *label_5;
    QSpinBox *spinBoxMosaicX;
    QLabel *label_6;
    QSpinBox *spinBoxMosaicY;
    QLabel *label_7;
    QSpinBox *spinBoxMosaicWidth;
    QLabel *label_8;
    QSpinBox *spinBoxMosaicHeight;
    QFrame *line_2;
    QGroupBox *groupAI;
    QVBoxLayout *verticalLayout_11;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_10;
    QLabel *lblConfidence;
    QSlider *sliderConfidence;
    QPushButton *btnDownloadModels;
    QCheckBox *chkShowLabels;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_9;
    QSpinBox *spinBoxFrameRate;
    QSpacerItem *verticalSpacer_2;
    QLabel *lblVideo;
    QMenuBar *menubar;
    QMenu *menu;
    QMenu *menuAI;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1200, 800);
        MainWindow->setStyleSheet(QString::fromUtf8("QMainWindow {\n"
"    background-color: #f0f0f0;\n"
"}\n"
"QPushButton {\n"
"    background-color: #4a86e8;\n"
"    color: white;\n"
"    border: none;\n"
"    padding: 8px 16px;\n"
"    border-radius: 4px;\n"
"    font-weight: bold;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #3a76d8;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: #2a66c8;\n"
"}\n"
"QSlider::groove:horizontal {\n"
"    border: 1px solid #999999;\n"
"    height: 8px;\n"
"    background: #cccccc;\n"
"    margin: 2px 0;\n"
"    border-radius: 4px;\n"
"}\n"
"QSlider::handle:horizontal {\n"
"    background: #4a86e8;\n"
"    border: 1px solid #5c5c5c;\n"
"    width: 18px;\n"
"    margin: -8px 0;\n"
"    border-radius: 9px;\n"
"}\n"
"QLabel {\n"
"    color: #333333;\n"
"}\n"
"QTabWidget::pane {\n"
"    border: 1px solid #cccccc;\n"
"    background-color: #f9f9f9;\n"
"}\n"
"QTabBar::tab {\n"
"    background-color: #e0e0e0;\n"
"    color: #333333;\n"
"    padding: 8px 16px;\n"
"    border-top-left-radius: 4px;\n"
"    border-top"
                        "-right-radius: 4px;\n"
"    border: 1px solid #cccccc;\n"
"    border-bottom: none;\n"
"}\n"
"QTabBar::tab:selected {\n"
"    background-color: #f9f9f9;\n"
"    border-bottom: 1px solid #f9f9f9;\n"
"}\n"
"QTabBar::tab:!selected {\n"
"    margin-top: 2px;\n"
"}\n"
"QGroupBox {\n"
"    border: 1px solid #cccccc;\n"
"    border-radius: 5px;\n"
"    margin-top: 10px;\n"
"    padding-top: 15px;\n"
"}\n"
"QGroupBox::title {\n"
"    subcontrol-origin: margin;\n"
"    subcontrol-position: top center;\n"
"    padding: 0 5px;\n"
"}\n"
"QRadioButton, QCheckBox {\n"
"    padding: 2px;\n"
"}\n"
""));
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName("actionOpen");
        actionSave = new QAction(MainWindow);
        actionSave->setObjectName("actionSave");
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName("actionExit");
        actionOpenVideo = new QAction(MainWindow);
        actionOpenVideo->setObjectName("actionOpenVideo");
        actionOpenCamera = new QAction(MainWindow);
        actionOpenCamera->setObjectName("actionOpenCamera");
        actionDownloadYOLO = new QAction(MainWindow);
        actionDownloadYOLO->setObjectName("actionDownloadYOLO");
        actionInitYOLO = new QAction(MainWindow);
        actionInitYOLO->setObjectName("actionInitYOLO");
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName("tabWidget");
        tabImage = new QWidget();
        tabImage->setObjectName("tabImage");
        verticalLayout_6 = new QVBoxLayout(tabImage);
        verticalLayout_6->setObjectName("verticalLayout_6");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        btnOpen = new QPushButton(tabImage);
        btnOpen->setObjectName("btnOpen");

        horizontalLayout->addWidget(btnOpen);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        lblImageInfo = new QLabel(tabImage);
        lblImageInfo->setObjectName("lblImageInfo");

        horizontalLayout->addWidget(lblImageInfo);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        btnPrev = new QPushButton(tabImage);
        btnPrev->setObjectName("btnPrev");
        btnPrev->setEnabled(false);

        horizontalLayout->addWidget(btnPrev);

        btnNext = new QPushButton(tabImage);
        btnNext->setObjectName("btnNext");
        btnNext->setEnabled(false);

        horizontalLayout->addWidget(btnNext);


        verticalLayout_6->addLayout(horizontalLayout);

        splitter = new QSplitter(tabImage);
        splitter->setObjectName("splitter");
        splitter->setOrientation(Qt::Horizontal);
        frameControls = new QFrame(splitter);
        frameControls->setObjectName("frameControls");
        frameControls->setMaximumSize(QSize(250, 16777215));
        frameControls->setFrameShape(QFrame::StyledPanel);
        frameControls->setFrameShadow(QFrame::Raised);
        verticalLayout_2 = new QVBoxLayout(frameControls);
        verticalLayout_2->setObjectName("verticalLayout_2");
        groupBoxProcessing = new QGroupBox(frameControls);
        groupBoxProcessing->setObjectName("groupBoxProcessing");
        verticalLayout_3 = new QVBoxLayout(groupBoxProcessing);
        verticalLayout_3->setObjectName("verticalLayout_3");
        btnOriginal = new QPushButton(groupBoxProcessing);
        btnOriginal->setObjectName("btnOriginal");
        btnOriginal->setEnabled(false);

        verticalLayout_3->addWidget(btnOriginal);

        btnGrayscale = new QPushButton(groupBoxProcessing);
        btnGrayscale->setObjectName("btnGrayscale");
        btnGrayscale->setEnabled(false);

        verticalLayout_3->addWidget(btnGrayscale);

        groupBinary = new QGroupBox(groupBoxProcessing);
        groupBinary->setObjectName("groupBinary");
        verticalLayout_4 = new QVBoxLayout(groupBinary);
        verticalLayout_4->setObjectName("verticalLayout_4");
        btnBinarization = new QPushButton(groupBinary);
        btnBinarization->setObjectName("btnBinarization");
        btnBinarization->setEnabled(false);

        verticalLayout_4->addWidget(btnBinarization);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        label = new QLabel(groupBinary);
        label->setObjectName("label");

        horizontalLayout_2->addWidget(label);

        lblThreshold = new QLabel(groupBinary);
        lblThreshold->setObjectName("lblThreshold");

        horizontalLayout_2->addWidget(lblThreshold);


        verticalLayout_4->addLayout(horizontalLayout_2);

        sliderThreshold = new QSlider(groupBinary);
        sliderThreshold->setObjectName("sliderThreshold");
        sliderThreshold->setEnabled(false);
        sliderThreshold->setMaximum(255);
        sliderThreshold->setValue(127);
        sliderThreshold->setOrientation(Qt::Horizontal);

        verticalLayout_4->addWidget(sliderThreshold);


        verticalLayout_3->addWidget(groupBinary);

        btnMeanBlur = new QPushButton(groupBoxProcessing);
        btnMeanBlur->setObjectName("btnMeanBlur");
        btnMeanBlur->setEnabled(false);

        verticalLayout_3->addWidget(btnMeanBlur);

        groupGamma = new QGroupBox(groupBoxProcessing);
        groupGamma->setObjectName("groupGamma");
        verticalLayout_5 = new QVBoxLayout(groupGamma);
        verticalLayout_5->setObjectName("verticalLayout_5");
        btnGamma = new QPushButton(groupGamma);
        btnGamma->setObjectName("btnGamma");
        btnGamma->setEnabled(false);

        verticalLayout_5->addWidget(btnGamma);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        label_2 = new QLabel(groupGamma);
        label_2->setObjectName("label_2");

        horizontalLayout_3->addWidget(label_2);

        lblGamma = new QLabel(groupGamma);
        lblGamma->setObjectName("lblGamma");

        horizontalLayout_3->addWidget(lblGamma);


        verticalLayout_5->addLayout(horizontalLayout_3);

        sliderGamma = new QSlider(groupGamma);
        sliderGamma->setObjectName("sliderGamma");
        sliderGamma->setEnabled(false);
        sliderGamma->setMinimum(1);
        sliderGamma->setMaximum(40);
        sliderGamma->setValue(10);
        sliderGamma->setOrientation(Qt::Horizontal);

        verticalLayout_5->addWidget(sliderGamma);


        verticalLayout_3->addWidget(groupGamma);

        btnEdgeDetection = new QPushButton(groupBoxProcessing);
        btnEdgeDetection->setObjectName("btnEdgeDetection");
        btnEdgeDetection->setEnabled(false);

        verticalLayout_3->addWidget(btnEdgeDetection);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer);


        verticalLayout_2->addWidget(groupBoxProcessing);

        splitter->addWidget(frameControls);
        lblImage = new QLabel(splitter);
        lblImage->setObjectName("lblImage");
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(lblImage->sizePolicy().hasHeightForWidth());
        lblImage->setSizePolicy(sizePolicy);
        lblImage->setMinimumSize(QSize(640, 480));
        lblImage->setStyleSheet(QString::fromUtf8("background-color: #222222;"));
        lblImage->setFrameShape(QFrame::Box);
        lblImage->setAlignment(Qt::AlignCenter);
        splitter->addWidget(lblImage);

        verticalLayout_6->addWidget(splitter);

        tabWidget->addTab(tabImage, QString());
        tabVideo = new QWidget();
        tabVideo->setObjectName("tabVideo");
        verticalLayout_7 = new QVBoxLayout(tabVideo);
        verticalLayout_7->setObjectName("verticalLayout_7");
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        btnOpenVideo = new QPushButton(tabVideo);
        btnOpenVideo->setObjectName("btnOpenVideo");

        horizontalLayout_4->addWidget(btnOpenVideo);

        btnOpenCamera = new QPushButton(tabVideo);
        btnOpenCamera->setObjectName("btnOpenCamera");

        horizontalLayout_4->addWidget(btnOpenCamera);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_3);

        lblVideoInfo = new QLabel(tabVideo);
        lblVideoInfo->setObjectName("lblVideoInfo");

        horizontalLayout_4->addWidget(lblVideoInfo);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_4);

        btnStartVideo = new QPushButton(tabVideo);
        btnStartVideo->setObjectName("btnStartVideo");
        btnStartVideo->setEnabled(false);

        horizontalLayout_4->addWidget(btnStartVideo);

        btnStopVideo = new QPushButton(tabVideo);
        btnStopVideo->setObjectName("btnStopVideo");
        btnStopVideo->setEnabled(false);

        horizontalLayout_4->addWidget(btnStopVideo);


        verticalLayout_7->addLayout(horizontalLayout_4);

        splitter_2 = new QSplitter(tabVideo);
        splitter_2->setObjectName("splitter_2");
        splitter_2->setOrientation(Qt::Horizontal);
        frameVideoControls = new QFrame(splitter_2);
        frameVideoControls->setObjectName("frameVideoControls");
        frameVideoControls->setMaximumSize(QSize(250, 16777215));
        frameVideoControls->setFrameShape(QFrame::StyledPanel);
        frameVideoControls->setFrameShadow(QFrame::Raised);
        verticalLayout_8 = new QVBoxLayout(frameVideoControls);
        verticalLayout_8->setObjectName("verticalLayout_8");
        groupBoxVideoProcessing = new QGroupBox(frameVideoControls);
        groupBoxVideoProcessing->setObjectName("groupBoxVideoProcessing");
        verticalLayout_9 = new QVBoxLayout(groupBoxVideoProcessing);
        verticalLayout_9->setObjectName("verticalLayout_9");
        radioOriginal = new QRadioButton(groupBoxVideoProcessing);
        radioOriginal->setObjectName("radioOriginal");
        radioOriginal->setChecked(true);

        verticalLayout_9->addWidget(radioOriginal);

        radioGrayscale = new QRadioButton(groupBoxVideoProcessing);
        radioGrayscale->setObjectName("radioGrayscale");

        verticalLayout_9->addWidget(radioGrayscale);

        radioBinarization = new QRadioButton(groupBoxVideoProcessing);
        radioBinarization->setObjectName("radioBinarization");

        verticalLayout_9->addWidget(radioBinarization);

        radioMeanBlur = new QRadioButton(groupBoxVideoProcessing);
        radioMeanBlur->setObjectName("radioMeanBlur");

        verticalLayout_9->addWidget(radioMeanBlur);

        radioEdgeDetection = new QRadioButton(groupBoxVideoProcessing);
        radioEdgeDetection->setObjectName("radioEdgeDetection");

        verticalLayout_9->addWidget(radioEdgeDetection);

        radioMosaic = new QRadioButton(groupBoxVideoProcessing);
        radioMosaic->setObjectName("radioMosaic");

        verticalLayout_9->addWidget(radioMosaic);

        radioObjectDetection = new QRadioButton(groupBoxVideoProcessing);
        radioObjectDetection->setObjectName("radioObjectDetection");

        verticalLayout_9->addWidget(radioObjectDetection);

        radioFaceDetection = new QRadioButton(groupBoxVideoProcessing);
        radioFaceDetection->setObjectName("radioFaceDetection");

        verticalLayout_9->addWidget(radioFaceDetection);


        verticalLayout_8->addWidget(groupBoxVideoProcessing);

        groupBoxVideoParams = new QGroupBox(frameVideoControls);
        groupBoxVideoParams->setObjectName("groupBoxVideoParams");
        verticalLayout_10 = new QVBoxLayout(groupBoxVideoParams);
        verticalLayout_10->setObjectName("verticalLayout_10");
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        label_3 = new QLabel(groupBoxVideoParams);
        label_3->setObjectName("label_3");

        horizontalLayout_5->addWidget(label_3);

        lblVideoThreshold = new QLabel(groupBoxVideoParams);
        lblVideoThreshold->setObjectName("lblVideoThreshold");

        horizontalLayout_5->addWidget(lblVideoThreshold);


        verticalLayout_10->addLayout(horizontalLayout_5);

        sliderVideoThreshold = new QSlider(groupBoxVideoParams);
        sliderVideoThreshold->setObjectName("sliderVideoThreshold");
        sliderVideoThreshold->setMaximum(255);
        sliderVideoThreshold->setValue(127);
        sliderVideoThreshold->setOrientation(Qt::Horizontal);

        verticalLayout_10->addWidget(sliderVideoThreshold);

        line = new QFrame(groupBoxVideoParams);
        line->setObjectName("line");
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout_10->addWidget(line);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        label_4 = new QLabel(groupBoxVideoParams);
        label_4->setObjectName("label_4");

        horizontalLayout_6->addWidget(label_4);

        spinBoxMosaicSize = new QSpinBox(groupBoxVideoParams);
        spinBoxMosaicSize->setObjectName("spinBoxMosaicSize");
        spinBoxMosaicSize->setMinimum(5);
        spinBoxMosaicSize->setMaximum(50);
        spinBoxMosaicSize->setValue(10);

        horizontalLayout_6->addWidget(spinBoxMosaicSize);


        verticalLayout_10->addLayout(horizontalLayout_6);

        formLayout = new QFormLayout();
        formLayout->setObjectName("formLayout");
        label_5 = new QLabel(groupBoxVideoParams);
        label_5->setObjectName("label_5");

        formLayout->setWidget(0, QFormLayout::LabelRole, label_5);

        spinBoxMosaicX = new QSpinBox(groupBoxVideoParams);
        spinBoxMosaicX->setObjectName("spinBoxMosaicX");
        spinBoxMosaicX->setMinimum(0);
        spinBoxMosaicX->setMaximum(1000);
        spinBoxMosaicX->setValue(100);

        formLayout->setWidget(0, QFormLayout::FieldRole, spinBoxMosaicX);

        label_6 = new QLabel(groupBoxVideoParams);
        label_6->setObjectName("label_6");

        formLayout->setWidget(1, QFormLayout::LabelRole, label_6);

        spinBoxMosaicY = new QSpinBox(groupBoxVideoParams);
        spinBoxMosaicY->setObjectName("spinBoxMosaicY");
        spinBoxMosaicY->setMaximum(1000);
        spinBoxMosaicY->setValue(100);

        formLayout->setWidget(1, QFormLayout::FieldRole, spinBoxMosaicY);

        label_7 = new QLabel(groupBoxVideoParams);
        label_7->setObjectName("label_7");

        formLayout->setWidget(2, QFormLayout::LabelRole, label_7);

        spinBoxMosaicWidth = new QSpinBox(groupBoxVideoParams);
        spinBoxMosaicWidth->setObjectName("spinBoxMosaicWidth");
        spinBoxMosaicWidth->setMinimum(10);
        spinBoxMosaicWidth->setMaximum(1000);
        spinBoxMosaicWidth->setValue(200);

        formLayout->setWidget(2, QFormLayout::FieldRole, spinBoxMosaicWidth);

        label_8 = new QLabel(groupBoxVideoParams);
        label_8->setObjectName("label_8");

        formLayout->setWidget(3, QFormLayout::LabelRole, label_8);

        spinBoxMosaicHeight = new QSpinBox(groupBoxVideoParams);
        spinBoxMosaicHeight->setObjectName("spinBoxMosaicHeight");
        spinBoxMosaicHeight->setMinimum(10);
        spinBoxMosaicHeight->setMaximum(1000);
        spinBoxMosaicHeight->setValue(150);

        formLayout->setWidget(3, QFormLayout::FieldRole, spinBoxMosaicHeight);


        verticalLayout_10->addLayout(formLayout);

        line_2 = new QFrame(groupBoxVideoParams);
        line_2->setObjectName("line_2");
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        verticalLayout_10->addWidget(line_2);

        groupAI = new QGroupBox(groupBoxVideoParams);
        groupAI->setObjectName("groupAI");
        verticalLayout_11 = new QVBoxLayout(groupAI);
        verticalLayout_11->setObjectName("verticalLayout_11");
        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName("horizontalLayout_8");
        label_10 = new QLabel(groupAI);
        label_10->setObjectName("label_10");

        horizontalLayout_8->addWidget(label_10);

        lblConfidence = new QLabel(groupAI);
        lblConfidence->setObjectName("lblConfidence");

        horizontalLayout_8->addWidget(lblConfidence);


        verticalLayout_11->addLayout(horizontalLayout_8);

        sliderConfidence = new QSlider(groupAI);
        sliderConfidence->setObjectName("sliderConfidence");
        sliderConfidence->setMinimum(10);
        sliderConfidence->setMaximum(100);
        sliderConfidence->setValue(50);
        sliderConfidence->setOrientation(Qt::Horizontal);

        verticalLayout_11->addWidget(sliderConfidence);

        btnDownloadModels = new QPushButton(groupAI);
        btnDownloadModels->setObjectName("btnDownloadModels");

        verticalLayout_11->addWidget(btnDownloadModels);

        chkShowLabels = new QCheckBox(groupAI);
        chkShowLabels->setObjectName("chkShowLabels");
        chkShowLabels->setChecked(true);

        verticalLayout_11->addWidget(chkShowLabels);


        verticalLayout_10->addWidget(groupAI);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        label_9 = new QLabel(groupBoxVideoParams);
        label_9->setObjectName("label_9");

        horizontalLayout_7->addWidget(label_9);

        spinBoxFrameRate = new QSpinBox(groupBoxVideoParams);
        spinBoxFrameRate->setObjectName("spinBoxFrameRate");
        spinBoxFrameRate->setMinimum(1);
        spinBoxFrameRate->setMaximum(60);
        spinBoxFrameRate->setValue(10);

        horizontalLayout_7->addWidget(spinBoxFrameRate);


        verticalLayout_10->addLayout(horizontalLayout_7);


        verticalLayout_8->addWidget(groupBoxVideoParams);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_8->addItem(verticalSpacer_2);

        splitter_2->addWidget(frameVideoControls);
        lblVideo = new QLabel(splitter_2);
        lblVideo->setObjectName("lblVideo");
        sizePolicy.setHeightForWidth(lblVideo->sizePolicy().hasHeightForWidth());
        lblVideo->setSizePolicy(sizePolicy);
        lblVideo->setMinimumSize(QSize(640, 480));
        lblVideo->setStyleSheet(QString::fromUtf8("background-color: #222222;"));
        lblVideo->setFrameShape(QFrame::Box);
        lblVideo->setAlignment(Qt::AlignCenter);
        splitter_2->addWidget(lblVideo);

        verticalLayout_7->addWidget(splitter_2);

        tabWidget->addTab(tabVideo, QString());

        verticalLayout->addWidget(tabWidget);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1200, 22));
        menu = new QMenu(menubar);
        menu->setObjectName("menu");
        menuAI = new QMenu(menubar);
        menuAI->setObjectName("menuAI");
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menu->menuAction());
        menubar->addAction(menuAI->menuAction());
        menu->addAction(actionOpen);
        menu->addAction(actionOpenVideo);
        menu->addAction(actionOpenCamera);
        menu->addAction(actionSave);
        menu->addAction(actionExit);
        menuAI->addAction(actionDownloadYOLO);
        menuAI->addAction(actionInitYOLO);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "\345\233\276\345\203\217\344\270\216\350\247\206\351\242\221\345\244\204\347\220\206\350\275\257\344\273\266", nullptr));
        actionOpen->setText(QCoreApplication::translate("MainWindow", "\346\211\223\345\274\200\345\233\276\347\211\207", nullptr));
        actionSave->setText(QCoreApplication::translate("MainWindow", "\344\277\235\345\255\230", nullptr));
        actionExit->setText(QCoreApplication::translate("MainWindow", "\351\200\200\345\207\272", nullptr));
        actionOpenVideo->setText(QCoreApplication::translate("MainWindow", "\346\211\223\345\274\200\350\247\206\351\242\221", nullptr));
        actionOpenCamera->setText(QCoreApplication::translate("MainWindow", "\346\211\223\345\274\200\346\221\204\345\203\217\345\244\264", nullptr));
        actionDownloadYOLO->setText(QCoreApplication::translate("MainWindow", "\345\210\235\345\247\213\345\214\226YOLO\346\250\241\345\236\213", nullptr));
        actionInitYOLO->setText(QCoreApplication::translate("MainWindow", "\345\210\235\345\247\213\345\214\226YOLO\346\250\241\345\236\213", nullptr));
        btnOpen->setText(QCoreApplication::translate("MainWindow", "\346\211\223\345\274\200\345\233\276\347\211\207", nullptr));
        lblImageInfo->setText(QCoreApplication::translate("MainWindow", "\350\257\267\345\205\210\346\211\223\345\274\200\345\233\276\347\211\207...", nullptr));
        btnPrev->setText(QCoreApplication::translate("MainWindow", "\344\270\212\344\270\200\345\274\240", nullptr));
        btnNext->setText(QCoreApplication::translate("MainWindow", "\344\270\213\344\270\200\345\274\240", nullptr));
        groupBoxProcessing->setTitle(QCoreApplication::translate("MainWindow", "\345\233\276\345\203\217\345\244\204\347\220\206", nullptr));
        btnOriginal->setText(QCoreApplication::translate("MainWindow", "\345\216\237\345\247\213\345\233\276\345\203\217", nullptr));
        btnGrayscale->setText(QCoreApplication::translate("MainWindow", "\347\201\260\345\272\246\345\214\226", nullptr));
        groupBinary->setTitle(QCoreApplication::translate("MainWindow", "\344\272\214\345\200\274\345\214\226", nullptr));
        btnBinarization->setText(QCoreApplication::translate("MainWindow", "\345\272\224\347\224\250\344\272\214\345\200\274\345\214\226", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\351\230\210\345\200\274\357\274\232", nullptr));
        lblThreshold->setText(QCoreApplication::translate("MainWindow", "127", nullptr));
        btnMeanBlur->setText(QCoreApplication::translate("MainWindow", "3\303\2273\345\235\207\345\200\274\346\273\244\346\263\242", nullptr));
        groupGamma->setTitle(QCoreApplication::translate("MainWindow", "\344\274\275\351\251\254\345\217\230\346\215\242", nullptr));
        btnGamma->setText(QCoreApplication::translate("MainWindow", "\345\272\224\347\224\250\344\274\275\351\251\254\345\217\230\346\215\242", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "\344\274\275\351\251\254\345\200\274\357\274\232", nullptr));
        lblGamma->setText(QCoreApplication::translate("MainWindow", "1.0", nullptr));
        btnEdgeDetection->setText(QCoreApplication::translate("MainWindow", "\350\276\271\347\274\230\346\243\200\346\265\213", nullptr));
        lblImage->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(tabImage), QCoreApplication::translate("MainWindow", "\345\233\276\345\203\217\345\244\204\347\220\206", nullptr));
        btnOpenVideo->setText(QCoreApplication::translate("MainWindow", "\346\211\223\345\274\200\350\247\206\351\242\221", nullptr));
        btnOpenCamera->setText(QCoreApplication::translate("MainWindow", "\346\211\223\345\274\200\346\221\204\345\203\217\345\244\264", nullptr));
        lblVideoInfo->setText(QCoreApplication::translate("MainWindow", "\350\257\267\345\205\210\346\211\223\345\274\200\350\247\206\351\242\221\346\210\226\346\221\204\345\203\217\345\244\264...", nullptr));
        btnStartVideo->setText(QCoreApplication::translate("MainWindow", "\345\274\200\345\247\213\345\244\204\347\220\206", nullptr));
        btnStopVideo->setText(QCoreApplication::translate("MainWindow", "\345\201\234\346\255\242\345\244\204\347\220\206", nullptr));
        groupBoxVideoProcessing->setTitle(QCoreApplication::translate("MainWindow", "\350\247\206\351\242\221\345\244\204\347\220\206\346\250\241\345\274\217", nullptr));
        radioOriginal->setText(QCoreApplication::translate("MainWindow", "\345\216\237\345\247\213\350\247\206\351\242\221", nullptr));
        radioGrayscale->setText(QCoreApplication::translate("MainWindow", "\347\201\260\345\272\246\345\214\226", nullptr));
        radioBinarization->setText(QCoreApplication::translate("MainWindow", "\344\272\214\345\200\274\345\214\226", nullptr));
        radioMeanBlur->setText(QCoreApplication::translate("MainWindow", "3\303\2273\345\235\207\345\200\274\346\273\244\346\263\242", nullptr));
        radioEdgeDetection->setText(QCoreApplication::translate("MainWindow", "\350\276\271\347\274\230\346\243\200\346\265\213", nullptr));
        radioMosaic->setText(QCoreApplication::translate("MainWindow", "\345\261\200\351\203\250\351\251\254\350\265\233\345\205\213", nullptr));
        radioObjectDetection->setText(QCoreApplication::translate("MainWindow", "AI\347\211\251\344\275\223\346\243\200\346\265\213", nullptr));
        radioFaceDetection->setText(QCoreApplication::translate("MainWindow", "\344\272\272\350\204\270\346\243\200\346\265\213(\346\227\240\351\234\200\344\270\213\350\275\275\346\250\241\345\236\213)", nullptr));
        groupBoxVideoParams->setTitle(QCoreApplication::translate("MainWindow", "\345\217\202\346\225\260\350\256\276\347\275\256", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "\351\230\210\345\200\274\357\274\232", nullptr));
        lblVideoThreshold->setText(QCoreApplication::translate("MainWindow", "127", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "\351\251\254\350\265\233\345\205\213\345\214\272\345\237\237\345\244\247\345\260\217\357\274\232", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "X:", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "Y:", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "\345\256\275\345\272\246:", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "\351\253\230\345\272\246:", nullptr));
        groupAI->setTitle(QCoreApplication::translate("MainWindow", "AI\345\217\202\346\225\260\350\256\276\347\275\256", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "\347\275\256\344\277\241\345\272\246\357\274\232", nullptr));
        lblConfidence->setText(QCoreApplication::translate("MainWindow", "0.5", nullptr));
        btnDownloadModels->setText(QCoreApplication::translate("MainWindow", "\345\210\235\345\247\213\345\214\226YOLO\346\250\241\345\236\213", nullptr));
        chkShowLabels->setText(QCoreApplication::translate("MainWindow", "\346\230\276\347\244\272\346\240\207\347\255\276", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "\345\270\247\347\216\207\346\216\247\345\210\266(FPS)\357\274\232", nullptr));
        lblVideo->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(tabVideo), QCoreApplication::translate("MainWindow", "\350\247\206\351\242\221\345\244\204\347\220\206", nullptr));
        menu->setTitle(QCoreApplication::translate("MainWindow", "\346\226\207\344\273\266", nullptr));
        menuAI->setTitle(QCoreApplication::translate("MainWindow", "AI\345\212\237\350\203\275", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
