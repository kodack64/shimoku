#include"woodbase.h"
#include "game_common.h"

WoodBase::WoodBase(){
	vertex=NULL;
	edge=NULL;
	color=NULL;
}
WoodBase::~WoodBase(){
	SAFE_DELETE_ARRAY(vertex);
	SAFE_DELETE_ARRAY(color);
}

int WoodBase::Init(Vec3d center,pdColor col,double down_width,double up_width,double depth){
	uw=uh=up_width;
	dw=dh=down_width;
	de=depth;
	mypos=center;
	mycol=col;
	vertex=new Vec3d[8];
	vertex[0]=mypos+Vec3d(-uw/2,	-uh/2,	de/2);
	vertex[1]=mypos+Vec3d(uw/2,		-uh/2,	de/2);
	vertex[2]=mypos+Vec3d(uw/2,		uh/2,	de/2);
	vertex[3]=mypos+Vec3d(-uw/2,	uh/2,	de/2);
	vertex[4]=mypos+Vec3d(-dw/2,	-dh/2,	-de/2);
	vertex[5]=mypos+Vec3d(dw/2,		-dh/2,	-de/2);
	vertex[6]=mypos+Vec3d(dw/2,		dh/2,	-de/2);
	vertex[7]=mypos+Vec3d(-dw/2,	dh/2,	-de/2);
	color=new pdColor[6];
	color[0]=mycol;
	color[1]=mycol;
	color[2]=mycol;
	color[3]=mycol;
	color[4]=mycol;
	color[5]=mycol;
	return 0;
}

int WoodBase::Main(){
	return 0;
}

int WoodBase::Draw(){
	int i;
	int edge[][4]={
		{0,1,2,3},
		{0,4,5,1},
		{1,5,6,2},
		{2,6,7,3},
		{3,7,4,0},
		{7,6,5,4},
	};
	GLfloat vtex[][2]={
		{0.0,0.0},
		{1.0,0.0},
		{1.0,1.0},
		{0.0,1.0}
	};
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture( GL_TEXTURE_2D, myTex->texture );
	glBegin(GL_QUADS);
	for(i=0;i<6;i++){

		Vec3d t=VecCross(vertex[edge[i][1]]-vertex[edge[i][0]],vertex[edge[i][3]]-vertex[edge[i][0]]);
		t/=t.length();
		glNormal3d(t.x,t.y,t.z);

		glColor4d(color[i].r,color[i].g,color[i].b,color[i].a);
		GLfloat material[] = {(float)color[i].r,(float)color[i].g,(float)color[i].b,(float)color[i].a};
		glMaterialfv(GL_FRONT_AND_BACK , GL_AMBIENT_AND_DIFFUSE , material); 

		for(int j=0;j<4;j++){
			glTexCoord2f(vtex[j][0],vtex[j][1]);
			glVertex3d(vertex[edge[i][j]].x,vertex[edge[i][j]].y,vertex[edge[i][j]].z);
		}
	}
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	return 0;
}