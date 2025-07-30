#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QDir>
#include <QFileInfo>
#include <QButtonGroup>
#include <QDebug>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QProgressDialog>
#include <QFile>
#include <QProgressBar>
#include <QElapsedTimer>
#include <QThread>
#include <QCoreApplication>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , currentImageIndex(0)
    , isVideoPlaying(false)
    , isVideoOpened(false)
    , isUsingCamera(false)
    , videoFrameRate(24)
    , currentVideoProcessingMode(0)
    , mosaicSize(10)
    , isProcessingFrame(false)
    , yoloInitialized(false)
    , confidenceThreshold(0.5f)
    , faceDetectorInitialized(false)
    , useFaceDetection(false)
{
    ui->setupUi(this);
    
    // 初始化视频相关变量
    videoTimer = new QTimer(this);
    
    // 图像处理相关连接信号和槽
    connect(ui->btnOpen, &QPushButton::clicked, this, &MainWindow::openImages);
    connect(ui->actionOpen, &QAction::triggered, this, &MainWindow::openImages);
    connect(ui->btnNext, &QPushButton::clicked, this, &MainWindow::showNextImage);
    connect(ui->btnPrev, &QPushButton::clicked, this, &MainWindow::showPrevImage);
    connect(ui->btnOriginal, &QPushButton::clicked, [this]() { displayImage(originalImages[currentImageIndex]); });
    connect(ui->btnGrayscale, &QPushButton::clicked, this, &MainWindow::applyGrayscale);
    connect(ui->btnBinarization, &QPushButton::clicked, this, &MainWindow::applyBinarization);
    connect(ui->btnMeanBlur, &QPushButton::clicked, this, &MainWindow::applyMeanBlur);
    connect(ui->btnGamma, &QPushButton::clicked, this, &MainWindow::applyGammaCorrection);
    connect(ui->btnEdgeDetection, &QPushButton::clicked, this, &MainWindow::applyEdgeDetection);
    
    connect(ui->sliderThreshold, &QSlider::valueChanged, this, &MainWindow::sliderValueChanged);
    connect(ui->sliderGamma, &QSlider::valueChanged, this, &MainWindow::sliderValueChanged);
    
    connect(ui->actionSave, &QAction::triggered, [this]() {
        if (!processedImages.isEmpty()) {
            QString fileName = QFileDialog::getSaveFileName(this, tr("保存图片"), "", 
                               tr("JPEG (*.jpg *.jpeg);;PNG (*.png);;BMP (*.bmp);;All Files (*)"));
            if (!fileName.isEmpty()) {
                cv::imwrite(fileName.toStdString(), processedImages[currentImageIndex]);
            }
        }
    });
    
    connect(ui->actionExit, &QAction::triggered, this, &QMainWindow::close);
    
    // 视频处理相关连接信号和槽
    connect(ui->btnOpenVideo, &QPushButton::clicked, this, &MainWindow::openVideo);
    connect(ui->btnOpenCamera, &QPushButton::clicked, this, &MainWindow::openCamera);
    connect(ui->actionOpenVideo, &QAction::triggered, this, &MainWindow::openVideo);
    connect(ui->actionOpenCamera, &QAction::triggered, this, &MainWindow::openCamera);
    connect(ui->btnStartVideo, &QPushButton::clicked, this, &MainWindow::startVideoProcessing);
    connect(ui->btnStopVideo, &QPushButton::clicked, this, &MainWindow::stopVideoProcessing);
    connect(videoTimer, &QTimer::timeout, this, &MainWindow::processVideoFrame);
    
    connect(ui->sliderVideoThreshold, &QSlider::valueChanged, this, &MainWindow::videoSliderValueChanged);
    connect(ui->spinBoxFrameRate, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &MainWindow::videoFrameRateChanged);
    
    // 创建一个按钮组用于视频处理模式选择
    QButtonGroup *videoModeGroup = new QButtonGroup(this);
    videoModeGroup->addButton(ui->radioOriginal, 0);
    videoModeGroup->addButton(ui->radioGrayscale, 1);
    videoModeGroup->addButton(ui->radioBinarization, 2);
    videoModeGroup->addButton(ui->radioMeanBlur, 3);
    videoModeGroup->addButton(ui->radioEdgeDetection, 4);
    videoModeGroup->addButton(ui->radioMosaic, 5);
    videoModeGroup->addButton(ui->radioObjectDetection, 6);
    videoModeGroup->addButton(ui->radioFaceDetection, 7);  // 添加人脸检测模式
    
    // 修复：使用buttonClicked(QAbstractButton*)信号，根据按钮获取id
    connect(videoModeGroup, static_cast<void (QButtonGroup::*)(QAbstractButton*)>(&QButtonGroup::buttonClicked), 
            [this, videoModeGroup](QAbstractButton* button) {
                currentVideoProcessingMode = videoModeGroup->id(button);
                
                // 如果选择了AI对象检测模式，检查模型是否已初始化
                if (currentVideoProcessingMode == 6 && !yoloInitialized) {
                    QMessageBox::information(this, tr("提示"), tr("请先初始化YOLO模型，您可以点击\"初始化YOLO模型\"按钮或AI菜单中的相关选项"));
                    initYOLO();
                }
                
                // 如果选择了人脸检测模式，确保人脸检测器已初始化
                if (currentVideoProcessingMode == 7 && !faceDetectorInitialized) {
                    initFaceDetector();
                    if (!faceDetectorInitialized) {
                        QMessageBox::warning(this, tr("提示"), tr("无法初始化人脸检测模型，请检查OpenCV安装是否完整"));
                    }
                }
                
                // 实时应用处理效果到当前帧
                if (isVideoOpened && !currentFrame.empty()) {
                    processedFrame = processFrame(currentFrame, currentVideoProcessingMode);
                    displayImage(processedFrame);
                }
            });
    
    // AI相关连接
    connect(ui->sliderConfidence, &QSlider::valueChanged, this, &MainWindow::confidenceValueChanged);
    connect(ui->btnDownloadModels, &QPushButton::clicked, this, &MainWindow::initYOLO);  // 修改为直接初始化
    connect(ui->actionDownloadYOLO, &QAction::triggered, this, &MainWindow::initYOLO);  // 修改为直接初始化
    connect(ui->actionInitYOLO, &QAction::triggered, this, &MainWindow::initYOLO);
    
    // 修改按钮文本
    ui->btnDownloadModels->setText(tr("初始化YOLO模型"));
    ui->actionDownloadYOLO->setText(tr("初始化YOLO模型"));
    
    // 连接各个单选按钮的toggled信号，以便手动处理模式切换
    connect(ui->radioOriginal, &QRadioButton::toggled, [this](bool checked) {
        if (checked) {
            currentVideoProcessingMode = 0;
            // 实时应用处理效果到当前帧
            if (isVideoOpened && !currentFrame.empty()) {
                processedFrame = processFrame(currentFrame, currentVideoProcessingMode);
                displayImage(processedFrame);
            }
        }
    });
    connect(ui->radioGrayscale, &QRadioButton::toggled, [this](bool checked) {
        if (checked) {
            currentVideoProcessingMode = 1;
            // 实时应用处理效果到当前帧
            if (isVideoOpened && !currentFrame.empty()) {
                processedFrame = processFrame(currentFrame, currentVideoProcessingMode);
                displayImage(processedFrame);
            }
        }
    });
    connect(ui->radioBinarization, &QRadioButton::toggled, [this](bool checked) {
        if (checked) {
            currentVideoProcessingMode = 2;
            // 实时应用处理效果到当前帧
            if (isVideoOpened && !currentFrame.empty()) {
                processedFrame = processFrame(currentFrame, currentVideoProcessingMode);
                displayImage(processedFrame);
            }
        }
    });
    connect(ui->radioMeanBlur, &QRadioButton::toggled, [this](bool checked) {
        if (checked) {
            currentVideoProcessingMode = 3;
            // 实时应用处理效果到当前帧
            if (isVideoOpened && !currentFrame.empty()) {
                processedFrame = processFrame(currentFrame, currentVideoProcessingMode);
                displayImage(processedFrame);
            }
        }
    });
    connect(ui->radioEdgeDetection, &QRadioButton::toggled, [this](bool checked) {
        if (checked) {
            currentVideoProcessingMode = 4;
            // 实时应用处理效果到当前帧
            if (isVideoOpened && !currentFrame.empty()) {
                processedFrame = processFrame(currentFrame, currentVideoProcessingMode);
                displayImage(processedFrame);
            }
        }
    });
    connect(ui->radioMosaic, &QRadioButton::toggled, [this](bool checked) {
        if (checked) {
            currentVideoProcessingMode = 5;
            // 实时应用处理效果到当前帧
            if (isVideoOpened && !currentFrame.empty()) {
                processedFrame = processFrame(currentFrame, currentVideoProcessingMode);
                displayImage(processedFrame);
            }
        }
    });
    connect(ui->radioObjectDetection, &QRadioButton::toggled, [this](bool checked) {
        if (checked) {
            currentVideoProcessingMode = 6;
            
            // 如果选择了AI对象检测模式，检查模型是否已初始化
            if (!yoloInitialized) {
                QMessageBox::information(this, tr("提示"), tr("请先初始化YOLO模型，您可以点击\"初始化YOLO模型\"按钮或AI菜单中的相关选项"));
                initYOLO();
                return;
            }
            
            // 实时应用处理效果到当前帧
            if (isVideoOpened && !currentFrame.empty()) {
                processedFrame = processFrame(currentFrame, currentVideoProcessingMode);
                displayImage(processedFrame);
            }
        }
    });
    connect(ui->radioFaceDetection, &QRadioButton::toggled, [this](bool checked) {
        if (checked) {
            currentVideoProcessingMode = 7;
            
            // 如果选择了人脸检测模式，检查模型是否已初始化
            if (!faceDetectorInitialized) {
                initFaceDetector();
                if (!faceDetectorInitialized) {
                    QMessageBox::warning(this, tr("提示"), tr("无法初始化人脸检测模型，请检查OpenCV安装是否完整"));
                    return;
                }
            }
            
            // 实时应用处理效果到当前帧
            if (isVideoOpened && !currentFrame.empty()) {
                processedFrame = processFrame(currentFrame, currentVideoProcessingMode);
                displayImage(processedFrame);
            }
        }
    });
    
    // 马赛克区域设置
    mosaicROI = cv::Rect(100, 100, 200, 150);
    connect(ui->spinBoxMosaicX, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), [this](int value) {
        mosaicROI.x = value;
        // 实时更新马赛克效果
        if (isVideoOpened && !currentFrame.empty() && currentVideoProcessingMode == 5) {
            processedFrame = processFrame(currentFrame, currentVideoProcessingMode);
            displayImage(processedFrame);
        }
    });
    connect(ui->spinBoxMosaicY, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), [this](int value) {
        mosaicROI.y = value;
        // 实时更新马赛克效果
        if (isVideoOpened && !currentFrame.empty() && currentVideoProcessingMode == 5) {
            processedFrame = processFrame(currentFrame, currentVideoProcessingMode);
            displayImage(processedFrame);
        }
    });
    connect(ui->spinBoxMosaicWidth, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), [this](int value) {
        mosaicROI.width = value;
        // 实时更新马赛克效果
        if (isVideoOpened && !currentFrame.empty() && currentVideoProcessingMode == 5) {
            processedFrame = processFrame(currentFrame, currentVideoProcessingMode);
            displayImage(processedFrame);
        }
    });
    connect(ui->spinBoxMosaicHeight, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), [this](int value) {
        mosaicROI.height = value;
        // 实时更新马赛克效果
        if (isVideoOpened && !currentFrame.empty() && currentVideoProcessingMode == 5) {
            processedFrame = processFrame(currentFrame, currentVideoProcessingMode);
            displayImage(processedFrame);
        }
    });
    connect(ui->spinBoxMosaicSize, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), [this](int value) {
        mosaicSize = value;
        // 实时更新马赛克效果
        if (isVideoOpened && !currentFrame.empty() && currentVideoProcessingMode == 5) {
            processedFrame = processFrame(currentFrame, currentVideoProcessingMode);
            displayImage(processedFrame);
        }
    });
    
    // 初始化界面
    updateVideoUI(false);
    
    // 设置默认帧率较低，避免CPU负载过高
    ui->spinBoxFrameRate->setValue(10);
    
    // 初始化人脸检测器
    initFaceDetector();
}

MainWindow::~MainWindow()
{
    // 释放资源
    if (isVideoOpened) {
        videoCapture.release();
    }
    delete ui;
}

void MainWindow::openImages()
{
    QStringList fileNames = QFileDialog::getOpenFileNames(this, tr("打开图片"), "", 
                            tr("图片文件 (*.png *.jpg *.jpeg *.bmp *.tif);;所有文件 (*)"));
    
    if (fileNames.isEmpty()) {
        return;
    }
    
    // 清除之前的图像
    originalImages.clear();
    processedImages.clear();
    
    // 读取所有选择的图片
    for (const QString &fileName : fileNames) {
        cv::Mat img = cv::imread(fileName.toStdString());
        if (!img.empty()) {
            originalImages.push_back(img.clone());
            processedImages.push_back(img.clone());
        }
    }
    
    // 如果成功加载图片
    if (!originalImages.isEmpty()) {
        currentImageIndex = 0;
        enableControls(true);
        updateImageInfo();
        displayImage(originalImages[currentImageIndex]);
    }
}

void MainWindow::displayImage(const cv::Mat &img)
{
    if (img.empty()) {
        qDebug() << "空图像，无法显示";
        return;
    }

    QImage qImg = matToQImage(img);
    
    if (qImg.isNull()) {
        qDebug() << "图像转换失败，无法显示";
        return;
    }
    
    // 根据显示区域调整大小，保持宽高比
    QSize imgSize = qImg.size();
    QLabel *displayLabel;
    
    // 根据当前选项卡确定显示的标签
    if (ui->tabWidget->currentIndex() == 0) {
        displayLabel = ui->lblImage;
    } else {
        displayLabel = ui->lblVideo;
    }
    
    QSize labelSize = displayLabel->size();
    
    // 计算缩放比例，确保图像完全显示在区域内
    double scaleW = static_cast<double>(labelSize.width()) / imgSize.width();
    double scaleH = static_cast<double>(labelSize.height()) / imgSize.height();
    double scale = qMin(scaleW, scaleH);
    
    if (scale < 1.0) {
        // 缩小图像
        int newWidth = static_cast<int>(imgSize.width() * scale);
        int newHeight = static_cast<int>(imgSize.height() * scale);
        QPixmap scaledPixmap = QPixmap::fromImage(qImg).scaled(
            newWidth, newHeight, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        displayLabel->setPixmap(scaledPixmap);
    } else {
        // 保持原始大小
        displayLabel->setPixmap(QPixmap::fromImage(qImg));
    }
    
    // 强制更新界面显示
    displayLabel->repaint();
}

QImage MainWindow::matToQImage(const cv::Mat &mat)
{
    // 检查图像是否为空
    if (mat.empty()) {
        return QImage();
    }

    // 将OpenCV Mat转换为QImage
    if (mat.type() == CV_8UC3) {
        // BGR图像
        cv::Mat rgbMat;
        cv::cvtColor(mat, rgbMat, cv::COLOR_BGR2RGB);
        return QImage(rgbMat.data, rgbMat.cols, rgbMat.rows,
                    rgbMat.step, QImage::Format_RGB888).copy();
    } else if (mat.type() == CV_8UC1) {
        // 灰度图像
        return QImage(mat.data, mat.cols, mat.rows, 
                    mat.step, QImage::Format_Grayscale8).copy();
    }
    
    return QImage();
}

void MainWindow::showNextImage()
{
    if (originalImages.size() > 1 && currentImageIndex < originalImages.size() - 1) {
        currentImageIndex++;
        updateImageInfo();
        displayImage(originalImages[currentImageIndex]);
    }
}

void MainWindow::showPrevImage()
{
    if (originalImages.size() > 1 && currentImageIndex > 0) {
        currentImageIndex--;
        updateImageInfo();
        displayImage(originalImages[currentImageIndex]);
    }
}

void MainWindow::updateImageInfo()
{
    // 更新图像信息标签和导航按钮状态
    if (!originalImages.isEmpty()) {
        const cv::Mat &img = originalImages[currentImageIndex];
        QString info = QString("图片 %1/%2 - %3x%4").arg(currentImageIndex + 1)
                      .arg(originalImages.size())
                      .arg(img.cols)
                      .arg(img.rows);
        ui->lblImageInfo->setText(info);
        
        // 更新导航按钮状态
        ui->btnPrev->setEnabled(currentImageIndex > 0);
        ui->btnNext->setEnabled(currentImageIndex < originalImages.size() - 1);
    }
}

void MainWindow::enableControls(bool enable)
{
    ui->btnOriginal->setEnabled(enable);
    ui->btnGrayscale->setEnabled(enable);
    ui->btnBinarization->setEnabled(enable);
    ui->sliderThreshold->setEnabled(enable);
    ui->btnMeanBlur->setEnabled(enable);
    ui->btnGamma->setEnabled(enable);
    ui->sliderGamma->setEnabled(enable);
    ui->btnEdgeDetection->setEnabled(enable);
    ui->btnPrev->setEnabled(enable && originalImages.size() > 1 && currentImageIndex > 0);
    ui->btnNext->setEnabled(enable && originalImages.size() > 1 && currentImageIndex < originalImages.size() - 1);
}

void MainWindow::sliderValueChanged(int value)
{
    // 根据滑块更新标签显示
    QObject *sender = QObject::sender();
    
    if (sender == ui->sliderThreshold) {
        ui->lblThreshold->setText(QString::number(value));
        // 如果已经选择了二值化功能，则实时更新结果
        if (ui->btnBinarization->isChecked()) {
            applyBinarization();
        }
    } else if (sender == ui->sliderGamma) {
        double gamma = value / 10.0;
        ui->lblGamma->setText(QString::number(gamma, 'f', 1));
        // 如果已经选择了伽马变换功能，则实时更新结果
        if (ui->btnGamma->isChecked()) {
            applyGammaCorrection();
        }
    }
}

void MainWindow::applyGrayscale()
{
    if (originalImages.isEmpty() || currentImageIndex < 0 || currentImageIndex >= originalImages.size()) {
        return;
    }
    
    cv::Mat srcImg = originalImages[currentImageIndex].clone();
    cv::Mat grayImg;
    
    // 使用自定义的(R+G+B)/3方法进行灰度化
    grayImg = cv::Mat::zeros(srcImg.size(), CV_8UC1);
    
    for (int y = 0; y < srcImg.rows; y++) {
        for (int x = 0; x < srcImg.cols; x++) {
            cv::Vec3b pixel = srcImg.at<cv::Vec3b>(y, x);
            uchar gray = static_cast<uchar>((pixel[0] + pixel[1] + pixel[2]) / 3);
            grayImg.at<uchar>(y, x) = gray;
        }
    }
    
    processedImages[currentImageIndex] = grayImg;
    displayImage(grayImg);
}

void MainWindow::applyBinarization()
{
    if (originalImages.isEmpty() || currentImageIndex < 0 || currentImageIndex >= originalImages.size()) {
        return;
    }
    
    // 首先转为灰度图像
    cv::Mat srcImg = originalImages[currentImageIndex].clone();
    cv::Mat grayImg;
    
    if (srcImg.channels() == 3) {
        // 使用自定义的(R+G+B)/3方法进行灰度化
        grayImg = cv::Mat::zeros(srcImg.size(), CV_8UC1);
        
        for (int y = 0; y < srcImg.rows; y++) {
            for (int x = 0; x < srcImg.cols; x++) {
                cv::Vec3b pixel = srcImg.at<cv::Vec3b>(y, x);
                uchar gray = static_cast<uchar>((pixel[0] + pixel[1] + pixel[2]) / 3);
                grayImg.at<uchar>(y, x) = gray;
            }
        }
    } else {
        grayImg = srcImg.clone();
    }
    
    // 进行二值化
    int threshold = ui->sliderThreshold->value();
    cv::Mat binaryImg = cv::Mat::zeros(grayImg.size(), CV_8UC1);
    
    for (int y = 0; y < grayImg.rows; y++) {
        for (int x = 0; x < grayImg.cols; x++) {
            uchar pixel = grayImg.at<uchar>(y, x);
            binaryImg.at<uchar>(y, x) = (pixel >= threshold) ? 255 : 0;
        }
    }
    
    processedImages[currentImageIndex] = binaryImg;
    displayImage(binaryImg);
}

void MainWindow::applyMeanBlur()
{
    if (originalImages.isEmpty() || currentImageIndex < 0 || currentImageIndex >= originalImages.size()) {
        return;
    }
    
    cv::Mat srcImg = originalImages[currentImageIndex].clone();
    cv::Mat blurImg;
    
    // 使用OpenCV内置的均值滤波函数
    cv::blur(srcImg, blurImg, cv::Size(3, 3));
    
    processedImages[currentImageIndex] = blurImg;
    displayImage(blurImg);
}

void MainWindow::applyGammaCorrection()
{
    if (originalImages.isEmpty() || currentImageIndex < 0 || currentImageIndex >= originalImages.size()) {
        return;
    }
    
    cv::Mat srcImg = originalImages[currentImageIndex].clone();
    cv::Mat gammaImg;
    
    // 只对彩色图像进行伽马变换
    if (srcImg.channels() != 3) {
        return;
    }
    
    double gamma = ui->sliderGamma->value() / 10.0;
    double invGamma = 1.0 / gamma;
    
    // 创建伽马查找表
    uchar lut[256];
    for (int i = 0; i < 256; i++) {
        lut[i] = cv::saturate_cast<uchar>(std::pow((i / 255.0), invGamma) * 255.0);
    }
    
    // 进行伽马变换
    gammaImg = cv::Mat::zeros(srcImg.size(), CV_8UC3);
    
    for (int y = 0; y < srcImg.rows; y++) {
        for (int x = 0; x < srcImg.cols; x++) {
            cv::Vec3b pixel = srcImg.at<cv::Vec3b>(y, x);
            gammaImg.at<cv::Vec3b>(y, x) = cv::Vec3b(
                lut[pixel[0]],
                lut[pixel[1]],
                lut[pixel[2]]
            );
        }
    }
    
    processedImages[currentImageIndex] = gammaImg;
    displayImage(gammaImg);
}

void MainWindow::applyEdgeDetection()
{
    if (originalImages.isEmpty() || currentImageIndex < 0 || currentImageIndex >= originalImages.size()) {
        return;
    }
    
    // 首先转为灰度图像
    cv::Mat srcImg = originalImages[currentImageIndex].clone();
    cv::Mat grayImg;
    
    if (srcImg.channels() == 3) {
        // 使用自定义的(R+G+B)/3方法进行灰度化
        grayImg = cv::Mat::zeros(srcImg.size(), CV_8UC1);
        
        for (int y = 0; y < srcImg.rows; y++) {
            for (int x = 0; x < srcImg.cols; x++) {
                cv::Vec3b pixel = srcImg.at<cv::Vec3b>(y, x);
                uchar gray = static_cast<uchar>((pixel[0] + pixel[1] + pixel[2]) / 3);
                grayImg.at<uchar>(y, x) = gray;
            }
        }
    } else {
        grayImg = srcImg.clone();
    }
    
    // 使用Sobel算子进行边缘检测
    cv::Mat edgeImg = cv::Mat::zeros(grayImg.size(), CV_8UC1);
    
    for (int y = 1; y < grayImg.rows - 1; y++) {
        for (int x = 1; x < grayImg.cols - 1; x++) {
            // Sobel算子
            int gx = -grayImg.at<uchar>(y-1, x-1) - 2 * grayImg.at<uchar>(y, x-1) - grayImg.at<uchar>(y+1, x-1)
                   + grayImg.at<uchar>(y-1, x+1) + 2 * grayImg.at<uchar>(y, x+1) + grayImg.at<uchar>(y+1, x+1);
                   
            int gy = -grayImg.at<uchar>(y-1, x-1) - 2 * grayImg.at<uchar>(y-1, x) - grayImg.at<uchar>(y-1, x+1)
                   + grayImg.at<uchar>(y+1, x-1) + 2 * grayImg.at<uchar>(y+1, x) + grayImg.at<uchar>(y+1, x+1);
            
            // 计算梯度幅值
            int magnitude = static_cast<int>(std::sqrt(gx * gx + gy * gy));
            edgeImg.at<uchar>(y, x) = cv::saturate_cast<uchar>(magnitude);
        }
    }
    
    processedImages[currentImageIndex] = edgeImg;
    displayImage(edgeImg);
}

void MainWindow::openVideo()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("打开视频文件"), "", 
                      tr("视频文件 (*.mp4 *.avi *.wmv *.mov *.mkv);;所有文件 (*)"));
    
    if (fileName.isEmpty()) {
        return;
    }
    
    qDebug() << "正在打开视频:" << fileName;
    
    // 关闭之前的视频
    if (isVideoOpened) {
        stopVideoProcessing();
        videoCapture.release();
    }
    
    // 打开新视频
    videoCapture.open(fileName.toStdString());
    if (!videoCapture.isOpened()) {
        QMessageBox::warning(this, tr("错误"), tr("无法打开视频文件！"));
        return;
    }
    
    isVideoOpened = true;
    isUsingCamera = false;
    
    // 获取视频信息
    int frameCount = static_cast<int>(videoCapture.get(cv::CAP_PROP_FRAME_COUNT));
    double fps = videoCapture.get(cv::CAP_PROP_FPS);
    int width = static_cast<int>(videoCapture.get(cv::CAP_PROP_FRAME_WIDTH));
    int height = static_cast<int>(videoCapture.get(cv::CAP_PROP_FRAME_HEIGHT));
    
    qDebug() << "视频信息: " << width << "x" << height << ", FPS:" << fps << ", 帧数:" << frameCount;
    
    // 更新界面
    ui->lblVideoInfo->setText(QString("视频信息: %1×%2, %3 FPS, %4 帧")
                            .arg(width).arg(height).arg(fps, 0, 'f', 1).arg(frameCount));
    
    // 读取第一帧
    if (!videoCapture.read(currentFrame)) {
        QMessageBox::warning(this, tr("错误"), tr("无法读取视频第一帧！"));
        videoCapture.release();
        isVideoOpened = false;
        return;
    }
    
    if (currentFrame.empty()) {
        QMessageBox::warning(this, tr("错误"), tr("视频第一帧为空！"));
        videoCapture.release();
        isVideoOpened = false;
        return;
    }
    
    qDebug() << "第一帧尺寸:" << currentFrame.cols << "x" << currentFrame.rows;
    
    // 处理第一帧
    processedFrame = processFrame(currentFrame, currentVideoProcessingMode);
    
    // 确保切换到视频选项卡
    ui->tabWidget->setCurrentIndex(1);
    
    // 显示第一帧
    displayImage(processedFrame);
    
    // 更新UI
    updateVideoUI(true);
    
    // 自动开始播放视频
    startVideoProcessing();
}

void MainWindow::openCamera()
{
    // 关闭之前的视频或摄像头
    if (isVideoOpened) {
        stopVideoProcessing();
        videoCapture.release();
    }
    
    // 打开默认摄像头(0)
    videoCapture.open(0);
    if (!videoCapture.isOpened()) {
        QMessageBox::warning(this, tr("错误"), tr("无法打开摄像头！"));
        return;
    }
    
    isVideoOpened = true;
    isUsingCamera = true;
    
    // 设置摄像头属性
    videoCapture.set(cv::CAP_PROP_FRAME_WIDTH, 640);
    videoCapture.set(cv::CAP_PROP_FRAME_HEIGHT, 480);
    
    // 获取摄像头信息
    int width = static_cast<int>(videoCapture.get(cv::CAP_PROP_FRAME_WIDTH));
    int height = static_cast<int>(videoCapture.get(cv::CAP_PROP_FRAME_HEIGHT));
    
    // 更新界面
    ui->lblVideoInfo->setText(QString("摄像头: %1×%2").arg(width).arg(height));
    
    // 读取第一帧
    videoCapture >> currentFrame;
    
    if (!currentFrame.empty()) {
        cv::flip(currentFrame, currentFrame, 1); // 水平翻转摄像头画面，更自然
        processedFrame = processFrame(currentFrame, currentVideoProcessingMode);
        displayImage(processedFrame);
    }
    
    // 更新UI
    updateVideoUI(true);
    
    // 确保切换到视频选项卡
    ui->tabWidget->setCurrentIndex(1);
    
    // 自动开始播放视频
    startVideoProcessing();
}

void MainWindow::startVideoProcessing()
{
    if (!isVideoOpened) {
        return;
    }
    
    qDebug() << "开始视频处理";
    
    // 如果视频已经结束，重新开始
    if (isUsingCamera == false && videoCapture.get(cv::CAP_PROP_POS_FRAMES) >= videoCapture.get(cv::CAP_PROP_FRAME_COUNT)) {
        videoCapture.set(cv::CAP_PROP_POS_FRAMES, 0);
    }
    
    isVideoPlaying = true;
    
    // 设置定时器帧率
    videoFrameRate = ui->spinBoxFrameRate->value();
    int interval = 1000 / videoFrameRate;
    qDebug() << "设置定时器间隔:" << interval << "毫秒";
    
    // 确保先停止定时器再启动
    if (videoTimer->isActive()) {
        videoTimer->stop();
    }
    videoTimer->start(interval);
    
    // 更新UI状态
    ui->btnStartVideo->setEnabled(false);
    ui->btnStopVideo->setEnabled(true);
    ui->btnOpenVideo->setEnabled(false);
    ui->btnOpenCamera->setEnabled(false);
    
    // 立即处理当前帧
    processVideoFrame();
}

void MainWindow::stopVideoProcessing()
{
    isVideoPlaying = false;
    videoTimer->stop();
    
    // 更新UI状态
    ui->btnStartVideo->setEnabled(true);
    ui->btnStopVideo->setEnabled(false);
    ui->btnOpenVideo->setEnabled(true);
    ui->btnOpenCamera->setEnabled(true);
}

void MainWindow::processVideoFrame()
{
    if (!isVideoOpened || !isVideoPlaying || isProcessingFrame) {
        return;
    }
    
    // 标记正在处理
    isProcessingFrame = true;
    
    // 读取下一帧
    cv::Mat frame;
    bool readSuccess = videoCapture.read(frame);
    
    // 检查是否成功读取
    if (!readSuccess || frame.empty()) {
        // 如果是视频文件，到达末尾则重新开始播放
        if (!isUsingCamera) {
            qDebug() << "视频结束，重新开始播放";
            videoCapture.set(cv::CAP_PROP_POS_FRAMES, 0);
            readSuccess = videoCapture.read(frame);
            
            if (!readSuccess || frame.empty()) {
                qDebug() << "无法重新开始视频，停止播放";
                stopVideoProcessing();
                isProcessingFrame = false;
                return;
            }
        } else {
            // 如果是摄像头但读取失败，尝试继续
            isProcessingFrame = false;
            return;
        }
    }
    
    if (isUsingCamera) {
        cv::flip(frame, frame, 1); // 水平翻转摄像头画面
    }
    
    currentFrame = frame.clone();
    
    // 根据当前模式处理帧
    processedFrame = processFrame(currentFrame, currentVideoProcessingMode);
    
    // 显示处理后的帧
    displayImage(processedFrame);
    
    // 处理完毕
    isProcessingFrame = false;
}

cv::Mat MainWindow::processFrame(const cv::Mat &frame, int processingMode)
{
    cv::Mat result;
    
    switch (processingMode) {
        case 0: // 原始视频
            result = frame.clone();
            break;
            
        case 1: // 灰度化
        {
            // 使用自定义的(R+G+B)/3方法进行灰度化
            result = cv::Mat::zeros(frame.size(), CV_8UC1);
            
            for (int y = 0; y < frame.rows; y++) {
                for (int x = 0; x < frame.cols; x++) {
                    cv::Vec3b pixel = frame.at<cv::Vec3b>(y, x);
                    uchar gray = static_cast<uchar>((pixel[0] + pixel[1] + pixel[2]) / 3);
                    result.at<uchar>(y, x) = gray;
                }
            }
            break;
        }
            
        case 2: // 二值化
        {
            // 首先转为灰度图像
            cv::Mat grayImg;
            
            // 使用自定义的(R+G+B)/3方法进行灰度化
            grayImg = cv::Mat::zeros(frame.size(), CV_8UC1);
            
            for (int y = 0; y < frame.rows; y++) {
                for (int x = 0; x < frame.cols; x++) {
                    cv::Vec3b pixel = frame.at<cv::Vec3b>(y, x);
                    uchar gray = static_cast<uchar>((pixel[0] + pixel[1] + pixel[2]) / 3);
                    grayImg.at<uchar>(y, x) = gray;
                }
            }
            
            // 进行二值化
            int threshold = ui->sliderVideoThreshold->value();
            result = cv::Mat::zeros(grayImg.size(), CV_8UC1);
            
            for (int y = 0; y < grayImg.rows; y++) {
                for (int x = 0; x < grayImg.cols; x++) {
                    uchar pixel = grayImg.at<uchar>(y, x);
                    result.at<uchar>(y, x) = (pixel >= threshold) ? 255 : 0;
                }
            }
            break;
        }
            
        case 3: // 3×3均值滤波
        {
            // 使用OpenCV内置的均值滤波函数
            cv::blur(frame, result, cv::Size(3, 3));
            break;
        }
            
        case 4: // 边缘检测
        {
            // 首先转为灰度图像
            cv::Mat grayImg;
            
            // 使用自定义的(R+G+B)/3方法进行灰度化
            grayImg = cv::Mat::zeros(frame.size(), CV_8UC1);
            
            for (int y = 0; y < frame.rows; y++) {
                for (int x = 0; x < frame.cols; x++) {
                    cv::Vec3b pixel = frame.at<cv::Vec3b>(y, x);
                    uchar gray = static_cast<uchar>((pixel[0] + pixel[1] + pixel[2]) / 3);
                    grayImg.at<uchar>(y, x) = gray;
                }
            }
            
            // 使用Sobel算子进行边缘检测
            result = cv::Mat::zeros(grayImg.size(), CV_8UC1);
            
            for (int y = 1; y < grayImg.rows - 1; y++) {
                for (int x = 1; x < grayImg.cols - 1; x++) {
                    // Sobel算子
                    int gx = -grayImg.at<uchar>(y-1, x-1) - 2 * grayImg.at<uchar>(y, x-1) - grayImg.at<uchar>(y+1, x-1)
                           + grayImg.at<uchar>(y-1, x+1) + 2 * grayImg.at<uchar>(y, x+1) + grayImg.at<uchar>(y+1, x+1);
                           
                    int gy = -grayImg.at<uchar>(y-1, x-1) - 2 * grayImg.at<uchar>(y-1, x) - grayImg.at<uchar>(y-1, x+1)
                           + grayImg.at<uchar>(y+1, x-1) + 2 * grayImg.at<uchar>(y+1, x) + grayImg.at<uchar>(y+1, x+1);
                    
                    // 计算梯度幅值
                    int magnitude = static_cast<int>(std::sqrt(gx * gx + gy * gy));
                    result.at<uchar>(y, x) = cv::saturate_cast<uchar>(magnitude);
                }
            }
            break;
        }
            
        case 5: // 局部马赛克
        {
            result = frame.clone();
            // 检查ROI是否有效
            cv::Rect safeROI = mosaicROI & cv::Rect(0, 0, frame.cols, frame.rows);
            if (safeROI.width > 0 && safeROI.height > 0) {
                applyMosaic(result, safeROI);
            }
            break;
        }
        
        case 6: // AI对象检测
        {
            result = frame.clone();
            if (useFaceDetection && faceDetectorInitialized) {
                // 如果启用了人脸检测并且人脸检测器已初始化，使用人脸检测
                applyFaceDetection(result);
            } else if (yoloInitialized) {
                // 否则，如果YOLO模型已初始化，使用YOLO对象检测
                applyObjectDetection(result);
            } else if (faceDetectorInitialized) {
                // 如果YOLO未初始化但人脸检测器已初始化，使用人脸检测作为备选
                cv::putText(result, "Falling back to face detection", 
                           cv::Point(50, 30), cv::FONT_HERSHEY_SIMPLEX, 0.7,
                           cv::Scalar(0, 0, 255), 2);
                applyFaceDetection(result);
            } else {
                // 如果两者都未初始化，显示提示信息
                cv::putText(result, "No AI models initialized!", 
                           cv::Point(50, 50), cv::FONT_HERSHEY_SIMPLEX, 1.0,
                           cv::Scalar(0, 0, 255), 2);
            }
            break;
        }
            
        case 7: // 专用人脸检测
        {
            result = frame.clone();
            if (faceDetectorInitialized) {
                cv::putText(result, "OpenCV Built-in Face Detection", 
                           cv::Point(10, 30), cv::FONT_HERSHEY_SIMPLEX, 0.7,
                           cv::Scalar(0, 255, 0), 2);
                applyFaceDetection(result);
            } else {
                cv::putText(result, "Face detector not initialized!", 
                           cv::Point(50, 50), cv::FONT_HERSHEY_SIMPLEX, 1.0,
                           cv::Scalar(0, 0, 255), 2);
            }
            break;
        }
            
        default:
            result = frame.clone();
            break;
    }
    
    return result;
}

void MainWindow::applyMosaic(cv::Mat &frame, const cv::Rect &roi)
{
    int blockSize = mosaicSize;
    if (blockSize <= 0) blockSize = 1;
    
    // 在指定区域内应用马赛克效果
    for (int y = roi.y; y < roi.y + roi.height; y += blockSize) {
        for (int x = roi.x; x < roi.x + roi.width; x += blockSize) {
            // 计算块的实际大小（处理边界情况）
            int blockW = std::min(blockSize, roi.x + roi.width - x);
            int blockH = std::min(blockSize, roi.y + roi.height - y);
            
            if (blockW <= 0 || blockH <= 0) continue;
            
            // 计算块内平均颜色
            cv::Vec3i sum(0, 0, 0);
            int count = 0;
            
            for (int by = 0; by < blockH; by++) {
                for (int bx = 0; bx < blockW; bx++) {
                    if (y + by < frame.rows && x + bx < frame.cols) {
                        cv::Vec3b pixel = frame.at<cv::Vec3b>(y + by, x + bx);
                        sum[0] += pixel[0];
                        sum[1] += pixel[1];
                        sum[2] += pixel[2];
                        count++;
                    }
                }
            }
            
            if (count > 0) {
                // 计算平均颜色
                cv::Vec3b avgColor(
                    static_cast<uchar>(sum[0] / count),
                    static_cast<uchar>(sum[1] / count),
                    static_cast<uchar>(sum[2] / count)
                );
                
                // 将块内所有像素设为平均颜色
                for (int by = 0; by < blockH; by++) {
                    for (int bx = 0; bx < blockW; bx++) {
                        if (y + by < frame.rows && x + bx < frame.cols) {
                            frame.at<cv::Vec3b>(y + by, x + bx) = avgColor;
                        }
                    }
                }
            }
        }
    }
    
    // 绘制马赛克区域边框
    cv::rectangle(frame, roi, cv::Scalar(0, 255, 0), 2);
}

void MainWindow::videoSliderValueChanged(int value)
{
    ui->lblVideoThreshold->setText(QString::number(value));
    
    // 如果正在播放且处于二值化模式，实时更新处理
    if (isVideoPlaying && currentVideoProcessingMode == 2) {
        processedFrame = processFrame(currentFrame, currentVideoProcessingMode);
        displayImage(processedFrame);
    }
}

void MainWindow::videoFrameRateChanged(int value)
{
    videoFrameRate = value;
    
    // 如果正在播放，更新定时器周期
    if (isVideoPlaying) {
        videoTimer->start(1000 / videoFrameRate);
    }
}

void MainWindow::updateVideoUI(bool isVideoMode)
{
    ui->btnStartVideo->setEnabled(isVideoMode);
    ui->btnStopVideo->setEnabled(false);
    
    // 如果是视频模式，启用相关控件
    ui->sliderVideoThreshold->setEnabled(isVideoMode);
    ui->spinBoxFrameRate->setEnabled(isVideoMode);
    ui->spinBoxMosaicSize->setEnabled(isVideoMode);
    ui->spinBoxMosaicX->setEnabled(isVideoMode);
    ui->spinBoxMosaicY->setEnabled(isVideoMode);
    ui->spinBoxMosaicWidth->setEnabled(isVideoMode);
    ui->spinBoxMosaicHeight->setEnabled(isVideoMode);
}

void MainWindow::initYOLO()
{
    // 定义要搜索的文件
    QStringList modelFiles = {"yolov4-tiny.weights", "yolov4-tiny.cfg", "coco.names"};
    
    // 定义可能的路径
    QStringList searchPaths = {
        "",                                                  // 当前目录
        "./",                                                // 当前目录(另一种表示)
        "../",                                               // 项目父目录
        "../../",                                            // 项目父目录的父目录
        QCoreApplication::applicationDirPath() + "/",        // 可执行文件所在目录
        "D:/MyCppCode/QT/code/FinalTest/SelfPro/lr002/"      // 项目主目录(绝对路径)
    };
    
    // 存储找到的文件路径
    QMap<QString, QString> foundFiles;
    
    // 在各个可能的路径中查找文件
    for (const QString& filePath : modelFiles) {
        bool found = false;
        for (const QString& basePath : searchPaths) {
            QString fullPath = basePath + filePath;
            QFileInfo fileInfo(fullPath);
            if (fileInfo.exists()) {
                qDebug() << "找到文件:" << fullPath;
                foundFiles[filePath] = fullPath;
                found = true;
                break;
            }
        }
        
        if (!found) {
            QMessageBox::warning(this, tr("错误"), tr("无法找到文件: %1\n"
                                                   "请确保文件放在以下位置之一:\n"
                                                   "- 程序运行目录\n"
                                                   "- 项目目录\n"
                                                   "完整路径: %2").arg(filePath, QCoreApplication::applicationDirPath()));
            return;
        }
    }
    
    try {
        // 加载YOLO模型，使用找到的路径
        qDebug() << "正在加载YOLO模型...";
        qDebug() << "配置文件路径:" << foundFiles["yolov4-tiny.cfg"];
        qDebug() << "权重文件路径:" << foundFiles["yolov4-tiny.weights"];
        
        yoloNet = cv::dnn::readNetFromDarknet(foundFiles["yolov4-tiny.cfg"].toStdString(), 
                                             foundFiles["yolov4-tiny.weights"].toStdString());
        
        // 直接强制使用CPU，避免GPU兼容性问题
        yoloNet.setPreferableBackend(cv::dnn::DNN_BACKEND_OPENCV);
        yoloNet.setPreferableTarget(cv::dnn::DNN_TARGET_CPU);
        qDebug() << "使用CPU后端进行推理";
        
        // 加载类别名称
        QString classesFile = foundFiles["coco.names"];
        QFile file(classesFile);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&file);
            classNames.clear();
            while (!in.atEnd()) {
                QString line = in.readLine();
                classNames.push_back(line.toStdString());
            }
            file.close();
        } else {
            throw std::runtime_error("无法打开类别文件");
        }
        
        // 为每个类别生成随机颜色
        colors.clear();
        std::srand(static_cast<unsigned>(std::time(nullptr)));
        for (size_t i = 0; i < classNames.size(); i++) {
            int b = std::rand() % 256;
            int g = std::rand() % 256;
            int r = std::rand() % 256;
            colors.push_back(cv::Scalar(b, g, r));
        }
        
        // 设置初始化标志
        yoloInitialized = true;
        qDebug() << "YOLO模型初始化成功，加载了" << classNames.size() << "个类别";
        QMessageBox::information(this, tr("成功"), tr("YOLO模型初始化成功!"));
    } catch (const cv::Exception& e) {
        yoloInitialized = false;
        qDebug() << "YOLO初始化失败: " << e.what();
        QMessageBox::critical(this, tr("错误"), tr("YOLO模型初始化失败：%1").arg(e.what()));
    } catch (const std::exception& e) {
        yoloInitialized = false;
        qDebug() << "YOLO初始化失败: " << e.what();
        QMessageBox::critical(this, tr("错误"), tr("YOLO模型初始化失败：%1").arg(e.what()));
    }
}

void MainWindow::applyObjectDetection(cv::Mat &frame)
{
    if (!yoloInitialized || frame.empty()) {
        // 如果模型未初始化或帧为空，显示提示信息
        cv::putText(frame, "YOLO Model not initialized!", 
                   cv::Point(50, 50), cv::FONT_HERSHEY_SIMPLEX, 1.0,
                   cv::Scalar(0, 0, 255), 2);
        return;
    }
    
    try {
        // 获取图像尺寸
        int frameHeight = frame.rows;
        int frameWidth = frame.cols;
        
        // 使用更健壮的错误处理
        cv::Mat blob;
        try {
            // 将图像转换为blob
            cv::dnn::blobFromImage(frame, blob, 1/255.0, cv::Size(416, 416), cv::Scalar(0,0,0), true, false);
        } catch (const cv::Exception& e) {
            qDebug() << "Blob转换错误: " << e.what();
            cv::putText(frame, "Image preprocessing error!", 
                       cv::Point(50, 50), cv::FONT_HERSHEY_SIMPLEX, 1.0,
                       cv::Scalar(0, 0, 255), 2);
            return;
        }
        
        // 设置网络输入
        yoloNet.setInput(blob);
        
        // 获取输出层名称
        std::vector<std::string> outLayerNames;
        try {
            outLayerNames = yoloNet.getUnconnectedOutLayersNames();
        } catch (const cv::Exception& e) {
            qDebug() << "获取输出层错误: " << e.what();
            cv::putText(frame, "Model structure error!", 
                       cv::Point(50, 50), cv::FONT_HERSHEY_SIMPLEX, 1.0,
                       cv::Scalar(0, 0, 255), 2);
            return;
        }
        
        if (outLayerNames.empty()) {
            cv::putText(frame, "Invalid model output!", 
                       cv::Point(50, 50), cv::FONT_HERSHEY_SIMPLEX, 1.0,
                       cv::Scalar(0, 0, 255), 2);
            return;
        }
        
        // 前向传播
        std::vector<cv::Mat> netOutputs;
        try {
            yoloNet.forward(netOutputs, outLayerNames);
        } catch (const cv::Exception& e) {
            qDebug() << "模型推理错误: " << e.what();
            cv::putText(frame, "Inference error!", 
                       cv::Point(50, 50), cv::FONT_HERSHEY_SIMPLEX, 1.0,
                       cv::Scalar(0, 0, 255), 2);
            return;
        }
        
        if (netOutputs.empty()) {
            cv::putText(frame, "No detection results!", 
                       cv::Point(50, 50), cv::FONT_HERSHEY_SIMPLEX, 1.0,
                       cv::Scalar(0, 0, 255), 2);
            return;
        }
        
        // 处理检测结果
        std::vector<int> classIds;
        std::vector<float> confidences;
        std::vector<cv::Rect> boxes;
        
        // 遍历所有输出层
        for (const auto &output : netOutputs) {
            if (output.empty() || output.rows <= 0) continue;
            
            // 遍历输出中的每个检测
            for (int i = 0; i < output.rows; ++i) {
                const int probabilityIndex = 5;  // 概率值开始的索引
                if (output.cols <= probabilityIndex) continue;
                
                // 获取每个检测框的所有类别概率
                cv::Mat scores = output.row(i).colRange(probabilityIndex, output.cols);
                cv::Point classIdPoint;
                double confidence;
                
                // 获取最大概率及其索引
                cv::minMaxLoc(scores, 0, &confidence, 0, &classIdPoint);
                int classId = classIdPoint.x;
                
                // 检查置信度是否超过阈值
                if (confidence > confidenceThreshold) {
                    try {
                        // 中心坐标，宽度和高度
                        float centerX = output.at<float>(i, 0) * frameWidth;
                        float centerY = output.at<float>(i, 1) * frameHeight;
                        float width = output.at<float>(i, 2) * frameWidth;
                        float height = output.at<float>(i, 3) * frameHeight;
                        
                        // 左上角坐标
                        float left = centerX - width / 2;
                        float top = centerY - height / 2;
                        
                        // 保存结果
                        classIds.push_back(classId);
                        confidences.push_back(static_cast<float>(confidence));
                        boxes.push_back(cv::Rect(static_cast<int>(left), static_cast<int>(top),
                                              static_cast<int>(width), static_cast<int>(height)));
                    } catch (const cv::Exception& e) {
                        qDebug() << "边界框计算错误: " << e.what();
                        // 继续处理下一个检测，不中断
                        continue;
                    }
                }
            }
        }
        
        // 如果没有检测到任何有效目标
        if (boxes.empty()) {
            cv::putText(frame, "No objects detected", cv::Point(50, 50),
                      cv::FONT_HERSHEY_SIMPLEX, 1.0, cv::Scalar(0, 255, 0), 2);
            return;
        }
        
        // 执行非最大抑制，过滤重叠框
        std::vector<int> indices;
        try {
            cv::dnn::NMSBoxes(boxes, confidences, confidenceThreshold, 0.4f, indices);
        } catch (const cv::Exception& e) {
            qDebug() << "NMS错误: " << e.what();
            // 如果NMS失败，使用所有边界框
            indices.resize(boxes.size());
            for (size_t i = 0; i < boxes.size(); ++i) indices[i] = static_cast<int>(i);
        }
        
        // 显示结果
        bool showLabels = ui->chkShowLabels->isChecked();
        for (size_t i = 0; i < indices.size(); ++i) {
            int idx = indices[i];
            if (idx >= boxes.size()) continue;  // 安全检查
            
            cv::Rect box = boxes[idx];
            
            // 确保框在图像范围内
            box.x = std::max(0, box.x);
            box.y = std::max(0, box.y);
            box.width = std::min(frameWidth - box.x, box.width);
            box.height = std::min(frameHeight - box.y, box.height);
            
            // 绘制框和标签
            int classId = classIds[idx];
            if (classId < classNames.size()) {
                cv::rectangle(frame, box, colors[classId], 2);
                
                if (showLabels) {
                    try {
                        std::string label = classNames[classId] + ": " + 
                                           cv::format("%.2f", confidences[idx]);
                        
                        int baseLine;
                        cv::Size labelSize = cv::getTextSize(label, cv::FONT_HERSHEY_SIMPLEX, 0.5, 1, &baseLine);
                        
                        // 标签背景
                        cv::rectangle(frame, 
                                    cv::Point(box.x, box.y - labelSize.height - baseLine - 10),
                                    cv::Point(box.x + labelSize.width, box.y),
                                    colors[classId], 
                                    cv::FILLED);
                        
                        // 白色文本
                        cv::putText(frame, 
                                  label, 
                                  cv::Point(box.x, box.y - baseLine - 5),
                                  cv::FONT_HERSHEY_SIMPLEX, 
                                  0.5, 
                                  cv::Scalar(255, 255, 255), 
                                  1);
                    } catch (const cv::Exception& e) {
                        qDebug() << "标签绘制错误: " << e.what();
                        // 继续处理下一个检测，不中断
                        continue;
                    }
                }
            }
        }
        
        // 在右下角显示识别到的物体数量
        std::string statusText = "Objects: " + std::to_string(indices.size());
        cv::putText(frame, statusText, cv::Point(frame.cols - 150, frame.rows - 20),
                  cv::FONT_HERSHEY_SIMPLEX, 0.6, cv::Scalar(0, 255, 0), 2);
    } catch (const cv::Exception& e) {
        qDebug() << "对象检测错误: " << e.what();
        cv::putText(frame, "Detection Error!", cv::Point(50, 50),
                  cv::FONT_HERSHEY_SIMPLEX, 1.0, cv::Scalar(0, 0, 255), 2);
    } catch (const std::exception& e) {
        qDebug() << "标准异常: " << e.what();
        cv::putText(frame, "Error occurred!", cv::Point(50, 50),
                  cv::FONT_HERSHEY_SIMPLEX, 1.0, cv::Scalar(0, 0, 255), 2);
    } catch (...) {
        qDebug() << "未知错误!";
        cv::putText(frame, "Unknown error!", cv::Point(50, 50),
                  cv::FONT_HERSHEY_SIMPLEX, 1.0, cv::Scalar(0, 0, 255), 2);
    }
}

void MainWindow::confidenceValueChanged(int value)
{
    confidenceThreshold = static_cast<float>(value) / 100.0f;
    ui->lblConfidence->setText(QString::number(confidenceThreshold, 'f', 2));
    
    // 如果正在播放且处于对象检测模式，实时更新处理
    if (isVideoPlaying && currentVideoProcessingMode == 6 && !currentFrame.empty()) {
        processedFrame = processFrame(currentFrame, currentVideoProcessingMode);
        displayImage(processedFrame);
    }
}

void MainWindow::downloadYOLOModels()
{
    // 直接调用初始化函数，不再需要下载
    initYOLO();
}

// 备用AI功能：人脸检测实现
void MainWindow::initFaceDetector()
{
    // 检查OpenCV内置的人脸检测模型（Haar级联分类器）
    QString faceModelPath = "haarcascade_frontalface_default.xml";
    
    // 尝试在各种可能的路径查找模型文件
    QStringList searchPaths;
    searchPaths << "" // 当前目录
               << "./" // 当前目录(另一种表示)
               << "../" // 项目父目录
               << "../../" // 项目父目录的父目录
               << QCoreApplication::applicationDirPath() + "/" // 可执行文件所在目录
               << "D:/MyCppCode/QT/code/FinalTest/SelfPro/lr002/" // 项目主目录(绝对路径)
               << "data/" // 相对于程序目录的data文件夹
               << "D:/MyCppCode/openCV/opencv/build/etc/haarcascades/" // OpenCV安装目录
               << "D:/opencv/opencv-4.9.0/build/etc/haarcascades/" // 另一个可能的OpenCV路径
               << "C:/opencv/build/etc/haarcascades/"
               << "C:/Program Files/opencv/etc/haarcascades/"
               << "../opencv/build/etc/haarcascades/"
               << "../../opencv/build/etc/haarcascades/"
               << "D:/opencv/build/etc/haarcascades/"
               << "C:/Program Files (x86)/opencv/etc/haarcascades/";
    
    bool loaded = false;
    for (const QString &basePath : searchPaths) {
        QString fullPath = basePath + faceModelPath;
        QFileInfo fileInfo(fullPath);
        if (fileInfo.exists()) {
            try {
                // 加载人脸检测模型
                qDebug() << "尝试加载人脸检测模型: " << fullPath;
                loaded = faceDetector.load(fullPath.toStdString());
                if (loaded) {
                    faceDetectorInitialized = true;
                    qDebug() << "人脸检测模型加载成功";
                    break;
                }
            } catch (const cv::Exception& e) {
                qDebug() << "加载人脸检测模型失败: " << e.what();
            }
        } else {
            qDebug() << "人脸检测模型文件不存在: " << fullPath;
        }
    }
    
    if (!faceDetectorInitialized) {
        qDebug() << "无法找到或加载人脸检测模型";
        
        // 给用户显示有用的提示
        QMessageBox::warning(this, tr("人脸检测模型加载失败"), 
                          tr("无法找到人脸检测模型文件 'haarcascade_frontalface_default.xml'。\n\n"
                             "请确保OpenCV安装正确，或将人脸检测模型文件放在程序目录下。\n"
                             "程序运行目录: %1").arg(QCoreApplication::applicationDirPath()));
    } else {
        QMessageBox::information(this, tr("人脸检测"), tr("OpenCV内置人脸检测模型加载成功！"));
    }
}

void MainWindow::applyFaceDetection(cv::Mat &frame)
{
    if (!faceDetectorInitialized || frame.empty()) {
        cv::putText(frame, "Face detector not initialized!", 
                   cv::Point(50, 50), cv::FONT_HERSHEY_SIMPLEX, 1.0,
                   cv::Scalar(0, 0, 255), 2);
        return;
    }
    
    try {
        // 转换为灰度图进行处理
        cv::Mat gray;
        cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);
        
        // 对比度增强，提高检测效果
        cv::equalizeHist(gray, gray);
        
        // 检测人脸
        std::vector<cv::Rect> faces;
        faceDetector.detectMultiScale(gray, faces, 
                                    1.1, // 缩放因子
                                    5,   // 最小邻居
                                    0,   // 标志
                                    cv::Size(30, 30)); // 最小人脸尺寸
        
        // 在原图上绘制人脸框
        for (const cv::Rect &face : faces) {
            // 绿色矩形框
            cv::rectangle(frame, face, cv::Scalar(0, 255, 0), 2);
            
            // 可选：添加标签
            std::string label = "Face";
            cv::putText(frame, label, 
                      cv::Point(face.x, face.y - 10),
                      cv::FONT_HERSHEY_SIMPLEX, 
                      0.7, 
                      cv::Scalar(0, 255, 0),
                      2);
        }
        
        // 显示检测到的人脸数量
        std::string statusText = "Faces: " + std::to_string(faces.size());
        cv::putText(frame, statusText, 
                  cv::Point(frame.cols - 150, frame.rows - 20),
                  cv::FONT_HERSHEY_SIMPLEX, 
                  0.7, 
                  cv::Scalar(0, 255, 0),
                  2);
    } catch (const cv::Exception& e) {
        qDebug() << "人脸检测错误: " << e.what();
        cv::putText(frame, "Face Detection Error!", 
                  cv::Point(50, 50), cv::FONT_HERSHEY_SIMPLEX, 1.0,
                  cv::Scalar(0, 0, 255), 2);
    } catch (const std::exception& e) {
        qDebug() << "标准异常: " << e.what();
    } catch (...) {
        qDebug() << "未知错误";
    }
}

void MainWindow::toggleFaceDetection(bool enabled)
{
    useFaceDetection = enabled;
}
