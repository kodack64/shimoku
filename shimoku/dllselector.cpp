#include "dllselector.h"

DllSelector::DllSelector(){
}

DllSelector::~DllSelector(){
}

void DllSelector::Init(Vec2d s_pos,DllManager* s_dllmn){
	pos=s_pos;
	dllmn=s_dllmn;
	Reset();
}
void DllSelector::Reset(){
	cur=dllmn->GetDllNum();
	decideflag=false;
}

void DllSelector::Move(int i){
	if(dllmn==NULL || i==0)return;
	cur+=i;
	if(cur<0)cur+=(int)(((-cur)/(dllmn->GetDllNum()+1))+1)*(dllmn->GetDllNum()+1);
	cur%=(dllmn->GetDllNum()+1);
}

void DllSelector::Decide(){
	decideflag=true;
	return;
}
void DllSelector::UnDecide(){
	decideflag=false;
	return;
}
int DllSelector::GetDecide(){
	if(decideflag){
		return cur;
	}else{
		assert(false);
		return 0;
	}
}

void DllSelector::Draw(){
	int shownum=3,count;
	count=cur+dllmn->GetDllNum()+1-shownum%(dllmn->GetDllNum()+1);
	count%=(dllmn->GetDllNum()+1);
	for(int i=-shownum;i<=shownum;i++){
		string name;
		if(count<dllmn->GetDllNum()){
			name=dllmn->GetDllName(count);
		}else{
			name="Human";
		}
		count++;
		count%=(dllmn->GetDllNum()+1);
		if(decideflag){
			if(i==0)
				DrawString(name.c_str(),pos+Vec2d(0,30)*i,pdColor(0,0,0));
			else
				DrawString(name.c_str(),pos+Vec2d(0,30)*i,pdColor(0,0,0,0.1));
		}else{
			double cp;
			if(i==0)cp=1.0;
			else cp=0.5-0.5*abs(i)/(shownum+1);
			DrawString(name.c_str(),pos+Vec2d(0,30)*i,pdColor(0,0,0,cp));
		}
	}
}

void DllSelector::Close(){
}