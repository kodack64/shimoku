#include "game.h"
#include "logger.h"

int Game::InitResult(){
	if(winner==1){
		Logger::Print("Game : Brown-%s Win",isCom[0]?dllmanager->GetDllName(dllselector[0]->GetDecide()).c_str():"Human");
	}else if(winner==-1){
		Logger::Print("Game : Brown-%s Win",isCom[1]?dllmanager->GetDllName(dllselector[1]->GetDecide()).c_str():"Human");
	}else{
		Logger::Print("Game : Draw");
	}
	return 0;
}

int Game::ProcResult(){
	if(mouse->GetDiff().length()!=0){
		if(mouse->GetLeft()){
			camera->MovePolar(0,mouse->GetDiff().y*0.01,mouse->GetDiff().x*0.01);
		}
	}
	if(mouse->GetRight()){
		camera->Reset();
	}
	if(mouse->GetRoll()!=0){
		camera->Approach(1.0+5e-2*mouse->GetRoll());
	}
	if(keyboard->GetDown(VK_RETURN)){
		return 1;
	}
	return 0;
}

int Game::DrawResult(){
	world->Draw();
//	DrawString("Result",Vec2d(-300,200),pdColor(0,0,0));
	char buf[256];
	sprintf_s(buf,256,"Turn : %2d",turn+1);
	DrawString(buf,Vec2d(-glutGet(GLUT_WINDOW_WIDTH)/2+30,-glutGet(GLUT_WINDOW_HEIGHT)/2+100),pdColor(0,0,0));
	if(winner==1){
		DrawString("Win : Brown Player",Vec2d(-glutGet(GLUT_WINDOW_WIDTH)/2+30,-glutGet(GLUT_WINDOW_HEIGHT)/2+70),pdColor(0,0,0));
	}else if(winner==-1){
		DrawString("Win : Black Player",Vec2d(-glutGet(GLUT_WINDOW_WIDTH)/2+30,-glutGet(GLUT_WINDOW_HEIGHT)/2+70),pdColor(0,0,0));
	}else{
		DrawString("Draw",Vec2d(-glutGet(GLUT_WINDOW_WIDTH)/2+30,-glutGet(GLUT_WINDOW_HEIGHT)/2+70),pdColor(0,0,0));
	}
	return 0;
}