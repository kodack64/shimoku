#ifndef _WORLD_H_
#define _WORLD_H_

#include "woodbase.h"
#include "woodbar.h"
#include "woodball.h"
#include "jpeg.h"

#define NN	4

class World{
private:
	WoodBase* woodbase;
	WoodBar* woodbar[NN][NN];
	WoodBall* woodball[NN][NN][NN];
	JPEG* img_ball;
	JPEG* img_bar;
	JPEG* img_base;
	int kx;
	int ky;
	int kz;
public:
	World();
	virtual ~World();
	virtual int Init();
	virtual int Main();
	virtual int Judge();
	virtual int RJudge(int ph);
	virtual int Draw();
	virtual int Close();
	virtual void SetBallState(int x,int y,int z,int st);
	virtual void SetNextBallPos(int x,int y,int z,int st);
	virtual void EraseNextBallPos();
	virtual void ResetNextBallPos();
	virtual void ResetBall();
};

#endif _WORLD_H_