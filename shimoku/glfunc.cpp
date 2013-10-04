#include "glfunc.h"

Vec3d VecCross (Vec3d p , Vec3d q){
	Vec3d r;
	r.x = p.y*q.z-p.z*q.y;
	r.y = p.z*q.x-p.x*q.z;
	r.z = p.x*q.y-p.y*q.x;
	return r;
};
Vec2d VecCross (Vec2d p , Vec2d q){
	Vec2d r;
	r.x = p.x*q.y-p.y*q.x;
	r.y = p.y*q.x-p.x*q.y;
	return r;
};
Vec3d VecDot (Vec3d p , Vec3d q){
	Vec3d r;
	r.x=p.x*q.x;
	r.y=p.y*q.y;
	r.z=p.z*q.z;
	return r;
};
Vec2d VecDot (Vec2d p , Vec2d q){
	Vec2d r;
	r.x = p.x*q.x;
	r.y = p.y*q.y;
	return r;
};

int ClearScreen(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_BLEND);
	return 0;
}

int SetScreenColor(pdColor c){
	glClearColor((GLclampf)c.r,(GLclampf)c.g,(GLclampf)c.b, (GLclampf)c.a);
	return 0;
}

int SwapScreen(){
	glDisable(GL_BLEND);
	glutSwapBuffers();
	return 0;
}

int DrawLine(Vec2d* v,pdColor* c,int num){
	glPushMatrix();
	glBegin(GL_LINE_STRIP);
	for(int n=0;n<num;n++){
		glColor4d(c[n].r,c[n].g,c[n].b,c[n].a);
		GLfloat material[] = {(float)c[n].r,(float)c[n].g,(float)c[n].b,(float)c[n].a};
		glMaterialfv(GL_FRONT_AND_BACK , GL_AMBIENT_AND_DIFFUSE , material); 
		glVertex2d(v[n].x,v[n].y);
	}
	glEnd();
	glPopMatrix();
	return 0;
}

int DrawLine(Vec3d* v,pdColor* c,int num){
	glPushMatrix();
	glBegin(GL_LINE_STRIP);
	for(int n=0;n<num;n++){
		glColor4d(c[n].r,c[n].g,c[n].b,c[n].a);
		GLfloat material[] = {(float)c[n].r,(float)c[n].g,(float)c[n].b,(float)c[n].a};
		glMaterialfv(GL_FRONT_AND_BACK , GL_AMBIENT_AND_DIFFUSE , material); 
		glVertex3d(v[n].x,v[n].y,v[n].z);
	}
	glEnd();
	glPopMatrix();
	return 0;
}

int DrawPolygon(Vec2d* v,pdColor* c,int num){
	glPushMatrix();
	glBegin(GL_POLYGON);
	glNormal3d(0,0,1);
	for(int n=0;n<num;n++){
		glColor4d(c[n].r,c[n].g,c[n].b,c[n].a);
		GLfloat material[] = {(float)c[n].r,(float)c[n].g,(float)c[n].b,(float)c[n].a};
		glMaterialfv(GL_FRONT_AND_BACK , GL_AMBIENT_AND_DIFFUSE , material); 
		glVertex2d(v[n].x,v[n].y);
	}
	glEnd();
	glPopMatrix();
	return 0;
}

int DrawPolygon(Vec3d* v,pdColor* c,int num){
	glPushMatrix();
	glBegin(GL_POLYGON);
	for(int n=0;n<num;n++){
		glColor4d(c[n].r,c[n].g,c[n].b,c[n].a);
		GLfloat material[] = {(float)c[n].r,(float)c[n].g,(float)c[n].b,(float)c[n].a};
		glMaterialfv(GL_FRONT_AND_BACK , GL_AMBIENT_AND_DIFFUSE , material); 
		glVertex3d(v[n].x,v[n].y,v[n].z);
	}
	glEnd();
	glPopMatrix();
	return 0;
}
int DrawPolygon(Vec2d* v,int edge[][3] ,pdColor* c,int num){
	glPushMatrix();
	for(int i=0;i<num;i++){
		glBegin(GL_POLYGON);
		glNormal3d(0,0,1);
		glColor4d(c[i].r,c[i].g,c[i].b,c[i].a);
		GLfloat material[] = {(float)c[i].r,(float)c[i].g,(float)c[i].b,(float)c[i].a};
		glMaterialfv(GL_FRONT_AND_BACK , GL_AMBIENT_AND_DIFFUSE , material); 
		for(int j=0;j<3;j++){
			glVertex2d(v[edge[i][j]].x,v[edge[i][j]].y);
		}
		glEnd();
	}
	glPopMatrix();
	return 0;
}
int DrawPolygon(Vec3d* v,int edge[][3] ,pdColor* c,int num){
	glPushMatrix();
	for(int i=0;i<num;i++){
		glBegin(GL_POLYGON);
		glNormal3d(0,0,1);
		glColor4d(c[i].r,c[i].g,c[i].b,c[i].a);
		GLfloat material[] = {(float)c[i].r,(float)c[i].g,(float)c[i].b,(float)c[i].a};
		glMaterialfv(GL_FRONT_AND_BACK , GL_AMBIENT_AND_DIFFUSE , material); 
		for(int j=0;j<3;j++){
			glVertex3d(v[edge[i][j]].x,v[edge[i][j]].y,v[edge[i][j]].z);
		}
		glEnd();
	}
	glPopMatrix();
	return 0;
}
int DrawPolygon(Vec3d* v,int edge[][4] ,pdColor* c,int num){
	glPushMatrix();
	for(int i=0;i<num;i++){
		glBegin(GL_POLYGON);
		glNormal3d(0,0,1);
		glColor4d(c[i].r,c[i].g,c[i].b,c[i].a);
		GLfloat material[] = {(float)c[i].r,(float)c[i].g,(float)c[i].b,(float)c[i].a};
		glMaterialfv(GL_FRONT_AND_BACK , GL_AMBIENT_AND_DIFFUSE , material); 
		for(int j=0;j<4;j++){
			glVertex3d(v[edge[i][j]].x,v[edge[i][j]].y,v[edge[i][j]].z);
		}
		glEnd();
	}
	glPopMatrix();
	return 0;
}

int DrawCircle(Vec2d v,pdColor c,double r){
	double theta,d;
	d=PI/360;
	glPushMatrix();
	glBegin(GL_LINE_STRIP);
	for (theta=0;theta<2*PI+d;theta+=d)
	{
		glColor4d(c.r,c.g,c.b,c.a);
		GLfloat material[] = {(float)c.r,(float)c.g,(float)c.b,(float)c.a};
		glMaterialfv(GL_FRONT_AND_BACK , GL_AMBIENT_AND_DIFFUSE , material); 
		glVertex2d( v.x+r*cos(theta) , v.y+r*sin(theta) );
    }
	glEnd();
	glPopMatrix();
	return 0;
}
int DrawCircle(Vec3d v,pdColor c,double r){
	glPushMatrix();
	glColor4d(c.r,c.g,c.b,c.a);
	GLfloat material[] = {(float)c.r,(float)c.g,(float)c.b,(float)c.a};
	glMaterialfv(GL_FRONT_AND_BACK , GL_AMBIENT_AND_DIFFUSE , material); 
	glTranslated(v.x,v.y,v.z);

	glutWireSphere(r,20,20);
	glPopMatrix();
	return 0;
}
int DrawBall(Vec2d v,pdColor c,double r){
	double theta,d;
	d=PI/360;
	glPushMatrix();
	glBegin(GL_POLYGON);
	glNormal3d(0,0,1);
	for (theta=0;theta<2*PI;theta+=d)
	{
		glColor4d(c.r,c.g,c.b,c.a);
		GLfloat material[] = {(float)c.r,(float)c.g,(float)c.b,(float)c.a};
		glMaterialfv(GL_FRONT_AND_BACK , GL_AMBIENT_AND_DIFFUSE , material); 
		glVertex2d( v.x+r*cos(theta) , v.y+r*sin(theta) );
    }
	glEnd();
	glPopMatrix();
	return 0;
}
int DrawBall(Vec3d v,pdColor c,double r){
	glPushMatrix();
	glColor4d(c.r,c.g,c.b,c.a);
		GLfloat material[] = {(float)c.r,(float)c.g,(float)c.b,(float)c.a};
		glMaterialfv(GL_FRONT_AND_BACK , GL_AMBIENT_AND_DIFFUSE , material); 
	glTranslated(v.x,v.y,v.z);
	glutSolidSphere(r,50,50);
	glPopMatrix();
	return 0;
}
int DrawCylinder(Vec3d v,pdColor c,double r,double len,double theta,double phi){
	glPushMatrix();
	glColor4d(c.r,c.g,c.b,c.a);
	GLfloat material[] = {(float)c.r,(float)c.g,(float)c.b,(float)c.a};
	glMaterialfv(GL_FRONT_AND_BACK , GL_AMBIENT_AND_DIFFUSE , material); 
	glTranslated(v.x,v.y,v.z);
	glutSolidCylinder(r,len,100,100);
	glPopMatrix();
	return 0;
}

int DrawString(const char *str,Vec2d p,pdColor c){
	glPushMatrix();
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glDisable(GL_LIGHTING);

	glLoadIdentity();
	gluOrtho2D(0,glutGet(GLUT_WINDOW_WIDTH), 0, glutGet(GLUT_WINDOW_HEIGHT));
	glPushAttrib(GL_CURRENT_BIT|GL_DEPTH_BUFFER_BIT);
	glDisable(GL_DEPTH_TEST);

	glColor4d(c.r,c.g,c.b,c.a);
	glRasterPos2d(glutGet(GLUT_WINDOW_WIDTH)/2+p.x,glutGet(GLUT_WINDOW_HEIGHT)/2-p.y); //¶‰º‚ªŒ´“_
	while(*str){
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *str);
//		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *str);
//		glutBitmapCharacter(GLUT_STROKE_ROMAN, *str);
//		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, *str);
		str++;
	}

	glPopAttrib();			
	glEnable(GL_LIGHTING);
	glPopMatrix(); 
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	return 0;
};