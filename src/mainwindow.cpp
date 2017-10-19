#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->statusBar->setSizeGripEnabled(false);
	ui->progressBar->setMaximum(XPIX * YPIX - 1);
	image = QImage(XPIX, YPIX, QImage::Format_RGB32);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_buttonRender_clicked()
{
	ui->statusBar->showMessage(QString::fromStdString("Rendering image"));

	dialogOptions.getRenderOptions()->setViewKdTree(ui->checkBoxViewKd->isChecked());
	rayTracing->setRenderOptions(dialogOptions.getRenderOptions());

	rayTracing->setUseKdTree(ui->checkBoxKd->isChecked());

	Camera camera = generateCamera();
	dialogLights.setCamera(camera);
	rayTracing->setCamera(camera);
	rayTracing->setLights(dialogLights.getLights());

	emit signalStartRender();
	ui->buttonSave->setEnabled(true);
}

void MainWindow::on_buttonLoad_clicked()
{
    QFileDialog fileDialog(this, tr("Open File"), "", tr("OBJ Files (*.OBJ)"));
	if(fileDialog.exec()) {
		delete rayTracing;
		rayTracing = new RayTracing(fileDialog.selectedFiles().first().toStdString());
		QObject::connect(rayTracing, SIGNAL(signalRenderProgress(int,double)), this, SLOT(slotUpdateUI(int,double)));
		QObject::connect(this, SIGNAL(signalStartRender()), rayTracing, SLOT(slotStartRender()));

        ui->buttonSave->setEnabled(false);
        ui->buttonRender->setEnabled(true);
        ui->buttonKd->setEnabled(true);
        ui->checkBoxKd->setEnabled(false);
        ui->checkBoxKd->setChecked(false);
		ui->checkBoxViewKd->setEnabled(false);
		ui->checkBoxViewKd->setChecked(false);
        ui->buttonLights->setEnabled(true);
		ui->dialVertical->setValue(0);
		ui->dialHorizontal->setValue(180);
        on_buttonCenter_clicked();

		std::ostringstream message;
		message << "File loaded. Number of Triangles = " << rayTracing->getTriangleCount() << ".";
		ui->statusBar->showMessage(QString::fromStdString(message.str()), 5000);
    }
}

void MainWindow::on_buttonKd_clicked()
{
	rayTracing->generateKdTree();
    ui->checkBoxKd->setEnabled(true);
	ui->checkBoxViewKd->setEnabled(true);
}

void MainWindow::on_buttonSave_clicked()
{
	QFileDialog fileDialog(this, tr("Save File"), "", "BMP (*.bmp)");
    fileDialog.setAcceptMode(QFileDialog::AcceptSave);
    if(fileDialog.exec()) {
		if(image.save(fileDialog.selectedFiles().first())) {
            ui->statusBar->showMessage(QString::fromStdString("Image saved."), 5000);
        } else {
            ui->statusBar->showMessage(QString::fromStdString("ERROR: Image could not be saved."), 5000);
        }
    }
}

void MainWindow::on_buttonCenter_clicked()
{
	double x = rayTracing->getMinPoint(DataStructure::X) + (rayTracing->getMaxPoint(DataStructure::X) - rayTracing->getMinPoint(DataStructure::X)) / 2;
	double y = rayTracing->getMinPoint(DataStructure::Y) + (rayTracing->getMaxPoint(DataStructure::Y) - rayTracing->getMinPoint(DataStructure::Y)) / 2;
	double z = rayTracing->getMinPoint(DataStructure::Z) + (rayTracing->getMaxPoint(DataStructure::Z) - rayTracing->getMinPoint(DataStructure::Z)) / 2;
    ui->cameraLookX->setValue(x);
    ui->cameraLookY->setValue(y);
    ui->cameraLookZ->setValue(z);
}

void MainWindow::on_buttonLights_clicked()
{
    dialogLights.exec();
}

void MainWindow::slotUpdateUI(int percentage, double duration)
{
	updateImage();
	if(percentage == 100) {
		std::ostringstream message;
		message << "Image Rendered in: " << duration << " seconds.";
		ui->statusBar->showMessage(QString::fromStdString(message.str()), 5000);
	}
	ui->progressBar->setValue(percentage);
}

void MainWindow::on_buttonOptions_clicked()
{
	dialogOptions.exec();
}

Camera MainWindow::generateCamera()
{
	double size = 0;
	for(int dim = 0; dim < 3; dim++) {
		size = fmax(size, rayTracing->getMaxPoint(dim) - rayTracing->getMinPoint(dim));
	}

	double x = ui->cameraLookX->value();
	double y = ui->cameraLookY->value();
	double z = ui->cameraLookZ->value();
	Point lookat(x, y, z);
	Vector fromOrigin(x, y, z);
	double elevation = (double) (ui->dialVertical->value()) * PI / 180;
	double azimuth = (double) (ui->dialHorizontal->value()) * PI / 180;
	double distance = (double) ui->sliderZoom->value() / 200 * size;
	z = distance * cosf(elevation) * cosf(azimuth);
	x = distance * cosf(elevation) * sinf(azimuth);
	y = distance * sinf(elevation);
	Point location = Point(x, y, z) + fromOrigin;

	return Camera(location, lookat, size, size, size, XPIX, YPIX);
}

void MainWindow::updateImage()
{
	for(int y = 0; y < YPIX; y++) {
		for(int x = 0; x < XPIX; x++) {
			Colour colour = rayTracing->getImageData()->getPixel(x, y);
			QRgb rgb = qRgb(colour.getR() * 255, colour.getG() * 255, colour.getB() * 255);
			image.setPixel(x, y, rgb);
		}
	}
	ui->labelImage->setPixmap(QPixmap::fromImage(image));
}
