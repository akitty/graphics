#include "BasicMath.h"
#include "Matrix4.h"
#include <math.h>

Matrix4::Matrix4()
{
  for (int i=0; i<4; ++i)
  {
    for (int j=0; j<4; ++j)
    {
      m[i][j] = 0;
    }
  }
} 
Matrix4::Matrix4(
  double m00, double m01, double m02, double m03,
  double m10, double m11, double m12, double m13,
  double m20, double m21, double m22, double m23,
  double m30, double m31, double m32, double m33 )
{
  m[0][0] = m00;
  m[0][1] = m01;
  m[0][2] = m02;
  m[0][3] = m03;
  m[1][0] = m10;
  m[1][1] = m11;
  m[1][2] = m12;
  m[1][3] = m13;
  m[2][0] = m20;
  m[2][1] = m21;
  m[2][2] = m22;
  m[2][3] = m23;
  m[3][0] = m30;
  m[3][1] = m31;
  m[3][2] = m32;
  m[3][3] = m33;
}

double* Matrix4::getPointer()
{
  return &m[0][0];
}

void Matrix4::identity()
{
  double ident[4][4]={{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}};
  for (int i=0; i<4; ++i)
  {
    for (int j=0; j<4; ++j)
    {
      m[i][j] = ident[i][j];
    }
  }
}

// angle in degrees
void Matrix4::rotateY(double angle)
{
	double th = BasicMath::radian(angle);
	m[0][0] = cos(th);
	m[0][1] = 0;
	m[0][2] = sin(th);
	m[0][3] = 0;
	m[1][0] = 0;
	m[1][1] = 1;
	m[1][2] = 0;
	m[1][3] = 0;
	m[2][0] = -sin(th);
	m[2][1] = 0;
	m[2][2] = cos(th);
	m[2][3] = 0;
	m[3][0] = 0;
	m[3][1] = 0;
	m[3][2] = 0;
	m[3][3] = 1;
}

void Matrix4::multiply(Matrix4& b)
{
	//store old matrix values
	int nums[]={00,01,02,03,10,11,12,13,20,21,22,23,30,31,32,33};
	Matrix4 a=Matrix4();
	for(int i =0;i<16;i++)
	{
		a.set(nums[i],get(nums[i]));
	}
	m[0][0] = a.m[0][0]*b.m[0][0]+a.m[0][1]*b.m[1][0]+a.m[0][2]*b.m[2][0]+a.m[0][3]*b.m[3][0];
	m[0][1] = a.m[0][0]*b.m[0][1]+a.m[0][1]*b.m[1][1]+a.m[0][2]*b.m[2][1]+a.m[0][3]*b.m[3][1];
	m[0][2] = a.m[0][0]*b.m[0][2]+a.m[0][1]*b.m[1][2]+a.m[0][2]*b.m[2][2]+a.m[0][3]*b.m[3][2];
	m[0][3] = a.m[0][0]*b.m[0][3]+a.m[0][1]*b.m[1][3]+a.m[0][2]*b.m[2][3]+a.m[0][3]*b.m[3][3];
	
	m[1][0] = a.m[1][0]*b.m[0][0]+a.m[1][1]*b.m[1][0]+a.m[1][2]*b.m[2][0]+a.m[1][3]*b.m[3][0];
	m[1][1] = a.m[1][0]*b.m[0][1]+a.m[1][1]*b.m[1][1]+a.m[1][2]*b.m[2][1]+a.m[1][3]*b.m[3][1];
	m[1][2] = a.m[1][0]*b.m[0][2]+a.m[1][1]*b.m[1][2]+a.m[1][2]*b.m[2][2]+a.m[1][3]*b.m[3][2];
	m[1][3] = a.m[1][0]*b.m[0][3]+a.m[1][1]*b.m[1][3]+a.m[1][2]*b.m[2][3]+a.m[1][3]*b.m[3][3];
	
	m[2][0] = a.m[2][0]*b.m[0][0]+a.m[2][1]*b.m[1][0]+a.m[2][2]*b.m[2][0]+a.m[2][3]*b.m[3][0];
	m[2][1] = a.m[2][0]*b.m[0][1]+a.m[2][1]*b.m[1][1]+a.m[2][2]*b.m[2][1]+a.m[2][3]*b.m[3][1];
	m[2][2] = a.m[2][0]*b.m[0][2]+a.m[2][1]*b.m[1][2]+a.m[2][2]*b.m[2][2]+a.m[2][3]*b.m[3][2];
	m[2][3] = a.m[2][0]*b.m[0][3]+a.m[2][1]*b.m[1][3]+a.m[2][2]*b.m[2][3]+a.m[2][3]*b.m[3][3];
	
	m[3][0] = a.m[3][0]*b.m[0][0]+a.m[3][1]*b.m[1][0]+a.m[3][2]*b.m[2][0]+a.m[3][3]*b.m[3][0];
	m[3][1] = a.m[3][0]*b.m[0][1]+a.m[3][1]*b.m[1][1]+a.m[3][2]*b.m[2][1]+a.m[3][3]*b.m[3][1];
	m[3][2] = a.m[3][0]*b.m[0][2]+a.m[3][1]*b.m[1][2]+a.m[3][2]*b.m[2][2]+a.m[3][3]*b.m[3][2];
	m[3][3] = a.m[3][0]*b.m[0][3]+a.m[3][1]*b.m[1][3]+a.m[3][2]*b.m[2][3]+a.m[3][3]*b.m[3][3];



}
/*
*Multiplys a vector4 with this matrix and modifies the vector4
*
**/
void Matrix4::multiply(Vector4& a) {
	//dot each row of the matrix with the column vector a
	Vector4 r=Vector4();
	float result[4];
	for(int i = 0; i <4;i++)
	{
		row(i,r);
		result[i]=r.dot(a);
	}
	a.set(result[0],result[1],result[2],result[3]);
	return;
}

void Matrix4::multiply(Vector3& a) {
	// extend a with 1
	//dot each row with the column vector a
	Vector4 v4 = Vector4(a[0],a[1],a[2],1);
	multiply(v4);
	v4.dehomogenize();
	a.set(v4[0],v4[1],v4[2]);
	return;

}


void Matrix4::row(int i,Vector4&a){
	float row[4];
	for(int j=0;j<4;j++)
	{
		row[j]=this->m[j][i];
	}
	a.set(row[0],row[1],row[2],row[3]);
	return;
}

void Matrix4::column(int j,Vector4&a){
	float col[4];
	for(int i=0;i<4;i++)
	{
		col[i]=this->m[i][j];
	}
	a.set(col[0],col[1],col[2],col[3]);
	return;
}

void Matrix4::rotatex(float t){
	//change t from deg to radians
	t=BasicMath::radian((double)t);
	m[0][0] = 1;
	m[0][1] = 0;
	m[0][2] = 0;
	m[0][3] = 0;
	m[1][0] = 0;
	m[1][1] = cos(t);
	m[1][2] = sin(t);
	m[1][3] = 0;
	m[2][0] = 0;
	m[2][1] = -sin(t);
	m[2][2] = cos(t);
	m[2][3] = 0;
	m[3][0] = 0;
	m[3][1] = 0;
	m[3][2] = 0;
	m[3][3] = 1;


}

void Matrix4::rotatey(float t){
	//change t from deg to radians
	t=BasicMath::radian((double)t);
	m[0][0] = cos(t);
	m[0][1] = 0;
	m[0][2] = -sin(t);
	m[0][3] = 0;
	m[1][0] = 0;
	m[1][1] = 1;
	m[1][2] = 0;
	m[1][3] = 0;
	m[2][0] = sin(t);
	m[2][1] = 0;
	m[2][2] = cos(t);
	m[2][3] = 0;
	m[3][0] = 0;
	m[3][1] = 0;
	m[3][2] = 0;
	m[3][3] = 1;
}
void Matrix4::rotatez(float t){
	//change t from deg to radians
	t=BasicMath::radian((double)t);
	m[0][0] = cos(t);
	m[0][1] = sin(t);
	m[0][2] = 0;
	m[0][3] = 0;
	m[1][0] = -sin(t);
	m[1][1] = cos(t);
	m[1][2] = 0;
	m[1][3] = 0;
	m[2][0] = 0;
	m[2][1] = 0;
	m[2][2] = 1;
	m[2][3] = 0;
	m[3][0] = 0;
	m[3][1] = 0;
	m[3][2] = 0;
	m[3][3] = 1;
}

void Matrix4::rotate(Vector3& v, float t){
	t=BasicMath::radian((double)t);
	//normalize v
	v.normalize();
	float c=cos(t);
	float s=sin(t);
	m[0][0] = v[0]*v[0]+c*(1- v[0]*v[0]);
	m[0][1] = v[0]*v[1]*(1-c)+v[2]*s;
	m[0][2] = v[0]*v[2]*(1-c)-v[1]*s;
	m[0][3] = 0;
	m[1][0] = v[0]*v[1]*(1-c)-v[2]*s;
	m[1][1] = v[1]*v[1]+c*(1- v[1]*v[1]);
	m[1][2] = v[1]*v[2]*(1-c)+v[0]*s;
	m[1][3] = 0;
	m[2][0] = v[0]*v[2]*(1-c)+v[1]*s;
	m[2][1] = v[2]*v[3]*(1-c)-v[0]*s;
	m[2][2] = v[2]*v[2]+c*(1- v[2]*v[2]);
	m[2][3] = 0;
	m[3][0] = 0;
	m[3][1] = 0;
	m[3][2] = 0;
	m[3][3] = 1;
}

void Matrix4::scale(float x, float y, float z){
	m[0][0] = x;
	m[0][1] = 0;
	m[0][2] = 0;
	m[0][3] = 0;
	m[1][0] = 0;
	m[1][1] = y;
	m[1][2] = 0;
	m[1][3] = 0;
	m[2][0] = 0;
	m[2][1] = 0;
	m[2][2] = z;
	m[2][3] = 0;
	m[3][0] = 0;
	m[3][1] = 0;
	m[3][2] = 0;
	m[3][3] = 1;


}

void Matrix4::scale(Vector3&a){
	scale(a[0],a[1],a[2]);
	return;
}

void Matrix4::translate(float x, float y, float z){
	m[0][0] = 1;
	m[0][1] = 0;
	m[0][2] = 0;
	m[0][3] = 0;
	m[1][0] = 0;
	m[1][1] = 1;
	m[1][2] = 0;
	m[1][3] = 0;
	m[2][0] = 0;
	m[2][1] = 0;
	m[2][2] = 1;
	m[2][3] = 0;
	m[3][0] = x;
	m[3][1] = y;
	m[3][2] = z;
	m[3][3] = 1;

}

void Matrix4::shear(float a, float b, float w, float x, float y, float z){
  m[0][0] = 1;
  m[0][1] = a;
  m[0][2] = b;
  m[0][3] = 0;

  m[1][0] = w;
  m[1][1] = 1;
  m[1][2] = x;
  m[1][3] = 0;

  m[2][0] = y;
  m[2][1] = z;
  m[2][2] = 1;
  m[2][3] = 0;

  m[3][0] = 0;
  m[3][1] = 0;
  m[3][2] = 0;
  m[3][3] = 1;
}

void Matrix4::translate(Vector3&a){
	translate(a[0],a[1],a[2]);
}

void Matrix4::set(int i,float a){
	int ones=i%10;
	int tens=i/10;
	m[tens][ones]=a;
}

float Matrix4::get(int i){
	int ones=i%10;
	int tens=i/10;
	return m[tens][ones];
}

