/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.5.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../mainwindow.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.5.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSMainWindowENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSMainWindowENDCLASS = QtMocHelpers::stringData(
    "MainWindow",
    "openImages",
    "",
    "showNextImage",
    "showPrevImage",
    "applyGrayscale",
    "applyBinarization",
    "applyMeanBlur",
    "applyGammaCorrection",
    "applyEdgeDetection",
    "sliderValueChanged",
    "value",
    "openVideo",
    "openCamera",
    "startVideoProcessing",
    "stopVideoProcessing",
    "processVideoFrame",
    "applyMosaic",
    "cv::Mat&",
    "frame",
    "cv::Rect",
    "roi",
    "videoSliderValueChanged",
    "videoFrameRateChanged",
    "initYOLO",
    "applyObjectDetection",
    "confidenceValueChanged",
    "downloadYOLOModels",
    "initFaceDetector",
    "applyFaceDetection",
    "toggleFaceDetection",
    "enabled"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSMainWindowENDCLASS_t {
    uint offsetsAndSizes[64];
    char stringdata0[11];
    char stringdata1[11];
    char stringdata2[1];
    char stringdata3[14];
    char stringdata4[14];
    char stringdata5[15];
    char stringdata6[18];
    char stringdata7[14];
    char stringdata8[21];
    char stringdata9[19];
    char stringdata10[19];
    char stringdata11[6];
    char stringdata12[10];
    char stringdata13[11];
    char stringdata14[21];
    char stringdata15[20];
    char stringdata16[18];
    char stringdata17[12];
    char stringdata18[9];
    char stringdata19[6];
    char stringdata20[9];
    char stringdata21[4];
    char stringdata22[24];
    char stringdata23[22];
    char stringdata24[9];
    char stringdata25[21];
    char stringdata26[23];
    char stringdata27[19];
    char stringdata28[17];
    char stringdata29[19];
    char stringdata30[20];
    char stringdata31[8];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSMainWindowENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSMainWindowENDCLASS_t qt_meta_stringdata_CLASSMainWindowENDCLASS = {
    {
        QT_MOC_LITERAL(0, 10),  // "MainWindow"
        QT_MOC_LITERAL(11, 10),  // "openImages"
        QT_MOC_LITERAL(22, 0),  // ""
        QT_MOC_LITERAL(23, 13),  // "showNextImage"
        QT_MOC_LITERAL(37, 13),  // "showPrevImage"
        QT_MOC_LITERAL(51, 14),  // "applyGrayscale"
        QT_MOC_LITERAL(66, 17),  // "applyBinarization"
        QT_MOC_LITERAL(84, 13),  // "applyMeanBlur"
        QT_MOC_LITERAL(98, 20),  // "applyGammaCorrection"
        QT_MOC_LITERAL(119, 18),  // "applyEdgeDetection"
        QT_MOC_LITERAL(138, 18),  // "sliderValueChanged"
        QT_MOC_LITERAL(157, 5),  // "value"
        QT_MOC_LITERAL(163, 9),  // "openVideo"
        QT_MOC_LITERAL(173, 10),  // "openCamera"
        QT_MOC_LITERAL(184, 20),  // "startVideoProcessing"
        QT_MOC_LITERAL(205, 19),  // "stopVideoProcessing"
        QT_MOC_LITERAL(225, 17),  // "processVideoFrame"
        QT_MOC_LITERAL(243, 11),  // "applyMosaic"
        QT_MOC_LITERAL(255, 8),  // "cv::Mat&"
        QT_MOC_LITERAL(264, 5),  // "frame"
        QT_MOC_LITERAL(270, 8),  // "cv::Rect"
        QT_MOC_LITERAL(279, 3),  // "roi"
        QT_MOC_LITERAL(283, 23),  // "videoSliderValueChanged"
        QT_MOC_LITERAL(307, 21),  // "videoFrameRateChanged"
        QT_MOC_LITERAL(329, 8),  // "initYOLO"
        QT_MOC_LITERAL(338, 20),  // "applyObjectDetection"
        QT_MOC_LITERAL(359, 22),  // "confidenceValueChanged"
        QT_MOC_LITERAL(382, 18),  // "downloadYOLOModels"
        QT_MOC_LITERAL(401, 16),  // "initFaceDetector"
        QT_MOC_LITERAL(418, 18),  // "applyFaceDetection"
        QT_MOC_LITERAL(437, 19),  // "toggleFaceDetection"
        QT_MOC_LITERAL(457, 7)   // "enabled"
    },
    "MainWindow",
    "openImages",
    "",
    "showNextImage",
    "showPrevImage",
    "applyGrayscale",
    "applyBinarization",
    "applyMeanBlur",
    "applyGammaCorrection",
    "applyEdgeDetection",
    "sliderValueChanged",
    "value",
    "openVideo",
    "openCamera",
    "startVideoProcessing",
    "stopVideoProcessing",
    "processVideoFrame",
    "applyMosaic",
    "cv::Mat&",
    "frame",
    "cv::Rect",
    "roi",
    "videoSliderValueChanged",
    "videoFrameRateChanged",
    "initYOLO",
    "applyObjectDetection",
    "confidenceValueChanged",
    "downloadYOLOModels",
    "initFaceDetector",
    "applyFaceDetection",
    "toggleFaceDetection",
    "enabled"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSMainWindowENDCLASS[] = {

 // content:
      11,       // revision
       0,       // classname
       0,    0, // classinfo
      24,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,  158,    2, 0x08,    1 /* Private */,
       3,    0,  159,    2, 0x08,    2 /* Private */,
       4,    0,  160,    2, 0x08,    3 /* Private */,
       5,    0,  161,    2, 0x08,    4 /* Private */,
       6,    0,  162,    2, 0x08,    5 /* Private */,
       7,    0,  163,    2, 0x08,    6 /* Private */,
       8,    0,  164,    2, 0x08,    7 /* Private */,
       9,    0,  165,    2, 0x08,    8 /* Private */,
      10,    1,  166,    2, 0x08,    9 /* Private */,
      12,    0,  169,    2, 0x08,   11 /* Private */,
      13,    0,  170,    2, 0x08,   12 /* Private */,
      14,    0,  171,    2, 0x08,   13 /* Private */,
      15,    0,  172,    2, 0x08,   14 /* Private */,
      16,    0,  173,    2, 0x08,   15 /* Private */,
      17,    2,  174,    2, 0x08,   16 /* Private */,
      22,    1,  179,    2, 0x08,   19 /* Private */,
      23,    1,  182,    2, 0x08,   21 /* Private */,
      24,    0,  185,    2, 0x08,   23 /* Private */,
      25,    1,  186,    2, 0x08,   24 /* Private */,
      26,    1,  189,    2, 0x08,   26 /* Private */,
      27,    0,  192,    2, 0x08,   28 /* Private */,
      28,    0,  193,    2, 0x08,   29 /* Private */,
      29,    1,  194,    2, 0x08,   30 /* Private */,
      30,    1,  197,    2, 0x08,   32 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   11,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 18, 0x80000000 | 20,   19,   21,
    QMetaType::Void, QMetaType::Int,   11,
    QMetaType::Void, QMetaType::Int,   11,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 18,   19,
    QMetaType::Void, QMetaType::Int,   11,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 18,   19,
    QMetaType::Void, QMetaType::Bool,   31,

       0        // eod
};

Q_CONSTINIT const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_CLASSMainWindowENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSMainWindowENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSMainWindowENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<MainWindow, std::true_type>,
        // method 'openImages'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'showNextImage'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'showPrevImage'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'applyGrayscale'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'applyBinarization'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'applyMeanBlur'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'applyGammaCorrection'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'applyEdgeDetection'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'sliderValueChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'openVideo'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'openCamera'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'startVideoProcessing'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'stopVideoProcessing'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'processVideoFrame'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'applyMosaic'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<cv::Mat &, std::false_type>,
        QtPrivate::TypeAndForceComplete<const cv::Rect &, std::false_type>,
        // method 'videoSliderValueChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'videoFrameRateChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'initYOLO'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'applyObjectDetection'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<cv::Mat &, std::false_type>,
        // method 'confidenceValueChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'downloadYOLOModels'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'initFaceDetector'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'applyFaceDetection'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<cv::Mat &, std::false_type>,
        // method 'toggleFaceDetection'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>
    >,
    nullptr
} };

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->openImages(); break;
        case 1: _t->showNextImage(); break;
        case 2: _t->showPrevImage(); break;
        case 3: _t->applyGrayscale(); break;
        case 4: _t->applyBinarization(); break;
        case 5: _t->applyMeanBlur(); break;
        case 6: _t->applyGammaCorrection(); break;
        case 7: _t->applyEdgeDetection(); break;
        case 8: _t->sliderValueChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 9: _t->openVideo(); break;
        case 10: _t->openCamera(); break;
        case 11: _t->startVideoProcessing(); break;
        case 12: _t->stopVideoProcessing(); break;
        case 13: _t->processVideoFrame(); break;
        case 14: _t->applyMosaic((*reinterpret_cast< std::add_pointer_t<cv::Mat&>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<cv::Rect>>(_a[2]))); break;
        case 15: _t->videoSliderValueChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 16: _t->videoFrameRateChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 17: _t->initYOLO(); break;
        case 18: _t->applyObjectDetection((*reinterpret_cast< std::add_pointer_t<cv::Mat&>>(_a[1]))); break;
        case 19: _t->confidenceValueChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 20: _t->downloadYOLOModels(); break;
        case 21: _t->initFaceDetector(); break;
        case 22: _t->applyFaceDetection((*reinterpret_cast< std::add_pointer_t<cv::Mat&>>(_a[1]))); break;
        case 23: _t->toggleFaceDetection((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSMainWindowENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 24)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 24;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 24)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 24;
    }
    return _id;
}
QT_WARNING_POP
