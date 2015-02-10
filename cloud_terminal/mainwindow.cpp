#include "mainwindow.h"
#include <QLabel>
#include <QtWidgets/QApplication>
#include <QTextCodec>
#include <QDesktopWidget>
#include "clabel.h"
#include "util.h"
#include "cusercard.h"
#include "cuserpicpanel.h"
#include "cleftarrawpwdedit.h"

#include "chostlist.h"
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
	createChangePassWidget();
	createChangeUserWidget();
	createCloudHostSelectWidget();
	

	mainLayout = new QStackedLayout();
	mainLayout->setAlignment(Qt::AlignCenter);
	mainLayout->addWidget(firstLoginWidget);//0
	mainLayout->addWidget(secondLoginWidget);
	mainLayout->addWidget(morethan3Widget);
	mainLayout->addWidget(changePswdWidget);
	mainLayout->addWidget(changeuserwidget);
	mainLayout->addWidget(chostselectWdiget);

	mainLayout->setCurrentIndex(5);
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

	CUserCard* userpic = new CUserCard(1);
	userpic->setPixmap(QPixmap(QString(":/changeuser/default")));
	userpic->setText(QStringLiteral("致云云主机"));

	CLeftArrawPWDEdit* edit = new CLeftArrawPWDEdit;
	edit->setFixedSize(280, 50);

	QPushButton* changpwdbtn = new QPushButton;
	changpwdbtn->setFixedSize(48, 12);
	changpwdbtn->setObjectName("changpwdbtn");
	changpwdbtn->setStyleSheet("QPushButton#changpwdbtn{border-image: url(:/second_logres/changepwdnomal);}"
		"QPushButton#changpwdbtn:pressed{border-image: url(:/second_logres/changpwdclicked);}");


	QPushButton *userchangeBtn = new QPushButton();
	userchangeBtn->setFixedSize(48, 44);
	userchangeBtn->setObjectName("userchangeBtn");
	userchangeBtn->setStyleSheet("QPushButton#userchangeBtn{border-image: url(:/second_logres/changnomal);}"
		"QPushButton#userchangeBtn:hover{border-image: url(:/second_logres/changhover);}"
		"QPushButton#userchangeBtn:pressed{border-image: url(:/second_logres/changclicked);}");

	QPushButton *changsetBtn = new QPushButton();
	changsetBtn->setFixedSize(48, 44);
	changsetBtn->setObjectName("changsetBtn");
	changsetBtn->setStyleSheet("QPushButton#changsetBtn{border-image: url(:/second_logres/changesetnomal);}"
		"QPushButton#changsetBtn:hover{border-image: url(:/second_logres/changesethover);}"
		"QPushButton#changsetBtn:pressed{border-image: url(:/second_logres/changesetclicked);}");

	QHBoxLayout* pic_layout = new QHBoxLayout;
	pic_layout->setAlignment(Qt::AlignCenter);
	pic_layout->addWidget(userpic);

	QHBoxLayout* eidt_layout = new QHBoxLayout;
	eidt_layout->setAlignment(Qt::AlignCenter);
	eidt_layout->addWidget(edit);

	QHBoxLayout* changebtn_layout = new QHBoxLayout;
	changebtn_layout->addStretch(98);
	changebtn_layout->addWidget(changpwdbtn);
	changebtn_layout->addStretch(52);

	QHBoxLayout* btn_layout = new QHBoxLayout;
	btn_layout->addStretch(70);
	btn_layout->addWidget(userchangeBtn);
	btn_layout->addStretch(40);
	btn_layout->addWidget(changsetBtn);
	btn_layout->addStretch(70);

	QVBoxLayout* main_layout = new QVBoxLayout;
	main_layout->setAlignment(Qt::AlignCenter);
	main_layout->addLayout(pic_layout);
	main_layout->addSpacing(50);
	main_layout->addLayout(eidt_layout);
	main_layout->addSpacing(20);
	main_layout->addLayout(changebtn_layout);
	main_layout->addSpacing(50);
	main_layout->addLayout(btn_layout);

	secondLoginWidget->setLayout(main_layout);

}



void CMainWindow::createMoreThan3Widget()
{
	morethan3Widget = new QWidget();
	morethan3Widget->setFixedSize(CENTER_WIDGET_W, CENTER_WIDGET_H);



	QHBoxLayout* h_layout = new QHBoxLayout;
	h_layout->setAlignment(Qt::AlignCenter);
	h_layout->setContentsMargins(0, 0, 0, 150);
	h_layout->setSpacing(30);

	QPushButton* lbtn = new QPushButton;
	QPushButton* rbtn = new QPushButton;
	lbtn->setIcon(QIcon(QString(":/morethan3/left")));
	lbtn->setFixedSize(26, 26);
	rbtn->setIcon(QIcon(QString(":/morethan3/right")));
	rbtn->setFixedSize(26, 26);
	h_layout->addWidget(lbtn);
	lbtn->setStyleSheet("background-color:transparent");
	rbtn->setStyleSheet("background-color:transparent");


	for (int i = 0; i < 3;i++)
	{
		CUserCard* card = new CUserCard();
		QString strPic = Util::getSkinName(i);
		card->setPixmap(QPixmap(strPic));
		//card->setText(QString("Admin007"));
		h_layout->addWidget(card);
	
	}
	CUserCard* card = new CUserCard(1);
	card->setPixmap(QPixmap(QString(":/changeuser/addusernomal")), 110, 110);
	h_layout->addWidget(card);
	h_layout->addWidget(rbtn);

	
	CUserPicPanel* panel = new CUserPicPanel;

	
	QVBoxLayout* main_layout = new QVBoxLayout;
	main_layout->setAlignment(Qt::AlignCenter);
	main_layout->setContentsMargins(0, 100, 0, 80);

	QHBoxLayout* pannel_layout = new QHBoxLayout;
	
	pannel_layout->setAlignment(Qt::AlignCenter);
	pannel_layout->addWidget(panel);

	main_layout->addLayout(h_layout);
	main_layout->addLayout(pannel_layout);

	morethan3Widget->setLayout(main_layout);

}

void CMainWindow::createChangePassWidget()
{
	changePswdWidget = new QWidget;
	changePswdWidget->setFixedSize(CENTER_WIDGET_W, CENTER_WIDGET_H);
	QLabel* usericon = new QLabel;
	usericon->setFixedSize(70, 70);
	usericon->setPixmap(QPixmap(QString(":/userpic/p1")));

	QLabel* username = new QLabel;
	username->setFixedSize(280, 20);
	username->setStyleSheet("font-size:16px");
	username->setStyleSheet("background-color:transparent;color:rgb(228,228,228);font-size:20px;border:0px;");
	username->setText("929015200@qq.com");

	QLabel* changepwd = new QLabel;
	changepwd->setFixedSize(280, 20);
	changepwd->setStyleSheet("background-color:transparent;color:rgb(228,228,228);font-size:20px;border:0px;");
	changepwd->setText(QStringLiteral("修改密码"));

	CMyTextEdit* pwdeidt = new CMyTextEdit(":/first_login_res/input", QStringLiteral(""), 480, 50);
	CMyTextEdit* newpwdeidt = new CMyTextEdit(":/first_login_res/input", QStringLiteral("新密码"), 480, 50);
	CMyTextEdit* surenewpwdeidt = new CMyTextEdit(":/first_login_res/input", QStringLiteral("确认新密码"), 480, 50);

	QPushButton *returnBtn = new QPushButton();
	returnBtn->setFixedSize(130, 50);
	returnBtn->setObjectName("returnBtn");
	returnBtn->setStyleSheet("QPushButton#returnBtn{border-image: url(:/changepwd/retnomal);}"
		"QPushButton#returnBtn:hover{border-image: url(:/changepwd/rethover);}"
		"QPushButton#returnBtn:pressed{border-image: url(:/changepwd/retclicked);}");

	QPushButton *sureBtn = new QPushButton();
	sureBtn->setFixedSize(130, 50);
	sureBtn->setObjectName("sureBtn");
	sureBtn->setStyleSheet("QPushButton#sureBtn{border-image: url(:/changepwd/surenomal);}"
		"QPushButton#sureBtn:hover{border-image: url(:/changepwd/surehover);}"
		"QPushButton#sureBtn:pressed{border-image: url(:/changepwd/sureclicked);}");

	QHBoxLayout* h_usericon_name = new QHBoxLayout;
	h_usericon_name->setAlignment(Qt::AlignCenter);
	h_usericon_name->addStretch(31);
	h_usericon_name->addWidget(usericon);
	h_usericon_name->addStretch(3);
	h_usericon_name->addWidget(username);
	h_usericon_name->addStretch(52);

	QHBoxLayout* h_changepwd = new QHBoxLayout;
	h_changepwd->addStretch(30);
	h_changepwd->addWidget(changepwd);
	h_changepwd->addStretch(70);

	QHBoxLayout* h_btn_layout = new QHBoxLayout;
	h_btn_layout->setAlignment(Qt::AlignCenter);
	h_btn_layout->addStretch(70);
	h_btn_layout->addWidget(returnBtn);
	h_btn_layout->addStretch(1);
	h_btn_layout->addWidget(sureBtn);
	h_btn_layout->addStretch(30);

	QVBoxLayout* v_layout = new QVBoxLayout;
	v_layout->setAlignment(Qt::AlignCenter);

	v_layout->addWidget(pwdeidt);
	v_layout->addSpacing(6);
	v_layout->addWidget(newpwdeidt);
	v_layout->addSpacing(6);
	v_layout->addWidget(surenewpwdeidt);
	

	QHBoxLayout* h_layout = new QHBoxLayout;
	h_layout->setAlignment(Qt::AlignCenter);
	h_layout->addLayout(v_layout);

	QVBoxLayout* main_layout = new QVBoxLayout;
	main_layout->setAlignment(Qt::AlignCenter);
	main_layout->addLayout(h_usericon_name);
	main_layout->addSpacing(40);
	main_layout->addLayout(h_changepwd);
	main_layout->addSpacing(24);
	main_layout->addLayout(h_layout);
	main_layout->addSpacing(26);
	main_layout->addLayout(h_btn_layout);
	main_layout->addStretch();
	main_layout->setContentsMargins(0, 70, 0, 0);

	QHBoxLayout* main_l = new QHBoxLayout;
	main_l->setAlignment(Qt::AlignCenter);

	main_l->addLayout(main_layout);

	changePswdWidget->setLayout(main_l);
}

void CMainWindow::createCloudHostSelectWidget()
{
	chostselectWdiget = new QWidget;
	chostselectWdiget->setFixedSize(CENTER_WIDGET_W, CENTER_WIDGET_H);

	QLabel* usericon = new QLabel;
	usericon->setFixedSize(70, 70);
	usericon->setPixmap(QPixmap(QString(":/hostselect/logo")));

	QLabel* username = new QLabel;
	username->setFixedSize(280, 20);
	username->setStyleSheet("font-size:16px");
	username->setStyleSheet("background-color:transparent;color:rgb(228,228,228);font-size:20px;border:0px;");
	username->setText("929015200@qq.com");

	QLabel* selectlabel = new QLabel;
	selectlabel->setFixedSize(280, 20);
	selectlabel->setStyleSheet("background-color:transparent;color:rgb(228,228,228);font-size:20px;border:0px;");
	selectlabel->setText(QStringLiteral("请选择您需要登录的云主机"));


	
 	QScrollArea *pArea = new QScrollArea(chostselectWdiget);
	setScrollSheet(pArea);
	pArea->viewport()->setStyleSheet("background-color:transparent;");

	CHostList * hostlistwd = new CHostList(pArea);//需要滚动的是一个Qwidget，而如果是在设计器里面拖入控件，会自动添加一个
	hostlistwd->AddCloudItem(QString("Windows xp"));
	hostlistwd->AddCloudItem(QString("Windows 7"));
	hostlistwd->AddCloudItem(QString("Windows 8.1"));
	hostlistwd->AddCloudItem(QString("Windows 9.1"));
	hostlistwd->AddCloudItem(QString("Windows 10.1"));
	hostlistwd->endAdd();
	
 	pArea->setWidget(hostlistwd);//这里设置滚动窗口qw，
 	pArea->setFixedSize(490,170);//要显示的区域大小


	QPushButton *returnBtn = new QPushButton();
	returnBtn->setFixedSize(130, 50);
	returnBtn->setObjectName("retBtn");
	returnBtn->setStyleSheet("QPushButton#retBtn{border-image: url(:/hostselect/retnomal);}"
		"QPushButton#retBtn:hover{border-image: url(:/hostselect/rethover);}"
		"QPushButton#retBtn:pressed{border-image: url(:/hostselect/retclicked);}");

	QPushButton *okBtn = new QPushButton();
	okBtn->setFixedSize(130, 50);
	okBtn->setObjectName("okBtn");
	okBtn->setStyleSheet("QPushButton#okBtn{border-image: url(:/hostselect/surenomal);}"
		"QPushButton#okBtn:hover{border-image: url(:/hostselect/surehover);}"
		"QPushButton#okBtn:pressed{border-image: url(:/hostselect/sureclicked);}");


	QHBoxLayout* logo_l = new QHBoxLayout;
	logo_l->addStretch(38);
	logo_l->addWidget(usericon);
	logo_l->addWidget(username);
	logo_l->addStretch(62);

	QHBoxLayout* s_layout = new QHBoxLayout;
	s_layout->setAlignment(Qt::AlignCenter);
	s_layout->addStretch(32);
	s_layout->addWidget(selectlabel);
	s_layout->addStretch(68);

	QHBoxLayout* hostlist_l = new QHBoxLayout;
	hostlist_l->setAlignment(Qt::AlignCenter);
	hostlist_l->addWidget(pArea);

	QHBoxLayout* btn_layout = new QHBoxLayout;
	btn_layout->addStretch(70);
	btn_layout->addWidget(returnBtn);
	btn_layout->addStretch(5);
	btn_layout->addWidget(okBtn);
	btn_layout->addStretch(30);
	QVBoxLayout* main_layout = new QVBoxLayout;
	main_layout->setAlignment(Qt::AlignCenter);
	main_layout->addLayout(logo_l);
	main_layout->addSpacing(35);
	main_layout->addLayout(s_layout);
	main_layout->addSpacing(20);
	main_layout->addLayout(hostlist_l);
	main_layout->addSpacing(25);
	main_layout->addLayout(btn_layout);
	main_layout->setContentsMargins(0, 110, 0, 100);
	chostselectWdiget->setLayout(main_layout);

}

void CMainWindow::createChangeUserWidget()
{
	changeuserwidget = new QWidget;
	CUserCard* leftbtn = new CUserCard();
	CUserCard* rightbtn = new CUserCard(1);


	leftbtn->setPixmap(QPixmap(QString(":/changeuser/default")));

	rightbtn->setPixmap(QPixmap(QString(":/changeuser/addusernomal")));

	QGridLayout* midlayout = new QGridLayout;
	midlayout->addWidget(leftbtn, 0, 0);
	midlayout->setSpacing(30);
	midlayout->addWidget(rightbtn, 0, 1);
	midlayout->setContentsMargins(0, 0, 0, 150);

	QHBoxLayout* h_layout = new QHBoxLayout;
	h_layout->setAlignment(Qt::AlignCenter);
	h_layout->addLayout(midlayout);


	QVBoxLayout* main_layout = new QVBoxLayout;
	main_layout->addLayout(h_layout);

	changeuserwidget->setLayout(main_layout);
}

void CMainWindow::setScrollSheet(QScrollArea* scroll)
{
		scroll->setStyleSheet("QScrollArea"
		"{"
		"background-color:transparent;"
		"border-radius:0px;"
		"}"
		"QScrollBar:vertical"
		"{"
		"width:8px;"
		"background:rgba(0,0,0,100%);"
		"background:url(:/hostselect/spiderbg);"
		"margin:0px,0px,0px,0px;"
		"padding-top:9px;"
		"padding-bottom:0px;"
		"}"
		"QScrollBar::handle:vertical"
		"{"
		"width:5px;"
		"background:rgba(0,0,0,25%);"
		"background:url(:/hostselect/spidernomal);"
		"border-radius:5px;"
		"min-height:22;"
		"}"
		"QScrollBar::handle:vertical:pressed"
		"{"
		"width:5px;"
		"background:rgba(0,0,0,25%);"
		"background:url(:/hostselect/spiderclicked);"
		" border-radius:5px;"
		"min-height:22;"
		"}"
// 		"QScrollBar::handle:vertical:hover"
// 		"{"
// 		"width:5px;"
// 		"background:rgba(0,0,0,50%);"
// 		" border-radius:5px;"
// 		"min-height:22;"
// 		"}"
		"QScrollBar::add-line:vertical"
		"{"
		"height:0px;width:8px;"
		"border-image:url(:/images/a/3.png);"
		"subcontrol-position:bottom;"
		"}"
		"QScrollBar::sub-line:vertical"
		"{"
		"height:0px;width:8px;"
		"border-image:url(:/images/a/1.png);"
		"subcontrol-position:top;"
		"}"
		"QScrollBar::add-line:vertical:hover"
		"{"
		"height:0px;width:8px;"
		"border-image:url(:/images/a/4.png);"
		"subcontrol-position:bottom;"
		"}"
		"QScrollBar::sub-line:vertical:hover"
		"{"
		"height:0px;width:8px;"
		"border-image:url(:/images/a/2.png);"
		"subcontrol-position:top;"
		"}"
		"QScrollBar::add-page:vertical,QScrollBar::sub-page:vertical"
		"{"
		"background:rgba(0,0,0,10%);"
		"border-radius:4px;"
		"}"
		);
}