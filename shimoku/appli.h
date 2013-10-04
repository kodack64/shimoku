#ifndef __APP_H_
#define __APP_H_

#include "common.h"
#include "listener.h"

class Appli{
private:
	Listener* plisten;
public:
	Appli();
	virtual ~Appli();
	virtual int Init(int* argc,char** argv);
	virtual int Run();
	virtual int Close();
};

#endif __APP_H_