#include "game.h"
#include "logger.h"
#include "player_com.h"
#include "player_human.h"
#include "player_replay.h"
#include "dirmanager.h"
#include "inimanager.h"

int Game::InitPlay(){
	Logger::Print("Game : Initialize Players");
	int i;
	for(i=0;i<2;i++){
		if(replay){
			player[i]=new Replayer;
			((Replayer*)player[i])->Init(keyboard,&replayOrder);
		}else if(isCom[i]){
			player[i]=new Com;
			((Com*)player[i])->Init(dllmanager->GetDllPath(comDllNum[i]));
		}else{
			player[i]=new Human;
			((Human*)player[i])->Init(keyboard);
		}
	}
	Logger::Print("Game : Brown-%s vs Black-%s"
		,isCom[0]?dllmanager->GetDllName(dllselector[0]->GetDecide()).c_str():"Human"
		,isCom[1]?dllmanager->GetDllName(dllselector[1]->GetDecide()).c_str():"Human");
	turn=0;
	memset(state,0,sizeof(state));
	isReach[0]=false;
	isReach[1]=false;
	world->ResetBall();

	rec = IniManager::ReadInt("Application","Rec",0);
	if(replay)rec=0;
	if(rec!=0){
		int c=IniManager::ReadInt("Application","RecCount",0);
		char buf[256];
		sprintf_s(buf,256,"kifu%d.txt",c);
		fopen_s(&kifu_fp,buf,"w");
		if(kifu_fp==NULL){
			rec=0;
		}else{
			Logger::Print("Game : Record On");
			rec=1;
			sprintf_s(buf,256,"%d",c+1);
			IniManager::WriteInt("Application","RecCount",c+1);
		}
	}else{
		kifu_fp=NULL;
	}

	if(repeat==0){
		repeat = IniManager::ReadInt("Application","Repeat",0);
		if(replay)repeat=0;
		if(repeat!=0){
			Logger::Print("Game : Repeat On");
			repeatCount=IniManager::ReadInt("Application","RepeatCount",1);
			if(repeatCount<1)repeatCount=1;
			Logger::Print("Game : Repeat %d Times",repeatCount);
			repeatWinCount[0]=repeatWinCount[1]=repeatWinCount[2]=0;
		}
	}else{
		Logger::Print("Game : Repeat %d Rest",repeatCount);
	}

	return 0;
}

int Game::ProcPlay(){
	//カメラワークの操作
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

	int sx,sy,sz;
	//もしプレイヤーだったら現在指しているカーソルの処理
	if(!isCom[turn%2] && !replay){
		sx=player[turn%2]->GetX();
		sy=player[turn%2]->GetY();
		for(sz=0;sz<NN;sz++){
			if(state[sx*NN*NN+sy*NN+sz]==0){
				break;
			}
		}
		world->EraseNextBallPos();
		if(turn%2==0)world->SetNextBallPos(sx,sy,sz,1);
		else world->SetNextBallPos(sx,sy,sz,-1);
	}

	//思考ルーチンの実行
	int res;
	if(turn%2==0)res=player[turn%2]->Main(1,state);
	else res=player[turn%2]->Main(-1,state);

	//結論が出たら次のターンへ
	if(res==1){
		sx=player[turn%2]->GetX();
		sy=player[turn%2]->GetY();
		for(sz=0;sz<NN;sz++){
			if(state[sx*NN*NN+sy*NN+sz]==0){
				if(turn%2==0){
					state[sx*NN*NN+sy*NN+sz]=1;
					world->SetBallState(sx,sy,sz,1);
				}else{
					state[sx*NN*NN+sy*NN+sz]=-1;
					world->SetBallState(sx,sy,sz,-1);
				}
				break;
			}
		}
		if(kifu_fp!=NULL)fprintf(kifu_fp,"%d %d %d %d\n",turn,sx,sy,sz);
		if(isCom[turn%2]){
			((Com*)player[turn%2])->GetPlugin()->pushOrder(sx,sy,sz,1);
		}
		if(isCom[(turn+1)%2]){
			((Com*)player[(turn+1)%2])->GetPlugin()->pushOrder(sx,sy,sz,-1);
		}
		if(replay){
			((Replayer*)player[0])->PushOrder();
			((Replayer*)player[1])->PushOrder();
		}
		world->ResetNextBallPos();
		assert(sz<NN);
		winner=world->Judge();
		isReach[0]=(world->RJudge(1)==1);
		isReach[1]=(world->RJudge(-1)==1);
		if(abs(winner)==1){
			Logger::Print("Game : Release Players");
			if(isCom[0] && !replay){
				((Com*)(player[0]))->GetPlugin()->close(winner);
			}
			if(isCom[1] && !replay){
				((Com*)(player[1]))->GetPlugin()->close(-winner);
			}
			player[0]->Close();
			player[1]->Close();
			SAFE_DELETE(player[0]);
			SAFE_DELETE(player[1]);
			if(kifu_fp!=NULL)fclose(kifu_fp);
			if(repeat){
				if(repeatCount>1){
					if(winner==1){
						repeatWinCount[0]++;
					}else if(winner==-1){
						repeatWinCount[1]++;
					}else{
						repeatWinCount[2]++;
					}
					repeatCount--;
					InitPlay();
				}else{
					repeat=0;
					return 1;
				}
			}else{
				return 1;
			}
		}
		else turn++;
		if(turn==NN*NN*NN){
			winner=0;
			Logger::Print("Game : Release Players");
			if(isCom[0] && !replay){
				((Com*)(player[0]))->GetPlugin()->close(0);
			}
			if(isCom[1] && !replay){
				((Com*)(player[1]))->GetPlugin()->close(0);
			}
			player[0]->Close();
			player[1]->Close();
			SAFE_DELETE(player[0]);
			SAFE_DELETE(player[1]);
			if(kifu_fp!=NULL)fclose(kifu_fp);
			if(repeat){
				if(repeatCount>1){
					if(winner==1){
						repeatWinCount[0]++;
					}else if(winner==-1){
						repeatWinCount[1]++;
					}else{
						repeatWinCount[2]++;
					}
					repeatCount--;
					InitPlay();
				}else{
					repeat=0;
					return 1;
				}
			}else{
				return 1;
			}
		}
	}

	return 0;
}

int Game::DrawPlay(){
	world->Draw();
	if(repeat!=0){
		char buf[256];
		DrawString("Result",Vec2d(-300,140),pdColor(0,0,0));
		sprintf_s(buf,256,"Brown Win : %d",repeatWinCount[0]);
		DrawString(buf,Vec2d(-300,160),pdColor(0,0,0));
		sprintf_s(buf,256,"Black Win : %d",repeatWinCount[1]);
		DrawString(buf,Vec2d(-300,180),pdColor(0,0,0));
		sprintf_s(buf,256,"Draw : %d",repeatWinCount[2]);
		DrawString(buf,Vec2d(-300,200),pdColor(0,0,0));
		sprintf_s(buf,256,"Rest : %d",repeatCount);
		DrawString(buf,Vec2d(-300,220),pdColor(0,0,0));
	}else{
		char buf[256];
		sprintf_s(buf,256,"Turn : %2d %s (%s)",turn+1,isCom[turn%2]?"Com":"Player",turn%2==0?"Brown":"Black");
		DrawString(buf,Vec2d(-glutGet(GLUT_WINDOW_WIDTH)/2+30,-glutGet(GLUT_WINDOW_HEIGHT)/2+100),pdColor(0,0,0));

		if(isReach[0]){
			sprintf_s(buf,256,"%s (%s) - Reach!",isCom[0]?"Com":"Player","Brown");
			DrawString(buf,Vec2d(-glutGet(GLUT_WINDOW_WIDTH)/2+30,-glutGet(GLUT_WINDOW_HEIGHT)/2+70),pdColor(0,0,0));
		}
		if(isReach[1]){
			sprintf_s(buf,256,"%s (%s) - Reach!",isCom[1]?"Com":"Player","Black");
			DrawString(buf,Vec2d(-glutGet(GLUT_WINDOW_WIDTH)/2+30,-glutGet(GLUT_WINDOW_HEIGHT)/2+40),pdColor(0,0,0));
		}
	}
	return 0;
}