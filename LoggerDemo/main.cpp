#include "Logger.h"




void main()
{	
	char szExePath[MAX_PATH] = { 0 };
	char szDllPath[MAX_PATH] = { 0 };
	GetModuleFileNameA(NULL, szExePath, MAX_PATH*sizeof(char));
	char *temp = strrchr(szExePath, '\\');
	strncpy_s(szDllPath, szExePath, temp - szExePath + 1);
	strcat_s(szDllPath, MAX_PATH, "log");
	LOGGER::CLogger logger(LOGGER::LogLevel_Info, szDllPath, "3test");
	LOGGER::CLogger *pLogger = new LOGGER::CLogger(LOGGER::LogLevel_Info, szDllPath, "4test");

	for(int i=0; i<100000; i++)
	{
		pFATAL_LOG(pLogger, "TraceFatal %d", i);
		pERROR_LOG(pLogger, "TraceError %s", "sun");
		pWARNING_LOG(pLogger, "�л����񹲺͹���");
		pINFO_LOG(pLogger, "TraceInfo");

		FATAL_LOG(*pLogger, "TraceFatal %d", i);
		ERROR_LOG(*pLogger, "TraceError %s", "sun2");
		WARNING_LOG(*pLogger, "TraceWarning");
		INFO_LOG(*pLogger, "TraceInfo ����һ�����Ĳ���");

		pFATAL_LOG(&logger, "TraceFatal %d", i);
		pERROR_LOG(&logger, "TraceError %s", "sun");
		pWARNING_LOG(&logger, "�л����񹲺͹���");
		pINFO_LOG(&logger, "TraceInfo");

		FATAL_LOG(logger, "TraceFatal %d", i);
		ERROR_LOG(logger, "TraceError %s", "sun2");
		WARNING_LOG(logger, "TraceWarning");
		INFO_LOG(logger, "TraceInfo ����һ�����Ĳ���");
	}

	if(pLogger)
	{
		delete pLogger;
		pLogger = NULL;
	}
}
