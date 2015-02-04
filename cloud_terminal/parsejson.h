#ifndef __MYPARSEJSON_H__
#define __MYPARSEJSON_H__

#include <QObject>
#include <QString>
#include <QByteArray>

#include <QString>
#include <QtGlobal>
#include <QtDebug>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonParseError>
#include <QJsonObject>
#include <QStringList>

#include "common.h"

class ParseJson : public QObject
{
	Q_OBJECT

public:
	ParseJson(QObject *parent = 0);
public:
	bool loginJsonToStruct(QByteArray loginAuth, LoginAuth **loginAuth_tmp);//解析json数据到结构体中
	bool showJsonToStruct(QByteArray totalHostMsg, TotalHostMessage **totalHostMsg_struct);
	bool controlJsonToStruct(QByteArray data, ControlHostMsg **controlHostMsg_struct);
	bool queryJsonToStruct(QByteArray priceData, HostPrice **queryHostPrice_struct);
	bool queryVersionToStruct(QByteArray versionData, ProgressVersion **queryVersion_struct);
private:
	QJsonParseError jsonError;
	QJsonDocument jsonDoc;
};

#endif