#include "cuserpicpanel.h"
#include <QGridLayout>

CSiglePic* CSiglePic::curpic = NULL;

CUserPicPanel::CUserPicPanel(QWidget *parent)
	: QWidget(parent)
{
	this->setFixedSize(355, 172);
	
	setAutoFillBackground(true);

	QPalette palette;
	palette.setBrush(QPalette::Background, QBrush(QPixmap(":/userpic/picbg")));
	this->setPalette(palette);


	QGridLayout* main_layout = new QGridLayout;
	main_layout->setContentsMargins(15, 52, 15, 15);


	for (int i = 0; i < 12; i++)
	{
		CSiglePic* pic = new CSiglePic;
		pic->setFixedSize(50, 50);
		pic->setPixmap(QPixmap(QString(":/userpic/p%1").arg(i + 1)).scaled(QSize(50, 50), Qt::IgnoreAspectRatio));
		main_layout->setSpacing(5);
		main_layout->addWidget(pic, i / 6, i % 6);
	}
	
	this->setLayout(main_layout);

}

CUserPicPanel::~CUserPicPanel()
{

}

CSiglePic::CSiglePic(QWidget *parent /*= 0*/)
{
	piclabel = new MyLabel(this);
	
	piclabel->setGeometry(0, 0, 50, 50);
	
	ismidselected = 0;
	piclabel->setStyleSheet("border-width: 1px;   border-style: solid;   border-color: rgba(88,178, 255,100);");

	connect(piclabel, SIGNAL(clicked()), this, SLOT(clickfunc()));
}

void CSiglePic::setPixmap(QPixmap pix)
{
	curpix = pix;
	piclabel->setPixmap(pix);
}

void CSiglePic::clickfunc()
{
	if (!ismidselected)
	{
		piclabel->setStyleSheet("border-width: 1px;   border-style: solid;   border-color: rgb(88,178, 255);");
		ismidselected = 1;

		if ((CSiglePic::GetCurSelectPic() != NULL)
			&& CSiglePic::GetCurSelectPic() != this)
		{
			CSiglePic::GetCurSelectPic()->clickfunc();
		}
		CSiglePic::SetCurSelectPic(this);

		return;
	}
	if (ismidselected)
	{
		piclabel->setStyleSheet("border-width: 1px;   border-style: solid;   border-color: rgba(88,178, 255,100);");
		ismidselected = 0;
		CSiglePic::SetCurSelectPic(NULL);
		return;
	}
}

CSiglePic::~CSiglePic()
{

}

void CSiglePic::SetCurSelectPic(CSiglePic* pic)
{
	curpic = pic;
}

CSiglePic* CSiglePic::GetCurSelectPic()
{
	return curpic;
}