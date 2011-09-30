#include "Vector4.h"
#include <math.h>;

float Vector4::get(int i) {
	switch (i){
	case 0: return w;
	case 1: return x;
	case 2: return y;
	case 3: return z;
	default: 
		//should throw exception
		return 0;
	}
}

Vector4& Vector4::operator+(Vector4&a){
	Vector4* b = new Vector4(w+a.w, x+a.x, y+a.y, z+a.z);
	return *b;
}

Vector4& Vector4::operator-(Vector4&a){
	Vector4* b = new Vector4(w-a.w, x-a.x, y-a.y, z-a.z);
	return *b;
}

float Vector4::operator[](int i) {
	switch (i){
	case 0: return w;
	case 1: return x;
	case 2: return y;
	case 3: return z;
	default: 
		//should throw exception
		return 0;
	}
}

float Vector4::length() {
	return (float)sqrt(w*w+x*x+y*y+z*z);
}