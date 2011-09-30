
#include "Vector3.h"
//#include <iostream>
//using namespace std;




float Vector3::get(int a) {
	
	switch (a) {
	case 0:
		return x;
		break;
	case 1:
		return y;
		break;
	case 2:
		return z;
		break;
	default:
		//should throw exception
		return 0;

	}
	
}

Vector3& Vector3::operator+(Vector3&a){
	Vector3* b = new Vector3(x+a.x,y+a.y,z+a.z);
	return *b;
}


Vector3& Vector3::operator-(Vector3&a){
	Vector3* b = new Vector3(x-a.x,y-a.y,z-a.z);
	return *b;
}

float Vector3::operator[](int i) {
	switch (i){
	case 0: return x;
	case 1: return y;
	case 2: return z;
	default: 
		//should throw exception
		return 0;
	}
}

void Vector3::cross(Vector3& a){
	x= y*a.z-z*a.y;
	y= z*a.x-x*a.z;
	z= x*a.y-y*a.x;
}

float Vector3::length() {
	return (float)sqrt(x*x+y*y+z*z);
}

