#include "game.h"

int Game::MouseEvent(int button,int state,int x,int y){
	mouse->Set(button,state);
	return 0;
}

int Game::MouseMove(int x,int y){
	mouse->Move(x,y);
	return 0;
}

int Game::KeyEvent(int key,int flag){
	keyboard->Set(key,flag);
	return 0;
}

int Game::ReshapeEvent(int w,int h){
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(camera->GetFovy(), (double)w / (double)h,camera->GetNear(),camera->GetFar());
	glMatrixMode(GL_MODELVIEW);
	return 0;
}