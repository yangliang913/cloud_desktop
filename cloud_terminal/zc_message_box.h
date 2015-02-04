/*
* 文件名称：zc_message_box.h
* 描述：实现了自定义的消息对话框
*/

#ifndef ZCMESSAGEBOX_H
#define ZCMESSAGEBOX_H


#include <QString>
#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QThread>
#include <QDialog>
#include <QtCore> 
#include <QtGui>
#include <QGroupBox>
#include <QtGlobal>
#include <QMainWindow>
#include <QThread>
#include <QHBoxLayout>
#include <QApplication>
class QAction;
class QDialogButtonBox;
class QGroupBox;
class QLabel;
class QLineEdit;
class QMenu;
class QMenuBar;
class QPushButton;
class QTextEdit;
class QTabWidget;


class ZCMessageBox : public QDialog
{
	Q_OBJECT;
public:
	explicit ZCMessageBox(QString msg ="");
	~ZCMessageBox();

signals:
	public slots:
		void downDialogSlot();
		void closeDialogSlot();


private:
	void createDialog();
	void setDialogMessage(QString msg);

	QWidget *dialogWidget;
	QString dialogMessage;
	QPushButton *dialogButton;
	QPushButton *dialogClose;
};

#endif
