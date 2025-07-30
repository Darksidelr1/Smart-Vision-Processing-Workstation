#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <opencv2/opencv.hpp>
#include <opencv2/dnn.hpp>
#include <QFileDialog>
#include <QImage>
#include <QPixmap>
#include <QSlider>
#include <QPushButton>
#include <QLabel>
#include <QVector>
#include <QTimer>
#include <QCheckBox>
#include <QGroupBox>
#include <QRadioButton>
#include <QSpinBox>
#include <QMap>
#include <QDir>
#include <QFile>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // 图像处理相关
    void openImages();
    void showNextImage();
    void showPrevImage();
    void applyGrayscale();
    void applyBinarization();
    void applyMeanBlur();
    void applyGammaCorrection();
    void applyEdgeDetection();
    void sliderValueChanged(int value);
    
    // 视频处理相关
    void openVideo();
    void openCamera();
    void startVideoProcessing();
    void stopVideoProcessing();
    void processVideoFrame();
    void applyMosaic(cv::Mat &frame, const cv::Rect &roi);
    void videoSliderValueChanged(int value);
    void videoFrameRateChanged(int value);
    
    // AI智能视觉相关
    void initYOLO();
    void applyObjectDetection(cv::Mat &frame);
    void confidenceValueChanged(int value);
    void downloadYOLOModels();
    
    // 备选AI功能：人脸检测
    void initFaceDetector();
    void applyFaceDetection(cv::Mat &frame);
    void toggleFaceDetection(bool enabled);

private:
    Ui::MainWindow *ui;
    QVector<cv::Mat> originalImages;
    QVector<cv::Mat> processedImages;
    int currentImageIndex;
    
    // 视频相关
    cv::VideoCapture videoCapture;
    QTimer *videoTimer;
    cv::Mat currentFrame;
    cv::Mat processedFrame;
    bool isVideoPlaying;
    bool isVideoOpened;
    bool isUsingCamera;
    bool isProcessingFrame;   // 标记是否正在处理帧，避免重入
    int videoFrameRate;
    int currentVideoProcessingMode;
    cv::Rect mosaicROI;  // 马赛克区域
    int mosaicSize;      // 马赛克块大小
    
    // YOLO对象检测相关
    cv::dnn::Net yoloNet;
    bool yoloInitialized;
    float confidenceThreshold;
    std::vector<std::string> classNames;
    std::vector<cv::Scalar> colors;
    
    // 人脸检测相关
    cv::CascadeClassifier faceDetector;
    bool faceDetectorInitialized;
    bool useFaceDetection;
    
    void displayImage(const cv::Mat &img);
    QImage matToQImage(const cv::Mat &mat);
    void updateImageInfo();
    void enableControls(bool enable);
    void setupVideoUI();
    void updateVideoUI(bool isVideoMode);
    cv::Mat processFrame(const cv::Mat &frame, int processingMode);
};
#endif // MAINWINDOW_H
