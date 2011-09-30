#ifndef _BASICMATH_H_
#define _BASICMATH_H_

#include <math.h>

class BasicMath
{
  public:
	  static const double PI;

	  static double radian(double a) { return a * PI/180.f; };
};

const double BasicMath::PI = acos(-1.0);

#endif