#include "network.h"
#include <iostream>
#include <QDebug>
#include <QBuffer>
#include <QMutex>
#include <QMessageBox>
#include <QSsl>  
#include <QSslConfiguration>  
#include <QSslSocket>  
//#include <qt_windows.h>
#include <string>
using namespace std;
//#include "setdebugnew.h"

ZcNetwork::ZcNetwork(QObject *parent) :
QObject(parent)
{
	m_manager = new QNetworkAccessManager(this);
	command = -1;
	prevCommand = -1;
	loginData = NULL;
	totalHostData = NULL;
	controlHostData = NULL;
	hostPrice = NULL;
	progressVersion = NULL;
	//totalHostData = new TotalHostMessage;

	parserJson = new ParseJson(this);
	connect(m_manager, SIGNAL(finished(QNetworkReply*)),
		this, SLOT(replyFinished(QNetworkReply*)));
}

void ZcNetwork::replyFinished(QNetworkReply *reply)
{
	if(reply && reply->error() == QNetworkReply::NoError) 
	{
		QByteArray data = reply->readAll();
		//MyZCLog::Instance().WriteToLog(ZCINFO, data);
		if(command == Auth)
		{
			//freeStructMemory(loginData);
			bool login_succ = parserJson->loginJsonToStruct(data, &loginData);
			if (!login_succ)
			{
				MyZCLog::Instance().WriteToLog(ZCERROR, "login failed!");
				MyZCLog::Instance().WriteToLog(ZCINFO, data);
			}
			MyZCLog::Instance().WriteToLog(ZCINFO, data);
			
			prevCommand = Auth;
			emit notifyUi(login_succ, command);
		}
		else if (command == GetHostInfo)//获取云主机信息
		{
			//freeStructMemory(totalHostData);
			bool showMsg_succ = parserJson->showJsonToStruct(data, &totalHostData);
			
			if (!showMsg_succ)
			{
				MyZCLog::Instance().WriteToLog(ZCERROR, "get host info failed!");
			}
			MyZCLog::Instance().WriteToLog(ZCINFO, data);
			emit notifyUi(showMsg_succ, command);
		}
		else if (command == UpdateHostInfo)	//更新云主机信息
		{
			//freeStructMemory(totalHostData);
			bool updateMsg_succ = parserJson->showJsonToStruct(data, &totalHostData);
			emit notifyControlHostUi(updateMsg_succ, command);
		}
		else if (command == UpdateHostInfo2)
		{
			//freeStructMemory(totalHostData);
			bool updateMsg_succ = parserJson->showJsonToStruct(data, &totalHostData);
			emit notifyControlHostUi(updateMsg_succ, command);
		}
		else if (command == StartHost) //开启云主机
		{
			//freeStructMemory(controlHostData);
			prevCommand = StartHost;
			bool controlMsg_succ = parserJson->controlJsonToStruct(data, &controlHostData);
			emit notifyControlHostUi(controlMsg_succ, command);
		}
		else if (command == StopHost) //关闭云主机
		{
			//freeStructMemory(controlHostData);
			prevCommand = StopHost;
			bool controlMsg_succ = parserJson->controlJsonToStruct(data, &controlHostData);
			emit notifyControlHostUi(controlMsg_succ, command);
		}
		else if (command == RestartHost) //重启云主机
		{
			//freeStructMemory(controlHostData);
			prevCommand = RestartHost;
			bool controlMsg_succ = parserJson->controlJsonToStruct(data, &controlHostData);
			emit notifyControlHostUi(controlMsg_succ, command);
		}
		else if (command == ModifyHostConfig) //修改云主机配置
		{
			//freeStructMemory(controlHostData);
			prevCommand = ModifyHostConfig;
			bool controlMsg_succ = parserJson->controlJsonToStruct(data, &controlHostData);
			emit notifyControlHostUi(controlMsg_succ, command);
		}
		else if (command == ForceStopHost) //强制关闭云主机
		{
			//freeStructMemory(controlHostData);
			prevCommand = ForceStopHost;
			bool controlMsg_succ = parserJson->controlJsonToStruct(data, &controlHostData);
			emit notifyControlHostUi(controlMsg_succ, command);
		}
		else if (command == QueryHostPrice)  //查询当前配置主机时价格
		{
			prevCommand = QueryHostPrice;
			bool controlMsg_succ = parserJson->queryJsonToStruct(data, &hostPrice);
			emit notifyControlHostUi(controlMsg_succ, command);
		}
		else if (command == FirstQueryHostPrice)  //每次进入配置页面查询云主机价格
		{
			prevCommand = FirstQueryHostPrice;
			bool controlMsg_succ = parserJson->queryJsonToStruct(data, &hostPrice);
			emit notifyControlHostUi(controlMsg_succ, command);
		}
		else if (command == QueryLastVersion) //查询最新版本号
		{
			prevCommand = QueryLastVersion;
			MyZCLog::Instance().WriteToLog(ZCINFO, data);
			bool controlMsg_succ = parserJson->queryVersionToStruct(data, &progressVersion);
			emit notifyControlHostUi(controlMsg_succ, command);
		}
	}
	else 
	{
		prevCommand = -1;
		QByteArray data = reply->readAll();
		int err = reply->error();
		QString errStr = QStringLiteral("连接失败！");
		errStr += errorToChinese(err);
		//写日志时加上错误码
		QString logStr = errStr + QStringLiteral("  错误码：");
		logStr += QString::number(err, 10);
		MyZCLog::Instance().WriteToLog(ZCERROR, logStr);
		emit notifyUi(2, command);
		QMessageBox::information(NULL, QStringLiteral("致云"), errStr, QMessageBox::Ok);
	}
	reply->close();
}

//cmd 操作命令：1为鉴权，2为获取云主机信息
void ZcNetwork::parseJson(int cmd, QString strUrl)
{
	QNetworkRequest request;
	command = cmd;
	printf("%s\n", strUrl.toLatin1().data());
	request.setUrl(QUrl(strUrl));
	//设置头信息
	MyZCLog::Instance().WriteToLog(ZCINFO, strUrl);
	QSslConfiguration config;

	config.setPeerVerifyMode(QSslSocket::VerifyNone);
	config.setProtocol(QSsl::TlsV1SslV3);
	request.setSslConfiguration(config);
	request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
	MyZCLog::Instance().WriteToLog(ZCINFO, strUrl);
	m_manager->get(request);
}

QString ZcNetwork::errorToChinese(int error)
{
	QString errStr= "";
	switch (error)
	{
	case QNetworkReply::ConnectionRefusedError:
		errStr = QStringLiteral("连接被拒绝！");
		break;
	case QNetworkReply::RemoteHostClosedError:
		errStr = QStringLiteral("远程主机被关闭！");
		break;
	case QNetworkReply::HostNotFoundError:
		errStr = QStringLiteral("没找到主机！");
		break;
	case QNetworkReply::TimeoutError:
		errStr = QStringLiteral("连接超时！");
		break;
	case QNetworkReply::OperationCanceledError:
		errStr = QStringLiteral("操作取消！");
		break;
	case QNetworkReply::SslHandshakeFailedError:
		errStr = QStringLiteral("SSL握手失败！");
		break;
	case QNetworkReply::TemporaryNetworkFailureError:
		errStr = QStringLiteral("临时网络失败！");
		break;
	case QNetworkReply::ProxyConnectionRefusedError:
		errStr = QStringLiteral("代理连接被拒绝！");
		break;
	case QNetworkReply::ProxyConnectionClosedError:
		errStr = QStringLiteral("代理连接被关闭！");
		break;
	case QNetworkReply::ProxyNotFoundError:
		errStr = QStringLiteral("没找到代理！");
		break;
	case QNetworkReply::ProxyTimeoutError:
		errStr = QStringLiteral("代理超时！");
		break;
	case QNetworkReply::ProxyAuthenticationRequiredError:
		errStr = QStringLiteral("代理验证请求错误！");
		break;
	case QNetworkReply::ContentAccessDenied:
		errStr = QStringLiteral("拒绝访问内容！");
		break;
	case QNetworkReply::ContentOperationNotPermittedError:
		errStr = QStringLiteral("拒绝操作内容！");
		break;
	case QNetworkReply::ContentNotFoundError:
		errStr = QStringLiteral("没找到内容！");
		break;
	case QNetworkReply::AuthenticationRequiredError:
		errStr = QStringLiteral("验证请求错误！");
		break;
	case QNetworkReply::ContentReSendError:
		errStr = QStringLiteral("内容重发错误！");
		break;
	case QNetworkReply::ProtocolUnknownError:
		errStr = QStringLiteral("未知协议！");
		break;
	case QNetworkReply::ProtocolInvalidOperationError:
		errStr = QStringLiteral("协议不合法操作！");
		break;
	case QNetworkReply::UnknownNetworkError:
		errStr = QStringLiteral("未知网络！");
		break;
	case QNetworkReply::UnknownProxyError:
		errStr = QStringLiteral("未知代理！");
		break;
	case QNetworkReply::UnknownContentError:
		errStr = QStringLiteral("未知内容");
		break;
	case QNetworkReply::ProtocolFailure:
		errStr = QStringLiteral("协议失败");
		break;

	default:
		errStr = QStringLiteral("未知错误！");
		break;
	}

	return errStr;
}

void ZcNetwork::freeStructMemory(void *mem)
{
	if (mem != NULL)
	{
		free(mem);
		mem = NULL;
	}
}