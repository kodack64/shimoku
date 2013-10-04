
#include "myplugin.h"

// �R���s���[�^�̖��O������buf�ɓ���܂��B
void CALLBACK getName(char* buf){
	sprintf_s(buf,MAX_NAME,"RandomChoice");
}

// �C���X�^���X�������Ɉ�x�����Ă΂�܂�
void MyPlugin::init(){
	logPrint("Initialized");
	myrand = new MersenneTwister;
}

// �C���X�^���X�J�����Ɉ�x�����Ă΂�܂�
void MyPlugin::close(int winner){
	if(winner==1)logPrint("Win");
	if(winner==-1)logPrint("Lose");
	if(winner==0)logPrint("Draw");
	logPrint("Closed");
	delete myrand;
}

// Main Algorithm
void MyPlugin::think(){

	//time�ŗ���������������Ɠ������ɏ���������ė����񂪓����ɂȂ�̂�
	//��U�͍ēx���g�̗�����p���ė��������������Ď��g�Ύ��g�̎��̃����_�������ێ�����
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