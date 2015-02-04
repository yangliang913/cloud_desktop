#ifndef NETWORK_H_
#define NETWORK_H_

#include <QObject>
#include <QString>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QByteArray>
#include "parsejson.h"
#include "common.h"
#include "log.h"

class ParseJson;

class ZcNetwork : public QObject
{
	Q_OBJECT

public:
	ZcNetwork(QObject *parent = 0);
signals:
	void notifyUi(int, int);
	void notifyControlHostUi(int, int);

	public slots:
	void replyFinished(QNetworkReply* reply);
public:
	void parseJson(int cmd, QString strUrl);

	LoginAuth			*loginData;
	TotalHostMessage	*totalHostData;
	ControlHostMsg		*controlHostData;
	HostPrice			*hostPrice;
	ProgressVersion     *progressVersion;
	int					prevCommand;		//ǰһ������
private:
	QString errorToChinese(int error);
	void freeStructMemory(void *mem);
private:
	QNetworkAccessManager* m_manager;
	//�������1Ϊ��Ȩ��2Ϊ��ȡ��������Ϣ������Ϊ����
	int command;
	ParseJson* parserJson;
};

#endif