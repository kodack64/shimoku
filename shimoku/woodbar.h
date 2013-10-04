#ifndef _WOODBAR_H
#define _WOODBAR_H

#include "glfunc.h"
#include "jpeg.h"

class WoodBar{
private:
	double r;
	double len;
	Vec3d mypos;
	pdColor mycol;
	pdColor myoncol;
	int st;
	JPEG* myTex;
public:
	WoodBar();
	virtual ~WoodBar();
	virtual int Init(Vec3d center,pdColor mycol,pdColor myoncol,double r,double len);
	virtual int Main();
	virtual int Draw();
	virtual int SetState(int i);
	virtual void SetTexture(JPEG* t){myTex=t;};
};

#endif _WOODBAR_H