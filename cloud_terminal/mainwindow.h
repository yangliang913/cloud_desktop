#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QStackedLayout>

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
};

#endif // MAINWINDOW_H
