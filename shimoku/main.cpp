
#include "common.h"
#include "appli.h"
#include "logger.h"

#ifndef	CONSOLE
#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")
#endif

int main(int argc, char *argv[]){

#ifdef	_DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif
#ifdef	CONSOLE
	Logger::SetTypeConsole();
	Logger::DebugOutput(true);
#else
	Logger::SetTypeTextout();
	Logger::DebugOutput(false);
#endif

	Logger::Print("Main : Initialize Application");
	Appli *appli = new Appli;
	appli->Init(&argc,argv);

	Logger::Print("Main : Run Application");
	appli->Run();

	Logger::Print("Main : Release Application");
	appli->Close();
	delete appli;

	Logger::Close();
	return 0;
}