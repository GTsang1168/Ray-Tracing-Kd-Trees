#include "DialogOptions.h"
#include "ui_DialogOptions.h"

DialogOptions::DialogOptions(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::DialogOptions)
{
	ui->setupUi(this);
}

DialogOptions::~DialogOptions()
{
	delete ui;
}

void DialogOptions::on_buttonBox_accepted()
{
	renderOptions.setGamma(ui->spinGamma->value());
	renderOptions.setRecursiveDepth(ui->spinRecursive->value());
	renderOptions.setDefaultMaterial(ui->checkDefaultM->isChecked());
	renderOptions.setPhong(ui->checkPhong->isChecked());
	renderOptions.setDiffuse(ui->checkDiffuse->isChecked());
	renderOptions.setSpecular(ui->checkSpecular->isChecked());
	renderOptions.setAmbient(ui->checkAmbient->isChecked());
	renderOptions.setShadows(ui->checkShadow->isChecked());
	renderOptions.setReflection(ui->checkReflection->isChecked());
	renderOptions.setRefraction(ui->checkRefraction->isChecked());
	renderOptions.setDistance(ui->checkDistance->isChecked());
	renderOptions.setGlobal(ui->checkGlobal->isChecked());
	renderOptions.setMultiThread(ui->checkMultiThreading->isChecked());
}

void DialogOptions::on_buttonBox_rejected()
{
	ui->spinGamma->setValue(renderOptions.getGamma());
	ui->spinRecursive->setValue(renderOptions.getRecursiveDepth());
	ui->checkDefaultM->setChecked(renderOptions.getDefaultMaterial());
	ui->checkPhong->setChecked(renderOptions.getPhong());
	ui->checkDiffuse->setChecked(renderOptions.getDiffuse());
	ui->checkSpecular->setChecked(renderOptions.getSpecular());
	ui->checkAmbient->setChecked(renderOptions.getAmbient());
	ui->checkShadow->setChecked(renderOptions.getShadows());
	ui->checkReflection->setChecked(renderOptions.getReflection());
	ui->checkRefraction->setChecked(renderOptions.getRefraction());
	ui->checkDistance->setChecked(renderOptions.getDistance());
	ui->checkGlobal->setChecked(renderOptions.getGlobal());
	ui->checkMultiThreading->setChecked(renderOptions.getMultiThread());
}
RenderOptions * DialogOptions::getRenderOptions()
{
	return &renderOptions;
}

void DialogOptions::setRenderOptions(const RenderOptions &value)
{
	renderOptions = value;
}

