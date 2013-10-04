#include "world.h"
#include "world_design.h"
#include "logger.h"

World::World()
:img_ball(NULL)
,img_base(NULL)
,img_bar(NULL){
}

World::~World(){
}

int World::Init(){
	Logger::Print("World : Initialize WoodBase WoodBar WoodBall");
	img_ball=new JPEG("wood1.jpg");
	img_bar=new JPEG("wood2.jpg");
	img_base=new JPEG("wood3.jpg");
	int i,j,k;
	Vec3d offset;
	offset=Vec3d(
		-(NN-1.0)*BAR_WIDTH_DIFF/2.0,
		-(NN-1.0)*BAR_WIDTH_DIFF/2.0,
		0);
	woodbase = new WoodBase;
	woodbase->Init(
		Vec3d(0,0,0),
		pdColor(1.0,0.5,0.3,1.0),
		BASE_WIDTH_DOWN,
		BASE_WIDTH_UP,
		BASE_DEPTH
		);
	woodbase->SetTexture(img_base);
	for(i=0;i<NN;i++){
		for(j=0;j<NN;j++){
		woodbar[i][j]=new WoodBar;

		woodbar[i][j]->Init(
			offset+Vec3d(i*BAR_WIDTH_DIFF,j*BAR_WIDTH_DIFF,BASE_DEPTH/2),
			pdColor(200.0/256,100.0/256,32.0/256,0.7),
			pdColor(200.0/256,100.0/256,32.0/256,1.0),
			BAR_SIZE,
			BAR_HEIGHT
			);
		woodbar[i][j]->SetTexture(img_bar);

		for(k=0;k<NN;k++){
				woodball[i][j][k]=new WoodBall;
				woodball[i][j][k]->Init(
					offset+Vec3d(i*BAR_WIDTH_DIFF,j*BAR_WIDTH_DIFF,BASE_DEPTH/2+BALL_SIZE+k*BAR_DEPTH_DIFF),
					pdColor(224.0/256,1.0/2,32.0/256,0.9),
					pdColor(0,0,0,0.9),
					BALL_SIZE);
				woodball[i][j][k]->SetTexture(img_ball);
			}
		}
	}
	return 0;
}
int World::Close(){
	Logger::Print("World : Release WoodBase WoordBar WoodBall");
	int i,j,k;
	SAFE_DELETE(woodbase);
	for(i=0;i<NN;i++){
		for(j=0;j<NN;j++){
		SAFE_DELETE(woodbar[i][j]);
			for(k=0;k<NN;k++){
				SAFE_DELETE(woodball[i][j][k]);
			}
		}
	}
	SAFE_DELETE(img_ball);
	SAFE_DELETE(img_bar);
	SAFE_DELETE(img_base);
	return 0;
}

int World::Main(void){
	int i,j,k;
	woodbase->Main();
	for(i=0;i<NN;i++){
		for(j=0;j<NN;j++){
		woodbar[i][j]->Main();
			for(k=0;k<NN;k++){
				woodball[i][j][k]->Main();
			}
		}
	}
	return 0;
}

void World::ResetBall(){
	int i,j,k;
	for(i=0;i<NN;i++){
		for(j=0;j<NN;j++){
			for(k=0;k<NN;k++){
				woodball[i][j][k]->SetState(0,0);
			}
			woodbar[i][j]->SetState(0);
		}
	}
	ResetNextBallPos();
}
void World::SetBallState(int x,int y,int z,int st){
	woodball[x][y][z]->SetState(st,0);
	woodbar[x][y]->SetState(0);
}
void World::ResetNextBallPos(){
	kx=-1;
	ky=-1;
	kz=-1;
}
void World::SetNextBallPos(int x,int y,int z,int st){
	if(z>=0 && z<NN)	woodball[x][y][z]->SetState(st,1);
	woodbar[x][y]->SetState(st);
	kx=x;
	ky=y;
	kz=z;
}
void World::EraseNextBallPos(){
	if(kx==-1 || ky==-1 || kz==-1)return;
	if(kz>=0 && kz<NN)	woodball[kx][ky][kz]->SetState(0,0);
	woodbar[kx][ky]->SetState(0);
}
int World::Judge(){
	int i,j,k;
	int sum;
	for(i=0;i<NN;i++){
		for(j=0;j<NN;j++){
			//zé≤
			sum=0;
			for(k=0;k<NN;k++){
				sum+=woodball[i][j][k]->GetState();
			}
			if(abs(sum)==NN)return sum/NN;
			//yé≤
			sum=0;
			for(k=0;k<NN;k++){
				sum+=woodball[i][k][j]->GetState();
			}
			if(abs(sum)==NN)return sum/NN;
			//xé≤
			sum=0;
			for(k=0;k<NN;k++){
				sum+=woodball[k][i][j]->GetState();
			}
			if(abs(sum)==NN)return sum/NN;
		}
	}
	for(i=0;i<NN;i++){
		//yz
		sum=0;
		for(j=0;j<NN;j++){
			sum+=woodball[i][j][j]->GetState();
		}
		if(abs(sum)==NN)return sum/NN;
		sum=0;
		for(j=0;j<NN;j++){
			sum+=woodball[i][j][NN-1-j]->GetState();
		}
		if(abs(sum)==NN)return sum/NN;

		//xy
		sum=0;
		for(j=0;j<NN;j++){
			sum+=woodball[j][j][i]->GetState();
		}
		if(abs(sum)==NN)return sum/NN;
		sum=0;
		for(j=0;j<NN;j++){
			sum+=woodball[j][NN-1-j][i]->GetState();
		}
		if(abs(sum)==NN)return sum/NN;

		//zx
		sum=0;
		for(j=0;j<NN;j++){
			sum+=woodball[j][i][j]->GetState();
		}
		if(abs(sum)==NN)return sum/NN;
		sum=0;
		for(j=0;j<NN;j++){
			sum+=woodball[NN-1-j][i][j]->GetState();
		}
		if(abs(sum)==NN)return sum/NN;
	}
	//xyz
	sum=0;
	for(i=0;i<NN;i++){
		sum+=woodball[i][i][i]->GetState();
	}
	if(abs(sum)==NN)return sum/NN;
	sum=0;
	for(i=0;i<NN;i++){
		sum+=woodball[i][i][NN-1-i]->GetState();
	}
	if(abs(sum)==NN)return sum/NN;
	sum=0;
	for(i=0;i<NN;i++){
		sum+=woodball[i][NN-1-i][i]->GetState();
	}
	if(abs(sum)==NN)return sum/NN;
	sum=0;
	for(i=0;i<NN;i++){
		sum+=woodball[i][NN-1-i][NN-1-i]->GetState();
	}
	if(abs(sum)==NN)return sum/NN;
	return 0;
}
int World::RJudge(int ph){
	int i,j,k;
	int sum;
	int NNM=NN-1;
	for(i=0;i<NN;i++){
		for(j=0;j<NN;j++){
			//zé≤
			sum=0;
			for(k=0;k<NN;k++){
				sum+=woodball[i][j][k]->GetState();
			}
			if(sum==NNM*ph)return 1;
			//yé≤
			sum=0;
			for(k=0;k<NN;k++){
				sum+=woodball[i][k][j]->GetState();
			}
			if(sum==NNM*ph)return 1;
			//xé≤
			sum=0;
			for(k=0;k<NN;k++){
				sum+=woodball[k][i][j]->GetState();
			}
			if(sum==NNM*ph)return 1;
		}
	}
	for(i=0;i<NN;i++){
		//yz
		sum=0;
		for(j=0;j<NN;j++){
			sum+=woodball[i][j][j]->GetState();
		}
		if(sum==NNM*ph)return 1;
		sum=0;
		for(j=0;j<NN;j++){
			sum+=woodball[i][j][NN-1-j]->GetState();
		}
		if(sum==NNM*ph)return 1;

		//xy
		sum=0;
		for(j=0;j<NN;j++){
			sum+=woodball[j][j][i]->GetState();
		}
		if(sum==NNM*ph)return 1;
		sum=0;
		for(j=0;j<NN;j++){
			sum+=woodball[j][NN-1-j][i]->GetState();
		}
		if(sum==NNM*ph)return 1;

		//zx
		sum=0;
		for(j=0;j<NN;j++){
			sum+=woodball[j][i][j]->GetState();
		}
		if(sum==NNM*ph)return 1;
		sum=0;
		for(j=0;j<NN;j++){
			sum+=woodball[NN-1-j][i][j]->GetState();
		}
		if(sum==NNM*ph)return 1;
	}
	//xyz
	sum=0;
	for(i=0;i<NN;i++){
		sum+=woodball[i][i][i]->GetState();
	}
	if(sum==NNM*ph)return 1;
	sum=0;
	for(i=0;i<NN;i++){
		sum+=woodball[i][i][NN-1-i]->GetState();
	}
	if(sum==NNM*ph)return 1;
	sum=0;
	for(i=0;i<NN;i++){
		sum+=woodball[i][NN-1-i][i]->GetState();
	}
	if(sum==NNM*ph)return 1;
	sum=0;
	for(i=0;i<NN;i++){
		sum+=woodball[i][NN-1-i][NN-1-i]->GetState();
	}
	if(sum==NNM*ph)return 1;
	return 0;
}

int World::Draw(void){
	int i,j,k;
	woodbase->Draw();
	for(i=0;i<NN;i++){
		for(j=0;j<NN;j++){
		woodbar[i][j]->Draw();
			for(k=0;k<NN;k++){
				woodball[i][j][k]->Draw();
			}
		}
	}
	return 0;
}