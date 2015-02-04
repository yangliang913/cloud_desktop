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
		else if (command == GetHostInfo)//��ȡ��������Ϣ
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
		else if (command == UpdateHostInfo)	//������������Ϣ
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
		else if (command == StartHost) //����������
		{
			//freeStructMemory(controlHostData);
			prevCommand = StartHost;
			bool controlMsg_succ = parserJson->controlJsonToStruct(data, &controlHostData);
			emit notifyControlHostUi(controlMsg_succ, command);
		}
		else if (command == StopHost) //�ر�������
		{
			//freeStructMemory(controlHostData);
			prevCommand = StopHost;
			bool controlMsg_succ = parserJson->controlJsonToStruct(data, &controlHostData);
			emit notifyControlHostUi(controlMsg_succ, command);
		}
		else if (command == RestartHost) //����������
		{
			//freeStructMemory(controlHostData);
			prevCommand = RestartHost;
			bool controlMsg_succ = parserJson->controlJsonToStruct(data, &controlHostData);
			emit notifyControlHostUi(controlMsg_succ, command);
		}
		else if (command == ModifyHostConfig) //�޸�����������
		{
			//freeStructMemory(controlHostData);
			prevCommand = ModifyHostConfig;
			bool controlMsg_succ = parserJson->controlJsonToStruct(data, &controlHostData);
			emit notifyControlHostUi(controlMsg_succ, command);
		}
		else if (command == ForceStopHost) //ǿ�ƹر�������
		{
			//freeStructMemory(controlHostData);
			prevCommand = ForceStopHost;
			bool controlMsg_succ = parserJson->controlJsonToStruct(data, &controlHostData);
			emit notifyControlHostUi(controlMsg_succ, command);
		}
		else if (command == QueryHostPrice)  //��ѯ��ǰ��������ʱ�۸�
		{
			prevCommand = QueryHostPrice;
			bool controlMsg_succ = parserJson->queryJsonToStruct(data, &hostPrice);
			emit notifyControlHostUi(controlMsg_succ, command);
		}
		else if (command == FirstQueryHostPrice)  //ÿ�ν�������ҳ���ѯ�������۸�
		{
			prevCommand = FirstQueryHostPrice;
			bool controlMsg_succ = parserJson->queryJsonToStruct(data, &hostPrice);
			emit notifyControlHostUi(controlMsg_succ, command);
		}
		else if (command == QueryLastVersion) //��ѯ���°汾��
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
		QString errStr = QStringLiteral("����ʧ�ܣ�");
		errStr += errorToChinese(err);
		//д��־ʱ���ϴ�����
		QString logStr = errStr + QStringLiteral("  �����룺");
		logStr += QString::number(err, 10);
		MyZCLog::Instance().WriteToLog(ZCERROR, logStr);
		emit notifyUi(2, command);
		QMessageBox::information(NULL, QStringLiteral("����"), errStr, QMessageBox::Ok);
	}
	reply->close();
}

//cmd �������1Ϊ��Ȩ��2Ϊ��ȡ��������Ϣ
void ZcNetwork::parseJson(int cmd, QString strUrl)
{
	QNetworkRequest request;
	command = cmd;
	printf("%s\n", strUrl.toLatin1().data());
	request.setUrl(QUrl(strUrl));
	//����ͷ��Ϣ
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
		errStr = QStringLiteral("���ӱ��ܾ���");
		break;
	case QNetworkReply::RemoteHostClosedError:
		errStr = QStringLiteral("Զ���������رգ�");
		break;
	case QNetworkReply::HostNotFoundError:
		errStr = QStringLiteral("û�ҵ�������");
		break;
	case QNetworkReply::TimeoutError:
		errStr = QStringLiteral("���ӳ�ʱ��");
		break;
	case QNetworkReply::OperationCanceledError:
		errStr = QStringLiteral("����ȡ����");
		break;
	case QNetworkReply::SslHandshakeFailedError:
		errStr = QStringLiteral("SSL����ʧ�ܣ�");
		break;
	case QNetworkReply::TemporaryNetworkFailureError:
		errStr = QStringLiteral("��ʱ����ʧ�ܣ�");
		break;
	case QNetworkReply::ProxyConnectionRefusedError:
		errStr = QStringLiteral("�������ӱ��ܾ���");
		break;
	case QNetworkReply::ProxyConnectionClosedError:
		errStr = QStringLiteral("�������ӱ��رգ�");
		break;
	case QNetworkReply::ProxyNotFoundError:
		errStr = QStringLiteral("û�ҵ�����");
		break;
	case QNetworkReply::ProxyTimeoutError:
		errStr = QStringLiteral("����ʱ��");
		break;
	case QNetworkReply::ProxyAuthenticationRequiredError:
		errStr = QStringLiteral("������֤�������");
		break;
	case QNetworkReply::ContentAccessDenied:
		errStr = QStringLiteral("�ܾ��������ݣ�");
		break;
	case QNetworkReply::ContentOperationNotPermittedError:
		errStr = QStringLiteral("�ܾ��������ݣ�");
		break;
	case QNetworkReply::ContentNotFoundError:
		errStr = QStringLiteral("û�ҵ����ݣ�");
		break;
	case QNetworkReply::AuthenticationRequiredError:
		errStr = QStringLiteral("��֤�������");
		break;
	case QNetworkReply::ContentReSendError:
		errStr = QStringLiteral("�����ط�����");
		break;
	case QNetworkReply::ProtocolUnknownError:
		errStr = QStringLiteral("δ֪Э�飡");
		break;
	case QNetworkReply::ProtocolInvalidOperationError:
		errStr = QStringLiteral("Э�鲻�Ϸ�������");
		break;
	case QNetworkReply::UnknownNetworkError:
		errStr = QStringLiteral("δ֪���磡");
		break;
	case QNetworkReply::UnknownProxyError:
		errStr = QStringLiteral("δ֪����");
		break;
	case QNetworkReply::UnknownContentError:
		errStr = QStringLiteral("δ֪����");
		break;
	case QNetworkReply::ProtocolFailure:
		errStr = QStringLiteral("Э��ʧ��");
		break;

	default:
		errStr = QStringLiteral("δ֪����");
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