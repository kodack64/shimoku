#include "dirmanager.h"
#include "common.h"

string DirManager::path;

void DirManager::SetDir(){
	char buf[MAX_PATH],drv[MAX_PATH],dir[MAX_PATH],fn[MAX_PATH],ext[MAX_PATH];
	int ret=GetModuleFileName(NULL,buf,sizeof(buf));
	if(ret==0){
		GetCurrentDirectory(MAX_PATH,buf);
	}else{
		_splitpath_s(buf,drv,sizeof(drv),dir,sizeof(dir),fn,sizeof(fn),ext,sizeof(ext));
		sprintf_s(buf,MAX_PATH,"%s%s",drv,dir);
		SetCurrentDirectory(buf);
	}
	path=buf;
}
string DirManager::GetDir(){
	return path;
}