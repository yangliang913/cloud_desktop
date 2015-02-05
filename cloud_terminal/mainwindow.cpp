#include "mainwindow.h"
#include <QLabel>
#include <QtWidgets/QApplication>
#include <QTextCodec>
#include <QDesktopWidget>
#include "clabel.h"
#include "util.h"
#include "cusercard.h"

#define CENTER_WIDGET_W 800
#define CENTER_WIDGET_H 600

CMainWindow::CMainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	currentScreenWidth = QApplication::desktop()->width();
	currentScreenHeight = QApplication::desktop()->height();
	widthRatio = currentScreenWidth / 1920.0;
	heightRatio = currentScreenHeight / 1080.0;
	this->setFixedSize(currentScreenWidth, currentScreenHeight);
	main_widget = new QWidget();
	setCentralWidget(main_widget);


	center_widget = new QWidget(main_widget);
	center_widget->setFixedSize(CENTER_WIDGET_W, CENTER_WIDGET_H);

	createFirstLoginWidget();
	createSecondLoginWidget();
	createMoreThan3Widget();
	

	mainLayout = new QStackedLayout();
	mainLayout->setAlignment(Qt::AlignCenter);
	mainLayout->addWidget(firstLoginWidget);
	mainLayout->addWidget(secondLoginWidget);
	mainLayout->addWidget(morethan3Widget);
	mainLayout->setCurrentIndex(2);
	mainLayout->setAlignment(Qt::AlignCenter);
	this->setStyleSheet("QMainWindow{border-image: url(:/first_login_res/background);}"); 
	center_widget->setLayout(mainLayout);


	QLabel *logoLabel = new QLabel;
	logoLabel->setFixedSize(185, 64);
	QPixmap *logoPixmap = new QPixmap(":/first_login_res/logo");
	logoLabel->setPixmap(*logoPixmap);
	QHBoxLayout* logolayout = new QHBoxLayout;
	logolayout->setAlignment(Qt::AlignCenter);
	logolayout->addWidget(logoLabel);

	QVBoxLayout* h_layout = new QVBoxLayout;
	h_layout->setAlignment(Qt::AlignCenter);
	h_layout->addStretch();
	h_layout->addWidget(center_widget);
	h_layout->addLayout(logolayout);
	h_layout->addStretch();
	main_widget->setLayout(h_layout);

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
	firstLoginWidget = new QWidget();
	firstLoginWidget->setFixedSize(CENTER_WIDGET_W, CENTER_WIDGET_H);
	QVBoxLayout *mainLayout = new QVBoxLayout;

	QLabel *photoLabel = new QLabel;
	photoLabel->setFixedSize(110, 110);
	QPixmap *photoPixmap = new QPixmap(":/first_login_res/default_photo");
	photoLabel->setPixmap(*photoPixmap);
	QHBoxLayout* photo_layout = new QHBoxLayout();
	photo_layout->setAlignment(Qt::AlignCenter);
	photo_layout->addWidget(photoLabel);
	userTextEdit = new CMyTextEdit(":/first_login_res/input", QStringLiteral("用户名"), 280, 50);
	passwordTextEdit = new CMyTextEdit(":/first_login_res/input", QStringLiteral("密码"), 280, 50);
	ToggleButton *saveUserBtn= new ToggleButton(SaveUserNameType, 66, 14);
	QPushButton *firstLoginBtn = new QPushButton();
	firstLoginBtn->setFixedSize(280, 50);
	firstLoginBtn->setObjectName("firstLoginBtn");
	firstLoginBtn->setStyleSheet("QPushButton#firstLoginBtn{border-image: url(:/first_login_res/btn_pressed);}"
		"QPushButton#firstLoginBtn:hover{border-image: url(:/first_login_res/btn_hover);}"
		"QPushButton#firstLoginBtn:pressed{border-image: url(:/first_login_res/btn_pressed);}");


	mainLayout->setAlignment(Qt::AlignCenter);
	mainLayout->setContentsMargins(0, 60, 0, 0);
	mainLayout->addLayout(photo_layout);
	mainLayout->addSpacing(40);
	mainLayout->addWidget(userTextEdit);
	mainLayout->addSpacing(6);
	mainLayout->addWidget(passwordTextEdit);
	mainLayout->addSpacing(10);
	mainLayout->addWidget(saveUserBtn);
	mainLayout->addSpacing(30);
	mainLayout->addWidget(firstLoginBtn);
	mainLayout->addSpacing(74);
	
	firstLoginWidget->setLayout(mainLayout);
}

void CMainWindow::createSecondLoginWidget()
{
	secondLoginWidget = new QWidget();
	secondLoginWidget->setFixedSize(CENTER_WIDGET_W, CENTER_WIDGET_H);
	CUserCard* leftbtn = new CUserCard();
	CUserCard* rightbtn = new CUserCard;

	
	leftbtn->setPixmap(QPixmap(QString(":/second_logres/default")));
	
	rightbtn->setPixmap(QPixmap(QString(":/second_logres/addusernomal")));
	
	QGridLayout* midlayout = new QGridLayout;
	midlayout->addWidget(leftbtn, 0, 0);
	midlayout->setSpacing(30);
	midlayout->addWidget(rightbtn, 0, 1);
	midlayout->setContentsMargins(0,0, 0, 150);
	
	QHBoxLayout* h_layout = new QHBoxLayout;
	h_layout->setAlignment(Qt::AlignCenter);
	h_layout->addLayout(midlayout);


	QVBoxLayout* main_layout = new QVBoxLayout;
	main_layout->addLayout(h_layout);

	secondLoginWidget->setLayout(main_layout);

}



void CMainWindow::createMoreThan3Widget()
{
	morethan3Widget = new QWidget();
	morethan3Widget->setFixedSize(CENTER_WIDGET_W, CENTER_WIDGET_H);


	CUserCard* btnarray = new CUserCard[4];
	QHBoxLayout* h_layout = new QHBoxLayout;
	h_layout->setAlignment(Qt::AlignCenter);
	h_layout->setContentsMargins(0, 0, 0, 150);
	h_layout->setSpacing(30);
	for (int i = 0; i < 3;i++)
	{
		QString strPic = Util::getSkinName(i);
		btnarray[i].setPixmap(QPixmap(strPic));
		//btnarray[i].setText(QString("HAHAHA"));
		h_layout->addWidget(&btnarray[i]);
	
	}
	btnarray[3].setPixmap(QPixmap(QString(":/second_logres/addusernomal")),110,110);
	h_layout->addWidget(&btnarray[3]);


	
	QWidget* panalwidget = new QWidget;
	panalwidget->setMaximumSize(400, 150);
	panalwidget->setAutoFillBackground(true);
	QPalette palette;
	palette.setBrush(QPalette::Background, QBrush(QPixmap(":/userpic/p1")));
	panalwidget->setPalette(palette);




	CLabel* photoarray = new CLabel[12];
	QGridLayout* panlelayout = new QGridLayout;
	for (int i = 0; i < 12;i++)
	{
		photoarray[i].setFixedSize(60, 60);
		photoarray[i].setPixmap(QPixmap(QString(":/userpic/p%1").arg(i+1)), 60, 60);
		panlelayout->setSpacing(5);
		panlelayout->addWidget(&photoarray[i], i / 6, i % 6);
	}
	panlelayout->setContentsMargins(0, 0, 0, 0);
	panalwidget->setLayout(panlelayout);
	
	QVBoxLayout* main_layout = new QVBoxLayout;
	main_layout->setAlignment(Qt::AlignCenter);

	QHBoxLayout* pannel_layout = new QHBoxLayout;
	pannel_layout->setAlignment(Qt::AlignCenter);
	pannel_layout->addWidget(panalwidget);

	main_layout->addLayout(h_layout);
	main_layout->addLayout(pannel_layout);

	morethan3Widget->setLayout(main_layout);

}