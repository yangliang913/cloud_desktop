#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QStackedLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPixmap>
#include "mytextedit.h"
#include "zc_message_box.h"

class CMainWindow : public QMainWindow
{
	Q_OBJECT

public:
	CMainWindow(QWidget *parent=0);
	~CMainWindow();

public:
	void createFirstLoginWidget();
	void createSecondLoginWidget();

private:
	QWidget				*firstLoginWidget;
	QWidget				*secondLoginWidget;
	QStackedLayout		*mainLayout;
	int					currentScreenWidth;
	int					currentScreenHeight;
	double				widthRatio;
	double				heightRatio;
	CMyTextEdit			*userTextEdit;
	CMyTextEdit			*passwordTextEdit;
};

#endif // MAINWINDOW_H
