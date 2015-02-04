#include <qmath.h>
#include "zc_message_box.h"
#include <QDesktopWidget>

ZCMessageBox ::ZCMessageBox(QString msg)
{
	dialogMessage = msg;
	createDialog();
	QHBoxLayout *layout = new QHBoxLayout;
	layout->setContentsMargins(0, 0, 0, 0);
	
	//dialogWidget->setVisible(FALSE);
	layout->addWidget(dialogWidget);
	this->setLayout(layout);
	this->setFixedSize(246, 150);
	this->setWindowFlags(Qt::FramelessWindowHint);		//把窗口设置成没框架的
	this->setAttribute(Qt::WA_TranslucentBackground,true);		//背景透明
	//this->setStyleSheet("background-color:transparent;");
	//this->setWindowOpacity(0.7);		//所有的东西全都设置为了半透明
	QDesktopWidget* desktop = QApplication::desktop();
	QRect deskrect = desktop->availableGeometry();
	//printf("--------------------msgbox: %d\n", deskrect.width());
	//居中显示
	this->move((deskrect.width() - this->width())/2, (deskrect.height() - this->height())/2);
}

ZCMessageBox::~ZCMessageBox()
{

}

void ZCMessageBox :: createDialog()
{
	dialogWidget = new QWidget;
	dialogWidget->setObjectName("dialogWidget");
	dialogWidget->setStyleSheet("QWidget#dialogWidget{border-image: url(:/dialog_res/dialogBackground);background-color:transparent;}");
	 
	
	QLabel *dialogLabel = new QLabel(dialogWidget);
	dialogLabel->setGeometry(0,94, 240, 20);
	dialogLabel->setStyleSheet("font-size:12.5px");
	dialogLabel->setText(dialogMessage);
	dialogLabel->setAlignment(Qt::AlignHCenter);

	//确定按钮
	dialogButton = new QPushButton(dialogWidget);
	dialogButton->setGeometry(0, 114, 246, 36);
	dialogButton->setObjectName("btn");
	dialogButton->setStyleSheet("QPushButton#btn{border-image: url(:/dialog_res/dialogButton);}"
		"QPushButton#btn:pressed{border-image: url(:/dialog_res/dialogButton_pressed);}");
	/*dialogButton->setIcon(QPixmap("Resources/dialog_res/dialogButton.png"));
	dialogButton->setIconSize(QPixmap("Resources/dialog_res/dialogButton.png").size());*/

	//关闭按钮
	dialogClose = new QPushButton(dialogWidget);
	//dialogClose->setStyleSheet("background-color:transparent");
	dialogClose->setGeometry(230,4,12, 12);
	dialogClose->setObjectName("close");	
	dialogClose->setStyleSheet("QPushButton#close{border-image: url(:/dialog_res/dialogClose);}"
		"QPushButton#close:hover{border-image: url(:/dialog_res/dialogClose_hover);}");
	//dialogClose->setIcon(QPixmap("Resources/dialog_res/dialogClose.png"));
	//dialogClose->setIconSize(QPixmap("Resources/dialog_res/dialogClose.png").size());

	connect(dialogButton,SIGNAL(clicked()),SLOT(downDialogSlot()));
	connect(dialogClose,SIGNAL(clicked()),SLOT(closeDialogSlot()));

}

void ZCMessageBox::downDialogSlot()
{
	dialogButton->move(dialogButton->x()+1, dialogButton->y());
	QTime t;
	t.start();
	while(t.elapsed()<200)
		QCoreApplication::processEvents(); 
	dialogButton->move(dialogButton->x()-1, dialogButton->y());
	close();
}

void ZCMessageBox::closeDialogSlot()
{
	dialogClose->move(dialogClose->x()+1, dialogClose->y());
	QTime t;
	t.start();
	while(t.elapsed()<200)
		QCoreApplication::processEvents(); 
	dialogClose->move(dialogClose->x()-1, dialogClose->y());
	close();
}
