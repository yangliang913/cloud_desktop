#include "mainwindow.h"
#include <QLabel>
#include <QtWidgets/QApplication>
#include <QTextCodec>
#include <QDesktopWidget>

CMainWindow::CMainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	currentScreenWidth = QApplication::desktop()->width();
	currentScreenHeight = QApplication::desktop()->height();
	createFirstLoginWidget();
	createSecondLoginWidget();
	mainLayout = new QStackedLayout();
	mainLayout->addWidget(firstLoginWidget);
	mainLayout->addWidget(secondLoginWidget);
	this->setLayout(mainLayout);
	mainLayout->setCurrentIndex(0);
	this->resize(currentScreenWidth, currentScreenHeight);

	this->setWindowTitle(QStringLiteral("ÖÂÔÆ¿Æ¼¼×ÀÃæÔÆÖÕ¶Ë"));
	this->setWindowFlags(Qt::FramelessWindowHint);
}

CMainWindow::~CMainWindow()
{

}

void CMainWindow::createFirstLoginWidget()
{
	firstLoginWidget = new QWidget(this);
	QLabel *label = new QLabel("firstLoginWidget", firstLoginWidget);
}

void CMainWindow::createSecondLoginWidget()
{
	secondLoginWidget = new QWidget(this);
	QLabel *label = new QLabel("secondLoginWidget", secondLoginWidget);
	QHBoxLayout *layout = new QHBoxLayout;

	secondLoginWidget->setLayout(layout);
	
}
