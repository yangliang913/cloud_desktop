#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QStackedLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPixmap>
#include <QPushButton>
#include "mytextedit.h"
#include "zc_message_box.h"
#include "togglebutton.h"
#include <QScrollArea>
class CMainWindow : public QMainWindow
{
	Q_OBJECT

public:
	CMainWindow(QWidget *parent=0);
	~CMainWindow();

public:
	void createFirstLoginWidget();
	void createSecondLoginWidget();
	void createMoreThan3Widget();
	void createChangePassWidget();
	void createCloudHostSelectWidget();
	void createChangeUserWidget();
public:
	void setScrollSheet(QScrollArea* scroll);
private:
	QWidget				*firstLoginWidget;
	QWidget				*secondLoginWidget;
	QWidget				*morethan3Widget;
	QWidget				*changePswdWidget;
	QWidget				*chostselectWdiget;
	QWidget				*changeuserwidget;
	QStackedLayout		*mainLayout;
	int					currentScreenWidth;
	int					currentScreenHeight;
	double				widthRatio;
	double				heightRatio;
	CMyTextEdit			*userTextEdit;
	CMyTextEdit			*passwordTextEdit;
	QWidget				*main_widget;
	QWidget				*center_widget;
};

#endif // MAINWINDOW_H
