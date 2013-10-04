#ifndef _PLAYER_HUMAN_H
#define _PLAYER_HUMAN_H

#include "player.h"
#include "keyboard.h"

class Human:public Player{
private:
	Keyboard *keyboard;
public:
	virtual int Init(Keyboard*);
	virtual int Main(int myst,int* state);
	virtual int Close();
};

#endif _PLAYER_HUMAN_H