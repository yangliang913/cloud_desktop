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
	widthRatio = currentScreenWidth / 1920.0;
	heightRatio = currentScreenHeight / 1080.0;
	createFirstLoginWidget();
	createSecondLoginWidget();
	mainLayout = new QStackedLayout();
	mainLayout->addWidget(firstLoginWidget);
	mainLayout->addWidget(secondLoginWidget);
	this->setStyleSheet("QMainWindow{border-image: url(:/first_login_res/background);}"); 
	this->setLayout(mainLayout);
	mainLayout->setCurrentIndex(0);
	this->resize(currentScreenWidth, currentScreenHeight);

	this->setWindowTitle(QStringLiteral("致云科技桌面云终端"));
	this->setWindowFlags(Qt::FramelessWindowHint);
}

CMainWindow::~CMainWindow()
{

}

void CMainWindow::createFirstLoginWidget()
{
	//ZCMessageBox *msgBox = new ZCMessageBox(QStringLiteral("主机地址格式错误，格式如：172.16.5.1:5901"));
	//msgBox->show();
	//delete msgBox;
	firstLoginWidget = new QWidget(this);
	firstLoginWidget->setFixedSize(currentScreenWidth, currentScreenHeight);
	QVBoxLayout *mainLayout = new QVBoxLayout;
	QHBoxLayout *hLayout1 = new QHBoxLayout;
	QLabel *photoLabel = new QLabel;
	photoLabel->setFixedSize(160, 160);
	QPixmap *photoPixmap = new QPixmap(":/first_login_res/default_photo");
	photoLabel->setPixmap(*photoPixmap);
	hLayout1->setAlignment(Qt::AlignCenter);
	hLayout1->addWidget(photoLabel);
	
	QHBoxLayout *hLayout2 = new QHBoxLayout;
	userTextEdit = new CMyTextEdit(":/first_login_res/input", QStringLiteral("用户名"), 280, 50);
	hLayout2->setAlignment(Qt::AlignCenter);
	hLayout2->addWidget(userTextEdit);
	
	QHBoxLayout *hLayout3 = new QHBoxLayout;
	passwordTextEdit = new CMyTextEdit(":/first_login_res/input", QStringLiteral("密码"), 280, 50);
	hLayout3->setAlignment(Qt::AlignCenter);
	hLayout3->addWidget(passwordTextEdit);

	//QHBoxLayout *hLayout3 = new QHBoxLayout;
	//passwordTextEdit = new CMyTextEdit(":/first_login_res/input", QStringLiteral("密码"), 280, 50);
	//hLayout3->setAlignment(Qt::AlignCenter);
	//hLayout3->addWidget(passwordTextEdit);

	mainLayout->addLayout(hLayout1);
	mainLayout->addLayout(hLayout2);
	mainLayout->addLayout(hLayout3);
	firstLoginWidget->setLayout(mainLayout);
}

void CMainWindow::createSecondLoginWidget()
{
	secondLoginWidget = new QWidget(this);
	QLabel *label = new QLabel("secondLoginWidget", secondLoginWidget);
	QHBoxLayout *layout = new QHBoxLayout;

	secondLoginWidget->setLayout(layout);
}
