#ifndef DIALOGLIGHTS_H
#define DIALOGLIGHTS_H

#include <QDialog>
#include <iostream>
#include <vector>

#include "Camera.h"
#include "LightPoint.h"
#include "Point.h"

namespace Ui {
class DialogLights;
}

class DialogLights : public QDialog
{
    Q_OBJECT

public:
    explicit DialogLights(QWidget *parent = 0);
    ~DialogLights();

    void setCamera(Camera camera);
    vector<Light> getLights();

private slots:
    void on_buttonAdd_clicked();

    void on_buttonDelete_clicked();

private:
    Ui::DialogLights *ui;

    vector<Light> lights;
    Camera camera;

    void addLight(Point location, Colour colour);
};

#endif // DIALOGLIGHTS_H
