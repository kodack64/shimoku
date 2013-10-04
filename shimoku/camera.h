#ifndef _CAMERA_H
#define _CAMERA_H

#include "glfunc.h"

class Camera{
private:
	double s_ex;
	double s_ey;
	double s_ez;
	double s_ox;
	double s_oy;
	double s_oz;
	double min_theta;
	double max_theta;
	double minr;
	double maxr;
	double fovy;

	double r;
	double theta;
	double phi;

	Vec3d eye;

	Vec3d org;

public:

	Camera();
	virtual ~Camera();
	virtual void Reset();
	virtual string ToString();
	virtual void Update();

	virtual void SetPolar(double s_r,double s_theta,double s_phi);
	virtual void MovePolar(double s_r,double s_theta,double s_phi);
	virtual void SetOrgVector(double s_x,double s_y,double s_z);
	virtual void MoveOrgVector(double s_x,double s_y,double s_z);

	virtual double GetDist();
	virtual Vec3d GetVector();
	virtual Vec3d GetOrigine();
	virtual double GetFovy();
	virtual double GetNear();
	virtual double GetFar();

	virtual void Approach(double ap);

	virtual void UpdatePolarToVector();
	virtual void UpdateVectorToPolar();
};


#endif _CAMERA_H