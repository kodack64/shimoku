
#include "appli.h"
#include "appli_common.h"
#include "logger.h"
#include "dirmanager.h"
#include "inimanager.h"

Appli::Appli(){
	plisten=NULL;
}

Appli::~Appli(){
}


int Appli::Init(int* argc,char** argv){
	//static class initialize
	DirManager::SetDir();
	IniManager::SetFile("setup.ini");

	//GL initialize
	Logger::Print("Application : Initialize OpenGL");
	glutInit(argc,argv);
	string section="Application";
	int winx=IniManager::ReadInt(section,"window_x",DEF_WINDOW_X);
	int winy=IniManager::ReadInt(section,"window_y",DEF_WINDOW_Y);
	int winposx=IniManager::ReadInt(section,"window_pos_x",DEF_WINDOW_POS_X);
	int winposy=IniManager::ReadInt(section,"window_pos_y",DEF_WINDOW_POS_Y);
	int fps=IniManager::ReadInt(section,"fps",DEF_FPS);
	int fullsc=IniManager::ReadInt(section,"fullscreen",DEF_FULLSCREEN);
	bool useLight=(IniManager::ReadInt(section,"UseLight",1)!=0);
	char title[MAX_PATH];
	sprintf_s(title,MAX_PATH,WINDOWTITLE);
	glutInitWindowSize(winx,winy);
	glutInitWindowPosition(winposx,winposy);
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE,GLUT_ACTION_GLUTMAINLOOP_RETURNS);
	glutInitDisplayMode(GLUT_RGBA|GLUT_DOUBLE|GLUT_DEPTH);
	glutCreateWindow(argv[0]);
	glutSetWindowTitle(title);

	//check replay or not
	if((*argc)>1){
		Listener::setReplayName(argv[1]);
	}

	//event regist
	Logger::Print("Application : Initialize Event Listener");
	plisten=new Listener;
	plisten->Init(winx,winy,winposx,winposy,fps,fullsc);
	glutDisplayFunc(plisten->Disp);
	glutMouseFunc(plisten->Mouse);
	glutMotionFunc(plisten->Motion);
	glutReshapeFunc(plisten->Reshape);
	glutTimerFunc(0,(plisten->Timer),0);
	glutKeyboardFunc(plisten->Keyboard);
	glutKeyboardUpFunc(plisten->KeyboardUp);
	glutSpecialFunc(plisten->SpecialKeyboard);
	glutSpecialUpFunc(plisten->SpecialKeyboardUp);


	if(IniManager::ReadInt("Graphic","WireFrame",0)==1){
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}


	//display initialize
	glClearColor(0,0,0,1);
	if(fullsc)glutFullScreen();
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glAlphaFunc(GL_GREATER, 0.5);
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	glDisable(GL_ALPHA_TEST);
	if(useLight){
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		glEnable(GL_LIGHT1);
		glEnable(GL_LIGHT2);
		GLfloat light0pos[] = { 10.0, 10.0, 3.0, 1.0 };
		glLightfv(GL_LIGHT0,GL_POSITION,light0pos);
		GLfloat light1pos[] = { -10.0, -10.0, 3.0, 1.0 };
		glLightfv(GL_LIGHT1,GL_POSITION,light1pos);
		GLfloat light2pos[] = { -0.0, -0.0, -10.0, 1.0 };
		glLightfv(GL_LIGHT2,GL_POSITION,light2pos);

		GLfloat lightcol[] = { 0.3f, 0.3f, 0.3f, 1.0f };
		GLfloat lightamb[] = { 0.1f, 0.1f, 0.1f, 1.0f };
		glLightfv(GL_LIGHT0, GL_DIFFUSE, lightcol);
		glLightfv(GL_LIGHT0, GL_SPECULAR, lightcol);
		glLightfv(GL_LIGHT0, GL_AMBIENT, lightamb);
		glLightfv(GL_LIGHT1, GL_DIFFUSE, lightcol);
		glLightfv(GL_LIGHT1, GL_SPECULAR, lightcol);
		glLightfv(GL_LIGHT1, GL_AMBIENT, lightamb);
		glLightfv(GL_LIGHT2, GL_DIFFUSE, lightcol);
		glLightfv(GL_LIGHT2, GL_SPECULAR, lightcol);
		glLightfv(GL_LIGHT2, GL_AMBIENT, lightamb);
	}
	if(/*useTexture*/ true){
		GLdouble genfunc[][4] = {
		  { 1.0, 0.0, 0.0, 0.0 },
		  { 0.0, 1.0, 0.0, 0.0 },
		  { 0.0, 0.0, 1.0, 0.0 },
		  { 0.0, 0.0, 0.0, 1.0 },
		};
/*		glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
		glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
		glTexGeni(GL_R, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
		glTexGeni(GL_Q, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
		glTexGendv(GL_S, GL_OBJECT_PLANE, genfunc[0]);
		glTexGendv(GL_T, GL_OBJECT_PLANE, genfunc[1]);
		glTexGendv(GL_R, GL_OBJECT_PLANE, genfunc[2]);
		glTexGendv(GL_Q, GL_OBJECT_PLANE, genfunc[3]);*/
		glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
		glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	}

	//srand
	srand((unsigned)time(NULL));
	return 0;
}

int Appli::Run(){
	Logger::Print("Application : Enter OpenGL MainLoop");
	glutMainLoop();
	return 0;
}

int Appli::Close(){
	Logger::Print("Application : Release Listener");
	if(plisten!=NULL)plisten->Close();
	SAFE_DELETE(plisten);
	return 0;
}