#ifndef CUSERPICPANEL_H
#define CUSERPICPANEL_H

#include <QWidget>
#include "mylabel.h"


class CSiglePic : public QWidget
{
	Q_OBJECT

public:
	CSiglePic(QWidget *parent = 0);
	~CSiglePic();
	void setPixmap(QPixmap pix);

	QPixmap* getPix(){ return &curpix; };

	static void SetCurSelectPic(CSiglePic* pic);
	static CSiglePic* GetCurSelectPic();
	
	
private:
	MyLabel* piclabel;
	int ismidselected;
	static CSiglePic* curpic;
	QPixmap curpix;
public slots:
	void clickfunc();
};




class CUserPicPanel : public QWidget
{
	Q_OBJECT

public:
	CUserPicPanel(QWidget *parent = 0);
	~CUserPicPanel();

private:	
};

#endif // CUSERPICPANEL_H
