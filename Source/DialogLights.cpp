#include "DialogLights.h"
#include "ui_DialogLights.h"

DialogLights::DialogLights(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogLights)
{
    ui->setupUi(this);
    lights.push_back(Light(Point(0, 0, 0), Colour(0, 0, 0)));
}

DialogLights::~DialogLights()
{
    delete ui;
}

void DialogLights::setCamera(Camera camera)
{
    this->camera = camera;
}

void DialogLights::on_buttonAdd_clicked()
{
    Point location(ui->spinLocX->value(), ui->spinLocY->value(), ui->spinLocZ->value());
	double red = (ui->spinR->value());
	double green = (ui->spinG->value());
	double blue = (ui->spinB->value());
	Colour colour(red / 255, green / 255, blue / 255);
	addLight(location, colour);
}

vector<Light> DialogLights::getLights() {
    if(ui->buttonFlash->isChecked()) {
        lights[0] = Light(camera.getLocation(), Colour(1, 1, 1));
    } else {
        lights[0] = Light(camera.getLocation(), Colour(0, 0, 0));
    }
    return lights;
}

void DialogLights::on_buttonDelete_clicked()
{
    QList<QTableWidgetItem*> selectionRangeList = ui->tableLights->selectedItems();
    int rowIndex;

    assert(selectionRangeList.size() % ui->tableLights->columnCount() == 0);

    for(int i = 0; i < selectionRangeList.size(); i += ui->tableLights->columnCount()) {
        rowIndex = selectionRangeList.at(i)->row();
        ui->tableLights->removeRow(rowIndex);
		lights.erase(lights.begin() + rowIndex + 1);
    }
}

void DialogLights::addLight(Point location, Colour colour)
{
    lights.push_back(Light(location, colour));
    ui->tableLights->setRowCount(ui->tableLights->rowCount() + 1);
	QTableWidgetItem * itemX = new QTableWidgetItem(tr("%1").arg(location.getX()));
	QTableWidgetItem * itemY = new QTableWidgetItem(tr("%1").arg(location.getY()));
	QTableWidgetItem * itemZ = new QTableWidgetItem(tr("%1").arg(location.getZ()));
	QTableWidgetItem * itemR = new QTableWidgetItem(tr("%1").arg(colour.getR() * 255));
	QTableWidgetItem * itemG = new QTableWidgetItem(tr("%1").arg(colour.getG() * 255));
	QTableWidgetItem * itemB = new QTableWidgetItem(tr("%1").arg(colour.getB() * 255));
    ui->tableLights->setItem(ui->tableLights->rowCount() - 1, 0, itemX);
    ui->tableLights->setItem(ui->tableLights->rowCount() - 1, 1, itemY);
    ui->tableLights->setItem(ui->tableLights->rowCount() - 1, 2, itemZ);
    ui->tableLights->setItem(ui->tableLights->rowCount() - 1, 3, itemR);
    ui->tableLights->setItem(ui->tableLights->rowCount() - 1, 4, itemG);
    ui->tableLights->setItem(ui->tableLights->rowCount() - 1, 5, itemB);
}
