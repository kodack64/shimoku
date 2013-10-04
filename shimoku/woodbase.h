#ifndef _WOODBASE_H
#define _WOODBASE_H

#include "glfunc.h"
#include "jpeg.h"

class WoodBase{
private:
	double uw;
	double dw;
	double uh;
	double dh;
	double de;
	Vec3d mypos;
	pdColor mycol;

	Vec3d* vertex;
	int* edge;
	pdColor* color;
	JPEG* myTex;
public:
	WoodBase();
	virtual ~WoodBase();
	virtual int Init(Vec3d center,pdColor color,double down_width,double up_width,double depth);
	virtual int Main();
	virtual int Draw();
	virtual void SetTexture(JPEG* t){myTex=t;};
};

#endif _WOODBASE_H