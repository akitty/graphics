#include "Vector3.h";
#include "Vector4.h";
#include "Matrix4.h";
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

int main()
{
	cout<<"vector v3 instantiated"<<endl;
	Vector3 *v3 = new Vector3(1,1,1);
	cout<< *v3<<endl;

	Vector3 v2= Vector3(2,2,2);
	cout<<"vector v = 2,2,2"<<endl;
	cout<<"v2+v3=";
	v3->add(v2);
	cout<<*v3<<endl;

	cout<<"set v3 to 5,5,5"<<endl;
	v3->set(5,5,5);
	cout<<"v3:"<<*v3<<endl;

	///cout<<v3->get(0);
	float i = v2[0];
	//float j = v3[0];
	//cout<<"v2[0]:"<<i<<endl;



	system ("pause");
}