/*
* 文件名称：log.h
* 描述：简单的日志系统
*/

#ifndef _LOG_H_
#define _LOG_H_
#include <memory>
#include <cstdarg>
#include <QString>
#include <QFile>
#include <QTextStream>
using namespace std;

#include "singleton.h"
#include "common.h"
class ZCLog
{
public:
	ZCLog();
	~ZCLog();

	void WriteToLog(const LOG_LEVEL level, char *msg);
	void WriteToLog(const LOG_LEVEL level, QString msg);

	void InitLog();
	void UninitLog();

	const char* TypeToString(const LOG_LEVEL type);

	void Push(const QString& fileName);

private:
	QString m_fileName;
	QFile m_file;
	void write(const char* format, ...);

	void log(const LOG_LEVEL type, const char* message);
	void log(const LOG_LEVEL type, const char* format, const va_list& varArgs);
};

typedef Singleton<ZCLog> MyZCLog;

#endif