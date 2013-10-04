#ifndef _DIRMANAGER_H
#define _DIRMANAGER_H

#include "common.h"

class DirManager{
private:
	static string path;
public:
	static void SetPath();
	static void SetDir();
	static string GetDir();
};

#endif _DIRMANAGER_H