#include "camera.h"
#include "camera_common.h"
#include "inimanager.h"

Camera::Camera(){
	s_ex=IniManager::ReadDouble("Camera","eye_x",DEF_EYE_X);
	s_ey=IniManager::ReadDouble("Camera","eye_y",DEF_EYE_Y);
	s_ez=IniManager::ReadDouble("Camera","eye_z",DEF_EYE_Z);
	s_ox=IniManager::ReadDouble("Camera","org_x",DEF_ORG_X);
	s_oy=IniManager::ReadDouble("Camera","org_y",DEF_ORG_Y);
	s_oz=IniManager::ReadDouble("Camera","org_z",DEF_ORG_Z);
	minr=IniManager::ReadDouble("Camera","near",DEF_CAM_NEAR);
	maxr=IniManager::ReadDouble("Camera","far",DEF_CAM_FAR);
	fovy=IniManager::ReadDouble("Camera","fovy",DEF_CAM_FOVY);
	min_theta=IniManager::ReadInt("Camera","min_theta",DEF_CAM_MINTHETA);
	max_theta=IniManager::ReadInt("Camera","max_theta",DEF_CAM_MAXTHETA);
	min_theta=min_theta*PI/180.0;
	max_theta=max_theta*PI/180.0;
	Reset();
	UpdateVectorToPolar();
}

Camera::~Camera(){
}

void Camera::Reset(){
	org=Vec3d(s_ox,s_oy,s_oz);
	eye=Vec3d(s_ex,s_ey,s_ez);
	UpdateVectorToPolar();
}

double Camera::GetFovy(){
	return fovy;
}
double Camera::GetNear(){
	return minr;
}
double Camera::GetFar(){
	return maxr;
}

double Camera::GetDist(){
	return r;
}
string Camera::ToString(){
	char buf[256];
	string str;
	sprintf_s(buf,256,"(%4lf,%4lf,%4lf)",eye.x,eye.y,eye.z);
	str=buf;
	return str;
}

void Camera::Update(){
	gluLookAt(eye.x, eye.y, eye.z , org.x, org.y, org.z, 0.0, 0.0, 1.0);
}

void Camera::SetPolar(double s_r,double s_theta,double s_phi){
	if(s_r<minr || s_r>maxr){
		return;
	}
	r=s_r;
	theta=s_theta;
	phi=s_phi;
	if(theta>max_theta)theta=max_theta;
	if(theta<min_theta)theta=min_theta;
	UpdatePolarToVector();
}
void Camera::SetOrgVector(double s_x,double s_y,double s_z){
	Vec3d send=Vec3d(s_x,s_y,s_z);
	org=send;
	UpdateVectorToPolar();
}
void Camera::MovePolar(double s_r,double s_theta,double s_phi){
	if(r+s_r<minr || r+s_r>maxr){
		return;
	}
	r+=s_r;
	theta+=s_theta;
	phi+=s_phi;
	phi+=((int)(phi/2/PI))*2*PI;
	theta+=((int)(theta/2/PI))*2*PI;
	if(theta>max_theta)theta=max_theta;
	if(theta<min_theta)theta=min_theta;
	UpdatePolarToVector();
}
void Camera::MoveOrgVector(double s_x,double s_y,double s_z){
	Vec3d diff=Vec3d(s_x,s_y,s_z);
	eye+=diff;
	org+=diff;
}

Vec3d Camera::GetVector(){
	return eye;
}
Vec3d Camera::GetOrigine(){
	return org;
}

void Camera::Approach(double ap){
	if(r*ap<minr || r*ap>maxr){
		return;
	}
	r*=ap;
	UpdatePolarToVector();
}

void Camera::UpdatePolarToVector(){
	eye.x=org.x+r*sin(theta)*cos(phi);
	eye.y=org.y-r*sin(theta)*sin(phi);
	eye.z=org.z+r*cos(theta);
}

void Camera::UpdateVectorToPolar(){
	r = (eye-org).length();
	theta = acos((eye.z-org.z)/r);
	if(sin(theta)==0){
		phi=0;
	}else{
		phi = acos((eye.x-org.x)/(r*sin(theta)));
	}
	UpdatePolarToVector();
}