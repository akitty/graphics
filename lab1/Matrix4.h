#ifndef _MATRIX4_H_
#define _MATRIX4_H_

#include "Vector4.h"
#include "Vector3.h"

class Matrix4
{
  protected:
    double m[4][4];   // matrix elements
    
  public:
    Matrix4();        // constructor
    Matrix4(double, double, double, double, double, double, double, double, double, double, double, double, double, double, double, double);
    double* getPointer();  // return pointer to matrix elements
    void identity();  // create identity matrix
    void rotateY(double); // rotation about y 
	void set(int,float);
	float get(int);
	void multiply(Matrix4&);
	void multiply(Vector4&);
	void multiply(Vector3&);
	void row(int,Vector4&);
	void column(int,Vector4&);
	void rotatex(float);
	void rotatey(float);
	void rotatez(float);
	void rotate(Vector3&,float);
	void scale(float,float,float);
	void scale(Vector3&);
	void translate(float,float,float);
	void translate(Vector3&);
	void shear(float, float, float, float, float, float);
};

#endif