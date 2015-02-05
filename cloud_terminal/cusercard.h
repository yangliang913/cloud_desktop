#ifndef CUSERCARD_H
#define CUSERCARD_H

#include <QWidget>
#include "clabel.h"
#include <QPushButton>

class MyLabel : public QLabel
{ 
	Q_OBJECT
public:
		MyLabel(QWidget * parent = 0);
private:

protected:
	virtual void mouseReleaseEvent(QMouseEvent * ev);
signals:
	void clicked(void); 
};

class CUserCard : public QWidget
{
	Q_OBJECT

public:
	explicit CUserCard(QWidget *parent = 0);
	~CUserCard();

	void setPixmap(QPixmap pix,int height = 110,int width = 110);
	void setText(QString str);


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
};

#endif // CUSERCARD_H
