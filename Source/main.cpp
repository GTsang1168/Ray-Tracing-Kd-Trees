#include "mainwindow.h"
#include <QApplication>
#include <iostream>
#include <string>
#include <vector>

#include "initialize.h"
#include "Camera.h"
#include "ImageData.h"
#include "RayInitialization.h"
#include "kdTree.h"

using namespace std;

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
