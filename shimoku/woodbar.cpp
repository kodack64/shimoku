#include "woodbar.h"
#include "inimanager.h"

WoodBar::WoodBar(){
}

WoodBar::~WoodBar(){
}

int WoodBar::Init(Vec3d center,pdColor color,pdColor oncolor,double s_r,double s_len){
	len=s_len;
	r=s_r;
	st=0;
	mycol=color;
	myoncol=oncolor;
	mypos=center;
	return 0;
}

int WoodBar::Main(){
	return 0;
}

int WoodBar::Draw(){
	pdColor c;
	if(st==0){
		c=mycol;
//		DrawCylinder(mypos,mycol,r,len,0,0);
	}else{
		c=myoncol;
//		DrawCylinder(mypos,myoncol,r,len,0,0);
	}

	glPushMatrix();

	glEnable(GL_TEXTURE_2D);
	glBindTexture( GL_TEXTURE_2D, myTex->texture );

//	glColor4d(c.r,c.g,c.b,c.a);
//	GLfloat material[] = {(float)c.r,(float)c.g,(float)c.b,(float)c.a};
//	glColor4d(c.r,c.g,c.b,1.0);
//	GLfloat material[] = {(float)c.r,(float)c.g,(float)c.b,(float)1.0};
	glColor4d(1.0f,c.g,c.b,c.a);
	GLfloat material[] = {(float)1.0f,(float)c.g,(float)c.b,(float)c.a};
	glMaterialfv(GL_FRONT_AND_BACK , GL_AMBIENT_AND_DIFFUSE , material); 

	glTranslated(mypos.x,mypos.y,mypos.z);

	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);

	if(IniManager::ReadInt("Graphic","WireFrame",0)==1){
		glutSolidCylinder(r,len,10,1);
	}else{
		glutSolidCylinder(r,len,30,1);
	}

	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);

	glDisable(GL_TEXTURE_2D);

	glPopMatrix();

	return 0;
}

int WoodBar::SetState(int i){
	st=i;
	return 0;
}