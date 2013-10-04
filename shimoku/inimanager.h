#ifndef _INIMANAGER_H
#define _INIMANAGER_H

#include "common.h"

#define INI_MAX_BUF 256

class IniManager{
private:
	static string myinipath;
public:
	static int SetFile(string filename);
	static int ReadInt(string section,string key,int def);
	static double ReadDouble(string section,string key,double def);
	static string ReadString(string section,string key,string def);
	static void WriteInt(string section,string key,int value);
};

#endif _INIMANAGER_H