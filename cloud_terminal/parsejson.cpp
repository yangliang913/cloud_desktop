#include <iostream>
#include <QString>
#include <QtGlobal>
#include <QDebug>
#include <QMessageBox>
#include <string>

#include "parsejson.h"
#include "stdlib.h"
#include "log.h"
using namespace std;

ParseJson::ParseJson(QObject *parent):
QObject(parent)
{
}

//使用Qt5自带的json库解析json
bool ParseJson::loginJsonToStruct(QByteArray data, LoginAuth **loginAuth_tmp)
{
	//int i = 0;
	LoginAuth *loginAuth = NULL;
	QByteArray loginJsonData;
	loginJsonData = data;
	int conectionsSize;
	if (*loginAuth_tmp != NULL)
	{
	free(*loginAuth_tmp);
	*loginAuth_tmp = NULL;
	}
	jsonDoc = QJsonDocument::fromJson(loginJsonData, &jsonError);

	if (jsonError.error == QJsonParseError::NoError)
	{
		if (jsonDoc.isObject())
		{
			QJsonObject jsonObj = jsonDoc.object();
			int connSize = 0;

			//先获取大小，即链接的个数
			QJsonObject::iterator it = jsonObj.begin();
			while (it != jsonObj.end())
			{
				switch (it.value().type())
				{
				case QJsonValue::Array:
				{
						QString key = it.key();
						if (key == "connections")
						{
							connSize = it.value().toArray().size();
						}
						break;
				}
					
				default:
					qDebug() << "This is impossiable";
					break;
				}

				it++;
			}
			loginAuth = (struct LoginAuth *)malloc(sizeof(struct LoginAuth) + sizeof(struct Connections)*connSize);
			memset(loginAuth, 0, sizeof(struct LoginAuth) + sizeof(struct Connections)*connSize);
			loginAuth->connectionsNum = connSize;

			//赋值
			it = jsonObj.begin();
			while (it != jsonObj.end())
			{
				switch (it.value().type())
				{
				case QJsonValue::String:
				{
										   QString key = it.key();
										   if (key == "status")
										   {
											   strcpy_s(loginAuth->status, sizeof(loginAuth->status), it.value().toString().toLocal8Bit().data());
										   }
										   else if (key == "message")
										   {
											   strcpy_s(loginAuth->message, sizeof(loginAuth->message), it.value().toString().toLocal8Bit().data());
										   }
				}
				case QJsonValue::Object:
				{
					if (it.key() == "control_server")
					{
						QJsonValue csValue = it.value();
						if (csValue.isObject())
						{
							QJsonObject csObj = csValue.toObject();
							QJsonObject::iterator csIt = csObj.begin();
							while (csIt != csObj.end())
							{
								if (csIt.key() == "external_address")
								{
									strcpy_s(loginAuth->server.externalAddress, sizeof(loginAuth->server.externalAddress), csIt.value().toString().toLocal8Bit().data());
								}
								else if (csIt.key() == "internal_address")
								{
									strcpy_s(loginAuth->server.internalAddress, sizeof(loginAuth->server.internalAddress), csIt.value().toString().toLocal8Bit().data());
								}
								csIt++;
							}
						}
					}
						break;
				}
				case QJsonValue::Array:
				{
										  QString key = it.key();
										  if (key == "connections")
										  {
											  QJsonArray connArray = it.value().toArray();
											  //QJsonValue tmp = connArray.at(1);
											  for (int i = 0; i < connArray.size(); i++)
											  {
												  QJsonValue arrayValue= connArray.at(i);
												  if (arrayValue.isObject())
												  {
													  QJsonObject connObject = arrayValue.toObject();
													  QJsonObject::iterator connIt = connObject.begin();
													  while (connIt != jsonObj.end())
													  {
														  if (connIt.value().type() == QJsonValue::String)
														  {
															  if (connIt.key() == "display_name")
															  {
																  strcpy_s(loginAuth->connections[i].displayName, sizeof(loginAuth->connections[i].displayName), connIt.value().toString().toLocal8Bit().data());
															  }
															  else if (connIt.key() == "display_password")
															  {
																  strcpy_s(loginAuth->connections[i].displayPassword, sizeof(loginAuth->connections[i].displayPassword), connIt.value().toString().toLocal8Bit().data());
															  }
															  else if (connIt.key() == "external_address")
															  {
																  strcpy_s(loginAuth->connections[i].externalAddress, sizeof(loginAuth->connections[i].externalAddress), connIt.value().toString().toLocal8Bit().data());
															  }
															  else if (connIt.key() == "internal_address")
															  {
																  strcpy_s(loginAuth->connections[i].internalAddress, sizeof(loginAuth->connections[i].internalAddress), connIt.value().toString().toLocal8Bit().data());
															  }
														  }

														  connIt++;
													  }
												  }
											  }
										  }
										  break;
				}

				default:
					qDebug() << "This is impossiable";
					break;
				}

				it++;
			}
		}

		*loginAuth_tmp = loginAuth;
		if ((loginAuth->status)[0] == 's')
		{
			return true;
		}
		else
			return false;
	}
	return false;
}

bool ParseJson::showJsonToStruct(QByteArray data, TotalHostMessage **totalHostMsg_struct)
{
	QByteArray totalHostMsg;
	totalHostMsg = data;
	jsonDoc = QJsonDocument::fromJson(totalHostMsg, &jsonError);
	if (*totalHostMsg_struct != NULL)
	{
	free(*totalHostMsg_struct);
	*totalHostMsg_struct = NULL;
	}

	if (jsonError.error == QJsonParseError::NoError)
	{
		if (jsonDoc.isObject())
		{
			QJsonObject jsonObj = jsonDoc.object();
			QJsonObject::iterator it = jsonObj.begin();
			int hostSumNum = 0;
			int portSumNum = 0;
			//先算云主机的个数和端口的个数
			while (it != jsonObj.end())
			{
				switch (it.value().type())
				{
				case QJsonValue::Array:
					if (it.key() == "hosts")
					{
						QJsonArray hostsArray = it.value().toArray();
						hostSumNum = hostsArray.size();
						for (int i = 0; i < hostSumNum; i++)
						{
							QJsonValue hostValue = hostsArray.at(i);
							if (hostValue.isObject())
							{
								QJsonObject hostObj = hostValue.toObject();
								QJsonObject::iterator hostIt = hostObj.begin();
								while (hostIt != hostObj.end())
								{
									QString tmpStr = hostIt.key();
									if (hostIt.key() == "ports" && hostIt.value().isArray())
									{
										portSumNum += hostIt.value().toArray().size();
									}
									hostIt++;
								}
							}
						}
					}
					break;

				default:
					//qDebug() << "There may be some wrong!";
					break;
				}
				it++;
			}

			*totalHostMsg_struct = (struct TotalHostMessage *)malloc(sizeof(struct TotalHostMessage) + sizeof(struct HostMessage)*(hostSumNum)+sizeof(struct Ports)*(portSumNum));
			memset(*totalHostMsg_struct, 0, sizeof(struct TotalHostMessage) + sizeof(struct HostMessage)*(hostSumNum)+sizeof(struct Ports)*(portSumNum));
			(*totalHostMsg_struct)->hostNum = hostSumNum;
			//初始化和解析
			it = jsonObj.begin();
			while (it != jsonObj.end())
			{
				switch (it.value().type())
				{
				case QJsonValue::Array:
					if (it.key() == "hosts")
					{
						QJsonArray hostsArray = it.value().toArray();
						hostSumNum = hostsArray.size();
						for (int i = 0; i < hostSumNum; i++)
						{
							QJsonValue hostValue = hostsArray.at(i);
							if (hostValue.isObject())
							{
								QJsonObject hostObj = hostValue.toObject();
								QJsonObject::iterator hostIt = hostObj.begin();
								while (hostIt != hostObj.end())
								{
									QString hostKey = hostIt.key();
									/*if (hostIt.key() == "ports" && hostIt.value().isArray())
									{
									portSumNum += hostIt.value().toArray().size();
									}
									else*/
									//c++ switch不支持字符串，所以就用if判断吧
									if (hostKey == "uuid")
									{
										strcpy_s((*totalHostMsg_struct)->hostmsg[i].id, sizeof((*totalHostMsg_struct)->hostmsg[i].id), hostIt.value().toString().toLocal8Bit().data());
									}
									else if (hostKey == "host_name")
									{
										strcpy_s((*totalHostMsg_struct)->hostmsg[i].host_name, sizeof((*totalHostMsg_struct)->hostmsg[i].host_name), hostIt.value().toString().toLocal8Bit().data());
									}
									else if (hostKey == "type")
									{
										(*totalHostMsg_struct)->hostmsg[i].type = hostIt.value().toInt();
									}
									else if (hostKey == "account")
									{
										strcpy_s((*totalHostMsg_struct)->hostmsg[i].account, sizeof((*totalHostMsg_struct)->hostmsg[i].account), hostIt.value().toString().toLocal8Bit().data());
									}
									else if (hostKey == "password")
									{
										strcpy_s((*totalHostMsg_struct)->hostmsg[i].password, sizeof((*totalHostMsg_struct)->hostmsg[i].password), hostIt.value().toString().toLocal8Bit().data());
									}
									else if (hostKey == "cpu_core")
									{
										(*totalHostMsg_struct)->hostmsg[i].cpu_core = hostIt.value().toInt();
									}
									else if (hostKey == "cpu_usage")
									{
										(*totalHostMsg_struct)->hostmsg[i].cpu_usage = hostIt.value().toDouble() * 100;			//这儿的范围改为[0, 100]，因为后面的接口是这样的
									}
									else if (hostKey == "memory")
									{
										(*totalHostMsg_struct)->hostmsg[i].memory = hostIt.value().toDouble()/1024/1024/1024;
									}
									else if (hostKey == "memory_usage")
									{
										(*totalHostMsg_struct)->hostmsg[i].memory_usage = hostIt.value().toDouble() * 100;			//这儿的范围是[0, 100]，因为后面的接口是这样的
									}
									else if (hostKey == "sys_disk")
									{
										(*totalHostMsg_struct)->hostmsg[i].sys_disk = hostIt.value().toDouble()/1024/1024/1024;
									}
									else if (hostKey == "sys_disk_usage")
									{
										(*totalHostMsg_struct)->hostmsg[i].sys_disk_usage = hostIt.value().toDouble() * 100;		//这儿的范围是[0, 100]，因为后面的接口是这样的
									}
									else if (hostKey == "data_disk")
									{
										(*totalHostMsg_struct)->hostmsg[i].data_disk = hostIt.value().toDouble()/1024/1024/1024;
									}
									else if (hostKey == "data_disk_usage")
									{
										(*totalHostMsg_struct)->hostmsg[i].data_disk_usage = hostIt.value().toDouble() * 100;		//这儿的范围是[0, 100]，因为后面的接口是这样的
									}
									else if (hostKey == "bandwidth")
									{
										(*totalHostMsg_struct)->hostmsg[i].bandwidth = hostIt.value().toDouble()/1000/1000;
									}
									else if (hostKey == "is_auto_startup")
									{
										(*totalHostMsg_struct)->hostmsg[i].is_auto_startup = hostIt.value().toInt();
									}
									else if (hostKey == "running_status")
									{
										(*totalHostMsg_struct)->hostmsg[i].running_status = hostIt.value().toInt();
									}
									else if (hostKey == "status")
									{
										(*totalHostMsg_struct)->hostmsg[i].status = hostIt.value().toInt();
									}
									else if (hostKey == "region")
									{
										(*totalHostMsg_struct)->hostmsg[i].region = hostIt.value().toInt();
									}
									else if (hostKey == "inner_ip")
									{
										strcpy_s((*totalHostMsg_struct)->hostmsg[i].inner_ip, sizeof((*totalHostMsg_struct)->hostmsg[i].inner_ip), hostIt.value().toString().toLocal8Bit().data());
									}
									else if (hostKey == "inner_port")
									{
										strcpy_s((*totalHostMsg_struct)->hostmsg[i].inner_port, sizeof((*totalHostMsg_struct)->hostmsg[i].inner_port), hostIt.value().toString().toLocal8Bit().data());
									}
									else if (hostKey == "outer_ip")
									{
										strcpy_s((*totalHostMsg_struct)->hostmsg[i].outer_ip, sizeof((*totalHostMsg_struct)->hostmsg[i].outer_ip), hostIt.value().toString().toLocal8Bit().data());
									}
									else if (hostKey == "outer_port")
									{
										//char *tmp1 = hostIt.value().toString().toLocal8Bit().data();
										int out_port = hostIt.value().toInt();
										char str[8] = { 0 };
										itoa(out_port, str, 10);
										//MyZCLog::Instance().WriteToLog(ZCINFO, "out_port");
										//MyZCLog::Instance().WriteToLog(ZCINFO, str);
										strcpy_s((*totalHostMsg_struct)->hostmsg[i].outer_port, sizeof((*totalHostMsg_struct)->hostmsg[i].outer_port), str);
									}
									else if (hostKey == "sysImageName")
									{
										strcpy_s((*totalHostMsg_struct)->hostmsg[i].sysImageName, sizeof((*totalHostMsg_struct)->hostmsg[i].sysImageName), hostIt.value().toString().toLocal8Bit().data());
									}
									else if (hostKey == "inactivate_time")
									{
										strcpy_s((*totalHostMsg_struct)->hostmsg[i].inactivate_time, sizeof((*totalHostMsg_struct)->hostmsg[i].inactivate_time), hostIt.value().toString().toLocal8Bit().data());
									}
									else if (hostKey == "ports")
									{
										if (it.value().isArray())
										{
											QJsonArray portsArray = it.value().toArray();
											int portNum = portsArray.size();
											for (int j = 0; j < portNum; j++)
											{
												QJsonValue portValue = hostsArray.at(j);
												if (portValue.isObject())
												{
													QJsonObject portObj = portValue.toObject();
													QJsonObject::iterator portIt = portObj.begin();
													while (portIt != portObj.end())
													{
														QString portKey = portIt.key();
														if (portKey == "protocol")
														{
															(*totalHostMsg_struct)->hostmsg[i].ports[j].protocol = portIt.value().toInt();
														}
														else if (portKey == "port")
														{
															strcpy_s((*totalHostMsg_struct)->hostmsg[i].ports[j].port, sizeof((*totalHostMsg_struct)->hostmsg[i].ports[j].port), portIt.value().toString().toLocal8Bit().data());
														}
														else if (portKey == "server_port")
														{
															strcpy_s((*totalHostMsg_struct)->hostmsg[i].ports[j].server_port, sizeof((*totalHostMsg_struct)->hostmsg[i].ports[j].server_port), portIt.value().toString().toLocal8Bit().data());
														}
														else if (portKey == "outer_port")
														{
															strcpy_s((*totalHostMsg_struct)->hostmsg[i].ports[j].outer_port, sizeof((*totalHostMsg_struct)->hostmsg[i].ports[j].outer_port), portIt.value().toString().toLocal8Bit().data());
														}
														portIt++;
													}
												}
											}
										}
									}
									hostIt++;
								}
							}
						}
					}
					break;

				case QJsonValue::String:
				{
										   if (it.key() == "status")
										   {
											   strcpy_s((*totalHostMsg_struct)->status, sizeof((*totalHostMsg_struct)->status), it.value().toString().toLocal8Bit().data());
										   }
										   else if (it.key() == "message")
										   {
											   strcpy_s((*totalHostMsg_struct)->message, sizeof((*totalHostMsg_struct)->message), it.value().toString().toLocal8Bit().data());
										   }
										   break;
				}

				default:
					//qDebug() << "There may be some wrong!";
					break;
				}
				it++;
			}
		}
	}

	//QVariant result = parser->parse(totalHostMsg, &ok);
	//if (!ok)
	//{
	//	return false;
	//}
	//QVariantMap mymap = result.toMap();
	//hostSize = mymap["hosts"].toList().size();

	//int portsSumNum = 0;
	//foreach (QVariant hostMsg, mymap["hosts"].toList())
	//{
	//	QVariantMap hostMsgMap = hostMsg.toMap();
	//	portsSumNum += hostMsgMap["ports"].toList().size();

	//}

	///*if (*totalHostMsg_struct != NULL)
	//{
	//	delete *totalHostMsg_struct;
	//	*totalHostMsg_struct = NULL;
	//}*/
	////初始化结构体
	//*totalHostMsg_struct = (struct TotalHostMessage *)malloc(sizeof(struct TotalHostMessage)+sizeof(struct HostMessage)*(hostSize)+ sizeof(struct Ports)*(portsSumNum));
	//memset(*totalHostMsg_struct, 0, sizeof(struct TotalHostMessage)+sizeof(struct HostMessage)*(hostSize)+ sizeof(struct Ports)*(portsSumNum));
	//(*totalHostMsg_struct)->hostNum = hostSize;
	//strcpy((*totalHostMsg_struct)->status, mymap["status"].toString().toLocal8Bit().data());
	//strcpy((*totalHostMsg_struct)->message, mymap["message"].toString().toLocal8Bit().data());

	//foreach(QVariant hostMsg, mymap["hosts"].toList())
	//{
	//	QVariantMap hostMsgMap = hostMsg.toMap();
	//	strcpy((*totalHostMsg_struct)->hostmsg[i].host_name, hostMsgMap["host_name"].toString().toLocal8Bit().data());
	//	strcpy((*totalHostMsg_struct)->hostmsg[i].id, hostMsgMap["uuid"].toString().toLocal8Bit().data());
	//	(*totalHostMsg_struct)->hostmsg[i].type = atoi(hostMsgMap["type"].toString().toLocal8Bit().data());
	//	(*totalHostMsg_struct)->hostmsg[i].cpu_core = atoi(hostMsgMap["cpu_core"].toString().toLocal8Bit().data());
	//	(*totalHostMsg_struct)->hostmsg[i].cpu_usage = (int)((atof(hostMsgMap["cpu_usage"].toString().toLocal8Bit().data())) * 100);   //这儿的范围改为[0, 10]，因为后面的接口是这样
	//	(*totalHostMsg_struct)->hostmsg[i].memory = (int)(atof(hostMsgMap["memory"].toString().toLocal8Bit().data())/1024/1024/1024);//Byte转G
	//	(*totalHostMsg_struct)->hostmsg[i].memory_usage = (int)((atof(hostMsgMap["memory_usage"].toString().toLocal8Bit().data())) * 100); //这儿的范围改为[0, 10]，因为后面的接口是这样
	//	(*totalHostMsg_struct)->hostmsg[i].sys_disk = (int)(atof(hostMsgMap["sys_disk"].toString().toLocal8Bit().data())/1024/1024/1024);
	//	(*totalHostMsg_struct)->hostmsg[i].sys_disk_usage = (int)(atof(hostMsgMap["sys_disk_usage"].toString().toLocal8Bit().data())) * 100;  //这儿的范围改为[0, 10]，因为后面的接口是这样
	//	(*totalHostMsg_struct)->hostmsg[i].data_disk = (int)(atof(hostMsgMap["data_disk"].toString().toLocal8Bit().data())/1024/1024/1024);
	//	(*totalHostMsg_struct)->hostmsg[i].data_disk_usage = (int)((atof(hostMsgMap["data_disk_usage"].toString().toLocal8Bit().data())) * 100);
	//	(*totalHostMsg_struct)->hostmsg[i].bandwidth = (int)(atof(hostMsgMap["bandwidth"].toString().toLocal8Bit().data())/1000/1000);//Byte转M
	//	(*totalHostMsg_struct)->hostmsg[i].is_auto_startup = atoi(hostMsgMap["is_auto_startup"].toString().toLocal8Bit().data());
	//	(*totalHostMsg_struct)->hostmsg[i].running_status = atoi(hostMsgMap["running_status"].toString().toLocal8Bit().data());
	//	(*totalHostMsg_struct)->hostmsg[i].status = atoi(hostMsgMap["status"].toString().toLocal8Bit().data());
	//	(*totalHostMsg_struct)->hostmsg[i].region = atoi(hostMsgMap["region"].toString().toLocal8Bit().data());
	//	strcpy((*totalHostMsg_struct)->hostmsg[i].sysImageName, hostMsgMap["sysImageName"].toString().toLocal8Bit().data());
	//	strcpy((*totalHostMsg_struct)->hostmsg[i].inactivate_time, hostMsgMap["inactivate_time"].toString().toLocal8Bit().data());
	//	strcpy((*totalHostMsg_struct)->hostmsg[i].inner_ip, hostMsgMap["inner_ip"].toString().toLocal8Bit().data());
	//	strcpy((*totalHostMsg_struct)->hostmsg[i].inner_port, hostMsgMap["inner_port"].toString().toLocal8Bit().data());
	//	strcpy((*totalHostMsg_struct)->hostmsg[i].outer_ip, hostMsgMap["outer_ip"].toString().toLocal8Bit().data());
	//	strcpy((*totalHostMsg_struct)->hostmsg[i].outer_port, hostMsgMap["outer_port"].toString().toLocal8Bit().data());
	//	(*totalHostMsg_struct)->hostmsg[i].portsNum = hostMsgMap["ports"].toList().size();
	//	int j  = 0;
	//	/*//经测试此处foreach无效，改为for循环如下
	//	foreach(QVariant portsMsg, hostMsgMap["ports"].toList())
	//	{
	//		QVariantMap portsMsgMap = portsMsg.toMap();
	//		(*totalHostMsg_struct)->hostmsg[i].ports[j].protocol = atoi(portsMsgMap["protocol"].toString().toLocal8Bit().data());
	//		strcpy((*totalHostMsg_struct)->hostmsg[i].ports[j].port, portsMsgMap["port"].toString().toLocal8Bit().data());
	//		strcpy((*totalHostMsg_struct)->hostmsg[i].ports[j].server_port, portsMsgMap["server_port"].toString().toLocal8Bit().data());
	//		strcpy((*totalHostMsg_struct)->hostmsg[i].ports[j].outer_port, portsMsgMap["outer_port"].toString().toLocal8Bit().data());
	//		j++;
	//	}
	//	*///也许上面几个foreach（照着海军之前的格式写的)都达不到效果（未经测试因为没数据）
	//	for(;j < hostMsgMap["ports"].toList().size();)
	//	{
	//		QVariantMap portsMsgMap = hostMsgMap["ports"].toList()[j].toMap();
	//		(*totalHostMsg_struct)->hostmsg[i].ports[j].protocol = atoi(portsMsgMap["protocol"].toString().toLocal8Bit().data());
	//		strcpy((*totalHostMsg_struct)->hostmsg[i].ports[j].port, portsMsgMap["port"].toString().toLocal8Bit().data());
	//		strcpy((*totalHostMsg_struct)->hostmsg[i].ports[j].server_port, portsMsgMap["server_port"].toString().toLocal8Bit().data());
	//		strcpy((*totalHostMsg_struct)->hostmsg[i].ports[j].outer_port, portsMsgMap["outer_port"].toString().toLocal8Bit().data());
	//		j++;
	//	}
	//	i++;
	//}
	if (((*totalHostMsg_struct)->status)[0] == 's')
	{
		return true;
	}
	else 
		return false;
}

bool ParseJson::controlJsonToStruct(QByteArray data, ControlHostMsg **controlHostMsg_struct)
{
	QByteArray controlHostMsg;
	controlHostMsg = data;
	jsonDoc = QJsonDocument::fromJson(controlHostMsg, &jsonError);

	if (*controlHostMsg_struct != NULL)
	{
		free(*controlHostMsg_struct);
		*controlHostMsg_struct = NULL;
	}
	if (jsonError.error == QJsonParseError::NoError)
	{
		*controlHostMsg_struct = (struct ControlHostMsg *)malloc(sizeof(ControlHostMsg));
		memset(*controlHostMsg_struct, 0, sizeof(ControlHostMsg));
		QJsonObject controlObj = jsonDoc.object();
		QJsonObject::iterator it = controlObj.begin();
		while (it !=controlObj.end())
		{
			if (it.key() == "status")
			{
				strcpy_s((*controlHostMsg_struct)->status, sizeof((*controlHostMsg_struct)->status), it.value().toString().toLocal8Bit().data());
			}
			else if (it.key() == "message")
			{
				strcpy_s((*controlHostMsg_struct)->message, sizeof((*controlHostMsg_struct)->message), it.value().toString().toLocal8Bit().data());
			}
			it++;
		}
	}

	//QVariant result = parser->parse(controlHostMsg, &ok);
	//if (!ok)
	//{
	//	return false;
	//}
	///*if (*controlHostMsg_struct != NULL)
	//{
	//	delete *controlHostMsg_struct;
	//	*controlHostMsg_struct = NULL;
	//}*/

	//*controlHostMsg_struct = (struct ControlHostMsg *)malloc(sizeof(ControlHostMsg));
	//QVariantMap mymap = result.toMap();
	//strcpy((*controlHostMsg_struct)->status, mymap["status"].toString().toLocal8Bit().data());
	//strcpy((*controlHostMsg_struct)->message, mymap["message"].toString().toLocal8Bit().data());

	if (((*controlHostMsg_struct)->status)[0] == 's')
	{
		return true;
	}
	else 
		return false;
}

bool ParseJson::queryJsonToStruct(QByteArray priceData, HostPrice **queryHostPrice_struct)
{
	HostPrice *hostPrice = NULL;
	QByteArray queryHostPriceData;
	queryHostPriceData = priceData;
	jsonDoc = QJsonDocument::fromJson(queryHostPriceData, &jsonError);
	if (*queryHostPrice_struct != NULL)
	{
		free(*queryHostPrice_struct);
		*queryHostPrice_struct = NULL;
	}
	hostPrice = (struct HostPrice *)malloc(sizeof(struct HostPrice) + sizeof(struct Price));
	memset(hostPrice, 0, sizeof(struct HostPrice) + sizeof(struct Price));
	if (jsonError.error == QJsonParseError::NoError)
	{
		if (jsonDoc.isObject())
		{
			QJsonObject jsonObj = jsonDoc.object();
			QJsonObject::iterator it = jsonObj.begin();
			
			while (it != jsonObj.end())
			{
				switch (it.value().type())
				{
				case QJsonValue::String:
				{
										   QString key = it.key();
										   if (key == "status")
										   {
											   strcpy_s(hostPrice->status, sizeof(hostPrice->status), it.value().toString().toLocal8Bit().data());
										   }
										   else if (key == "message")
										   {
											   strcpy_s(hostPrice->message, sizeof(hostPrice->message), it.value().toString().toLocal8Bit().data());
										   }
				}
				case QJsonValue::Object:
				{
										   if (it.key() == "price")
										   {
											   QJsonValue priceValue = it.value();
											   if (priceValue.isObject())
											   {
												   QJsonObject priceObj = priceValue.toObject();
												   QJsonObject::iterator priceIt = priceObj.begin();
												   while (priceIt != priceObj.end())
												   {
													   if (priceIt.key() == "monthlyPrice")
													   {
														   hostPrice->price.monthlyPrice = priceIt.value().toDouble();
													   }
													   if (priceIt.key() == "balance")
													   {
														   hostPrice->price.balance = priceIt.value().toDouble();
													   }
													   priceIt++;
												   }
											   }
										   }
				}


				default:
					break;
				}
				it++;
			}

		}
		*queryHostPrice_struct = hostPrice;
		if ((hostPrice->status)[0] == 's')
		{
			return true;
		}
		else
			return false;
		
	}
	*queryHostPrice_struct = hostPrice;
	return false;
}

bool ParseJson::queryVersionToStruct(QByteArray versionData, ProgressVersion **queryVersion_struct)
{
	ProgressVersion *progressVersion = NULL;
	QByteArray queryProgressVersionData;
	queryProgressVersionData = versionData;
	jsonDoc = QJsonDocument::fromJson(queryProgressVersionData, &jsonError);
	if (*queryVersion_struct != NULL)
	{
		free(*queryVersion_struct);
		*queryVersion_struct = NULL;
	}
	progressVersion = (struct ProgressVersion *)malloc(sizeof(struct ProgressVersion) + sizeof(struct Versions));
	memset(progressVersion, 0, sizeof(struct ProgressVersion) + sizeof(struct Versions));
	if (jsonError.error == QJsonParseError::NoError)
	{
		if (jsonDoc.isObject())
		{
			QJsonObject jsonObj = jsonDoc.object();
			QJsonObject::iterator it = jsonObj.begin();

			while (it != jsonObj.end())
			{
				switch (it.value().type())
				{
				case QJsonValue::String:
				{
										   QString key = it.key();
										   if (key == "status")
										   {
											   strcpy_s(progressVersion->status, sizeof(progressVersion->status), it.value().toString().toLocal8Bit().data());
										   }
										   else if (key == "message")
										   {
											   strcpy_s(progressVersion->message, sizeof(progressVersion->message), it.value().toString().toLocal8Bit().data());
										   }
										  
				}
				case QJsonValue::Object:
				{
										   if (it.key() == "versions")
										   {
											   QJsonValue versionValue = it.value();
											   if (versionValue.isObject())
											   {
												   QJsonObject versionObj = versionValue.toObject();
												   QJsonObject::iterator versionIt = versionObj.begin();
												   while (versionIt != versionObj.end())
												   {
													   QString tmp = versionIt.key();
													   if (versionIt.key() == "updateinfo")
													   {
														   QString tmp = versionIt.value().toString().toUtf8();
														   QByteArray byteArray = tmp.toLocal8Bit();
														   char *tmp1 = byteArray.data();
														   //const char *tmp1 = str.c_str();
														   strcpy_s(progressVersion->versions.updateinfo, sizeof(progressVersion->versions.updateinfo), tmp1);
														 
														  // progressVersion->versions.updateinfo = tmp.toLocal8Bit().data();

													   }
													   if (versionIt.key() == "name")
													   {
														   strcpy_s(progressVersion->versions.name, sizeof(progressVersion->versions.name), versionIt.value().toString().toLocal8Bit().data());
													   }
													   if (versionIt.key() == "path")
													   {
														   strcpy_s(progressVersion->versions.path, sizeof(progressVersion->versions.path), versionIt.value().toString().toLocal8Bit().data());
													   }
													   versionIt++;
												   }
											   }
										   }
				}


				default:
					break;
				}
				it++;
			}
		}
		*queryVersion_struct = progressVersion;
		if ((progressVersion->status)[0] == 's')
		{
			return true;
		}
		else
			return false;

	}
	*queryVersion_struct = progressVersion;
	return false;
}