#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <string>
#include <ctime>
#include <sstream>

#include "Camera.h"
#include "DataStructure.h"
#include "ImageData.h"
#include "DialogLights.h"
#include "DialogOptions.h"
#include "RayInitialization.h"
#include "initialize.h"
#include "kdTree.h"
#include "RayTracing.h"

#define PI 3.14159265
#define XPIX 768
#define YPIX 768

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
	Camera getCamera();

public slots:
	void slotUpdateUI(int percentage, double duration);

signals:
	void signalStartRender();

private slots:
    void on_buttonRender_clicked();

    void on_buttonLoad_clicked();

    void on_buttonKd_clicked();

    void on_buttonSave_clicked();

    void on_buttonCenter_clicked();

    void on_buttonLights_clicked();

	void on_buttonOptions_clicked();

private:
	Camera generateCamera();
	void updateImage();

    Ui::MainWindow *ui;
    DialogLights dialogLights;
	DialogOptions dialogOptions;
	RayTracing * rayTracing = new RayTracing();
	QImage image;
};

#endif // MAINWINDOW_H
