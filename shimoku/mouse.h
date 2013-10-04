#ifndef _MOUSE_H
#define _MOUSE_H

#include "glfunc.h"

class Mouse{
private:
	int newstate[3];
	int state[3];
	int oldstate[3];
	Vec2d newpos;
	Vec2d pos;
	Vec2d oldpos;
	Vec2d newdiff;
	Vec2d diff;
	int roll;
	int newroll;
	bool fst;
public:
	Mouse(){
		memset(state,0,sizeof(state));
		memset(oldstate,0,sizeof(oldstate));
		memset(newstate,0,sizeof(newstate));

		diff=newpos=pos=oldpos=Vec2d(0,0);
		newroll=roll=0;

		POINT p;
		GetCursorPos(&p);
		newpos.x=p.x;
		newpos.y=p.y;
		pos=newpos;
		fst=false;
	}
	virtual ~Mouse(){};
	virtual int Update(){
		for(int i=0;i<3;i++){
			oldstate[i]=state[i];
			state[i]=newstate[i];
		}

		POINT p;
		GetCursorPos(&p);
		newpos.x=p.x;
		newpos.y=p.y;
		oldpos=pos;
		diff=newpos-pos;
		pos=newpos;

		roll=newroll;
		newroll=0;
		fst=true;

		return 0;
	};
	virtual int Set(int button,int flag){
		if(button==GLUT_LEFT_BUTTON){
			newstate[0]=flag;
		}else if(button==GLUT_MIDDLE_BUTTON){
			newstate[1]=flag;
		}else if(button==GLUT_RIGHT_BUTTON){
			newstate[2]=flag;
		}else if(button==0x0003){
			newroll++;
		}else if(button==0x0004){
			newroll--;
		}
		return 0;
	}
	virtual int Move(int x,int y){
//		newpos=Vec2d((double)x,(double)y);
		return 0;
	}
	virtual bool GetLeft()		{return fst&&state[0]!=0;};
	virtual bool GetMiddle()	{return fst&&state[1]!=0;};
	virtual bool GetRight()		{return fst&&state[2]!=0;};
	virtual bool GetLeftDown()	{return fst&&state[0]!=0&&oldstate[0]==0;};
	virtual bool GetMiddleDown(){return fst&&state[1]!=0&&oldstate[1]==0;};
	virtual bool GetRightDown()	{return fst&&state[2]!=0&&oldstate[2]==0;};
	virtual bool GetLeftUp()	{return fst&&state[0]==0&&oldstate[0]!=0;};
	virtual bool GetMiddleUp()	{return fst&&state[1]==0&&oldstate[1]!=0;};
	virtual bool GetRightUp()	{return fst&&state[2]==0&&oldstate[2]!=0;};
	virtual int GetRoll()		{return fst?roll:0;};
	virtual Vec2d GetPoint(){
		return pos;
	}
	virtual Vec2d GetDiff(){
		return fst?diff:Vec2d(0,0);
	}
};

#endif _MOUSE_H