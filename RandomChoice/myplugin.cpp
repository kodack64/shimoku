#include "myplugin.h"

MyPlugin* MyPlugin::myPlugin[PLUGIN_NUM]={NULL,NULL};

Plugin* CALLBACK MyPlugin::createInstance(){
	for(int i=0;i<PLUGIN_NUM;i++){
		if(myPlugin[i]!=NULL){
			continue;
		}else{
			myPlugin[i]=new MyPlugin;
			return myPlugin[i];
		}
	}
	return NULL;
}
void CALLBACK MyPlugin::destroyInstance(){
	for(int i=0;i<PLUGIN_NUM;i++){
		if(myPlugin[i]!=NULL){
			SAFE_DELETE(myPlugin[i])
		}
	}
}

