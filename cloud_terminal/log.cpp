#include "log.h"
#include "common.h"
#include <ctime>
#include <string.h>

ZCLog::ZCLog()
{
	InitLog();
};

ZCLog::~ZCLog()
{
	UninitLog();
}

//初始化日志
void ZCLog::InitLog()
{
	m_fileName = "/home/client.log";
	m_file.setFileName(m_fileName);
	if (!m_file.open(QFile::WriteOnly | QFile::Text))
	{
		return;
	}
}

void ZCLog::UninitLog()
{
	m_file.close();
}

const char* ZCLog::TypeToString(const LOG_LEVEL type) {
	switch (type) {
	case ZCFATAL:
		return "FATAL";
	case ZCERROR:
		return "ERROR";
	case ZCWARN:
		return "WARN ";
	case ZCINFO:
		return "INFO ";
	case ZCDEBUG:
		return "DEBUG";
	default:
		break;
	}
	return "UNKNOW";
}

void ZCLog::write(const char* format, ...)
{
	char buffer[10240] = { 0 };

	va_list varArgs;
	va_start(varArgs, format);
	vsnprintf(buffer, sizeof(buffer), format, varArgs);
	va_end(varArgs);
	
	QTextStream out(&m_file);
	out << buffer;
	m_file.flush();
}

void ZCLog::log(const LOG_LEVEL type, const char* message)
{
	static const int TIMESTAMP_BUFFER_SIZE = 21;
	char buffer[TIMESTAMP_BUFFER_SIZE];
	time_t timestamp;
	time(&timestamp);
	strftime(buffer, sizeof(buffer), "%X %x", localtime(&timestamp));

	write("%s [%s] - %s", buffer, TypeToString(type), message);
}
void ZCLog::log(const LOG_LEVEL type, const char* format, const va_list& varArgs)
{
	char buffer[10240] = { 0 };
	vsnprintf(buffer, sizeof(buffer), format, varArgs);
	log(type, buffer);
}

//写入日志信息
void ZCLog::WriteToLog(const LOG_LEVEL level, char *msg)
{
	if (msg == "" || msg == NULL) return;
	char tmp[1024] = { 0 };
	strncpy(tmp, msg, sizeof(tmp));
	strncat(tmp, "\n", sizeof("\n"));
	log(level, tmp);
}

void ZCLog::WriteToLog(const LOG_LEVEL level, QString msg)
{
	if (msg == "" || msg == NULL) return;
	msg += "\n";
	log(level, msg.toLatin1().data());
}