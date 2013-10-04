#include "player_com.h"
#include "logger.h"

int Com::Init(string dllpath){
	hdll=LoadLibrary(dllpath.c_str());
	createInstance=(FUNC_CREATE_INSTANCE)GetProcAddress(hdll,"createInstance");
	destroyInstance=(FUNC_DESTROY_INSTANCE)GetProcAddress(hdll,"destroyInstance");
	plugin=(Plugin*)createInstance();
	if(Logger::isConsole()){
		plugin->setLogConsole();
	}else{
		plugin->setLogText(LOGNAME);
	}
	plugin->init();
	nextx=nexty=0;
	threadflag=false;
	return 0;
}

int Com::Main(int myst,int* state){
	if(threadflag==false){
		unsigned int id;
		hThread= (HANDLE)_beginthreadex(NULL,0,Com::ThreadLaunch,this,0,&id);
		threadflag=true;
	}
	DWORD dw;
	GetExitCodeThread(hThread,&dw);
	if(dw!=STILL_ACTIVE){
		threadflag=false;
		return 1;
	}
	return 0;
}
int Com::Close(){
	destroyInstance();
	FreeLibrary(hdll);
	return 0;
}

unsigned int Com::ThreadLaunch(void* arg){
	Com* me = (Com*)arg;
	Plugin* plugin=me->GetPlugin();
	plugin->think();
	me->SetX(plugin->getX());
	me->SetY(plugin->getY());
	return 0;
}

Plugin* Com::GetPlugin(){
	return plugin;
}