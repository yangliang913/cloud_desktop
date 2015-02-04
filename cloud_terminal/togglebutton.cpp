#include "togglebutton.h"
QString g_zcSysFontFamily = QStringLiteral("΢���ź�");

ToggleButton::ToggleButton(int type, QString str, QWidget *parent)
	: QPushButton(parent)
{
	btnType = type;
	btnStr = str;
	isChecked = false;
	strStartPoint.setX(0);
	strStartPoint.setY(0);
	bandwidthLineEdit = NULL;
}

ToggleButton::~ToggleButton()
{

}

void ToggleButton::setBtnChecked()
{
	isChecked = TRUE;
	this->update();
}

void ToggleButton::setBtnUnchecked()
{
	isChecked = FALSE;
	this->update();
}

bool ToggleButton::isBtnChecked()
{
	return isChecked;
}

//��ǰ�Ƿ�ͼ�����͵ģ����ڲ����ˣ�Ϊ�˺���ǰ���ݣ��Ժ���ʱ������
void ToggleButton::paintEvent ( QPaintEvent * )
{
	QString fontFamily = g_zcSysFontFamily;
	int fontSize = 12;
	if (btnType == CpuBtnType)
	{
		if (isChecked)
		{
			QPainter painter(this);  
			painter.setRenderHint(QPainter::Antialiasing, true);  
			painter.drawPixmap(0, 0, 84, 28, QPixmap("./Resources/config_res/cpu_btn_click.png"));
			QStaticText *text = new QStaticText(btnStr);
			text->setTextFormat(Qt::AutoText);
			text->setTextWidth(84);
			QFont font;
			font.setFamily(fontFamily);
			font.setPointSize(fontSize);
			painter.setFont(font);
			painter.setPen(QColor(98, 98, 98));
			adjustStartPoint(84, 28, fontSize, btnStr.size());
			painter.drawStaticText(QPoint(strStartPoint.x(), strStartPoint.y()), *text);
		}
		else
		{
			QPainter painter(this);  
			painter.setRenderHint(QPainter::Antialiasing, true);  
			painter.drawPixmap(0, 0, 84, 28, QPixmap("./Resources/config_res/cpu_btn.png"));
			QStaticText *text = new QStaticText(btnStr);
			text->setTextFormat(Qt::AutoText);
			text->setTextWidth(84);
			QFont font;
			font.setFamily(fontFamily);
			font.setPointSize(fontSize);
			painter.setFont(font);
			painter.setPen(QColor(98, 98, 98));
			adjustStartPoint(84, 28, fontSize, btnStr.size());
			painter.drawStaticText(QPoint(strStartPoint.x(), strStartPoint.y()), *text);
		}
	}
	else if (btnType == MemBtnType)
	{
		if (isChecked)
		{
			QPainter painter(this);  
			painter.setRenderHint(QPainter::Antialiasing, true);  
			painter.drawPixmap(0, 0, 84, 28, QPixmap("./Resources/config_res/mem_btn_click.png"));
			QStaticText *text = new QStaticText(btnStr);
			text->setTextFormat(Qt::AutoText);
			text->setTextWidth(84);
			QFont font;
			font.setFamily(fontFamily);
			font.setPointSize(fontSize);
			painter.setFont(font);
			painter.setPen(QColor(98, 98, 98));
			adjustStartPoint(84, 28, fontSize, btnStr.size());
			painter.drawStaticText(QPoint(strStartPoint.x(), strStartPoint.y()), *text);
		}
		else
		{
			QPainter painter(this);  
			painter.setRenderHint(QPainter::Antialiasing, true);  
			painter.drawPixmap(0, 0, 84, 28, QPixmap("./Resources/config_res/mem_btn.png"));
			QStaticText *text = new QStaticText(btnStr);
			text->setTextFormat(Qt::AutoText);
			text->setTextWidth(84);
			QFont font;
			font.setFamily(fontFamily);
			font.setPointSize(fontSize);
			painter.setFont(font);
			painter.setPen(QColor(98, 98, 98));
			adjustStartPoint(84, 28, fontSize, btnStr.size());
			painter.drawStaticText(QPoint(strStartPoint.x(), strStartPoint.y()), *text);
		}
	}
	else if (btnType == BandwidthEditBtnType)
	{
			QPainter painter(this);  
			painter.setRenderHint(QPainter::Antialiasing, true);  
			painter.drawPixmap(0, 0, 84, 28, QPixmap("./Resources/config_res/cpu_btn_click.png"));
			QStaticText *text = new QStaticText(btnStr);
			text->setTextFormat(Qt::AutoText);
			text->setTextWidth(84);
			QFont font;
			font.setFamily(fontFamily);
			font.setPointSize(fontSize);
			painter.setFont(font);
			painter.setPen(QColor(98, 98, 98));
			adjustStartPoint(84, 28, fontSize, btnStr.size());
			painter.drawStaticText(QPoint(strStartPoint.x(), strStartPoint.y()), *text);
	}
}

void ToggleButton::switchCheck()
{
	isChecked = !isChecked;
}

void ToggleButton::adjustStartPoint(int width, int height, int fontSize, int fontNum)
{
	strStartPoint.setX((width - fontSize * fontNum) / 2 + 2);
	strStartPoint.setY((height - fontSize) / 2 - 5); 
}