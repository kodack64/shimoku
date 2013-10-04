#ifndef _PLAYER_COM_H
#define _PLAYER_COM_H

#include "player.h"
#include "plugin.h"
#include "plugin_host.h"

class Com:public Player{
private:
	bool threadflag;
	HINSTANCE hdll;
	FUNC_CREATE_INSTANCE createInstance;
	FUNC_DESTROY_INSTANCE destroyInstance;
	Plugin* plugin;
	HANDLE hThread;
public:
	virtual int Init(string str);
	virtual int Main(int myst,int* state);
	static unsigned int __stdcall ThreadLaunch(void*);
	virtual Plugin* GetPlugin();
	virtual int Close();
};

#endif _PLAYER_COM_H