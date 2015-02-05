#include "cusercard.h"
#include "clabel.h"
#include <QPushButton>

MyLabel::MyLabel(QWidget * parent) : 
QLabel(parent)
{
}
void MyLabel::mouseReleaseEvent(QMouseEvent * ev)
{
	Q_UNUSED(ev)emit clicked();
}


CUserCard::CUserCard(QWidget *parent)
	: QWidget(parent)
{
	this->setMinimumSize(121, 155);
	ismidselected = 0;
	midpic = new MyLabel(this);
	midpic->setPixmap(QPixmap(QString(":/usercard/defaultpic")));
	midpic->setGeometry(0, 10, 110, 110);
	midpic->setStyleSheet("border-width: 1px;   border-style: solid;   border-color: rgba(88,178, 255,100);");

	connect(midpic, SIGNAL(clicked()), this, SLOT(midclickfunc()));

	closebtn = new QPushButton(this);
	closebtn->setStyleSheet("border:2px groove gray;border-radius:11px;padding:2px 4px;");
	closebtn->setIcon(QIcon(QString(":/usercard/delnomal")));
	closebtn->setIconSize(QSize(22, 22));
	closebtn->setGeometry(99,0,22,22);
	connect(closebtn, SIGNAL(pressed()), this, SLOT(clspressfunc()));
	connect(closebtn, SIGNAL(released()), this, SLOT(clsreleasefunc()));
	closebtn->hide();

	username = new QLabel(this);
	username->setFixedSize(60, 10);
	username->setText(QString(" "));
	username->setGeometry(5, 144, 100, 14);

	editbtn = new QPushButton(this);
	editbtn->setIcon(QIcon(QString(":/usercard/edit")));
	editbtn->setGeometry(97 -13,108 - 13,26,26);
	editbtn->setStyleSheet("background-color:transparent");

	connect(editbtn, SIGNAL(pressed()), this, SLOT(editpressfunc()));
	connect(editbtn, SIGNAL(released()), this, SLOT(editreleasefunc()));
	editbtn->hide();

	
}

CUserCard::~CUserCard()
{

}

void CUserCard::setPixmap(QPixmap pix, int height /*= 110*/, int width /*= 110*/)
{
	midpic->setPixmap(pix);
}

void CUserCard::clsreleasefunc()
{
	closebtn->setIcon(QIcon(QString(":/usercard/delnomal")));
}

void CUserCard::clspressfunc()
{
	closebtn->setIcon(QIcon(QString(":/usercard/delclicked")));
}

void CUserCard::editpressfunc()
{
	editbtn->setIcon(QIcon(QString(":/usercard/editselected")));
}

void CUserCard::editreleasefunc()
{
	editbtn->setIcon(QIcon(QString(":/usercard/edit")));
}

void CUserCard::midclickfunc()
{
	
	if (!ismidselected)
	{
		midpic->setStyleSheet("border-width: 1px;   border-style: solid;   border-color: rgb(88,178, 255);");
		closebtn->show();
		editbtn->show();
		ismidselected = 1;
		return;
	}
	if (ismidselected)
	{
		midpic->setStyleSheet("border-width: 1px;   border-style: solid;   border-color: rgba(88,178, 255,100);");
		closebtn->hide();
		editbtn->hide();
		ismidselected = 0;
		return;
	}
	
}

void CUserCard::setText(QString str)
{
		username->setText(str);
}