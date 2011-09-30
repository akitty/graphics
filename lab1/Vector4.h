#ifndef _VECTOR4_
#define _VECTOR4_

class Vector4 {
	float w,x,y,z;
public:
	Vector4() {w=x=y=z=0;}
	Vector4(float w0, float x0,float y0,float z0)	{w=w0; x=x0; y=y0; z=z0;}
	void set(float w0, float x0,float y0,float z0) {w=w0; x=x0; y=y0; z=z0;}
	float get(int);

	void add(Vector4 &a)	{w=w+a.w; x=x+a.x; y=y+a.y; z=z+a.z;}
	Vector4& add(Vector4&a,Vector4&b)	{Vector4* v = new Vector4(a.w+b.w, a.x+b.x, a.y+b.y, a.z+b.z); return *v;}
	void sub(Vector4& a) {w=w-a.w; x=x-a.x; y=y-a.y; z=z-a.z;}
	Vector4& sub(Vector4& a,Vector4& b) {Vector4* v = new Vector4(a.w-b.w, a.x-b.x, a.y-b.y, a.z-b.z); return *v;}

	//add/sub vector to current vector returning new vector
	Vector4& operator+(Vector4& );
	float operator[](int);
	Vector4& operator-(Vector4&);

	void scalar(float s) {w=w*s; x=x*s; y=y*s; z=z*s;}
	float dot(Vector4& a) {return w*a.w+x*a.x+y*a.y+z*a.z;}
	float length();
	void normalize() {scalar(1.0/length());}

	void dehomogenize(){scalar(1/z);}

};

#endif