
#include "myplugin.h"

// コンピュータの名前を引数bufに入れます。
void CALLBACK getName(char* buf){
	sprintf_s(buf,MAX_NAME,"RandomChoice");
}

// インスタンス生成時に一度だけ呼ばれます
void MyPlugin::init(){
	logPrint("Initialized");
	myrand = new MersenneTwister;
}

// インスタンス開放時に一度だけ呼ばれます
void MyPlugin::close(int winner){
	if(winner==1)logPrint("Win");
	if(winner==-1)logPrint("Lose");
	if(winner==0)logPrint("Draw");
	logPrint("Closed");
	delete myrand;
}

// Main Algorithm
void MyPlugin::think(){

	//timeで乱数を初期化すると同時刻に初期化されて乱数列が同じになるので
	//後攻は再度自身の乱数を用いて乱数を初期化して自身対自身の時のランダム性を維持する
	if(getOrderCount()==1){
		myrand->sgenrand((unsigned)time(NULL)+myrand->Next(100));
	}

	int x,y;
	do{
		x=myrand->Next(NN);
		y=myrand->Next(NN);
	}while(getDomain(x,y,NN-1)!=0);
	logPrint("Choose (%d,%d)",x,y);
	setX(x);
	setY(y);
}