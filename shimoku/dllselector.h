#ifndef DLLSELECTOR_H
#define DLLSELECTOR_H

#include "dllmanager.h"
#include "glfunc.h"

class DllSelector{
private:
	DllManager* dllmn;
	int cur;
	Vec2d pos;
	bool decideflag;
public:
	DllSelector();
	virtual ~DllSelector();
	virtual void Init(Vec2d pos,DllManager* dllmn);
	virtual void Reset();
	virtual void Draw();
	virtual void Move(int i);
	virtual void Close();
	virtual void Decide();
	virtual void UnDecide();
	virtual int GetDecide();
};

#endif DLLSELECTOR_H