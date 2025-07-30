#include "mainwindow.h"

#include <QApplication>
#include <QIcon>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName("图像处理软件");
    a.setOrganizationName("Qt图像处理");
    
    MainWindow w;
    w.setWindowTitle("图像处理软件 v1.0");
    w.show();
    
    return a.exec();
}
