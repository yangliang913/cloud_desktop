#include "cloud_terminal.h"
#include "mainwindow.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	//cloud_terminal w;
	//w.show();
	CMainWindow w;
	w.show();
	return a.exec();
}
