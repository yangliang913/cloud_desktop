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
	mainLayout->setAlignment(Qt::AlignCenter);
	this->setStyleSheet("QMainWindow{border-image: url(:/first_login_res/background);}"); 
	this->setLayout(mainLayout);
	mainLayout->setCurrentIndex(0);
	//mainLayout->setContentsMargins(currentScreenWidth - 400, currentScreenHeight - 200, currentScreenWidth - 400, currentScreenHeight - 200);
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
	firstLoginWidget->setMaximumSize(800,400);
	firstLoginWidget->setMinimumSize(800, 400);
	QVBoxLayout *mainLayout = new QVBoxLayout;
	QHBoxLayout *hLayout1 = new QHBoxLayout;
	QLabel *photoLabel = new QLabel;
	photoLabel->setFixedSize(110, 110);
	QPixmap *photoPixmap = new QPixmap(":/first_login_res/default_photo");
	photoLabel->setPixmap(*photoPixmap);
	hLayout1->setAlignment(Qt::AlignCenter);
	hLayout1->setContentsMargins(0, 0, 0, 0);
	hLayout1->addWidget(photoLabel);
	
	QHBoxLayout *hLayout2 = new QHBoxLayout;
	userTextEdit = new CMyTextEdit(":/first_login_res/input", QStringLiteral("用户名"), 280, 50);
	hLayout2->setAlignment(Qt::AlignCenter);
	hLayout2->setContentsMargins(0, 0, 0, 0);
	hLayout2->addWidget(userTextEdit);
	
	QHBoxLayout *hLayout3 = new QHBoxLayout;
	passwordTextEdit = new CMyTextEdit(":/first_login_res/input", QStringLiteral("密码"), 280, 50);
	hLayout3->setAlignment(Qt::AlignCenter);
	hLayout3->setContentsMargins(0, 0, 0, 0);
	hLayout3->addWidget(passwordTextEdit);

	QHBoxLayout *hLayout4 = new QHBoxLayout;
	ToggleButton *saveUserBtn= new ToggleButton(SaveUserNameType, 66, 14);
	hLayout4->setContentsMargins(0, 0, 0, 0);
	hLayout4->setAlignment(Qt::AlignCenter);
	hLayout4->addWidget(saveUserBtn);

	QPushButton *firstLoginBtn = new QPushButton();
	firstLoginBtn->setFixedSize(280, 50);
	firstLoginBtn->setObjectName("firstLoginBtn");
	firstLoginBtn->setStyleSheet("QPushButton#firstLoginBtn{border-image: url(:/first_login_res/btn_pressed);}"
		"QPushButton#firstLoginBtn:hover{border-image: url(:/first_login_res/btn_hover);}"
		"QPushButton#firstLoginBtn:pressed{border-image: url(:/first_login_res/btn_pressed);}");
	QHBoxLayout *hLayout5 = new QHBoxLayout;
	hLayout5->setAlignment(Qt::AlignCenter);
	hLayout5->setContentsMargins(0, 0, 0, 0);
	hLayout5->addWidget(firstLoginBtn);

	QHBoxLayout *hLayout6 = new QHBoxLayout;
	QLabel *logoLabel = new QLabel;
	photoLabel->setFixedSize(185, 64);
	QPixmap *logoPixmap = new QPixmap(":/first_login_res/logo");
	logoLabel->setPixmap(*logoPixmap);
	hLayout6->setAlignment(Qt::AlignCenter);
	hLayout6->setContentsMargins(0, 0, 0, 0);
	hLayout6->addWidget(logoLabel);

	mainLayout->setContentsMargins(0, 0, 0, 0);
	mainLayout->addLayout(hLayout1);
	mainLayout->addSpacing(40);
	mainLayout->addLayout(hLayout2);
	mainLayout->addSpacing(6);
	mainLayout->addLayout(hLayout3);
	mainLayout->addSpacing(54);
	mainLayout->addLayout(hLayout4);
	mainLayout->addLayout(hLayout5);
	mainLayout->addLayout(hLayout6);
	firstLoginWidget->setLayout(mainLayout);
}

void CMainWindow::createSecondLoginWidget()
{
	secondLoginWidget = new QWidget(this);
	QLabel *label = new QLabel("secondLoginWidget", secondLoginWidget);
	QHBoxLayout *layout = new QHBoxLayout;

	secondLoginWidget->setLayout(layout);
}
