# LoggerDemo
CLogger Class,Win32

Class name: CLogger
Based on https://github.com/sunflover/LoggerDemo

Function introduction:
Win platform logging function
C language variable parameter format output log
Log writing in shared mode (you can view the log when the program is running)
You can write the logs of different modules to different files
Multi-threading safety
Support the setting of write log level
The log format includes log level, log time, file name, line number information, thread ID, and function name

Author: 57559684 2023-1-10
If you have problems using this log library, you can send an email to <57559684@qq.com>

Usage:
1: Add logger.h and logger.cpp to the project
2: Set the precompiled header option of logger.cpp to "Do not use precompiled headers"
3: Use code example:

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
		pWARNING_LOG(pLogger, "中华人民共和国！");
		pINFO_LOG(pLogger, "TraceInfo");

		FATAL_LOG(*pLogger, "TraceFatal %d", i);
		ERROR_LOG(*pLogger, "TraceError %s", "sun2");
		WARNING_LOG(*pLogger, "TraceWarning");
		INFO_LOG(*pLogger, "TraceInfo 这是一个中文测试");

		pFATAL_LOG(&logger, "TraceFatal %d", i);
		pERROR_LOG(&logger, "TraceError %s", "sun");
		pWARNING_LOG(&logger, "中华人民共和国！");
		pINFO_LOG(&logger, "TraceInfo");

		FATAL_LOG(logger, "TraceFatal %d", i);
		ERROR_LOG(logger, "TraceError %s", "sun2");
		WARNING_LOG(logger, "TraceWarning");
		INFO_LOG(logger, "TraceInfo 这是一个中文测试");
	}

	if(pLogger)
	{
		delete pLogger;
		pLogger = NULL;
	}
}

running result：3test20230215101031.log file context:

[Fatal][2023-02-15 10:10:31.968991][main.cpp:29][8748][main]TraceFatal 0
[Error][2023-02-15 10:10:31.968991][main.cpp:30][8748][main]TraceError sun
[Warning][2023-02-15 10:10:31.968991][main.cpp:31][8748][main]中华人民共和国！
[Info][2023-02-15 10:10:31.968991][main.cpp:32][8748][main]TraceInfo
[Fatal][2023-02-15 10:10:31.968991][main.cpp:34][8748][main]TraceFatal 0
[Error][2023-02-15 10:10:31.968991][main.cpp:35][8748][main]TraceError sun2
[Warning][2023-02-15 10:10:31.968991][main.cpp:36][8748][main]TraceWarning
[Info][2023-02-15 10:10:31.968991][main.cpp:37][8748][main]TraceInfo 这是一个中文测试
[Fatal][2023-02-15 10:10:31.969988][main.cpp:29][8748][main]TraceFatal 1
[Error][2023-02-15 10:10:31.969988][main.cpp:30][8748][main]TraceError sun
[Warning][2023-02-15 10:10:31.969988][main.cpp:31][8748][main]中华人民共和国！
[Info][2023-02-15 10:10:31.969988][main.cpp:32][8748][main]TraceInfo
[Fatal][2023-02-15 10:10:31.969988][main.cpp:34][8748][main]TraceFatal 1
[Error][2023-02-15 10:10:31.969988][main.cpp:35][8748][main]TraceError sun2
[Warning][2023-02-15 10:10:31.969988][main.cpp:36][8748][main]TraceWarning
[Info][2023-02-15 10:10:31.969988][main.cpp:37][8748][main]TraceInfo 这是一个中文测试
[Fatal][2023-02-15 10:10:31.969988][main.cpp:29][8748][main]TraceFatal 2
[Error][2023-02-15 10:10:31.969988][main.cpp:30][8748][main]TraceError sun
[Warning][2023-02-15 10:10:31.969988][main.cpp:31][8748][main]中华人民共和国！
[Info][2023-02-15 10:10:31.969988][main.cpp:32][8748][main]TraceInfo
[Fatal][2023-02-15 10:10:31.969988][main.cpp:34][8748][main]TraceFatal 2
[Error][2023-02-15 10:10:31.969988][main.cpp:35][8748][main]TraceError sun2
[Warning][2023-02-15 10:10:31.969988][main.cpp:36][8748][main]TraceWarning
[Info][2023-02-15 10:10:31.969988][main.cpp:37][8748][main]TraceInfo 这是一个中文测试


