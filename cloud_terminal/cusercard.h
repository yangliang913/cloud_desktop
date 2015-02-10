#ifndef CUSERCARD_H
#define CUSERCARD_H

#include <QWidget>
#include "clabel.h"
#include <QPushButton>
#include "mylabel.h"
#include <QString>

class CUserCard : public QWidget
{
	Q_OBJECT

public:
	explicit CUserCard(int noclickstate = 0,QWidget *parent = 0);
	~CUserCard();

	void setPixmap(QPixmap pix,int height = 110,int width = 110);
	void setText(QString str);

	static CUserCard* GetCurSelectCard();
	static void SetCurSelectCard(CUserCard* card);

public slots:
	void clspressfunc();
	void clsreleasefunc();
	void editpressfunc();
	void editreleasefunc();
	void midclickfunc();
	
private:
	MyLabel* midpic;
	QPushButton* closebtn;
	QPushButton* editbtn;
	QLabel*		username;
	int ismidselected;
	static CUserCard* curselect;
	int noclickstate;
};

#endif // CUSERCARD_H
