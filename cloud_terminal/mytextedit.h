#ifndef MYTEXTEDIT_H
#define MYTEXTEDIT_H

#include <QWidget>
#include <QLabel>
#include <QPixmap>
#include <QPalette>
#include <QString>
#include <QTextEdit>
#include <QHBoxLayout>
#include <QLineEdit>

class CMyTextEdit : public QWidget
{
	Q_OBJECT

public:
	CMyTextEdit(QString img, QString text, int wid, int hei, QWidget *parent = 0);
	~CMyTextEdit();

private:
	QPixmap		*pixmap;
	QString		imgPath;
	int			width;
	int			height;
	QLineEdit	*inputEdit;
	QString		showText;
};

#endif // MYTEXTEDIT_H
