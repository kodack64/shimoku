#include "logger.h"

int Logger::debuglevel=0;
Logger* Logger::mylog=NULL;
bool Logger::cons=true;

int Logger::SetTypeConsole(){
	if(mylog!=0)delete mylog;
	mylog=new ConsoleLogger;
	cons=true;
	return 0;
}
int Logger::SetTypeTextout(){
	if(mylog!=0)delete mylog;
	mylog=new TextLogger;
	cons=false;
	return 0;
}
bool Logger::isConsole(){
	return cons;
}
int Logger::DebugOutput(bool f){
	if(f)debuglevel=1;
	else debuglevel=0;
	return 0;
}
int Logger::Close(){
	if(mylog!=NULL)delete mylog;
	return 0;
}

int Logger::Print(const char* str,...){
    va_list arg;
	va_start(arg,str);
	if(mylog!=NULL)mylog->MyPrint(str,arg);
	va_end(arg);
	return 0;
}

int Logger::Debug(const char* str,...){
    va_list arg;
	va_start(arg,str);
	if(debuglevel)	mylog->MyPrint(str,arg);
	va_end(arg);
	return 0;
}

int ConsoleLogger::MyPrint(const char* str,va_list arg){
	printf_s("[exe_log] ");
	vprintf_s(str,arg);
	printf_s("\n");
	return 0;
}

TextLogger::TextLogger(){
	fopen_s(&mylog_fp,LOGNAME,"w");
	fprintf(mylog_fp,"[Logger] Log Start\n");
	fclose(mylog_fp);
}
TextLogger::~TextLogger(){
}

int TextLogger::MyPrint(const char* str,va_list arg){
	fopen_s(&mylog_fp,LOGNAME,"a");
	if(mylog_fp!=NULL){
		fprintf_s(mylog_fp,"[exe_log] ");
		vfprintf_s(mylog_fp,str,arg);
		fprintf_s(mylog_fp,"\n");
		fclose(mylog_fp);
	}
	return 0;
}