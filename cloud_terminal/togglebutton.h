#ifndef TOGGLEBUTTON_H
#define TOGGLEBUTTON_H

#include <QPushButton>
#include <QPainter>
#include <QtCore/qmath.h>
#include <QStaticText>
#include <QString>
#include <QPoint>
#include <QLineEdit>
#include <QIntValidator>
#include <qt_windows.h>

enum BtnType
{
	CpuBtnType,
	MemBtnType,
	BandwidthEditBtnType
};

class ToggleButton : public QPushButton
{
	Q_OBJECT

public:
	explicit ToggleButton(int type, QString str, QWidget *parent);
	~ToggleButton();

public:
	void switchCheck();
	void setBtnChecked();
	void setBtnUnchecked();
	bool isBtnChecked();
	void adjustStartPoint(int width, int height, int fontSize, int fontNum);

protected:
	void paintEvent ( QPaintEvent * );

private:
	bool isChecked;
	int btnType;
	QString btnStr;
	QPoint strStartPoint;
	QLineEdit *bandwidthLineEdit;
};

#endif // TOGGLEBUTTON_H
