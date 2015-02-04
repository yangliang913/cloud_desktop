#ifndef MYCLICKLABEL_H
#define MYCLICKLABEL_H

#include <QLabel>
#include <QtGui>
#include <QtGlobal>
#include <QString>

class QLabel;
class QWidget;
class QEvent;


/*************************************************
Class Name�� MyClickLabel
Description: ���е�����Ӧ�ı�ǩ��
*************************************************/
class MyClickLabel : public QLabel
{
	Q_OBJECT
public:
	explicit MyClickLabel(QWidget *parent = 0);
	MyClickLabel(const QString &text, QWidget *parent=0);
signals:
	// ��굥���ź�
	void clicked();//IMClickLabel* label);

protected:
	// ��굥���¼�
	void mouseReleaseEvent(QMouseEvent *);
	void enterEvent(QEvent *);
	void leaveEvent(QEvent *);
	public slots:

};

#endif // IMCLICKLABEL_H
