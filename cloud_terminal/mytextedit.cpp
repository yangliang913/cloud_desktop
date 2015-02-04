#include "mytextedit.h"

CMyTextEdit::CMyTextEdit(QString img, QString text, int wid, int hei, QWidget *parent)
	: QWidget(parent)
{
	imgPath = img;
	width = wid;
	height = hei;
	showText = text;

	this->setFixedSize(width, height);
	this->setAutoFillBackground(true);

	QPalette palette;
	palette.setBrush(QPalette::Background, QBrush(QPixmap(imgPath)));
	this->setPalette(palette);
	inputEdit = new QLineEdit();
	inputEdit->setPlaceholderText(showText);
	inputEdit->setStyleSheet("background-color:transparent;color:white;font-size:12px;border:0px;");
	QHBoxLayout *hLayout = new QHBoxLayout;
	hLayout->setAlignment(Qt::AlignCenter);
	hLayout->addWidget(inputEdit);
	this->setLayout(hLayout);
}

CMyTextEdit::~CMyTextEdit()
{

}
