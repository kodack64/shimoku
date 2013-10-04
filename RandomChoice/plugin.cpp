#include "plugin.h"

Plugin::Plugin(){
	int i;
	for(i=0;i<NN*NN*NN;i++){
		coordinate[i]=POINT_NOT_EXIST;
	}
	ordercount=0;
	memset(domain,0,sizeof(domain));
	memset(order,0,sizeof(order));
}
Plugin::~Plugin(){
}

void Plugin::pushOrder(int x,int y,int z,int d){
	domain[x][y][z]=d;
	coordinate[ordercount]=Point3d(x,y,z);
	order[x][y][z]=ordercount;
	ordercount++;
}
int Plugin::getDomain(int x,int y,int z){
	if(		0<=x && x<NN
		&&	0<=y && y<NN
		&&	0<=z && z<NN )
		return domain[x][y][z];
	else
		return 0;
}
int Plugin::getOrderCount(){
	return ordercount;
}
int Plugin::getOrder(int x,int y,int z){
	if(		0<=x && x<NN
		&&	0<=y && y<NN
		&&	0<=z && z<NN )
		return order[x][y][z];
	else
		return -1;
}
Point3d Plugin::getCoordinate(int o){
	if(0<=o && o<NN*NN*NN)
		return coordinate[o];
	else
		return POINT_NOT_EXIST;
}

void Plugin::logPrint(const char* str,...){
	va_list ap;
	va_start(ap,str);
	char buf[MAX_NAME];
	getName(buf);
	if(cons){
		printf_s("[dll] %s : ",buf);
		vprintf_s(str,ap);
		printf_s("\n");
	}
	else{
		if(logpath!=NULL){
			FILE *fp;
			fopen_s(&fp,logpath,"at");
			if(fp!=NULL){
				fprintf_s(fp,"[dll] %s : ",buf);
				vfprintf_s(fp,str,ap);
				fprintf_s(fp,"\n");
				fclose(fp);
			}
		}
	}
	va_end(ap);
}

void Plugin::setLogText(const char* buf){
	sprintf_s(logpath,MAX_PATH,"%s",buf);
	cons=false;
}

void Plugin::setLogConsole(){
	cons=true;
}