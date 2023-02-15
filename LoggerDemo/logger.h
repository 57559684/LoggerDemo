//logger.h
/*
//������CLogger
//���ܽ��ܣ�Winƽ̨��־��¼���ܣ����̰߳�ȫ��֧��д��־��������ã���־��ʽ������־�ȼ�����־ʱ�䣬�ļ������к���Ϣ
//���ߣ�sunflover 2016-1-15 14:31:27

//ʹ�÷�����
1����logger.h��logger.cpp���ӵ���Ŀ��
2������logger.cpp��Ԥ����ͷѡ��Ϊ����ʹ��Ԥ����ͷ��
3��ʹ�ô���ʾ����
#include "Logger.h"
LOGGER::CLogger logger;

void main()
{
logger.TraceFatal("TraceFatal %d", 1);
logger.TraceError("TraceError %s", "sun");
logger.TraceWarning("TraceWarning");
logger.TraceInfo("TraceInfo");

logger.ChangeLogLevel(LOGGER::LogLevel_Error);

logger.TraceFatal("TraceFatal %d", 2);
logger.TraceError("TraceError %s", "sun2");
logger.TraceWarning("TraceWarning");
logger.TraceInfo("TraceInfo");
}

ִ�н����20160115142829.log�ļ���������
Fatal	2016-01-15 14:28:29 logger.cpp:91	TraceFatal 1
Error	2016-01-15 14:28:29 logger.cpp:123	TraceError sun
Warning	2016-01-15 14:28:29 logger.cpp:155	TraceWarning
Info	2016-01-15 14:28:29 logger.cpp:188	TraceInfo
Fatal	2016-01-15 14:28:29 logger.cpp:91	TraceFatal 2
Error	2016-01-15 14:28:29 logger.cpp:123	TraceError sun2
*/

#ifndef _LOGGER_H_
#define _LOGGER_H_
#include <Windows.h>
#include <stdio.h>
#include <string>


namespace LOGGER
{
	//��־�������ʾ��Ϣ
	static const std::string strFatalPrefix = "[Fatal]";
	static const std::string strErrorPrefix = "[Error]";
	static const std::string strWarningPrefix = "[Warning]";
	static const std::string strInfoPrefix = "[Info]";

	//��־����ö��
	typedef enum EnumLogLevel
	{
		LogLevel_Stop = 0,	//ʲô������¼
		LogLevel_Fatal,		//ֻ��¼���ش���
		LogLevel_Error,		//��¼���ش�����ͨ����
		LogLevel_Warning,	//��¼���ش�����ͨ���󣬾���
		LogLevel_Info		//��¼���ش�����ͨ���󣬾��棬��ʾ��Ϣ(Ҳ����ȫ����¼)
	};

	class CLogger
	{
	public:
		//nLogLevel����־��¼�ĵȼ����ɿ�
		//strLogPath����־Ŀ¼���ɿ�
		//strLogName����־���ƣ��ɿ�
		CLogger(EnumLogLevel nLogLevel = LOGGER::LogLevel_Info, const std::string strLogPath = "", const std::string strLogName = "");
		//��������
		virtual ~CLogger();
	public:
		//д���ش�����Ϣ
		void TraceFatal(int linenum, const char* filename, const char* functionname, const char *lpcszFormat, ...);
		//д������Ϣ
		void TraceError(int linenum, const char* filename, const char* functionname, const char *lpcszFormat, ...);
		//д������Ϣ
		void TraceWarning(int linenum, const char* filename, const char* functionname, const char *lpcszFormat, ...);
		//д��ʾ��Ϣ
		void TraceInfo(int linenum, const char* filename, const char* functionname, const char *lpcszFormat, ...);
		//�ı�д��־����
		void ChangeLogLevel(EnumLogLevel nLevel);
	private:
		//д�ļ�����
		void Trace(const std::string &strLog);
		//��ȡ��ǰϵͳʱ��
		std::string GetTime();
		//��ȡ��������·��
		std::string GetAppPathA();
		//��ʽ���ַ���
		std::string FormatString(const char *lpcszFormat, ...);
		//�ļ�ȫ·���õ��ļ���
		const char *path_file(const char *path, char splitter);
	private:
		//д��־�ļ���
		FILE * m_pFileStream;
		//д��־����
		EnumLogLevel m_nLogLevel;
		//��־Ŀ¼
		std::string m_strLogPath;
		//��־������
		std::string m_strLogName;
		//��־�ļ�ȫ·��
		std::string m_strLogFilePath;
		//�߳�ͬ�����ٽ�������
		CRITICAL_SECTION m_cs;
	};



#define pINFO_LOG(pInstance, lpcszFormat, ...)         (pInstance)->TraceInfo(__LINE__, __FILE__, __FUNCTION__, lpcszFormat, ##__VA_ARGS__);

#define pWARNING_LOG(pInstance, lpcszFormat, ...)      (pInstance)->TraceWarning(__LINE__, __FILE__, __FUNCTION__, lpcszFormat, ##__VA_ARGS__);

#define pERROR_LOG(pInstance, lpcszFormat, ...)        (pInstance)->TraceError(__LINE__, __FILE__, __FUNCTION__, lpcszFormat, ##__VA_ARGS__);

#define pFATAL_LOG(pInstance, lpcszFormat, ...)        (pInstance)->TraceFatal(__LINE__, __FILE__, __FUNCTION__, lpcszFormat, ##__VA_ARGS__);

#define INFO_LOG(instance, lpcszFormat, ...)           (instance).TraceInfo(__LINE__, __FILE__, __FUNCTION__, lpcszFormat, ##__VA_ARGS__);

#define WARNING_LOG(instance, lpcszFormat, ...)        (instance).TraceWarning(__LINE__, __FILE__, __FUNCTION__, lpcszFormat, ##__VA_ARGS__);

#define ERROR_LOG(instance, lpcszFormat, ...)          (instance).TraceError(__LINE__, __FILE__, __FUNCTION__, lpcszFormat, ##__VA_ARGS__);

#define FATAL_LOG(instance, lpcszFormat, ...)          (instance).TraceFatal(__LINE__, __FILE__, __FUNCTION__, lpcszFormat, ##__VA_ARGS__);

}

#endif