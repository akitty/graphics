#ifndef _VECTOR3_H_
#define _VECTOR3_H_

#include "math.h"

#include <iostream>
using namespace std;

class Vector3 {
	friend ostream & operator<<(ostream& output,  Vector3& v){ 
	output << "x:"<<v.x<<" y:"<<v.y<<" z:"<<v.z;
		return output;
	}
	
public:
	float x,y,z;
	Vector3() {x=y=z=0;}
	Vector3(float x0,float y0,float z0)	{x=x0; y=y0; z=z0;}
	void set(float x0,float y0,float z0) {x=x0; y=y0; z=z0;}
	float get(int);
	void add(Vector3 &a)	{x=x+a.x;y=y+a.y;z=z+a.z;}
	Vector3& add(Vector3&a,Vector3&b)	{Vector3* v = new Vector3(a.x+b.x,a.y+b.y,a.z+b.z); return *v;}
	Vector3& operator+(Vector3& );
	float operator[](int);
	Vector3& operator-(Vector3&);
	void sub(Vector3& a) {x=x-a.x; y=y-a.y; z=z-a.z;}
	Vector3& sub(Vector3& a,Vector3& b) {Vector3* v = new Vector3(a.x-b.x,a.y-b.y,a.z-b.z); return *v;}
	void scalar(float s) {x=x*s; y=y*s; z=z*s;}
	float dot(Vector3& a) {return x*a.x+y*a.y+z*a.z;}
	void cross(Vector3&); 
	float length();
	void normalize() {scalar(1.0/length());}
	void print();
};


#endif