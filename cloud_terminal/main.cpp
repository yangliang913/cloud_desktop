#include "cloud_terminal.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	cloud_terminal w;
	w.show();
	return a.exec();
}
