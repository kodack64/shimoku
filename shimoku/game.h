#ifndef _GAME_H
#define _GAME_H

#include "game_common.h"
#include "world.h"
#include "player.h"
#include "dllmanager.h"
#include "dllselector.h"
#include "mouse.h"
#include "keyboard.h"
#include "camera.h"

class Game{
private:
	GAME_PHASE phase;
	bool phaseinit;

	int menust;

	Mouse* mouse;
	Keyboard* keyboard;
	Camera* camera;
	World* world;

	DllManager* dllmanager;
	DllSelector* dllselector[2];

	Player* player[2];
	bool isCom[2];
	int comDllNum[2];
	bool isReach[2];
	int turn;
	int winner;
	int state[NN*NN*NN];

	int rec;
	FILE* kifu_fp;
	vector <Vec3d> replayOrder;
	bool replay;

	int repeat;
	int repeatCount;

	int repeatWinCount[3];

	virtual int InitMenu();
	virtual int ProcMenu();
	virtual int DrawMenu();

	virtual int InitPlay();
	virtual int ProcPlay();
	virtual int DrawPlay();

	virtual int InitResult();
	virtual int ProcResult();
	virtual int DrawResult();

public:
	Game();
	virtual ~Game();
	virtual int Init();
	virtual int MainLoop();
	virtual int Draw();
	virtual int Close();

	virtual int KeyEvent(int key,int flag);
	virtual int MouseEvent(int button,int flag,int x,int y);
	virtual int MouseMove(int x,int y);
	virtual int ReshapeEvent(int w,int h);
	virtual void SetModeReplay(const char*);
};

#endif _GAME_H