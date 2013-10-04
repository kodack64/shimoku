#ifndef _PLAYER_H
#define _PLAYER_H

#include "common.h"

class Player{
private:
public:
	int nextx;
	int nexty;
	virtual int Main(int myst,int* state)=0;
	virtual int Close()=0;
	virtual int GetX(){return nextx;};
	virtual int GetY(){return nexty;};
	virtual void SetX(int x){nextx=x;};
	virtual void SetY(int y){nexty=y;};
};

#endif _PLAYER_H