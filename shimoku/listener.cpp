
#include "listener.h"
#include "appli_common.h"
#include "logger.h"

Game* Listener::game;
int Listener::fps;
int Listener::winx;
int Listener::winy;
int Listener::winposx;
int Listener::winposy;
int Listener::fullsc;
int Listener::frame;
int Listener::lastTime;
int Listener::elapsedTime;
bool Listener::replay=false;
char Listener::repfile[MAX_PATH];

Listener::Listener(){
	game=NULL;
}
Listener::~Listener(){
}

void Listener::Init(int s_winx,int s_winy,int s_winposx,int s_winposy,int s_fps,int s_fullsc){
	fps = s_fps;
	winx = s_winx;
	winy = s_winy;
	winposx = s_winposx;
	winposy = s_winposy;
	fullsc = s_fullsc;

	Logger::Print("Listener : Initialize Game");
	game = new Game;
	game->Init();
	if(replay){
		game->SetModeReplay(repfile);
	}
	lastTime=glutGet(GLUT_ELAPSED_TIME);
}
void Listener::Close(){
	Logger::Print("Listener : Release Game");
	if(game!=NULL)game->Close();
	SAFE_DELETE(game);
}

void __cdecl Listener::Timer(int val){
	if(game==NULL){
		assert(false);
		glutLeaveMainLoop();
	}

	if(game->MainLoop()==-1){
		Logger::Print("Exit MainLoop");
		glutLeaveMainLoop();
	}

	glutPostRedisplay();
	elapsedTime =glutGet(GLUT_ELAPSED_TIME)-lastTime;
	if(elapsedTime>=1000){
		char title[MAX_PATH];
		sprintf_s(title,MAX_PATH,"%s FPS:%d/%d",WINDOWTITLE,frame,fps);
		glutSetWindowTitle(title);
		frame=0;
		elapsedTime=0;
		lastTime=glutGet(GLUT_ELAPSED_TIME);
	}
	frame++;
	int diff=1000*frame/fps-elapsedTime;
	if(diff>0)glutTimerFunc(diff,Timer,0);
	else glutTimerFunc(0,Timer,0);
};

void __cdecl Listener::Disp(void){
	if(game==NULL){
		assert(false);
		glutLeaveMainLoop();
	}
	game->Draw();
};

void __cdecl Listener::Reshape(int w,int h){
	game->ReshapeEvent(w,h);
}

void __cdecl Listener::Mouse(int button,int state,int x,int y){
	if(state==GLUT_DOWN){
		game->MouseEvent(button,1,x,y);
	}else{
		game->MouseEvent(button,0,x,y);
	}
}

void __cdecl Listener::Motion(int x,int y){
	game->MouseMove(x,y);
}

void __cdecl Listener::Keyboard(unsigned char key,int x,int y){
	switch (key) {
	case VK_ESCAPE:
		Logger::Print("Listener : Exit MainLoop");
		glutLeaveMainLoop();
		break;
	case VK_SPACE:
		if(fullsc){
			ChangeDisplaySettings(NULL, 0);
			glutPositionWindow(winposx,winposy);
			glutReshapeWindow(winx,winy);
			fullsc=0;
		}else{
			glutFullScreen();
			fullsc=1;
		}
		break;
	default:
		game->KeyEvent(key,1);
		break;
	}
}

void __cdecl Listener::KeyboardUp(unsigned char key,int x,int y){
	game->KeyEvent(key,0);
}

void __cdecl Listener::SpecialKeyboard(int key,int x,int y){
	switch(key){
	case GLUT_KEY_RIGHT:
		game->KeyEvent(VK_RIGHT,1);
		break;
	case GLUT_KEY_LEFT:
		game->KeyEvent(VK_LEFT,1);
		break;
	case GLUT_KEY_UP:
		game->KeyEvent(VK_UP,1);
		break;
	case GLUT_KEY_DOWN:
		game->KeyEvent(VK_DOWN,1);
		break;
	}
}
void __cdecl Listener::SpecialKeyboardUp(int key,int x,int y){
	switch(key){
	case GLUT_KEY_RIGHT:
		game->KeyEvent(VK_RIGHT,0);
		break;
	case GLUT_KEY_LEFT:
		game->KeyEvent(VK_LEFT,0);
		break;
	case GLUT_KEY_UP:
		game->KeyEvent(VK_UP,0);
		break;
	case GLUT_KEY_DOWN:
		game->KeyEvent(VK_DOWN,0);
		break;
	}
}

void Listener::setReplayName(const char* str){
	replay=true;
	sprintf_s(repfile,MAX_PATH,"%s",str);
	return;
}