#ifndef _LOGGER_H
#define _LOGGER_H

#include <cstdio>
#include <Windows.h>

#define LOGNAME "Log.txt"
#define MAX_LOG_LENGTH 1024

class Logger{
private:
	static Logger* mylog;
	static int debuglevel;
	static bool cons;
public:
	static int SetTypeConsole();
	static int SetTypeTextout();
	static bool isConsole();
	static int DebugOutput(bool);
	static int Print(const char*,...);
	static int Debug(const char*,...);
	static int Close();
	virtual int MyPrint(const char*,va_list arg)=0;
};

class ConsoleLogger:public Logger{
public:
	virtual int MyPrint(const char*,va_list arg);
};

class TextLogger:public Logger{
	FILE* mylog_fp;
public:
	TextLogger();
	virtual ~TextLogger();
	virtual int MyPrint(const char*,va_list arg);
};

#endif _LOGGER_H