#ifndef __PDBASE_H_
#define __PDBASE_H_

#include "common.h"

//VEC
class Vec2d{
public:
	Vec2d(){x=y=0;}
	Vec2d(double p,double q){x=p;y=q;}
	double x;
	double y;

	Vec2d operator + (const Vec2d dvec) const {
		Vec2d v;
		v.x = x + dvec.x;
		v.y = y + dvec.y;
		return v;
	};

	Vec2d operator - (const Vec2d dvec) const {
		Vec2d v;
		v.x = x - dvec.x;
		v.y = y - dvec.y;
		return v;
	};

	Vec2d operator * (double d) const {
		Vec2d v;
		v.x = x * d;
		v.y = y * d;
		return v;
	};

	Vec2d operator / (double d) const {
		Vec2d v;
		if(d < EPS){
			return *this;
		}
		v.x = x / d;
		v.y = y / d;
		return v;
	};

	Vec2d& operator += (const Vec2d dvec) {
		x += dvec.x;
		y += dvec.y;
		return *this;
	};

	Vec2d& operator -= (const Vec2d dvec) {
		x -= dvec.x;
		y -= dvec.y;
		return *this;
	};

	Vec2d& operator *= (double d) {
		x *= d;
		y *= d;
		return *this;
	};

	Vec2d& operator /= (double d) {
		if(d < EPS){
			return *this;
		}
		x /= d;
		y /= d;
		return *this;
	};
	double length(){return sqrt(x * x + y * y);}
};

class Vec3d{
public:
	Vec3d(){x=y=z=0;}
	Vec3d(double p,double q,double r){x=p;y=q;z=r;}
	double x;
	double y;
	double z;
	Vec3d operator + (const Vec3d dvec) const {
		Vec3d v3;
		v3.x = x + dvec.x;
		v3.y = y + dvec.y;
		v3.z = z + dvec.z;
		return v3;
	};

	Vec3d operator - (const Vec3d dvec) const {
		Vec3d v3;
		v3.x = x - dvec.x;
		v3.y = y - dvec.y;
		v3.z = z - dvec.z;
		return v3;
	};

	Vec3d operator * (double d) const {
		Vec3d v3;
		v3.x = x * d;
		v3.y = y * d;
		v3.z = z * d;
		return v3;
	};

	Vec3d operator / (double d) const {
		Vec3d v3;
		if(d == 0.0){
			return v3;
		}
		v3.x = x / d;
		v3.y = y / d;
		v3.z = z / d;
		return v3;
	};

	Vec3d& operator += (const Vec3d dvec) {
		x += dvec.x;
		y += dvec.y;
		z += dvec.z;
		return *this;
	};

	Vec3d& operator -= (const Vec3d dvec) {
		x -= dvec.x;
		y -= dvec.y;
		z -= dvec.z;
		return *this;
	};

	Vec3d& operator *= (double d) {
		x *= d;
		y *= d;
		z *= d;
		return *this;
	};
	Vec3d& operator /= (double d) {
		if(d == 0.0){
			return *this;
		}

		x /= d;
		y /= d;
		z /= d;
		return *this;
	};
	double length(){return sqrt(x * x + y * y + z * z);}
};

Vec3d VecCross (Vec3d p , Vec3d q);
Vec2d VecCross (Vec2d p , Vec2d q);
Vec3d VecDot (Vec3d p , Vec3d q);
Vec2d VecDot (Vec2d p , Vec2d q);


//COLORS
class pdColor{
public:
	pdColor(){r=g=b=0.0;a=1.0;}
	pdColor(double rd,double gd,double bd){r=rd;g=gd;b=bd;a=1.0;}
	pdColor(double rd,double gd,double bd,double ad){r=rd;g=gd;b=bd;a=ad;}
	double r;
	double g;
	double b;
	double a;
};

/* preset function*/

//Screen
int ClearScreen();
int SetScreenColor(pdColor);
int SwapScreen();

//Draw
int DrawLine(Vec2d*,pdColor*,int num);
int DrawLine(Vec3d*,pdColor*,int num);
int DrawPolygon(Vec2d*,pdColor*,int num);
int DrawPolygon(Vec3d*,pdColor*,int num);
int DrawPolygon(Vec2d*,int[][3],pdColor*,int num);
int DrawPolygon(Vec3d*,int[][3],pdColor*,int num);
int DrawPolygon(Vec3d*,int[][4],pdColor*,int num);
int DrawCircle(Vec2d,pdColor,double r);
int DrawCircle(Vec3d,pdColor,double r);
int DrawBall(Vec2d,pdColor,double r);
int DrawBall(Vec3d,pdColor,double r);
int DrawCylinder(Vec3d,pdColor,double r,double len,double theta,double phi);
int DrawString(const char *str,Vec3d,pdColor);
int DrawString(const char *str,Vec2d,pdColor);

#endif __PDBASE_H_