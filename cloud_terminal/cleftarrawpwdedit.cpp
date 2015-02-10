#include "cleftarrawpwdedit.h"
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
CLeftArrawPWDEdit::CLeftArrawPWDEdit(QWidget *parent)
	: QWidget(parent)
{
	this->setFixedSize(280, 50);
	setAutoFillBackground(true);
	QPalette palette;
	palette.setBrush(QPalette::Background, QBrush(QPixmap(QString(":/first_login_res/input"))));
	this->setPalette(palette);
	QLineEdit* inputEdit = new QLineEdit();
	inputEdit->setStyleSheet("background-color:transparent;color:white;font-size:12px;border:0px;");
	inputEdit->setEchoMode(QLineEdit::Password);
	//inputEdit->setFixedSize(260,50);
	

	QPushButton* arraw = new QPushButton;
	arraw->setFixedSize(16,16);
	arraw->setIcon(QIcon(QString(":/second_logres/inputpwd")));
	arraw->setObjectName("arraw");
	arraw->setStyleSheet("background-color:transparent");
	//arraw->setStyleSheet("QPushButton#arraw:pressed{border-image: url(:/second_logres/pwdarrowclicked);}");

	QHBoxLayout* main_layout = new QHBoxLayout;
	main_layout->addWidget(inputEdit);
	main_layout->addStretch();
	main_layout->addWidget(arraw);
	this->setLayout(main_layout);


}

CLeftArrawPWDEdit::~CLeftArrawPWDEdit()
{

}
