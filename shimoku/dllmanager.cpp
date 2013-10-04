#include "dllmanager.h"
#include "logger.h"
#include "dirmanager.h"
#include "plugin_host.h"

DllManager::DllManager(){
}

DllManager::~DllManager(){
}

int DllManager::Init(){
	initflag=true;
	dllfold=DirManager::GetDir();
	dlldir.clear();
	dllname.clear();

	Search();

	return 0;
}

int DllManager::Close(){
	return 0;
}

int DllManager::GetDllNum(){
	return dlldir.size();
}

int DllManager::Search(){
	dlldir.clear();
	dllname.clear();
	WIN32_FIND_DATA file_data;
	HANDLE file_handle;

	Logger::Print("DllManager : Search dll");
	string searchpath=dllfold+"*.dll";
	file_handle=FindFirstFile(searchpath.c_str(),&file_data);
	if(file_handle!=INVALID_HANDLE_VALUE){
		for(;;){
			string filepath = dllfold+file_data.cFileName;
			string namebuf;
			if(strcmp(file_data.cFileName,"freeglut.dll")!=0){
				Logger::Print("DllManager : Check %s",file_data.cFileName);
				if(Check(filepath,&namebuf)){
					dlldir.push_back(filepath);
					dllname.push_back(file_data.cFileName);
					dllgetname.push_back(namebuf);
				}
			}
			if(FindNextFile(file_handle,&file_data)==0)break;
		}
		FindClose(file_handle);
	}
	return 0;
}

bool DllManager::Check(string dllpath,string* dllgetname){
	HINSTANCE hdll;
	bool flag=true;
	LPVOID lpMsgBuf;

	FUNC_CREATE_INSTANCE funcCreateInstance;
	FUNC_DESTROY_INSTANCE funcDestroyInstance;
	FUNC_GET_NAME	funcGetName;

	string funcname;
	funcname="MyMain";

	hdll=LoadLibrary(dllpath.c_str());

	if(hdll==NULL){
		Logger::Print("DllManager : Invalid Dll - Can't Load Dll");
	}else{
		funcCreateInstance=(FUNC_CREATE_INSTANCE)GetProcAddress(hdll,"createInstance");
		if(funcCreateInstance==NULL){
			Logger::Print("DllManager : Invalid Dll - Can't Load Function - createInstance");
			FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,NULL,
				GetLastError(),MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),(LPTSTR) &lpMsgBuf,0,NULL );
			Logger::Debug((LPCSTR)lpMsgBuf);
			LocalFree(lpMsgBuf);
			flag=false;
		}
		funcDestroyInstance=(FUNC_DESTROY_INSTANCE)GetProcAddress(hdll,"destroyInstance");
		if(funcCreateInstance==NULL){
			Logger::Print("DllManager : Invalid Dll - Can't Load Function - destroyInstance");
			FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,NULL,
				GetLastError(),MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),(LPTSTR) &lpMsgBuf,0,NULL );
			Logger::Debug((LPCSTR)lpMsgBuf);
			LocalFree(lpMsgBuf);
			flag=false;
		}
		funcGetName=(FUNC_GET_NAME)GetProcAddress(hdll,"getName");
		if(funcGetName==NULL){
			Logger::Print("DllManager : Invalid Dll - Can't Load Function - getName");
			FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,NULL,
				GetLastError(),MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),(LPTSTR) &lpMsgBuf,0,NULL );
			Logger::Debug((LPCSTR)lpMsgBuf);
			LocalFree(lpMsgBuf);
			flag=false;
		}
		if(flag){
			char buf[MAX_NAME];
			funcGetName(buf);
			(*dllgetname)=buf;
			Logger::Print("DllManager : %s - OK",buf);
		}
	}
	FreeLibrary(hdll);
	return flag;
}

string DllManager::GetDllName(unsigned int i){
	if(initflag && 0<=i && i<dlldir.size()){
		return dllgetname[i];
	}else{
		return "";
	}
}
string DllManager::GetDllPath(unsigned int i){
	if(initflag && 0<=i && i<dlldir.size()){
		return dlldir[i];
	}else{
		return "";
	}
}