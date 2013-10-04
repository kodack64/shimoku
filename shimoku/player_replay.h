#ifndef _PLAYER_REPLAY_H
#define _PLAYER_REPLAY_H

#include "player.h"
#include "keyboard.h"
#include "glfunc.h"
class Replayer:public Player{
private:
	vector<Vec3d>* order;
	int c;
	Keyboard *keyboard;
public:
	virtual int Init(Keyboard*,vector<Vec3d>* v);
	virtual int Main(int myst,int* state);
	virtual int Close();
	virtual void PushOrder();
};

#endif _PLAYER_REPLAY_H