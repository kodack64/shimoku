#ifndef _WOODBALL_H
#define _WOODBALL_H

#include "glfunc.h"
#include "jpeg.h"

class WoodBall{
private:
	Vec3d mypos;
	pdColor myfscol;
	pdColor mysccol;
	double r;
	int mystate;
	JPEG* myTex;
	bool isReach;
	int atr;
	double colphase;
public:
	WoodBall();
	virtual ~WoodBall();
	virtual int Init(Vec3d center,pdColor color1,pdColor color2,double r);
	virtual int Main();
	virtual int Draw();
	virtual int GetState();
	virtual void SetState(int state,int atr);
	virtual void SetTexture(JPEG* t){myTex=t;};
	virtual void SetReach(bool state);
};

#endif _WOODBALL_H