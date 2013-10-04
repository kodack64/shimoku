#include "game.h"

int Game::InitMenu(){
	SetScreenColor(pdColor(0.7,0.7,0.7));
	menust=0;
	dllselector[0]->Reset();
	dllselector[1]->Reset();
	return 0;
}

int Game::ProcMenu(){
	if(replay){
		isCom[0]=false;
		comDllNum[0]=0;
		isCom[1]=false;
		comDllNum[1]=0;
		world->ResetBall();
		return 1;
	}

	if(menust<2){
		if(keyboard->GetDown(VK_DOWN) || keyboard->GetDown(VK_RIGHT) || mouse->GetRoll()<0){
			dllselector[menust]->Move(1);
		}
		if(keyboard->GetDown(VK_UP) || keyboard->GetDown(VK_LEFT) || mouse->GetRoll()>0){
			dllselector[menust]->Move(-1);
		}
		if(keyboard->GetDown(VK_RETURN) || mouse->GetLeftDown()){
			dllselector[menust]->Decide();
			menust++;
		}
	}else{
		if(keyboard->GetDown(VK_RETURN) || mouse->GetLeftDown()){
			for(int i=0;i<2;i++){
				if(dllselector[i]->GetDecide()==dllmanager->GetDllNum()){
					isCom[i]=false;
					comDllNum[i]=0;
				}else{
					isCom[i]=true;
					comDllNum[i]=dllselector[i]->GetDecide();
				}
			}
			return 1;
		}
	}
	if(menust>0 && mouse->GetRightDown()){
		menust--;
		dllselector[menust]->UnDecide();
	}
	return 0;
}

int Game::DrawMenu(){
//	DrawString("Menu",Vec2d(-300,200),pdColor(0,0,0));
	DrawString("Brown",Vec2d(-180,-200),pdColor(0,0,0));
	DrawString("Black",Vec2d(180,-200),pdColor(0,0,0));
	DrawString("VS",Vec2d(-20,0),pdColor(0,0,0));
	dllselector[0]->Draw();
	dllselector[1]->Draw();
	if(menust==2){
		DrawString("OK?",Vec2d(-20,200),pdColor(0,0,0));
	}
	return 0;
}