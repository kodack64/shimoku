#include "game.h"
#include "logger.h"
#include "player_com.h"

Game::Game(){
	world=NULL;
	player[0]=NULL;
	player[1]=NULL;
	dllmanager=NULL;
	dllselector[0]=NULL;
	dllselector[1]=NULL;
	mouse=NULL;
	keyboard=NULL;
	camera=NULL;
	replay=false;
	repeat=0;
}

Game::~Game(){
}

int Game::Init(){
	Logger::Print("Game : Initialize Mouse");
	mouse=new Mouse;
	Logger::Print("Game : Initialize Keyboard");
	keyboard=new Keyboard;
	Logger::Print("Game : Initialize Camera");
	camera=new Camera();

	Logger::Print("Game : Initialize World");
	world = new World;
	world->Init();

	Logger::Print("Game : Initialize DllManager");
	dllmanager = new DllManager;
	dllmanager->Init();

	Logger::Print("Game : Initialize DllSelectors");
	dllselector[0] = new DllSelector;
	dllselector[0]->Init(Vec2d(-300,0),dllmanager);
	dllselector[1] = new DllSelector;
	dllselector[1]->Init(Vec2d(50,0),dllmanager);

	isCom[0]=isCom[1]=false;
	player[0]=player[1]=NULL;
	comDllNum[0]=comDllNum[1]=0;

	phase=MENU;
	phaseinit=true;

	return 0;
}

int Game::MainLoop(){
	keyboard->Update();
	mouse->Update();

	int res;
	//初期化フラグが立っていればそのphaseで必要な初期化をする。
	if(phaseinit){
		phaseinit=false;
		switch(phase){
		case MENU:
			Logger::Print("Game : Begin GameMenu");
			res=InitMenu();
			break;
		case PLAY:
			Logger::Print("Game : Begin GamePlay");
			res=InitPlay();
			break;
		case RESULT:
			Logger::Print("Game : Begin GameResult");
			res=InitResult();
			break;
		}
		if(res==-1){
			Logger::Print("Game : Initialize Fail");
			return -1;
		}
	}

	//メイン処理
	switch(phase){
	case MENU:
		res=ProcMenu();
		break;
	case PLAY:
		res=ProcPlay();
		break;
	case RESULT:
		res=ProcResult();
		break;
	}

	//現在のフェイズが終了したらフェイズをひとつ進めて初期化フラグを立てる。
	if(res==1){
		switch(phase){
		case MENU:
			phase=PLAY;
			break;
		case PLAY:
			phase=RESULT;
			break;
		case RESULT:
			phase=MENU;
			break;
		}
		phaseinit=true;
	}
	if(res==-1){
		Logger::Print("Game : Exit Program");
		return -1;
	}
	return 0;
}
int Game::Draw(){
	ClearScreen();
	glLoadIdentity();
	camera->Update();

	//描画処理
	switch(phase){
	case MENU:
		DrawMenu();
		break;
	case PLAY:
		DrawPlay();
		break;
	case RESULT:
		DrawResult();
		break;
	}

	SwapScreen();
	return 0;
}
int Game::Close(){
	Logger::Print("Game : Release Mouse");
	SAFE_DELETE(mouse);
	Logger::Print("Game : Release Keyboard");
	SAFE_DELETE(keyboard);
	Logger::Print("Game : Release Camera");
	SAFE_DELETE(camera);

	Logger::Print("Game : Release World");
	if(world!=NULL)world->Close();
	SAFE_DELETE(world);
	Logger::Print("Game : Release Players");
	if(isCom[0] && !replay && player[0]!=NULL){
		((Com*)(player[0]))->GetPlugin()->close(winner);
	}
	if(isCom[1] && !replay && player[1]!=NULL){
		((Com*)(player[1]))->GetPlugin()->close(-winner);
	}
	if(player[0]!=NULL)player[0]->Close();
	if(player[1]!=NULL)player[1]->Close();
	SAFE_DELETE(player[0]);
	SAFE_DELETE(player[1]);
	Logger::Print("Game : Release DllManager");
	if(dllmanager!=NULL)dllmanager->Close();
	SAFE_DELETE(dllmanager);
	Logger::Print("Game : Release DllSelectors");
	if(dllselector[0]!=NULL)dllselector[0]->Close();
	SAFE_DELETE(dllselector[0]);
	if(dllselector[1]!=NULL)dllselector[1]->Close();
	SAFE_DELETE(dllselector[1]);
	return 0;
}

void Game::SetModeReplay(const char* str){
	FILE* fp;
	fopen_s(&fp,str,"r");
	replayOrder.clear();
	if(fp!=NULL){
		int n,i,j,k;
		int c=0;
		while(fscanf_s(fp,"%d %d %d %d",&n,&i,&j,&k)==4){
			replayOrder.push_back(Vec3d(0,0,0));
			replayOrder[c].x=i;
			replayOrder[c].y=j;
			replayOrder[c].z=k;
			c++;
		}
		fclose(fp);
		replay=true;
	}
}