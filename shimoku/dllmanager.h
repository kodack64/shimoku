#ifndef _DLLMANAGER_H
#define _DLLMANAGER_H

#include "common.h"

class DllManager{
private:
	bool initflag;
	vector <string> dlldir;
	vector <string> dllname;
	vector <string> dllgetname;
	string dllfold;
	virtual bool Check(string str,string* dllgetname);
public:
	DllManager();
	virtual ~DllManager();
	virtual int Init();
	virtual int Close();
	virtual int Search();
	virtual int GetDllNum();
	virtual string GetDllName(unsigned int i);
	virtual string GetDllPath(unsigned int i);
};

#endif _DLLMANAGER_H