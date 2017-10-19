#ifndef DIALOGOPTIONS_H
#define DIALOGOPTIONS_H

#include <QDialog>

#include "RenderOptions.h"

namespace Ui {
class DialogOptions;
}

class DialogOptions : public QDialog
{
	Q_OBJECT

public:
	explicit DialogOptions(QWidget *parent = 0);
	~DialogOptions();

	RenderOptions * getRenderOptions();
	void setRenderOptions(const RenderOptions &value);

private slots:
	void on_buttonBox_accepted();

	void on_buttonBox_rejected();

private:
	Ui::DialogOptions *ui;
	RenderOptions renderOptions;
};

#endif // DIALOGOPTIONS_H
