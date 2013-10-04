#include "woodball.h"
#include "inimanager.h"

WoodBall::WoodBall(){
}

WoodBall::~WoodBall(){
}

int WoodBall::Init(Vec3d center,pdColor fscol,pdColor sccol,double s_r){
	mypos=center;
	myfscol=fscol;
	mysccol=sccol;
	r=s_r;
	mystate=0;
	atr=0;
	colphase=0.0;
	return 0;
}

int WoodBall::Main(){
	return 0;
}

int WoodBall::GetState(){
	return mystate;
}
void WoodBall::SetState(int st,int _atr){
	mystate=st;
	atr=_atr;
}

int WoodBall::Draw(){
	pdColor c;
	if(mystate==0){
		return 0;
	}else if(mystate==1){
		c=myfscol;
//		DrawBall(mypos,myfscol,r);
	}else if(mystate==-1){
		c=mysccol;
//		DrawBall(mypos,mysccol,r);
	}else{
		assert(false);
	}

	glPushMatrix();

//	glEnable(GL_TEXTURE_2D);
//	glBindTexture( GL_TEXTURE_2D, myTex->texture );

	if(atr==0){
		glColor4d(c.r,c.g,c.b,c.a);
		GLfloat material[] = {(float)c.r,(float)c.g,(float)c.b,(float)c.a};
		glMaterialfv(GL_FRONT_AND_BACK , GL_AMBIENT_AND_DIFFUSE , material); 
	}else{
		colphase+=0.03;
		glColor4d(c.r,c.g,c.b,0.6+0.4*sin(colphase));
		GLfloat material[] = {(float)c.r,(float)c.g,(float)c.b,(float)(0.6+0.4*sin(colphase))};
		glMaterialfv(GL_FRONT_AND_BACK , GL_AMBIENT_AND_DIFFUSE , material); 
	}


	glTranslated(mypos.x,mypos.y,mypos.z);

//	glEnable(GL_TEXTURE_GEN_S);
//	glEnable(GL_TEXTURE_GEN_T);

	if(IniManager::ReadInt("Graphic","WireFrame",0)==1){
		if(mystate==-1){
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			glutSolidSphere(r,10,10);
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}else if(mystate==1){
			glutSolidSphere(r,10,10);
		}
	}else{
		glutSolidSphere(r,50,50);
	}
//	glDisable(GL_TEXTURE_GEN_S);
//	glDisable(GL_TEXTURE_GEN_T);

//	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	return 0;
}

void WoodBall::SetReach(bool set){
	isReach=set;
}