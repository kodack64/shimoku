#include "inimanager.h"
#include "dirmanager.h"

string IniManager::myinipath="";

int IniManager::SetFile(string filename){
	myinipath=DirManager::GetDir()+filename;
	return 0;
}

int IniManager::ReadInt(string section,string key,int def){
	if(myinipath=="")return 0;
	int rtn=GetPrivateProfileInt(section.c_str(),key.c_str(),def,myinipath.c_str());
	if(rtn==def){
		char buf[INI_MAX_BUF];
		sprintf_s(buf,256,"%d",def);
		WritePrivateProfileString(section.c_str(),key.c_str(),buf,myinipath.c_str());
	}
	return rtn;
}

void IniManager::WriteInt(string section,string key,int value){
	if(myinipath=="")return;
	char buf[256];
	sprintf_s(buf,256,"%d",value);
	WritePrivateProfileString(section.c_str(),key.c_str(),buf,myinipath.c_str());
}

double IniManager::ReadDouble(string section,string key,double def){
	if(myinipath=="")return 0;
	double rtn;
	char buf[INI_MAX_BUF];
	char defstr[INI_MAX_BUF];
	sprintf_s(defstr,INI_MAX_BUF,"%lf",def);
	GetPrivateProfileString(section.c_str(),key.c_str(),defstr,buf,256,myinipath.c_str());
	if(strcmp(buf,defstr)==0){
		WritePrivateProfileString(section.c_str(),key.c_str(),buf,myinipath.c_str());
	}
	sscanf_s(buf,"%lf",&rtn);
	return rtn;
}

string IniManager::ReadString(string section,string key,string def){
	if(myinipath=="")return "";
	string rtn;
	char buf[INI_MAX_BUF];
	GetPrivateProfileString(section.c_str(),key.c_str(),def.c_str(),buf,256,myinipath.c_str());
	if(strcmp(buf,def.c_str())==0){
		WritePrivateProfileString(section.c_str(),key.c_str(),buf,myinipath.c_str());
	}
	rtn=buf;
	return rtn;
}