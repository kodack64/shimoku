#include "player_replay.h"
#include "world.h"
#include "logger.h"

int Replayer::Init(Keyboard *k,vector<Vec3d>* v){
	order=v;
	c=0;
	keyboard=k;
	return 0;
}

int Replayer::Main(int myst,int* state){
	if(keyboard->GetDown(VK_RETURN)){
		SetX((int)(*order)[c].x);
		SetY((int)(*order)[c].y);
		return 1;
	}else{
		return 0;
	}
}
void Replayer::PushOrder(){
	c++;
}

int Replayer::Close(){
	return 0;
}