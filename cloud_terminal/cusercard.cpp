#include "cusercard.h"
#include "clabel.h"
#include <QPushButton>

CUserCard* CUserCard::curselect = NULL;

CUserCard::CUserCard(int state,QWidget *parent)
	: QWidget(parent)
{
	noclickstate = state;
	this->setMinimumSize(121, 155);
	ismidselected = 0;
	midpic = new MyLabel(this);
	midpic->setPixmap(QPixmap(QString(":/usercard/defaultpic")));
	midpic->setGeometry(0, 10, 110, 110);
	midpic->setStyleSheet("border-width: 1px;   border-style: solid;   border-color: rgba(88,178, 255,100);");

	if (!noclickstate)
	{
		connect(midpic, SIGNAL(clicked()), this, SLOT(midclickfunc()));
	}

	closebtn = new QPushButton(this);
	closebtn->setStyleSheet("border:2px groove gray;border-radius:11px;padding:2px 4px;");
	closebtn->setIcon(QIcon(QString(":/usercard/delnomal")));
	closebtn->setIconSize(QSize(22, 22));
	closebtn->setGeometry(99,0,22,22);
	connect(closebtn, SIGNAL(pressed()), this, SLOT(clspressfunc()));
	connect(closebtn, SIGNAL(released()), this, SLOT(clsreleasefunc()));
	closebtn->hide();

	username = new QLabel(this);
	username->setFixedSize(280, 20);
	username->setStyleSheet("background-color:transparent;color:rgb(228,228,228);font-size:20px;border:0px;");
	username->setText(QString(" "));
	username->setGeometry(5, 135, 280, 20);

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


		if ((CUserCard::GetCurSelectCard() != NULL) 
			&& CUserCard::GetCurSelectCard() != this)
		{
			CUserCard::GetCurSelectCard()->midclickfunc();
		}
		CUserCard::SetCurSelectCard(this);

		return;
	}
	if (ismidselected)
	{
		midpic->setStyleSheet("border-width: 1px;   border-style: solid;   border-color: rgba(88,178, 255,100);");
		closebtn->hide();
		editbtn->hide();
		CUserCard::SetCurSelectCard(NULL);
		ismidselected = 0;
		return;
	}
	
}

void CUserCard::setText(QString str)
{
	username->setText(str);
}

CUserCard* CUserCard::GetCurSelectCard()
{
	return curselect;
}

void CUserCard::SetCurSelectCard(CUserCard* card)
{
	curselect = card;
}