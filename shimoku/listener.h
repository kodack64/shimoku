#ifndef __LISTEN_H_
#define __LISTEN_H_

#include "game.h"

class Listener{
private:
	static int fps;
	static int winx;
	static int winy;
	static int winposx;
	static int winposy;
	static int fullsc;
	static int frame;
	static int lastTime;
	static int elapsedTime;
	static Game* game;
	static bool replay;
	static char repfile[MAX_PATH];
public:
	Listener();
	virtual ~Listener();

	virtual void Init(int winx,int winy,int winposx,int winposy,int fps,int fullsc);
	virtual void Close();

	static void __cdecl Timer(int val);
	static void __cdecl Disp(void);
	static void __cdecl Reshape(int w,int h);
	static void __cdecl Mouse(int b,int st,int x,int y);
	static void __cdecl Motion(int x,int y);
	static void __cdecl Keyboard(unsigned char key,int x,int y);
	static void __cdecl KeyboardUp(unsigned char key,int x,int y);
	static void __cdecl SpecialKeyboard(int key,int x,int y);
	static void __cdecl SpecialKeyboardUp(int key,int x,int y);
	static void setReplayName(const char*);
};

#endif __LISTEN_H_