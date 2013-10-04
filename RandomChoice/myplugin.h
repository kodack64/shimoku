#ifndef _MYPLUGIN_H
#define _MYPLUGIN_H

#include "plugin.h"
#include "mersenne.h"


class MyPlugin:public Plugin{
private:
	MersenneTwister* myrand;
public:
	virtual void init();
	virtual void close(int winner);
	virtual void think();


	/*					*/
	/* Rquired Member	*/
	/*					*/
private:
	static MyPlugin* myPlugin[PLUGIN_NUM];
public:
	static __declspec(dllexport) Plugin* CALLBACK createInstance();
	static __declspec(dllexport) void CALLBACK destroyInstance();
};
__declspec(dllexport) void CALLBACK getName(char* buf);


#endif _MYPLUGIN_H