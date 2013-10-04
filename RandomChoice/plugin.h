#ifndef _PLUGIN_H
#define _PLUGIN_H

#include <Windows.h>
#include <cstdio>

#ifndef SAFE_DELETE
#define SAFE_DELETE(p)       { if (p) { delete (p);     (p)=NULL; } }
#endif

#define PLUGIN_NUM 2
#define NN 4
#define MAX_NAME	256

class Point3d{
public:
	int x;int y;int z;
	Point3d(){x=y=z=0;}
	Point3d(int p,int q,int r){x=p;y=q;z=r;}
	bool operator == (Point3d comp) {
		return (this->x==comp.x)&&(this->y==comp.y)&&(this->z==comp.z);
	}
};
#define POINT_NOT_EXIST Point3d(-1,-1,-1)

__declspec(dllexport) void CALLBACK getName(char* buf);

class Plugin{
private:
	int x;
	int y;
	char logpath[MAX_PATH];
	bool cons;
	int ordercount;
	int domain[NN][NN][NN];
	int order[NN][NN][NN];
	Point3d coordinate[NN*NN*NN];
public:
	Plugin();
	virtual ~Plugin();
	virtual void pushOrder(int x,int y,int z,int d);
	virtual int getDomain(int x,int y,int z);
	virtual int getOrder(int x,int y,int z);
	virtual Point3d getCoordinate(int order);
	virtual int getOrderCount();
	virtual int getX(){return x;};
	virtual int getY(){return y;};
	virtual void init()=0;
	virtual void close(int winner)=0;
	virtual void think()=0;
	virtual void setX(int sx){x=sx;};
	virtual void setY(int sy){y=sy;};
	virtual void logPrint(const char* str,...);
	virtual void setLogText(const char* buf);
	virtual void setLogConsole();
};

#endif _PLUGIN_H