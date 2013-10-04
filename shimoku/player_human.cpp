#include "player_human.h"
#include "world.h"
#include "logger.h"

int Human::Init(Keyboard* sk){
	keyboard=sk;
	nextx=nexty=0;
	return 0;
}

int Human::Main(int myst,int* state){
	if(keyboard->GetDown(VK_RIGHT)){
		if(nextx<NN-1)
			nextx++;
	}
	if(keyboard->GetDown(VK_LEFT)){
		if(nextx>0)
			nextx--;
	}
	if(keyboard->GetDown(VK_UP)){
		if(nexty<NN-1)
			nexty++;
	}
	if(keyboard->GetDown(VK_DOWN)){
		if(nexty>0)
			nexty--;
	}
	if(keyboard->GetDown(VK_RETURN)){
		int z;
		for(z=0;z<NN;z++){
			if(state[nextx*NN*NN+nexty*NN+z]==0){
				Logger::Print("Human : Choose (%d,%d)",nextx,nexty);
				return 1;
				break;
			}
		}
	}
	return 0;
}

int Human::Close(){
	return 0;
}