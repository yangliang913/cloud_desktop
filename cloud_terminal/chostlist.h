#ifndef CHOSTLIST_H
#define CHOSTLIST_H

#include <QWidget>
#include <QVBoxLayout>
#include <QDialog>
#define ITEM_W 480
#define ITEM_H 50
class CHostList : public QDialog
{
	Q_OBJECT

public:
	CHostList(QWidget *parent = 0);
	~CHostList();
	
	void AddCloudItem(QString name);
	void endAdd();
public slots:
	void clickfunc();

private:
	int itemcount;
	QVBoxLayout* main_layout;
	QPushButton* curselectbtn;

};

#endif // CHOSTLIST_H
