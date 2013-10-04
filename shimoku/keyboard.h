#ifndef _KEYBOARD_H
#define _KEYBOARD_H

#include "common.h"

class Keyboard{
private:
	BYTE up[256];
	BYTE key[256];
	BYTE old[256];
	bool fst;
public:
	Keyboard(){
		memset(key,0,sizeof(key));
		memset(old,0,sizeof(old));
		memset(up,0,sizeof(up));
		fst=false;
	};
	virtual ~Keyboard(){};
	virtual int Update(){
		memcpy_s(old,256,key,256);
		memcpy_s(key,256,up,256);
		fst=true;
		return 0;
	}
	virtual int Set(int i,int flag){
		up[i]=flag;
		return 0;
	}
	virtual bool Get(int i){
		return (key[i]!=0)&&fst;
	}
	virtual bool GetDown(int i){
		return ((key[i]!=0 && old[i]==0))&&fst;
	}
	virtual bool GetUp(int i){
		return ((key[i]==0 && old[i]!=0))&&fst;
	}
};


#endif _KEYBOARD_H